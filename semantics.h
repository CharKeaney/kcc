
#ifndef SEMANTICS_H
#define SEMANTICS_H 1

/* Scope */

enum class Scope {
	UNDEFINED = 0,
	BLOCK,
	FILE,
	FUNCTION,
	FUNCTION_PROTOTYPE,
};

static const char* scope_string_repr[]{
	"UNDEFINED",
	"BLOCK",
	"FILE",
	"FUNCTION",
	"FUNCTION_PROTOTYPE"
};

enum class IdentifierClassifier {
	UNDEFINED,
	OBJECT,
	FUNCTION,
	MEMBER,
	TYPEDEF_NAME,
	LABEL_NAME
};

static const char* identifier_classifier_string_repr[]{
	"UNDEFINED",
	"OBJECT",
	"FUNCTION",
	"MEMBER",
	"TYPEDEF_NAME",
	"LABEL_NAME"
};

enum class StorageClassSpecifier {
	UNDEFINED,
	UNSPECIFIED,
	TYPEDEF,
	EXTERN,
	STATIC,
	AUTO,
	REGISTER
};

enum class TypeQualifiers {
	UNQUALIFIED				= 0x0,
	CONST					= 0x1,
	VOLATILE				= 0X2,	
	CONST_VOLATILE			= CONST + VOLATILE,
	RESTRICT				= 0X4,
	CONST_RESTRICT			= CONST + RESTRICT,
	VOLATILE_RESTRICT		= VOLATILE + RESTRICT,	
	CONST_VOLATILE_RESTRICT = CONST + VOLATILE + RESTRICT,
	UNDEFINED               = 0x8,
};

enum class FunctionSpecifiers {
	UNDEFINED,
	UNSPECIFIED,
	INLINE
};

enum class TypeCategory {
	UNDEFINED = 0,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SIGNED_SHORT,
	UNSIGNED_SHORT,
	SIGNED_INT,
	UNSIGNED_INT,
	SIGNED_LONG,
	UNSIGNED_LONG,
	SIGNED_LONG_LONG,
	UNSIGNED_LONG_LONG,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	BOOL,
	COMPLEX,
	FUNCTION,
	INCOMPLETE
};

/* Forward declaration of all types. */

struct BasicType;
struct ArrayType;
struct MemberObject;
struct PointerType;
struct StructureType;
struct UnionType;
struct ObjectType;
struct Type;

enum class BasicTypeName {
	UNDEFINED = 0,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SIGNED_SHORT,
	UNSIGNED_SHORT,
	SIGNED_INT,
	UNSIGNED_INT,
	SIGNED_LONG,
	UNSIGNED_LONG,
	SIGNED_LONG_LONG,
	UNSIGNED_LONG_LONG,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	BOOL,
	COMPLEX,
	ARRAY,
	STRUCTURE,
	UNION,
	POINTER
};

struct BasicType {
	BasicTypeName  name;
	TypeQualifiers qualifier;
};

struct ArrayType {
	Type*          element_type;
	int            number_of_elements;
	TypeQualifiers qualifier;
};

struct MemberObject {
	const char*   name;
	ObjectType*   object_type;
	MemberObject* next_member;
};

struct PointerType {
	const Type*    referenced_type;
	TypeQualifiers qualifier;
};

struct StructureType {
	const MemberObject* member_object_list;
	TypeQualifiers      qualifier;
};

struct UnionType {
	const MemberObject* member_object_list;
	TypeQualifiers      qualifier;
};

struct IncompleteType {
	// TODO;
};

enum class ObjectTypeName {
	UNDEFINED = 0,
	BASIC_TYPE,
	ARRAY,
	STRUCTURE,
	UNION,
	POINTER
};

struct ObjectType {
	ObjectTypeName object_type_name;
	union {
		BasicType      basic_type;
		ArrayType      array_type;
		StructureType  structure_type;
		UnionType      union_type;
		PointerType    pointer_type;
	};
};

struct Parameter {
	const Type*      parameter_type;
	const char*      parameter_name;
	const Parameter* next_parameter;
};

struct FunctionType {
	const Type*      return_type;
	int              number_of_parameters;
	const Parameter* parameter_list;
};

enum class TypeClassifier {
	UNDEFINED,
	OBJECT,
	FUNCTION,
	INCOMPLETE
};

struct Type {
	TypeClassifier classifier;
	union {
		ObjectType     object_type;		/* OBJECT		*/
		FunctionType   function_type;	/* FUNCTION		*/
		IncompleteType incomplete_type; /* INCOMPLETE   */
	};
};

/* Construct types. */

static inline Type* construct_basic_type(
	BasicTypeName  const& basic_type_name,
	TypeQualifiers const& qualifier = TypeQualifiers::UNQUALIFIED)
{
	Type* output       = new Type();
	output->classifier = TypeClassifier::OBJECT;

	ObjectType* const object_type = &output->object_type;
	object_type->object_type_name  = ObjectTypeName::BASIC_TYPE;

	BasicType* const basic_type = &object_type->basic_type;
	basic_type->name      = basic_type_name;
	basic_type->qualifier = qualifier;

	return output;
}

static inline Type* construct_void_type()
{
	Type* output = new Type();
	output->classifier = TypeClassifier::INCOMPLETE;
	// TODO; stub.
	return output;
}

static inline Type* construct_derived_array(
	Type*          const& basic_type_name,
	int            const& number_of_elements,
	TypeQualifiers const& type_qualifier)
{
	Type* output       = new Type();
	output->classifier = TypeClassifier::OBJECT;

	ObjectType* const object_type = &output->object_type;;
	object_type->object_type_name = ObjectTypeName::ARRAY;

	ArrayType* const array_type    = &object_type->array_type;
	array_type->element_type       = basic_type_name;
	array_type->number_of_elements = number_of_elements;
	array_type->qualifier          = type_qualifier;

	return output;
}

inline Type* construct_derived_structure(
	Type*          const& basic_type_name,
	int            const& number_of_elements,
	TypeQualifiers const& qualifier = TypeQualifiers::UNQUALIFIED)
{
	Type* output = new Type(); 
	output->classifier = TypeClassifier::OBJECT;

	ObjectType* object_type = &output->object_type;;
	object_type->object_type_name = ObjectTypeName::STRUCTURE;

	StructureType* structure_type = &object_type->structure_type;
	structure_type->qualifier = qualifier;

	return output;
}

inline Type* construct_derived_union(
	Type*          const& basic_type_name,
	int            const& number_of_elements,
	TypeQualifiers const& type_qualifier = TypeQualifiers::UNQUALIFIED)
{
	Type* output = new Type(); 
	output->classifier = TypeClassifier::OBJECT;

	ObjectType* object_type = &output->object_type;;
	object_type->object_type_name = ObjectTypeName::UNION;
	return output;
}

static inline Type* construct_function_type(
	const Type*      const& return_type,
	int              const& number_of_parameters,
	const Parameter* const& parameter_list)
{
	Type* output       = new Type();
	output->classifier = TypeClassifier::FUNCTION;

	FunctionType* const function_type   = &output->function_type;
	function_type->number_of_parameters = number_of_parameters;
	function_type->parameter_list       = parameter_list;
	function_type->return_type          = return_type;

	return output;
}

static inline Type* construct_derived_pointer_type(
	const Type*     const& referenced_type,
	TypeQualifiers  const& qualifier)
{
	Type* output       = new Type();
	output->classifier = TypeClassifier::OBJECT;

	ObjectType* const object_type = &output->object_type;;
	object_type->object_type_name = ObjectTypeName::POINTER;

	PointerType* const pointer_type = &object_type->pointer_type;
	pointer_type->referenced_type   = referenced_type;
	pointer_type->qualifier         = qualifier;

	return output;
}

/* Print types. */

static const char* type_qualifier_string_repr[] {
	"",
	"const",
	"volatile",
	"const volatile",
	"restrict",
	"const restrict",
	"volatile restrict",
	"const volatile restrict",
	"undefined type qualifier"
};

#define print_type_qualifier(q)							\
			cout << type_qualifier_string_repr[(int) q]

static const char* basic_type_string_repr[]{
	"undefined type",
	"signed char",
	"unsigned char",
	"signed short",
	"unsigned short",
	"signed int",
	"unsigned int",
	"signed long",
	"unsigned long",
	"signed long long",
	"unsigned long long",
	"float",
	"double",
	"long double",
	"bool",
	"_complex"
};

/* Equivalency check forward declarations */

static inline bool basic_types_are_equivalent(
	const BasicType* const& a,
	const BasicType* const& b);

static inline bool member_object_types_are_equivalent(
	const MemberObject* const& a,
	const MemberObject* const& b);

static inline bool structure_types_are_equivalent(
	const StructureType* const& a,
	const StructureType* const& b);

static inline bool union_types_are_equivalent(
	const UnionType* const& a,
	const UnionType* const& b);

static inline bool pointer_types_are_equivalent(
	const PointerType* const& a,
	const PointerType* const& b);


static inline bool object_types_are_equivalent(
	const ObjectType* const& a,
	const ObjectType* const& b);

/* Constructor forward declarations */

static inline Type* construct_basic_type(
	BasicTypeName  const& basic_type_name,
	TypeQualifiers const& qualifier);

static inline Type* construct_derived_structure(
	const Type*    const& basic_type_name,
	int            const& number_of_elements,
	TypeQualifiers const& qualifier);

static inline Type* construct_derived_union(
	const Type*     const& basic_type_name,
	int            const& number_of_elements,
	TypeQualifiers const& type_qualifier);

static inline Type* construct_function_type(
	const Type*      const& return_type,
	int              const& number_of_parameters,
	const Parameter* const& parameter_list,
	TypeQualifiers   const& qualifier);

static inline Type* construct_derived_pointer_type(
	const Type*          const& referenced_type,
	const TypeQualifiers const& qualifier);

static inline void print_union_type(
	const UnionType* const& t);

static inline void print_basic_type(
	const BasicType* const& t);

static inline void print_parameter(
	const Parameter* const& t);

static inline void print_function_type(
	const FunctionType* const& t);

static inline void print_pointer_type(
	const PointerType* const& t);

static inline void print_object_type(
	const ObjectType* const& t);

static inline void print_incomplete_type(
	const IncompleteType* const& t);

static inline void print_array_type(
	const ArrayType* const& t);

static inline void print_member_object(
	const MemberObject* const& t);

static inline void print_structure_type(
	const StructureType* const& t);

static inline void print_type(
	const Type* const& t);

static inline const int get_sizeof_basic_type(
	const BasicType* const& type);

static inline const int get_sizeof_structure_type(
	const StructureType* const& type);

static inline const int get_sizeof_union_type(
	const UnionType* const& type);

static inline const int get_sizeof_incomplete_type(
	const IncompleteType* const& type);

static inline const int get_sizeof_array_type(
	const ArrayType* const& type);

static inline const int get_sizeof_object_type(
	const ObjectType* const& type);

static inline const int get_sizeof_type(
	const Type* const& type);

static inline void duplicate_type(
	const Type*  const& input,
	const Type*       & output);

static inline bool types_are_equivalent(
	const Type* const& a,
	const Type* const& b);

static inline bool is_object_type(
	const Type* const& type);

static inline bool is_function_type(
	const Type* const& type);

static inline bool is_incomplete_type(
	const Type* const& type);

static inline bool is_integer_type(
	const Type* const& type);

static inline bool is_real_floating_type(
	const Type* const& type);

static inline bool is_arithmetic_type(
	const Type* const& type);

static inline bool is_pointer_type(
	const Type* const& type);

static inline bool is_scalar_type(
	const Type* const& type);

static inline bool is_declared_as_register(
	const Type* const& type);

/* Function Implementations */

static inline bool basic_types_are_equivalent(
	const BasicType* const& a,
	const BasicType* const& b)
{
	const bool are_equivalent
		= (a->name == b->name)
		  && (a->qualifier == b->qualifier);
	return are_equivalent;
}

static inline bool array_types_are_equivalent(
	const ArrayType* const& a,
	const ArrayType* const& b)
{
	const bool are_equivalent
		= a->qualifier != b->qualifier
		  && a->number_of_elements != b->number_of_elements
	      && types_are_equivalent(a->element_type, b->element_type);
	return are_equivalent;
}

static inline bool member_object_types_are_equivalent(
	const MemberObject* const& a,
	const MemberObject* const& b)
{
	bool are_equivalent = true;

	const MemberObject* x = a;
	const MemberObject* y = b;
	do {
		if (((x != NULL) == (y != NULL))
		    || object_types_are_equivalent(
			       x->object_type, 
				   y->object_type)) {
			x = x->next_member;
			y = y->next_member;

		} else {
			are_equivalent = false;
			break;
		}
	} while (x || y);

	return are_equivalent;
}

static inline bool structure_types_are_equivalent(
	const StructureType* const& a,
	const StructureType* const& b)
{
	const bool are_equivalent
		= a->qualifier == b->qualifier
		  && member_object_types_are_equivalent(
			     a->member_object_list,
			     b->member_object_list);
	return are_equivalent;
}

static inline bool union_types_are_equivalent(
	const UnionType* const& a,
	const UnionType* const& b)
{
	const bool are_equivalent 
		=  a->qualifier == b->qualifier
	       && member_object_types_are_equivalent(
			   a->member_object_list,
			   b->member_object_list);
	return are_equivalent;
}

static inline bool pointer_types_are_equivalent(
	const PointerType* const& a,
	const PointerType* const& b)
{
	const bool are_equivalent
		= a->qualifier == b->qualifier
		  && types_are_equivalent(
		      a->referenced_type,
			  b->referenced_type);
	return are_equivalent;
}

static inline bool object_types_are_equivalent(
	const ObjectType* const& a,
	const ObjectType* const& b)
{
	bool are_equivalent
		= a->object_type_name 
		  == b->object_type_name;
	if (are_equivalent) {

		switch (a->object_type_name) {

			case ObjectTypeName::UNDEFINED:
				cout << "UNDEFINED";
				break;

			case ObjectTypeName::BASIC_TYPE:
				are_equivalent 
					= basic_types_are_equivalent(
					      &a->basic_type, 
					      &b->basic_type);
				break;

			case ObjectTypeName::ARRAY:
				are_equivalent 
					= array_types_are_equivalent(
					      &a->array_type, 
					      &b->array_type);
				break;

			case ObjectTypeName::STRUCTURE:
				are_equivalent 
					= structure_types_are_equivalent(
					      &a->structure_type, 
					      &b->structure_type);
				break;

			case ObjectTypeName::UNION:
				are_equivalent 
					= union_types_are_equivalent(
					      &a->union_type, 
					      &b->union_type);
				break;

			case ObjectTypeName::POINTER:
				are_equivalent 
					= pointer_types_are_equivalent(
					      &a->pointer_type, 
					      &b->pointer_type);
				break;

			default:
				break;
		}
	}
	return are_equivalent;
}

static inline void print_union_type(
	const UnionType* const& t)
{
	print_type_qualifier(t->qualifier);
	cout << "UNION "
		 << "{ ";
	print_member_object(t->member_object_list);
	cout << " }";
}

static inline void print_basic_type(
	const BasicType* const& t)
{
	print_type_qualifier(t->qualifier);
	cout << basic_type_string_repr[(int)t->name];
}

static inline void print_parameter(
	const Parameter* const& t) 
{
	print_type(t->parameter_type);
	cout << " ";
	// cout << t->parameter_name;
	if (t->next_parameter != NULL) {
		cout << ", ";
		print_parameter(t->next_parameter);
	}
}

static inline void print_function_type(
	const FunctionType* const& t)
{
	print_type(t->return_type);
	cout << " ( ";
	print_parameter(t->parameter_list);
	cout << " )";
}

static inline void print_pointer_type(
	const PointerType* const& t)
{
	print_type_qualifier(t->qualifier);
	cout << " ";
	print_type(t->referenced_type);
	cout << "*";

}

static inline void print_object_type(
	const ObjectType* const& t)
{
	switch (t->object_type_name) {

		case ObjectTypeName::UNDEFINED:
			cout << "UNDEFINED";
			break;

		case ObjectTypeName::BASIC_TYPE:
			print_basic_type(&t->basic_type);
			break;

		case ObjectTypeName::ARRAY:
			print_array_type(&t->array_type);
			break;

		case ObjectTypeName::STRUCTURE:
			print_structure_type(&t->structure_type);
			break;

		case ObjectTypeName::UNION:
			print_union_type(&t->union_type);
			break;

		case ObjectTypeName::POINTER:
			print_pointer_type(&t->pointer_type);
			break;

		default:
			break;

	}
}

static inline void print_incomplete_type(
	const IncompleteType* const& t)
{
	// TODO;
}

static inline void print_array_type(
	const ArrayType* const& t)
{
	cout << type_qualifier_string_repr[(int)t->qualifier]
		 << "ARRAY OF ";
	print_type(t->element_type);
	cout << " x "
		 << t->number_of_elements;
}

static inline void print_member_object(
	const MemberObject* const& t)
{
	print_object_type(t->object_type);
	cout << " " 
		 << t->name;
	if (t->next_member) {
		cout << ", ";
		print_member_object(t->next_member);
	}
}

static inline void print_structure_type(
	const StructureType* const& t)
{
	print_type_qualifier(t->qualifier);
	cout << "struct "
		 << "{ ";
	print_member_object(t->member_object_list);
	cout << " }";
}

static inline void print_type(
	const Type* const& t)
{
	switch (t->classifier) {

		case TypeClassifier::UNDEFINED:
			cout << "undefined type";
			break;

		case TypeClassifier::OBJECT:
			print_object_type(&t->object_type);
			break;

		case TypeClassifier::FUNCTION:
			print_function_type(&t->function_type);
			break;

		case TypeClassifier::INCOMPLETE:
			print_incomplete_type(&t->incomplete_type);
			break;

		default:
			break;

	}
}

static inline const int get_sizeof_basic_type(
	const BasicType* const& type)
{
	 static const int sizeof_basic_type_map[] = {
		0,							//UNDEFINED,
		sizeof(signed char),		//SIGNED_CHAR,
		sizeof(unsigned char),		//UNSIGNED_CHAR,
		sizeof(signed short),		//SIGNED_SHORT,
		sizeof(unsigned short),		//UNSIGNED_SHORT,
		sizeof(signed int),			//SIGNED_INT,
		sizeof(unsigned int),		//UNSIGNED_INT,
		sizeof(signed long),		//SIGNED_LONG,
		sizeof(unsigned long),		//UNSIGNED_LONG,
		sizeof(signed long long),	//SIGNED_LONG_LONG,
		sizeof(unsigned long long), //UNSIGNED_LONG_LONG,
		sizeof(float),				//FLOAT,
		sizeof(double),				//DOUBLE,
		sizeof(long double),		//LONG_DOUBLE,
		sizeof(bool),				//BOOL,
		sizeof(_complex)			//COMPLEX,
	};
	const int h = (int) type->name;
	const int sizeof_basic_type = sizeof_basic_type_map[h];
	return sizeof_basic_type;
}

static inline const int get_sizeof_structure_type(
	const StructureType* const& type)
{
	int size_required = 0;
	const MemberObject* current_member 
		= type->member_object_list;
	while (current_member != NULL) {
		size_required += get_sizeof_object_type(current_member->object_type);
		current_member = current_member->next_member;
	}
	return size_required;
}

static inline const int get_sizeof_union_type(
	const UnionType* const& type)
{
	int size_required = 0;
	const MemberObject* current_member
		= type->member_object_list;
	while (current_member != NULL) {
		const int sizeof_object
			= get_sizeof_object_type(current_member->object_type);
		size_required = (size_required < sizeof_object) 
			            ? sizeof_object 
			            : size_required;
		current_member = current_member->next_member;
	}
	return size_required;
}

static inline const int get_sizeof_incomplete_type(
	const IncompleteType* const& type)
{
	int sizeof_type = 0;
	// TODO; stub.
	return sizeof_type;
}

static inline const int get_sizeof_array_type(
	const ArrayType* const& type)
{
	const int sizeof_array_type =
		get_sizeof_type(type->element_type) 
		* type->number_of_elements;
	return sizeof_array_type;
}

static inline const int get_sizeof_object_type(
	const ObjectType* const& type)
{
	int sizeof_type = 0;
	switch (type->object_type_name) {

		case ObjectTypeName::ARRAY:
			sizeof_type = get_sizeof_array_type(&type->array_type);
			break;

		case ObjectTypeName::BASIC_TYPE:
			sizeof_type = get_sizeof_basic_type(&type->basic_type);
			break;

		case ObjectTypeName::POINTER:
			sizeof_type = sizeof(void*);
			break;

		case ObjectTypeName::STRUCTURE:
			sizeof_type = get_sizeof_structure_type(&type->structure_type);
			break;

		case ObjectTypeName::UNDEFINED:
			break;

		case ObjectTypeName::UNION:
			sizeof_type = get_sizeof_union_type(&type->union_type);
			break;

		default:
			break;

	}
	return sizeof_type;
}

static inline const int get_sizeof_type(
	const Type* const& type)
{
	int sizeof_type = 0;
	switch (type->classifier) {
		
		case TypeClassifier::OBJECT:
			sizeof_type = get_sizeof_object_type(&type->object_type);
			break;
		
		case TypeClassifier::FUNCTION:
			sizeof_type = 0;
			break;
		
		case TypeClassifier::INCOMPLETE:
			sizeof_type = get_sizeof_incomplete_type(&type->incomplete_type);
			break;

		default:
			break;
	}
	return sizeof_type;
}

/* 
	Assumes type is a pointer type.
*/
static inline const Type* dereference_type(
	const Type* const& type)
{
	const Type* const derefed_type 
		= type->object_type
		       .pointer_type
		       .referenced_type;
	return derefed_type;
}

static inline const Type* get_function_return_type(
	const Type* const& type)
{
	const Type* const return_type
		= type->function_type.return_type;
	return return_type;
}

static inline const Type* get_element_type(
	const Type* const& type)
{
	const Type* const return_type
		= type->object_type.array_type.element_type;
	return return_type;
}

static inline void duplicate_type(
	const Type* const& input,
	const Type*      &  output)
{
	output = input;
}

static inline bool parameters_are_equivalent(
	const Parameter* const& a,
	const Parameter* const& b)
{
	const bool are_equivalent
		= types_are_equivalent(a->parameter_type, b->parameter_type)
		  && parameters_are_equivalent(a->next_parameter, b->next_parameter);
	return are_equivalent;
}

static inline bool function_types_are_equivalent(
	const FunctionType* const& a,
	const FunctionType* const& b)
{
	const bool are_equivalent
		= (a->number_of_parameters == b->number_of_parameters)
		  && types_are_equivalent(a->return_type, b->return_type)
		  && parameters_are_equivalent(a->parameter_list, b->parameter_list);
	return are_equivalent;
}

static inline bool incomplete_types_are_equivalent(
	const IncompleteType* const& a,
	const IncompleteType* const& b)
{
	const bool are_equivalent
		= false;
	// TODO; stub.
	return are_equivalent;
}

static inline bool types_are_equivalent(
	const Type* const& a,
	const Type* const& b)
{
	bool are_equivalent = true;
	if (a->classifier != b->classifier) {
		are_equivalent = false;

	} else {

		switch (a->classifier) {

			case TypeClassifier::FUNCTION:
				are_equivalent 
					= function_types_are_equivalent(
						&a->function_type,
						&b->function_type);
				break;

			case TypeClassifier::INCOMPLETE:
				are_equivalent
					= incomplete_types_are_equivalent(
						&a->incomplete_type,
						&b->incomplete_type);
				break;

			case TypeClassifier::OBJECT:
				are_equivalent 
					= object_types_are_equivalent(
						&a->object_type, 
						&b->object_type);
				break; 

			case TypeClassifier::UNDEFINED:
				break;

			default:
				break;

		}
	}
	return are_equivalent;
}

static inline bool is_object_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::OBJECT;
	return retval;
}

static inline bool is_function_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::FUNCTION;
	return retval;
}

static inline bool is_array_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier  == TypeClassifier::OBJECT
		  && type->object_type.object_type_name == ObjectTypeName::ARRAY;
	return retval;
}

static inline bool is_struct_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::OBJECT
		&& type->object_type.object_type_name == ObjectTypeName::STRUCTURE;
	return retval;
}

static inline bool is_union_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::OBJECT
		&& type->object_type.object_type_name == ObjectTypeName::UNION;
	return retval;
}

static inline bool is_incomplete_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::INCOMPLETE;
	return retval;

}

static inline bool is_void_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::INCOMPLETE;
	//TODO; stub;
	return retval;
}

static inline bool is_signed_integer_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::OBJECT
		  && type->object_type.object_type_name == ObjectTypeName::BASIC_TYPE
		  && (type->object_type.basic_type.name    == BasicTypeName::SIGNED_CHAR
		  	  || type->object_type.basic_type.name == BasicTypeName::SIGNED_SHORT
			  || type->object_type.basic_type.name == BasicTypeName::SIGNED_INT
			  || type->object_type.basic_type.name == BasicTypeName::SIGNED_LONG
			  || type->object_type.basic_type.name == BasicTypeName::SIGNED_LONG_LONG);
	return retval;
}

static inline bool is_unsigned_integer_type(
	const Type* const& type)
{
	const bool retval
		= type->classifier == TypeClassifier::OBJECT
		&& type->object_type.object_type_name == ObjectTypeName::BASIC_TYPE
		&& (type->object_type.basic_type.name    == BasicTypeName::UNSIGNED_CHAR
			|| type->object_type.basic_type.name == BasicTypeName::UNSIGNED_SHORT
			|| type->object_type.basic_type.name == BasicTypeName::UNSIGNED_INT
			|| type->object_type.basic_type.name == BasicTypeName::UNSIGNED_LONG
			|| type->object_type.basic_type.name == BasicTypeName::UNSIGNED_LONG_LONG);
	return retval;
}


static inline bool is_integer_type(
	const Type* const& type)
{
	const bool retval
		= is_signed_integer_type(type)
		  || is_unsigned_integer_type(type);
	return retval;
}

static inline bool is_real_floating_type(
	const Type* const& type)
{
	const bool retval 
		= type->classifier == TypeClassifier::OBJECT
		  && type->object_type.object_type_name == ObjectTypeName::BASIC_TYPE
		  && (type->object_type.basic_type.name == BasicTypeName::FLOAT
		      || type->object_type.basic_type.name == BasicTypeName::DOUBLE
		      || type->object_type.basic_type.name == BasicTypeName::LONG_DOUBLE);
	return retval;
}

static inline bool is_arithmetic_type(
	const Type* const& type)
{
	const bool retval
		= is_integer_type(type)
		  || is_real_floating_type(type);
	return retval;
}

static inline bool is_pointer_type(
	const Type* const& type)
{
	const bool retval 
		= type->classifier == TypeClassifier::OBJECT
		  && type->object_type.object_type_name == ObjectTypeName::POINTER;
	return retval;
}

static inline bool  is_scalar_type(
	const Type* const& type)
{
	const bool retval
		= is_arithmetic_type(type)
		  || is_pointer_type(type);
	return retval;
}

static inline bool is_declared_as_register(
	const Type* const& type)
{
	return false;
}

static inline bool is_lvalue_type(
	const Type* const& type) 
{
	const bool retval 
		= is_object_type(type)
		  || (is_incomplete_type(type) 
			  && !is_void_type(type));
	return retval;
}

static inline bool is_const_qualified_type(
	const Type* const& type)
{
	const bool retval = false;
	// TODO; stub.
	return retval;
}

static inline bool is_container_for_const_qualified_type(
	const Type* const& type)
{
	const bool retval = false;
	// TODO; STUB.
	return retval;
}

static inline bool is_parenthesized_incomplete_type(
	const Type* const& type)
{
	const bool retval = false;
	// TODO; STUB.
	return retval;
}

static inline bool is_modifiable_lvalue_type(
	const Type* const& type) {
	const bool retval
		= is_lvalue_type(type)
		  && !is_array_type(type)
		  && !is_incomplete_type(type)
		  && !is_const_qualified_type(type)
		  && (!(is_struct_type(type)
			    || is_union_type(type))
			  || is_container_for_const_qualified_type(type));
	return retval;
}

#endif