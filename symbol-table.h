#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <string>

#include <iostream>
#include <iomanip>

#define DEBUG_TYPE_SHOW_NULL_DUPLICATION 0

using namespace std;

static int sizeof_map[] = {
	0,
	sizeof(char),
	sizeof(signed char),
	sizeof(unsigned char),
	sizeof(short),
	sizeof(unsigned short),
	sizeof(signed int),
	sizeof(unsigned int),
	sizeof(signed long),
	sizeof(unsigned long),
	sizeof(signed long long),
	sizeof(unsigned long long),
	sizeof(float),
	sizeof(double),
	sizeof(long double),
	sizeof(bool),
	sizeof(_complex)
};
#define size_of(i) size_of[i]

enum class BasicType {
	UNDEFINED = 0,
	VOID,
	CHAR,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SHORT,
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
};

static const char* basic_type_string_repr[] {
	"UNDEFINED",
	"VOID",
	"CHAR",
	"SIGNED_CHAR",
	"UNSIGNED_CHAR",
	"SHORT",
	"SIGNED_SHORT",
	"UNSIGNED_SHORT",
	"SIGNED_INT",
	"UNSIGNED_INT",
	"SIGNED_LONG",
	"UNSIGNED_LONG",
	"SIGNED_LONG_LONG",
	"UNSIGNED_LONG_LONG",
	"FLOAT",
	"DOUBLE",
	"LONG_DOUBLE",
	"BOOL",
	"COMPLEX",
};

enum class DerivedType {
	UNDEFINED = 0,
	ARRAY,
	STRUCTURE,
	UNION,
	FUNCTION,
	POINTER,
	PARAMETER_LIST,
};

static const char* derived_type_string_repr[] {
	"UNDEFINED",
	"ARRAY-",
	"STRUCTURE",
	"UNION",
	"FUNCTION",
	"POINTER",
	"PARAMETER_LIST"
};

enum class Scope {
	UNDEFINED = 0,
	LOCAL,
	GLOBAL,
	PARAM
};

static const char* scope_string_repr[]{
	"UNDEFINED",
	"LOCAL",
	"GLOBAL",
	"PARAM"
};

enum class DerivedOrBasic {
	DERIVED,
	BASIC
};

struct Type {
	DerivedOrBasic derived_or_basic;
	union {
		struct {
			DerivedType derived_type_name; 
			Type* base_type_1;
			Type* base_type_2;
		};	
		BasicType basic;
	};
};

static inline void print_type(
	Type* const& t) 
{
	if (t == NULL) {
		cout << "";

	} else if (t->derived_or_basic == DerivedOrBasic::BASIC) {
		cout << basic_type_string_repr[(int)t->basic];

	} else {
		switch (t->derived_type_name) {

			case DerivedType::ARRAY:
				cout << derived_type_string_repr[(int)t->derived_type_name]
					 << " OF ";
				print_type(t->base_type_1);
				break;

			case DerivedType::STRUCTURE:
				// TODO;
				break;

			case DerivedType::UNION:
				// TODO;
				break;

			case DerivedType::FUNCTION:
				cout << derived_type_string_repr[(int)t->derived_type_name];
				cout << " ";
				print_type(t->base_type_1);
				print_type(t->base_type_2);
				break;

			case DerivedType::POINTER:
				cout << derived_type_string_repr[(int)t->derived_type_name]
					 << " TO ";
				print_type(t->base_type_1);
				break;

			case DerivedType::PARAMETER_LIST:
			{
				cout << "( ";
				Type* current_param = t;
				print_type(current_param->base_type_1);
				while (current_param->base_type_2 != NULL) {					
					current_param = current_param->base_type_2;
					cout << ", ";
					print_type(current_param->base_type_1);
				}
				cout << " )";
				break;
			}

			default:
				break;

		}
	}
}

inline void duplicate_type(
	Type* const& input, 
	Type*& output)
{
	if (input == NULL) {
		if (DEBUG_TYPE_SHOW_NULL_DUPLICATION) {
			/* Not fatal, but a sign something went wrong with the compiler itself. */
			cout << "err.";
		}
	} else {
		output = new Type();
		output->derived_or_basic = input->derived_or_basic;
		if (output->derived_or_basic == DerivedOrBasic::DERIVED) {
			output->derived_type_name = input->derived_type_name;
			duplicate_type(input->base_type_1, output->base_type_1);
			duplicate_type(input->base_type_2, output->base_type_2);
		}
		else {
			output->basic = input->basic;
		}
	}
}

static inline bool types_are_equivalent(
	Type* const& a,
	Type* const& b) 
{	
	return a->derived_or_basic == b->derived_or_basic
		   && ((a->derived_or_basic == DerivedOrBasic::BASIC
				&& a->basic == b->basic)
			   || ((a->derived_or_basic == DerivedOrBasic::DERIVED
				    && a->derived_type_name == b->derived_type_name
					&& types_are_equivalent(a->base_type_1, b->base_type_1))
					&& types_are_equivalent(a->base_type_2, b->base_type_2)));
}


struct SymbolTableEntry {
	/* Key data. */
	const char* symbol;
	SymbolTableEntry* next_entry;
	/* General Attributes. */
	bool is_typedef;
	bool is_literal;
	int value;
	int base_pointer_offset;
	Type *type;
	int number_formal_parameters;
	SymbolTableEntry* function_ptr;
	int function_frame_size;
	Scope scope;	
	/* Attributes added during code generation. */
	const char* literal_constant_ptr_label;
};

static inline SymbolTableEntry construct_symbol_table_entry(
	const char* symbol)
{
	SymbolTableEntry result = {
		symbol,
		NULL,
		0,
		0,
		0,
		false,
		NULL,
		0,
		0,
		NULL
	};
	return result;
}

static inline void print_symbol_table_entry_header()
{
	cout << ": symbol       "
		 << ": is typedef?  "
		 << ": is literal?  "
		 << ": value        "
		 << ": offset       "
		 << ": function ptr "
		 << ": num_params   "		
		 << ": scope type   "
		 << ": frame size   "
		 << ": type         ";
}

static inline void print_symbol_table_entry_content(
	SymbolTableEntry* entry)
{
	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << entry->symbol;

	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << (entry->is_typedef 
			? "true" 
			: "false");

	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << (entry->is_literal 
			? "true" 
			: "false");

	cout << ": 0x"
		 << std::right
		 << std::hex
		 << std::setw(8)
		 << std::setfill('0')
		 << entry->value
		 << "   ";

	cout << ": 0x"
		 << std::right
		 << std::hex
		 << std::setw(8)
		 << std::setfill('0')
		 << entry->base_pointer_offset
		 << "   ";

	const char* id = entry->function_ptr 
					 ? entry->function_ptr->symbol 
					 : "N/A";
	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << id;

	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << entry->number_formal_parameters;

	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << scope_string_repr[(int)entry->scope];

	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << entry->function_frame_size;

	cout << ": ";
	if (entry->type != NULL) {
		print_type(entry->type);
	} else {
		cout << "N/A";
	}
}
#define NUM_SYMBOL_TABLE_ENTRIES 6151

class SymbolTable {
private:
	SymbolTableEntry* entries[NUM_SYMBOL_TABLE_ENTRIES];

	unsigned int hash(const char* x) 
	{
		long long string_val = 0;
		for (const char* c = x; *c; c++) {
			string_val += 256 * *c;
		}
		unsigned int h = (string_val * 12289) % 6151;
		return h;
	}

public:
	inline SymbolTable() {
		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {
			*e = NULL;
		}
	}

	~SymbolTable() {
		delete[] entries;
	}

	inline SymbolTableEntry* get_entry(const char *symbol) 
	{
		unsigned int h = hash(symbol);
		SymbolTableEntry* entry = *(entries + h);
		if (entry != NULL) {
			while (entry != NULL) {
				if (strcmp(entry->symbol, symbol) != 0) {
					entry = entry->next_entry;
				} else {
					break;
				}
			}
		}
		return entry;
	}

	inline void get_entries(SymbolTableEntry** returned_entries) 
	{
		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			for (SymbolTableEntry* f = *e;
				f != NULL;
				f = f->next_entry) {

				*returned_entries++ = f;
			}
		}
		return;
	}

	inline void add_entry(
		const char* symbol) 
	{
		SymbolTableEntry* data = new SymbolTableEntry(
			construct_symbol_table_entry(symbol)
		);

		unsigned int h = hash(symbol);
		SymbolTableEntry** entry_addr = entries + h;
		if (*entry_addr != NULL) {
			SymbolTableEntry* old_entry = *entry_addr;
			*entry_addr = data;
			(*entry_addr)->next_entry = old_entry;
		} else {
			*entry_addr = data;
		}
	}

	inline void print(string prefix = "") 
	{
		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;

		cout << prefix;
		print_symbol_table_entry_header();
		cout << endl;

		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;

		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			for (SymbolTableEntry* f = *e;
				f != NULL;
				f = f->next_entry) {

				cout << prefix;
				print_symbol_table_entry_content(f);
				cout << endl;
			}		
		}

		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;
	}
};

#endif