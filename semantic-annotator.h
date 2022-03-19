/* Authored By Charlie Keaney               */
/* semantic-annotator.h - Attaches semantic
                          annotations to a 
						  given tree of ast 
						  nodes.            */

#ifndef SEMANTIC_ANNOTATOR_H
#define SEMANTIC_ANNOTATOR_H 0

#include "annotated-ast-node.h"
#include "semantics.h"
#include "symbol-table.h"

#define DEBUG_SEMANTIC_ANNOTATOR_SHOW_VISIT		    0
#define DEBUG_SEMANTIC_ANNOTATOR_SHOW_TREE_ON_VISIT 0
#define DEBUG_SEMANTIC_ANNOTATOR_SHOW_SCOPE_ENTRY   0

using namespace std;

#define report_visit(m)							\
	if (DEBUG_SEMANTIC_ANNOTATOR_SHOW_VISIT) {	\
		cout << "semantic-annotator.h:"			\
			 << m								\
			 << ": visiting..."					\
			 << endl;							\
	}											\

#define report_exit(m)							\
	if (DEBUG_SEMANTIC_ANNOTATOR_SHOW_VISIT) {	\
		cout << "semantic-annotator.h:"			\
			 << m								\
			 << ": exiting..."					\
			 << endl;							\
	}		

/*****************************************************//**
*                      Declarations                      *
/********************************************************/

typedef enum class SemanticAnnotatorExitCode {
	SUCCESS,
	FAIL
} SemanticAnnotatorExitCode;

/**
* Responsible for converting a given tree of ast 
* nodes to a tree of annotated ast nodes with 
* blank annotations (not filled in yet).
*
* @param ast_node The given tree of ast nodes.
* @param anno_ast_node The location to place the
*	                   finished tree of annotated
*                      ast nodes.
* @return Returns a semantic annotator exit code.
**/
static inline
SemanticAnnotatorExitCode construct_unatrributed_annotated_ast(
	const AstNode*    const& ast_node, 
    AnnotatedAstNode*      & anno_ast_node);


static inline
int convert_parameter_list_to_parameter_type(
	const AnnotatedAstNode* const& parameter_list,
	const Parameter*             & parameter_type);

/**
* Responsible for creating an annotated ast node
* for a primary-expressions.
* Must annotate type and symbol.
* May annotate constant value.
* @param node The primary expression to visit.
* @param file The symbol table for file scope.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_primary_expression(
	AnnotatedAstNode* const& primary_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for 
* an argument expression and returning the types of 
* the arguments through a given array.
* @param argument_expression The argument-expression 
*                            to visit.
* @param file The symbol table for the scope of the 
*             file that this argument-expression is
*             contained in.
* @param argument_types The array to place returned
*                       argument types into.
* @return Returns an exit code describing how the 
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_argument_expression_list(
	AnnotatedAstNode* const& argument_expression,
	SymbolTable*      const& file,
	const Type**           & argument_types);

/**
* Responsible for visiting an annotated ast node for
* a postfix-expression.
* @param postfix_expression The postfix-expression
*                            to visit.
* @param file The symbol table for the scope of the
*             file that this argument-expression is
*             contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_postfix_expression(
	AnnotatedAstNode* const& postfix_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for
* a postfix-expression.
* @param type_name The postfix-expression to visit.
* @param file The symbol table for the scope of the
*             file that this argument-expression is
*             contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_type_name(
	AnnotatedAstNode* const& type_name,
	SymbolTable*      const& file,
	const Type*			   & synthesized_type);
  
/**
* Responsible for visiting an annotated ast node for
* a unary-operator.
* @param unary_operator The unary-operator to visit.
* 
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_unary_operator(
	AnnotatedAstNode* const& unary_operator);

/**
* Responsible for visiting an annotated ast node for
* a cast-expression, giving it a type and constant
* expression value if appropriate.
* @param cast_expression The cast-expression to visit.
* @param file The symbol table for the scope of the
*             file that this cast-expression is
*             contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_cast_expression(
	AnnotatedAstNode* const& cast_expression,
	SymbolTable*      const& file);
/**
* Responsible for visiting an annotated ast node for
* a unary-expression, giving it a type and constant
* expression value if appropriate.
* @param unary_expression The unary-expression to visit.
* @param file The symbol table for the scope of the
*             file that this cast-expression is
*             contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_unary_expression(
	AnnotatedAstNode* const& unary_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for
* a multiplicative-expression, giving it a type and 
* constant expression value if appropriate.
* @param multiplicative-expression The multiplicative-expression 
                                   to visit.
* @param file The symbol table for the scope of the
*             file that this multiplicative-expression 
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_multiplicative_expression(
	AnnotatedAstNode* const& multiplicative_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for
* a additive-expression, giving it a type and
* constant expression value if appropriate.
* @param additive_expression The additive-expression
							 to visit.
* @param file The symbol table for the scope of the
*             file that this additive-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_additive_expression(
	AnnotatedAstNode* const& additive_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for
* a shift-expression, giving it a type and
* constant expression value if appropriate.
* @param shift_expression The shift-expression
							 to visit.
* @param file The symbol table for the scope of the
*             file that this shift-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_shift_expression(
	AnnotatedAstNode* const& shift_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node for
* a relational-expression, giving it a type and 
* constant expression value if appropriate.
* @param relational_expression The relational-expression
							   to visit.
* @param file The symbol table for the scope of the
*             file that this relational-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_relational_expression(
	AnnotatedAstNode* const& relational_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node 
* for an equality-expression, giving it a type 
* and constant expression value if appropriate.
* @param equality_expression The equality-expression
							 to visit.
* @param file The symbol table for the scope of the
*             file that this relational-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_equality_expression(
	AnnotatedAstNode* const& equality_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an and-expression, giving it a type
* and constant expression value if appropriate.
* @param and_expression The and-expression
*                       to visit.
* @param file The symbol table for the scope of the
*             file that this relational-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_and_expression(
	AnnotatedAstNode* const& and_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an exclusive-or-expression, giving it a type
* and constant expression value if appropriate.
* @param exclusive_or_expression The exclusive-or-expression
*                                to visit.
* @param file The symbol table for the scope of the
*             file that this exclusive-or-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_exclusive_or_expression(
	AnnotatedAstNode* const& exclusive_or_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an inclusive-or-expression, giving it a type
* and constant expression value if appropriate.
* @param inclusive_or_expression The inclusive-or-expression
*                                to visit.
* @param file The symbol table for the scope of the
*             file that this inclusive-or-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_inclusive_or_expression(
	AnnotatedAstNode* const& inclusive_or_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an logical-and-expression, giving it a type
* and constant expression value if appropriate.
* @param logical_and_expression The logical-and-expression
*                               to visit.
* @param file The symbol table for the scope of the
*             file that this logical-and-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_logical_and_expression(
	AnnotatedAstNode* const& logical_and_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a logical-or-expression, giving it a type
* and constant expression value if appropriate.
* @param logical_or_expression The logical-or-expression
*                               to visit.
* @param file The symbol table for the scope of the
*             file that this logical-and-expression
*             is contained in.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_logical_or_expression(
	AnnotatedAstNode* const& logical_or_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a assignment-operator, giving it a type
* and constant expression value if appropriate.
* @param assignment_operator The assignment-operator
*                            to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_assignment_operator(
	AnnotatedAstNode* const& assignment_operator);

/**
* Responsible for visiting an annotated ast node
* for an expression, giving it a type
* and constant expression value if appropriate.
* @param expression The expression to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_expression(
	AnnotatedAstNode* const& expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a conditional-expression, giving it a type
* and constant expression value if appropriate.
* @param conditional_expression The conditional_expression 
*                               to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_conditional_expression(
	AnnotatedAstNode* const& conditional_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a assignment-expression, giving it a type
* and constant expression value if appropriate.
* @param assignment_expression The assignment-expression
*                               to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_assignment_expression(
	AnnotatedAstNode* const& assignment_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a constant-expression, giving it a type
* and constant expression value.
* 
* @param constant_expression The constant-expression
*                            to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_constant_expression(
	AnnotatedAstNode* const& constant_expression,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a declaration, giving it a type
* and constant expression value.
*
* @param declaration The declaration to visit.
* @param file The scope of the file this declaration
*             is contained within.
* @param declaration_scope The scope that this declaration
*                          is declared within. 
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_declaration(
	AnnotatedAstNode* const& declaration,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope);

/**
* Responsible for visiting an annotated ast node
* for a storage-class-specifier.
*
* @param storage_class_specifier The storage-class-specifier
*                                to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_storage_class_specifier(
	AnnotatedAstNode* const& storage_class_specifier);

/**
* Responsible for visiting an annotated ast 
* node for a type-specifier.
* 
* @param type_specifier The type-specifier to visit.
* @param synthesized_type The type synthesized by
*                         this type-specifier.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_type_specifier(
	AnnotatedAstNode* const& type_specifier,
	const Type*            & synthesized_type);


/**
* Responsible for visiting an annotated ast
* node for a function-specifier.
* 
* @param function_specifier The function-specifier
*                           to visit.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_function_specifier(
	AnnotatedAstNode* const& function_specifier);

/**
* Responsible for visiting an annotated ast node 
* for a declaration-specifiers.
* 
* @param declaration_specifiers The declaration-specifiers
*                               to visit.
* @param synthesized_type The type synthesized by these 
*                         declaration specifiers.
* @return Returns an exit code describing how the
*         visit went.
**/
static inline
SemanticAnnotatorExitCode visit_declaration_specifiers(
	AnnotatedAstNode* const& declaration_specifiers,
	const Type*            & synthesized_type);

/**
* Responsible for visiting an annotated ast node 
* for an init-declarator.
* 
* @param init_declarator The init-declarator to visit.
* @param declaration_scope The symbol table for the scope
*                          this init-declarator is in.
* @param declaration_specifier_type The type inherited
*                                   by this init-declarator
*                                   to give to declared names.
* @param file The symbol table for this cope of the file this
*             init-declarator is in.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_init_declarator(
	AnnotatedAstNode* const& init_declarator,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type,
	SymbolTable*      const& file);


/**
* Responsible for visiting an annotated ast node 
* for an init-declarator-list.
*
* @param init_declarator_list The init-declarator to visit.
* @param file The symbol table for this cope of the file this
*             init-declarator is in.
* @param declaration_scope The symbol table for the scope
*                          this init-declarator is in.
* @param declaration_specifier_type The type inherited
*                                   by this init-declarator
*                                   to give to declared names.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_init_declarator_list(
	AnnotatedAstNode* const& init_declarator_list,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type);

/**
* Responsible for visiting an annotated ast node 
* for an enum-specifier.
* 
* @param enum_specifier The enum-specifier to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_enum_specifier(
	AnnotatedAstNode* const& enum_specifier);

/**
* Responsible for visiting an annotated ast node 
* for a typedef-name.
* 
* @param typedef_name The typedef-name to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_typedef_name(
	AnnotatedAstNode* const& typedef_name);

/**
* Responsible for visiting an annotated ast node 
* for a struct-or-union-specifier.
*
* @param struct_or_union_specifier The struct-or-union-specifier 
*                                  to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_or_union_specifier(
	AnnotatedAstNode* const& struct_or_union_specifier);

/**
* Responsible for visiting an annotated ast node 
* for a struct-or-union.
*
* @param struct_or_union The struct_or_union to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_or_union(
	AnnotatedAstNode* const& struct_or_union);

/**
* Responsible for visiting an annotated ast node 
* for a struct-declaration-list.
*
* @param struct_declaration_list The struct-declaration-list 
*                                to visit.
* @param file The symbol table for the scope of the file that 
*             this struct-declaration-list is contained within.
* @param declaration_scope The symbol table for the scope that
*                          this struct-declaration-list is 
*                          declared within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_declaration_list(
	AnnotatedAstNode* const& struct_declaration_list,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope);

/**
* Responsible for visiting an annotated ast node 
* for a struct-declaration.
* 
* @param struct_declaration The struct-declaration to visit.
* @param file The symbol table for the scope of the file that
*             this struct-declaration-list is contained within.
* @param declaration_scope The symbol table for the scope that this
*                          struct declaration is contained within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_declaration(
	AnnotatedAstNode* const& struct_declaration,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope);

/**
* Responsible for visiting an annotated ast node 
* for a specifier-qualifier-list.
* 
* @param specifier_qualifier_list The specifier-qualifier-list 
*                                 to visit.
* @param synthesized_type The synthesized type produced by this
*                         visit to this specifier-qualifier-list.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_specifier_qualifier_list(
	AnnotatedAstNode* const& specifier_qualifier_list,
	const Type*            & synthesized_type);

/**
* Responsible for visiting an annotated ast node 
* for a struct-declarator-list.
*
* @param struct_declarator_list The struct-declarator-list
*                               to visit.
* @param declaration_scope The symbol table for the scope 
*                          this struct-declarator-list
*                          is declared within.
* @param file The symbol table for the scope of the file
*             this struct-declarator-list is declared within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_declarator_list(
	AnnotatedAstNode* const& struct_declarator_list,
	SymbolTable*      const& declaration_scope,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node 
* for a struct-declarator.
*
* @param struct_declarator The struct-declarator to visit.
* @param declaration_scope The symbol table for the scope 
*                          this struct-declarator is 
*                          declared within.
* @param declaration_specifier_type The type inherited by
*                                   this struct declarator.
* @param file The symbol table for the scope this 
*             struct-declarator is declared within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_struct_declarator(
	AnnotatedAstNode* const& struct_declarator,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type,
	SymbolTable*      const& file);

/**
* Responsible for visting an annotated ast node 
* for an enumerator.
* 
* @param enumerator The enumerator to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_enumerator(
	AnnotatedAstNode* const& enumerator);

/**
* Responsible for visting an annotated ast node 
* for an enumerator-list.
*
* @param enumerator_list The enumerator-list to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_enumerator_list(
	AnnotatedAstNode* const& enumerator_list);

/**
* Responsible for visting an annotated ast node 
* for an enumeration-specifier.
*
* @param enumeration_specifier The enumeration-specifier to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_enumeration_specifier(
	AnnotatedAstNode* const& enumeration_specifier);

/**
* Responsible for visiting an annotated ast node
* for a type-qualifier.
*
* @param type_qualifier The type-qualifier to visit.
* @param type_qualifiers The type qualifiers synthesized by this
*                        type-qualifier.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_type_qualifier(
	AnnotatedAstNode* const& type_qualifier,
	TypeQualifiers         & type_qualifiers);

/**
* Responsible for visiting an annotated ast node 
* for a declarator.
* 
* @param declarator The declarator to visit.
* @param file The symbol table for the scope of the file
*             this declarator is contained within.
* @param declaration_scope The symbol table for the scope
*                          this declarator is declared within.
* @param parameter_type_list_scope The symbol table for the scope
*                                  that parameter-type-list should
*                                  be declared within (if declared
*                                  by this declarator).
* @param declaration_specifier_type The type inherited by this 
*                                   declarator to give to its
*                                   declared names.
* @param parameter_type_list The parameter-type-list produced by this
*                            declarator (if appropriate).
* @param synthesized_type The type synthesized by this declarator.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_declarator(
	AnnotatedAstNode*       const& declarator,
	SymbolTable*            const& file,
	SymbolTable*            const& declaration_scope,
	SymbolTable*            const& parameter_type_list_scope,
	const Type*             const& declaration_specifier_type,
	const AnnotatedAstNode*		 & parameter_type_list,
	const Type*                  & synthesized_type);

/**
* Responsible for visiting an annotated ast node 
* for a direct-declarator.
* 
* @param direct_declarator The direct-declarator to visit.
* @param file The symbol table for the scope of the file 
*             that this direct-declarator is declared within. 
* @param declaration_scope The symbol table for the scope 
*                          which this direct-declarator is 
*                          declared within. 
* @param parameter_type_list_scope The symbol table for the scope 
*                                  of a parameter-type-list declared 
*                                  within this direct-declarator. 
* @param declaration_specifier_type The type inherited from the 
*                                   declaration-specifier for this
*                                   direct declarator to give to 
*                                   names declared by this 
*                                   direct declarator.
* @param parameter_list The parameter-list produced by this direct-declarator
*                       (if appropriate).
* @param synthesized_type The type synthesized by this direct-declarator.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_direct_declarator(
	AnnotatedAstNode*       const& direct_declarator,
	SymbolTable*            const& file,
	SymbolTable*            const& declaration_scope,
	SymbolTable*            const& parameter_type_list_scope,
	const Type*             const& declaration_specifier_type,
	const AnnotatedAstNode*      & parameter_list,
	const Type*					 & synthesized_type);

/**
* Responsible for visiting an annotated ast node 
* for a pointer.
* 
* @param pointer The pointer to visit.
* @param referenced_type The inherited type to which this pointer
*                        refers to.
* @param synthesized_type The type synthesized by this pointer.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_pointer(
	AnnotatedAstNode* const& pointer,
	const Type*       const& referenced_type,
	const Type*            & synthesized_type);

/**
* Responsible for visiting an annotated ast node
* for a type-qualifier-list.
* 
* @param type_qualifier_list The type-qualifier-list to visit.
* @param type_qualifiers The type qualifiers produced by this
*                        type-qualifier-list.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_type_qualifier_list(
	AnnotatedAstNode* const& type_qualifier_list,
	TypeQualifiers         & type_qualifiers);

/**
* Responsible for visiting an annotated ast node
* for a parameter-type-list.
* 
* @param parameter_type_list The parameter-type-list to visit.
* @param file The symbol table for the scope of the file
*             that this parameter-type-list is contained within.
* @param function_scope The symbol table for the scope of the function
*                       that this parameter-type-list is contained within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_parameter_type_list(
	AnnotatedAstNode* const& parameter_type_list,
	SymbolTable*      const& file,
	SymbolTable*      const& function_scope);

/**
* Responsible for visiting an annotated ast node
* for a parameter-list.
*
* @param parameter_list The parameter-list to visit.
* @param file The symbol table for the scope of the file
*             that this parameter-list is contained within.
* @param function_scope The symbol table for the scope of the file
*                       that this parameter-list is contained within.
* @param parameter_types_list The types synthesized by this parameter-list.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_parameter_list(
	AnnotatedAstNode* const& parameter_list,
	SymbolTable*      const& file,
	SymbolTable*      const& function_scope,
	const Type**           & parameter_types_list);
 
/**
* Responsible for visiting an annotated ast node
* for a parameter-declaration.
* 
* @param parameter_declaration The parameter-declaration to visit.
* @param function_scope The symbol table for the scope of the function
*                       that this parameter is declared within.
* @param file The symbol table for the scope of the file that this
*             parameter is declared within.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_parameter_declaration(
	AnnotatedAstNode* const& parameter_declaration,
	SymbolTable*      const& function_scope,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a identifier-list.
* 
* @param identifier_list The identifier-list to visit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_identifier_list(
	AnnotatedAstNode* const& identifier_list);

/**
* Responsible for visiting an annotated ast node
* for a identifier-list.
* 
* @param abstract_declarator The abstract-declarator to visit.
* @param file The symbol table for the scope of the file
*             that this abstract-declarator is declared within.
* @param specifier_qualifier_list_type The type inherited
*                                      from a specifier-qualifier-list
*                                      given to names declared by this
*                                      abstract declarator.
* @param synthesized_type The synthesized type produced by this
                          specifier-qualifier-list.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_abstract_declarator(
	AnnotatedAstNode* const& abstract_declarator,
	SymbolTable*      const& file,
	const Type*       const& specifier_qualifier_list_type,
	const Type*            & synthesized_type);

/**
* Responsible for visiting an annotated ast node
* for a direct-abstract-declarator.
* 
* @param direct_abstract_declarator The direct-abstract-declarator
*                                   to visit.
* @param file The symbol table for the scope of the file that
*             contains this direct-abstract-declarator.
* @param specifier_qualifier_list_type The type inherited from
*                                      a specifier-qualifier-list
*                                      given to names declared by
*                                      this direct-abstract-declarator.
* @param synthesized_type
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_direct_abstract_declarator(
	AnnotatedAstNode* const& direct_abstract_declarator,
	SymbolTable*      const& file,
	const Type*       const& specifier_qualifier_list_type,
	const Type*            & synthesized_type);

/**
* Responsible for visiting an annotated ast node
* for an initializer.
* 
* @param initializer The initializer to visit.
* @param file The symbol table for the scope of the file that 
*             contains this initializer.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_initializer(
	AnnotatedAstNode* const& initializer,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an initializer_list.
* 
* @param initializer_list The initializer-list to visit.
* @param file The symbol table for the scope of the file that
*             contains this initializer-list.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_initializer_list(
	AnnotatedAstNode* const& initializer_list,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an designation.
* 
* @param designation The designation to visit.
* @param file The symbol table for the scope of the file that
*             contains this designation.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_designation(
	AnnotatedAstNode* const& designation,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an designator-list.
* 
* @param designator_list The designator-list to visit.
* @param file The symbol table for the scope of the file that
*             contains this designation.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_designator_list(
	AnnotatedAstNode* const& designator_list,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an designator.
*
* @param designator The designator to visit.
* @param file The symbol table for the scope of the file that
*             contains this designator.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_designator(
	AnnotatedAstNode* const& designator,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a labeled-statement.
*
* @param labeled_statement The labeled-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this labeled-statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_labeled_statement(
	AnnotatedAstNode* const& labeled_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a statement.
*
* @param statement The statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_statement(
	AnnotatedAstNode* const& statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a compound-statement.
*
* @param compound_statement The compound-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_compound_statement(
	AnnotatedAstNode* const& compound_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a block-item-list.
*
* @param block_item_list The block-item-list to visit.
* @param file The symbol table for the scope of the file that
*             contains this block-item-list.
* @param block_scope The symbol table for the scope of the
*                    block within which this block-item-list is 
*                    contained.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_block_item_list(
	AnnotatedAstNode* const& block_item_list,
	SymbolTable*      const& file,
	SymbolTable*      const& block_scope);

/**
* Responsible for visiting an annotated ast node
* for a block-item.
*
* @param block_item The block-item to visit.
* @param file The symbol table for the scope of the file that
*             contains this block-item-list.
* @param block_scope The symbol table for the scope of the
*                    block within which this block-item is 
*                    contained.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_block_item(
	AnnotatedAstNode* const& block_item,
	SymbolTable*      const& file,
	SymbolTable*      const& block_scope);

/**
* Responsible for visiting an annotated ast node
* for a expression-statement.
*
* @param expression_statement The expression-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this expression-statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_expression_statement(
	AnnotatedAstNode* const& expression_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a selection-statement.
*
* @param selection_statement The selection-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this selection-statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_selection_statement(
	AnnotatedAstNode* const& selection_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a iteration-statement.
*
* @param iteration_statement The iteration-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this iteration-statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_iteration_statement(
	AnnotatedAstNode* const& iteration_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a jump-statement.
*
* @param jump_statement The jump-statement to visit.
* @param file The symbol table for the scope of the file that
*             contains this jump-statement.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_jump_statement(
	AnnotatedAstNode* const& jump_statement,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a translation-unit.
*
* @param translation_unit The translation-unit to visit.
* @param file The symbol table for the scope of the file that
*             contains this translation-unit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_translation_unit(
	AnnotatedAstNode* const& translation_unit,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for an external-declaration.
*
* @param external_declaration The external-declaration to visit.
* @param file The symbol table for the scope of the file that
*             contains this translation-unit.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_external_declaration(
	AnnotatedAstNode* const& external_declaration,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a function-definition.
* 
* @param function_definition The function-definition to visit.
* @param file The symbol table for the scope of the file that
*             contains this function-definition.
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_function_definition(
	AnnotatedAstNode* const& function_definition,
	SymbolTable*      const& file);

/**
* Responsible for visiting an annotated ast node
* for a declaration-list.
* 
* @param declaration_list The declaration-list to visit.
* @param file The symbol table for the scope of the file that
*             contains this declaration-list.
* @param declaration_scope The symbol table for the scope
*                          within which this declaration-list
*                          is declared.
* @param parameter_type_list The parameter-type-list within
*                            this declaration-list (if appropriate).
* @return Returns an exit code describing how the visit went.
**/
static inline
SemanticAnnotatorExitCode visit_declaration_list(
	AnnotatedAstNode*       const& declaration_list,
	SymbolTable*            const& file,
	SymbolTable*            const& declaration_scope,
	const AnnotatedAstNode*        parameter_type_list);

/**
* Responsible for taking the root of an ast node tree
* (a translation-unit) and outputting an equivalent annotated
* ast node tree.
*
* @param node The ast node root containing a translation-unit to visit.
* @param anno_node The produced annotated ast node root containing a 
*                  translation-unit that has been visited and annotated.
* @return Returns an exit code describing how the visit went.
**/
static inline
bool annotate(
	const AstNode*            node,
	const AnnotatedAstNode* & anno_node);

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

static inline
SemanticAnnotatorExitCode construct_unatrributed_annotated_ast(
	const AstNode*    const& ast_node, 
    AnnotatedAstNode*      & anno_ast_node)
{
	SemanticAnnotatorExitCode exitcode = SemanticAnnotatorExitCode::SUCCESS;

	anno_ast_node = new AnnotatedAstNode(ast_node);

	for (const AstNode* c = ast_node->get_child();
		 c != NULL;
		 c = c->get_sibling()) {

		AnnotatedAstNode* anno_c;
		if (construct_unatrributed_annotated_ast(c, anno_c)
			== SemanticAnnotatorExitCode::SUCCESS) {
			anno_ast_node->add_child(anno_c);
		} else {
			exitcode = SemanticAnnotatorExitCode::FAIL;
		}
	}
	return exitcode;
}

static inline
bool cast_expr_is_result_of_array_index(
	const AnnotatedAstNode* const& node) 
{
	const AnnotatedAstNode* current = node;
	
	bool return_value = false;
	bool halted = false;
	while (!halted) {

		switch (current->get_alt()) {

			case AstNodeAlt::CAST_EXPRESSION_1:
				current = current->get_child();
				break;

			case AstNodeAlt::CAST_EXPRESSION_2:
				current = current->get_child()->get_sibling();
				break;

			case AstNodeAlt::UNARY_EXPRESSION_1:
				current = current->get_child();
				break;

			case AstNodeAlt::POSTFIX_EXPRESSION_2:
				halted = true;
				return_value = true;
				break;

			default:
				halted = true;
				return_value = false;
				break;
		} 
		
	}
	return return_value;
}


static inline
bool cast_expr_is_result_of_deref(
	const AnnotatedAstNode* const& node
) {
	const AnnotatedAstNode* current = node;

	bool return_value = false;
	bool halted = false;
	while (!halted) {

		switch (current->get_alt()) {

		case AstNodeAlt::CAST_EXPRESSION_1:
			current = current->get_child();
			break;

		case AstNodeAlt::CAST_EXPRESSION_2:
			current = current->get_child()->get_sibling();
			break;

		case AstNodeAlt::UNARY_EXPRESSION_4:
			if (current->get_child()->get_alt() 
				== AstNodeAlt::UNARY_OPERATOR_2) {
				return_value = true;
			} else {
				return_value = false;
			}
			halted = true;
			break;

		default:
			halted = true;
			return_value = false;
			break;
		}

	}
	return return_value;
}

static inline
bool cast_expr_is_bitfield(
	const AnnotatedAstNode* const& node
) {
	const AnnotatedAstNode* current = node;

	bool return_value = false;
	//TODO; stub
	return return_value;
}

static inline
SemanticAnnotatorExitCode visit_primary_expression(
	AnnotatedAstNode* const& primary_expression,
	SymbolTable*      const& file) 
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("primary_expression");

	switch (primary_expression->get_alt()) {

		case AstNodeAlt::PRIMARY_EXPRESSION_1:
		{
			const char* const symbol
				= primary_expression->get_child()
			                        ->get_terminal()
			                        ->get_lexeme();

			primary_expression->set_symbol(symbol);

			const Type* const declared_primary_expression_type 
				= primary_expression->get_symbol_table(symbol)
					                ->get_entry(symbol)
					                ->type;

			const Type* primary_expression_type;
			duplicate_type(
				declared_primary_expression_type,
				primary_expression_type);
			primary_expression->set_type(
				primary_expression_type);
			primary_expression->set_is_constant_evaluation(
				false);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_2:
		{
			const TokenValue val 
				= primary_expression->get_child()
				                    ->get_terminal()
				                    ->get_constant_val();

			const char* const symbol 
				= primary_expression->get_child()
				                    ->get_terminal()
				                    ->get_lexeme();

			SymbolTableEntry* symbol_entry 
				= file->get_entry(symbol);

			if (!symbol_entry) {

				file->add_entry(symbol);
				symbol_entry = file->get_entry(symbol);

				symbol_entry->value = val.intvalue;
				symbol_entry->is_literal = true;
				
				TokenForm form 
					= primary_expression->get_child()
						                ->get_terminal()
						                ->get_form();

				const Type* type = NULL;
				switch (form) {

					case TokenForm::FLOATING_CONSTANT: 
						type = construct_basic_type(
							BasicTypeName::FLOAT,
							TypeQualifiers::UNQUALIFIED);
						break;

					case TokenForm::INTEGER_CONSTANT:
						type = construct_basic_type(
							BasicTypeName::SIGNED_INT,
							TypeQualifiers::UNQUALIFIED);

					case TokenForm::CHARACTER_CONSTANT:
						type = construct_basic_type(
							BasicTypeName::SIGNED_CHAR,
							TypeQualifiers::UNQUALIFIED);

					default:
						break;

				}
				symbol_entry->type = type;

				symbol_entry->scope = Scope::FILE;
			}	

			const Type* node_type;
			duplicate_type(
				symbol_entry->type, 
				node_type);
			primary_expression->set_type(
				node_type);
			primary_expression->set_symbol(
				symbol);
			primary_expression->set_is_constant_evaluation(
				true);
			primary_expression->set_constant_val(
				val.intvalue);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_3:
		{
			/* A string literal is a pointer to a character. */
			const Type* const char_type 
				= construct_basic_type(
					BasicTypeName::SIGNED_CHAR,
					TypeQualifiers::UNQUALIFIED);
			
			const Type* const primary_expression_type 
				= construct_derived_pointer_type(
					char_type,
					TypeQualifiers::CONST);

			primary_expression->set_type(
				primary_expression_type);
			primary_expression->set_is_constant_evaluation(
				true);
			primary_expression->set_constant_val(0);
			/* TODO; */

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_4:
		{
			AnnotatedAstNode* expression 
				= primary_expression->get_child();

			visit_expression(
				expression,
				file);

			const Type* const expression_type
				= expression->get_type();

			const Type* primary_expression_type;
			duplicate_type(
				expression_type,
				primary_expression_type);
			primary_expression->set_type(
				primary_expression_type);

			const uint64_t expression_constant_val
				= expression->get_constant_val();
			primary_expression->set_constant_val(
				expression_constant_val);

			primary_expression->set_is_constant_evaluation(
				expression->get_is_constant_evaluation());
			primary_expression->set_constant_val(
				expression->get_constant_val());

			exitcode 
				= SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("primary_expression");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_argument_expression_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	const Type**		   & argument_types)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_argument_expression_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ARGUMENT_EXPRESSION_LIST_1:
		{
			AnnotatedAstNode* assignment_expression
				= node->get_child();

			visit_assignment_expression(
				assignment_expression,
				file);

			*argument_types++ 
				= assignment_expression->get_type();
			
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ARGUMENT_EXPRESSION_LIST_2:
		{
			AnnotatedAstNode* argument_expression_list
				= node->get_child();
			AnnotatedAstNode* assignment_expression
				= argument_expression_list->get_sibling();

			visit_argument_expression_list(
				argument_expression_list,
				file,
				argument_types);
			visit_assignment_expression(
				assignment_expression,
				file);

			*argument_types++
				= assignment_expression->get_type();

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_argument_expression_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_postfix_expression(
	AnnotatedAstNode* const& postfix_expression,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_postfix_expression_1");

	switch (postfix_expression->get_alt()) {

		case AstNodeAlt::POSTFIX_EXPRESSION_1:
		{
			AnnotatedAstNode* primary_expression
				= postfix_expression->get_child();

			visit_primary_expression(
				primary_expression,
				file);

			const Type* postfix_expression_type;
			duplicate_type(
				primary_expression->get_type(), 
				postfix_expression_type);
			postfix_expression->set_type(
				postfix_expression_type);

			const char* const primary_expression_symbol
				= primary_expression->get_symbol();

			postfix_expression->set_symbol(
				primary_expression_symbol);

			const uint64_t primary_expression_constant_val
				= primary_expression->get_constant_val();
			postfix_expression->set_constant_val(
				primary_expression_constant_val);

			bool primary_expression_is_constant_eval
				= primary_expression->get_is_constant_evaluation();
			postfix_expression->set_is_constant_evaluation(
				primary_expression_is_constant_eval);
			uint64_t constant_val
				= primary_expression->get_constant_val();
			postfix_expression->set_constant_val(
				constant_val);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_2:
		{
			AnnotatedAstNode* lower_postfix_expression
				= postfix_expression->get_child();
			AnnotatedAstNode* expression
				= postfix_expression->get_sibling();

			visit_postfix_expression(
				lower_postfix_expression,
				file);
			visit_expression(
				expression,
				file);
			
			/* 1 The expression that denotes the called function shall have 
				 type pointer to function returning void or returning an object 
				 type other than an array type.*/

			const Type* const expression_type 
				= lower_postfix_expression->get_type();
			
			const bool is_pointer
				= is_pointer_type(expression_type);

			if (!is_pointer) {
				break;
			}
			
			const Type* const function_type
				= dereference_type(expression_type);

			const bool is_function 
				= is_function_type(function_type);

			if (!is_function) {
				break;
			}

			const Type* const return_type 
				= get_function_return_type(function_type);

			const bool returns_void_or_object_other_than_arr
				= is_void_type(return_type)
    			  || (is_object_type(return_type) 
					  && !is_array_type(return_type));

			if (!returns_void_or_object_other_than_arr) {
				break;
			}

			const Type* postfix_expression_type;
			duplicate_type(
				return_type,
				postfix_expression_type);
			postfix_expression->set_type(postfix_expression_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
		
		case AstNodeAlt::POSTFIX_EXPRESSION_3:
		{
			AnnotatedAstNode* lower_postfix_expression
				= postfix_expression->get_child();
			AnnotatedAstNode* argument_expression_list
				= postfix_expression->get_sibling();

			const Type* argument_types_list[16];
			const Type** atl_ptr = argument_types_list;

			visit_postfix_expression(
				lower_postfix_expression,
				file);
			visit_argument_expression_list(
				argument_expression_list,
				file,
				atl_ptr);

			/* 
			1 The expression that denotes the called function 
				shall have type pointer to function returning 
				void or returning an object type other than an 
				array type.
			*/				 

			const Type* const expression_type
				= lower_postfix_expression->get_type();

			const bool is_pointer
				= is_pointer_type(expression_type);

			if (!is_pointer) {
				break;
			}

			const Type* const function_type
				= dereference_type(expression_type);

			const bool is_function
				= is_function_type(function_type);

			if (!is_function) {
				break;
			}

			const Type* const return_type
				= get_function_return_type(function_type);

			const bool returns_void_or_object_other_than_arr
				= !is_array_type(return_type)
				  && (is_object_type(return_type)
					  || is_void_type(return_type));

			/*
			    2 If the expression that denotes the called 
				  function has a type that includes a prototype,
				  the number of arguments shall agree with the 
				  number of parameters. Each argument shall have 
				  a type such that its value may be assigned to 
				  an object with the unqualified version of the 
				  type of its corresponding parameter. 
			*/
			
			const Type** current_argument 
				= argument_types_list;
			const Parameter* current_parameter 
				= function_type->function_type.parameter_list;

			bool matched = true;

			for (int i = 0;
				 i < function_type->function_type.number_of_parameters;
				 i++) {

				const Type* current_argument_type
					= *current_argument;
				const Type* current_parameter_type 
					= current_parameter->parameter_type;
				 
				if (!types_are_equivalent(
						current_argument_type,
						current_parameter_type)) {
					matched = false;
					break;
				}

				current_argument++;
				current_parameter = current_parameter->next_parameter;
			}
			if (!matched) {
				break;
			}

			const Type* postfix_expr_type;
			duplicate_type(
				return_type, 
				postfix_expr_type);
			postfix_expression->set_type(postfix_expr_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_4:
		case AstNodeAlt::POSTFIX_EXPRESSION_5:
		{
			/*AnnotatedAstNode* postfix_expression
				= node->get_child();
			AnnotatedAstNode* argument_expression_list
				= postfix_expression->get_sibling();

			visit_postfix_expression_1(
				postfix_expression,
				file);
			if (argument_expression_list) {
				visit_identifier_1(
					argument_expression_list,
					file);
			}*/

			// TODO; Gather type.
			
			
			//exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_6:
		case AstNodeAlt::POSTFIX_EXPRESSION_7:
		{
			AnnotatedAstNode* lower_postfix_expression
				= postfix_expression->get_child();
			visit_postfix_expression(
				postfix_expression,
				file);
			
			const Type* postfix_expression_type;
			duplicate_type(
				lower_postfix_expression->get_type(),
				postfix_expression_type);
			postfix_expression->set_type(postfix_expression_type);

			postfix_expression->set_constant_val(
				false);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_8:
		case AstNodeAlt::POSTFIX_EXPRESSION_9:
		{
			AnnotatedAstNode* type_name
				= postfix_expression->get_child();
			AnnotatedAstNode* initializer_list
				= type_name->get_sibling();

			const Type* type_name_type;
			visit_type_name(
				type_name,
				file,
				type_name_type);

			visit_initializer_list(
				initializer_list,
				file);

			const Type* postfix_expression_type;
			duplicate_type(
				type_name_type, 
				postfix_expression_type);
			postfix_expression->set_type(
				postfix_expression_type);
			/* TODO; */
			postfix_expression->set_constant_val(
				false);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_postfix_expression_1");
	return exitcode;
}

/**
*	Responsible for visiting a type-name and synthesizing the
*	type recorded within.
*/
static inline
SemanticAnnotatorExitCode visit_type_name(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	const Type*			   & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_type_name_1");

	switch (node->get_alt()) {

		case AstNodeAlt::TYPE_NAME_1:
		{
			AnnotatedAstNode* specifier_qualifier_list
				= node->get_child();
			AnnotatedAstNode* abstract_declarator
				= specifier_qualifier_list->get_sibling();

			const Type* specifier_qualifier_list_type;
			visit_specifier_qualifier_list(
				specifier_qualifier_list,
				specifier_qualifier_list_type);

			const Type* abstract_declarator_type = NULL;
			if (abstract_declarator) {
				visit_abstract_declarator(
					abstract_declarator,
					file,
					specifier_qualifier_list_type,
					abstract_declarator_type);
			}
			
			const Type* type_name_source_type
				= abstract_declarator 
				  ? abstract_declarator_type
				  : specifier_qualifier_list_type;

			const Type* type_name_type;
			duplicate_type(
				type_name_source_type,
				type_name_type);
			synthesized_type = type_name_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_type_name_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_unary_operator(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_unary_operator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::UNARY_OPERATOR_1:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::UNARY_OPERATOR_2:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::UNARY_OPERATOR_3:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::UNARY_OPERATOR_4:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::UNARY_OPERATOR_5:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::UNARY_OPERATOR_6:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		default:
			break;

	}
	report_exit("visit_unary_operator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_cast_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_cast_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::CAST_EXPRESSION_1:
		{
			AnnotatedAstNode* unary_expression
				= node->get_child();

			visit_unary_expression(
				unary_expression,
				file);

			const Type* cast_expression_type;
			duplicate_type(
				unary_expression->get_type(), 
				cast_expression_type);
			node->set_type(
				cast_expression_type);
			node->set_symbol(
				unary_expression->get_symbol());

			node->set_is_constant_evaluation(
				unary_expression->get_is_constant_evaluation());
			node->set_constant_val(
				unary_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::CAST_EXPRESSION_2:
		{
			AnnotatedAstNode* type_name
				= node->get_child();
			AnnotatedAstNode* cast_expression
				= type_name->get_sibling();

			const Type* type_name_type;
			visit_type_name(
				type_name,
				file,
				type_name_type);
			visit_cast_expression(
				cast_expression,
				file);

			const Type* cast_expression_type;
			duplicate_type(
				type_name_type, 
				cast_expression_type);
			node->set_type(
				cast_expression_type);

			node->set_is_constant_evaluation(
				cast_expression->get_is_constant_evaluation());
			node->set_constant_val(
				cast_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_cast_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_unary_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_unary_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::UNARY_EXPRESSION_1:
		{
			AnnotatedAstNode* postfix_expression
				= node->get_child();

			visit_postfix_expression(
				postfix_expression,
				file);

			const Type* unary_expression_type;
			duplicate_type(
				postfix_expression->get_type(), 
				unary_expression_type);
			node->set_type(
				unary_expression_type);

			node->set_symbol(
				postfix_expression->get_symbol());

			node->set_is_constant_evaluation(
				postfix_expression->get_is_constant_evaluation());
			node->set_constant_val(
				postfix_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_2:
		case AstNodeAlt::UNARY_EXPRESSION_3:
		{
			AnnotatedAstNode* unary_expression
				= node->get_child();

			visit_unary_expression(
				unary_expression,
				file);

			const Type* unary_expression_type;
			duplicate_type(
				unary_expression->get_type(), 
				unary_expression_type);
			node->set_type(
				unary_expression_type);

			/* 1 The operand of the prefix increment or decrement
			     operator shall have qualified or unqualified real
				 or pointer type and shall be a modifiable lvalue. */
			const bool follows_constraint_1
				= (is_real_floating_type(unary_expression_type)
				   || is_pointer_type(unary_expression_type))
				  && is_modifiable_lvalue_type(unary_expression_type);

			node->set_is_constant_evaluation(
				false);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_4:
		{
			AnnotatedAstNode* unary_operator
				= node->get_child();
			AnnotatedAstNode* cast_expression
				= unary_operator->get_sibling();

			visit_unary_operator(
				unary_operator);
			visit_cast_expression(
				cast_expression,
				file);

			const Type* cast_expression_type
				= cast_expression->get_type();

			switch (unary_operator->get_alt()) {

				case AstNodeAlt::UNARY_OPERATOR_1:
				{
					/* 
						1 The operand of the unary & operator 
						  shall be either a function designator, 
						  the result of a [] or unary * operator, 
						  or an lvalue that designates an object
						  that is not a bit-field and is not 
						  declared with the register storage-class
						  specifier. 
					 */
					const bool follows_constraint_1
						= (is_function_type(cast_expression_type)
						   || (cast_expr_is_result_of_array_index(cast_expression)
							   || cast_expr_is_result_of_deref(cast_expression))
						   || (is_lvalue_type(cast_expression_type)
							   && is_object_type(cast_expression_type)
							   && !cast_expr_is_bitfield(cast_expression)
							   && !is_declared_as_register(cast_expression_type)));

					if (follows_constraint_1 || 1 /*TODO; proper logic */) {

						const Type* copy_cast_expression_type;
						duplicate_type(
							cast_expression_type, 
							copy_cast_expression_type);

						const Type* unary_expression_type
							= construct_derived_pointer_type(
								copy_cast_expression_type,
								TypeQualifiers::UNQUALIFIED);

						node->set_type(
							unary_expression_type);	

						node->set_is_constant_evaluation(
							false);

						exitcode 
							= SemanticAnnotatorExitCode::SUCCESS;
					}
					break;
				}

				case AstNodeAlt::UNARY_OPERATOR_2:
				{
					/* 
						2 The operand of the unary * operator shall have
					      pointer type. 
					*/
					const bool follows_constraint_2
						= is_pointer_type(cast_expression_type);

					if (follows_constraint_2) {

						const Type* unary_expression_type;
						duplicate_type(
							dereference_type(cast_expression_type), 
							unary_expression_type);

						node->set_type(
							unary_expression_type);

						node->set_is_constant_evaluation(
							cast_expression->get_is_constant_evaluation());
						node->set_is_constant_evaluation(
							false);
						
						exitcode = SemanticAnnotatorExitCode::SUCCESS;
					}
					break;
				}

				case AstNodeAlt::UNARY_OPERATOR_3:
				case AstNodeAlt::UNARY_OPERATOR_4:
				case AstNodeAlt::UNARY_OPERATOR_5:
				case AstNodeAlt::UNARY_OPERATOR_6:
				{
					/* 
					    1. The operand of the unary + or - operator
					       shall have arithmetic type; of the ~ 
						   operator, integer type; of the ! 
						   operator, scalar type. 
					*/
					const bool follows_constraint_1
						= ((unary_operator->get_alt() == AstNodeAlt::UNARY_OPERATOR_3
						    || unary_operator->get_alt() == AstNodeAlt::UNARY_OPERATOR_4) 
						   && is_arithmetic_type(cast_expression_type))
						  || (unary_operator->get_alt() == AstNodeAlt::UNARY_OPERATOR_4
							  && is_integer_type(cast_expression_type))
						  || (unary_operator->get_alt() == AstNodeAlt::UNARY_OPERATOR_5
							  && is_scalar_type(cast_expression_type));

					if (follows_constraint_1) {
						const Type* unary_expression_type;
						duplicate_type(
							cast_expression_type,
							unary_expression_type);
						node->set_type(
							unary_expression_type);


						node->set_is_constant_evaluation(
							true);

						switch (node->get_alt()) {

							case AstNodeAlt::UNARY_OPERATOR_3:
								node->set_constant_val(
									+ cast_expression->get_constant_val());
								break;

							case AstNodeAlt::UNARY_OPERATOR_4:
								node->set_constant_val(
									0 - cast_expression->get_constant_val());
								break;

							case AstNodeAlt::UNARY_OPERATOR_5:
								node->set_constant_val(
									~ cast_expression->get_constant_val());
								break;

							case AstNodeAlt::UNARY_OPERATOR_6:
								node->set_constant_val(
									! cast_expression->get_constant_val());
								break;

							default:
								break;
						}

						exitcode = SemanticAnnotatorExitCode::SUCCESS;
					}
					break;
				}

				default:
					break;
			}
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_5:
		{
			AnnotatedAstNode* unary_expression
				= node->get_child();

			visit_unary_expression(
				unary_expression,
				file);

			const Type* unary_expression_type
				= unary_expression->get_type();

			/* 
			   1 The sizeof operator shall not be applied to an expression 
			     that has function type or an incomplete type, to the 
				 parenthesized name of such a type, or to an expression that
				 designates a bit - field member. 
		    */
			const bool follows_constraint_1
				= !is_function_type(unary_expression_type)
				  && !is_incomplete_type(unary_expression_type)
				  && !is_parenthesized_incomplete_type(unary_expression_type)
				 /* && !is_designating_a_bit_field_member(unary_expression) 
				 TODO; stub */;

			const Type* higher_unary_expression_type = construct_basic_type(
				BasicTypeName::SIGNED_INT,
				TypeQualifiers::UNQUALIFIED);
			node->set_type(higher_unary_expression_type);

			node->set_is_constant_evaluation(
				true);
			node->set_constant_val(
				get_sizeof_type(unary_expression->get_type()));

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_6:
		{
			AnnotatedAstNode* type_name
				= node->get_child();

			const Type* type_name_type;
			visit_type_name(
				type_name,
				file,
				type_name_type);

			/*
				1 The sizeof operator shall not be applied to an expression
				  that has function type or an incomplete type, to the
				  parenthesized name of such a type, or to an expression that
				  designates a bit - field member.
			*/
			const bool follows_constraint_1
				= !is_function_type(type_name_type)
				  && !is_incomplete_type(type_name_type)
				  && !is_parenthesized_incomplete_type(type_name_type)
			   /* && !is_designating_a_bit_field_member(unary_expression)
				  TODO; stub */;

			const Type* unary_expression_type = construct_basic_type(
				BasicTypeName::SIGNED_INT,
				TypeQualifiers::UNQUALIFIED);

			node->set_is_constant_evaluation(
				true);
			node->set_constant_val(
				get_sizeof_type(type_name_type));

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_unary_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_multiplicative_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_multiplicative_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_1:
		{
			AnnotatedAstNode* cast_expression
				= node->get_child();

			visit_cast_expression(
				cast_expression,
				file);

			const Type* multiplicative_expression_type;
			duplicate_type(
				cast_expression->get_type(), 
				multiplicative_expression_type);
			node->set_type(
				multiplicative_expression_type);

			node->set_symbol(
				cast_expression->get_symbol());

			node->set_is_constant_evaluation(
				cast_expression->get_is_constant_evaluation());
			node->set_constant_val(
				cast_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2:
		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3:
		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4:
		{
			AnnotatedAstNode* multiplicative_expression
				= node->get_child();
			AnnotatedAstNode* cast_expression
				= multiplicative_expression->get_sibling();

			visit_multiplicative_expression(
				multiplicative_expression,
				file);
			visit_cast_expression(
				cast_expression,
				file);

			const Type* multiplicative_expression_type
				= multiplicative_expression->get_type();

			const Type* cast_expression_type
				= cast_expression->get_type();

			/* 2 Each of the operands shall have arithmetic type.
			     The operands of the % operator shall have integer type. */
			const bool follows_constraint_2
				= is_arithmetic_type(multiplicative_expression_type)
				  && is_arithmetic_type(cast_expression_type)
				  && ((node->get_alt() != AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4)
					  || (is_integer_type(multiplicative_expression_type)
						  && is_integer_type(cast_expression_type)));

			const Type* higher_multiplicative_expression_type;
			duplicate_type(
				multiplicative_expression->get_type(), 
				higher_multiplicative_expression_type);
			node->set_type(
				higher_multiplicative_expression_type);

			node->set_is_constant_evaluation(
				cast_expression->get_is_constant_evaluation());

			switch (node->get_alt()) {

				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2:
					node->set_constant_val(
						multiplicative_expression->get_constant_val()
						* cast_expression->get_constant_val());
					break;

				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3:
					node->set_constant_val(
						multiplicative_expression->get_constant_val()
						/ cast_expression->get_constant_val()); 
					break;

				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4:
					node->set_constant_val(
						multiplicative_expression->get_constant_val()
						% cast_expression->get_constant_val()); 
					break;

				default:
					break;

			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_multiplicative_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_additive_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{ 
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_additive_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ADDITIVE_EXPRESSION_1:
		{
			AnnotatedAstNode* multiplicative_expression
				= node->get_child();
			visit_multiplicative_expression(
				multiplicative_expression,
				file);

			const Type* additive_expression_type;
			duplicate_type(
				multiplicative_expression->get_type(), 
				additive_expression_type);
			node->set_type(
				additive_expression_type);

			node->set_symbol(
				multiplicative_expression->get_symbol());

			node->set_is_constant_evaluation(
				multiplicative_expression->get_is_constant_evaluation());
			node->set_constant_val(
				multiplicative_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ADDITIVE_EXPRESSION_2:
		case AstNodeAlt::ADDITIVE_EXPRESSION_3:
		{
			AnnotatedAstNode* additive_expression
				= node->get_child();
			AnnotatedAstNode* multiplicative_expression
				= additive_expression->get_sibling();

			visit_additive_expression(
				additive_expression,
				file);
			visit_multiplicative_expression(
				multiplicative_expression,
				file);

			/*
			2 For addition, either both operands 
			  shall have arithmetic type, or one 
			  operand shall be a pointer to an 
		 	  object type and the other shall 
			  have integer type. 
			  (Incrementing is equivalent to 
			  adding 1.)
			*/

			const Type* additive_expression_type;
			duplicate_type(
				additive_expression->get_type(), 
				additive_expression_type);
			node->set_type(
				additive_expression_type);

			bool is_constant_evaluation
				= additive_expression->get_is_constant_evaluation()
				  && multiplicative_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			
			if (is_constant_evaluation) {
				const uint64_t additive_expression_val
					= additive_expression->get_constant_val();
				const uint64_t multiplicative_expression_val
					= multiplicative_expression->get_constant_val();

				uint64_t constant_val 
					= (node->get_alt() 
					   == AstNodeAlt::ADDITIVE_EXPRESSION_2)
					  ? (additive_expression_val
					     + multiplicative_expression_val)
					  : (additive_expression_val
						  - multiplicative_expression_val);
				node->set_constant_val(
					constant_val);
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_additive_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_shift_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_shift_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::SHIFT_EXPRESSION_1:
		{
			AnnotatedAstNode* additive_expression
				= node->get_child();

			visit_additive_expression(
				additive_expression,
				file);

			const Type* shift_expression_type;
			duplicate_type(
				additive_expression->get_type(), 
				shift_expression_type);
			node->set_type(
				shift_expression_type);

			node->set_symbol(
				additive_expression->get_symbol());

			node->set_is_constant_evaluation(
				additive_expression->get_is_constant_evaluation());
			node->set_constant_val(
				additive_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::SHIFT_EXPRESSION_2:
		case AstNodeAlt::SHIFT_EXPRESSION_3:
		{
			AnnotatedAstNode* shift_expression
				= node->get_child();
			AnnotatedAstNode* additive_expression
				= shift_expression->get_sibling();

			visit_shift_expression(
				shift_expression,
				file);
			visit_additive_expression(
				additive_expression,
				file);

			const Type* shift_expression_type;
			duplicate_type(
				shift_expression->get_type(), 
				shift_expression_type);
			node->set_type(shift_expression_type);

			const uint64_t shift_expression_val
				= shift_expression->get_constant_val();
			const uint64_t additive_expression_val
				= additive_expression->get_constant_val();

			bool is_constant_evaluation
				= shift_expression->get_is_constant_evaluation()
				  && additive_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {
				uint64_t constant_value
					= (node->get_alt() 
					   == AstNodeAlt::SHIFT_EXPRESSION_2) 
					  ? (shift_expression_val
						 << additive_expression_val)
					  : (shift_expression_val
						 >> additive_expression_val);
				node->set_constant_val(
					constant_value);
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_shift_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_relational_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_relational_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::RELATIONAL_EXPRESSION_1:
		{
			AnnotatedAstNode* shift_expression
				= node->get_child();

			visit_shift_expression(
				shift_expression,
				file);

			const Type* relational_expression_type;
			duplicate_type(
				shift_expression->get_type(),
				relational_expression_type);
			node->set_type(
				relational_expression_type);

			node->set_symbol(
				shift_expression->get_symbol());

			node->set_is_constant_evaluation(
				shift_expression->get_is_constant_evaluation());
			node->set_constant_val(
				shift_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::RELATIONAL_EXPRESSION_2:
		case AstNodeAlt::RELATIONAL_EXPRESSION_3:
		case AstNodeAlt::RELATIONAL_EXPRESSION_4:
		case AstNodeAlt::RELATIONAL_EXPRESSION_5:
		{
			AnnotatedAstNode* relational_expression
				= node->get_child();
			AnnotatedAstNode* shift_expression
				= relational_expression->get_sibling();

			visit_relational_expression(
				relational_expression,
				file);
			visit_shift_expression(
				shift_expression,
				file);

			const Type* relational_expression_type
				= construct_basic_type(BasicTypeName::SIGNED_INT);
			node->set_type(
				relational_expression_type);

			const uint64_t relational_expression_val
				= relational_expression->get_constant_val();
			const uint64_t shift_expression_val
				= shift_expression->get_constant_val();

			bool is_constant_evaluation
				= relational_expression->get_is_constant_evaluation()
				  && shift_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {

				uint64_t val = 0;
				switch (node->get_alt()) {

					case AstNodeAlt::RELATIONAL_EXPRESSION_2:
					{
						val = relational_expression_val
							  < shift_expression_val;
						break;
					}

					case AstNodeAlt::RELATIONAL_EXPRESSION_3:
					{
						val = relational_expression_val
							  > shift_expression_val;
						break;
					}

					case AstNodeAlt::RELATIONAL_EXPRESSION_4:
					{
						val = relational_expression_val
							  <= shift_expression_val;
						break;
					}

					case AstNodeAlt::RELATIONAL_EXPRESSION_5:
					{
						val = relational_expression_val
							  >= shift_expression_val;
						break;
					}

					default:
						val = 0;
						break;
				}
				node->set_constant_val(
					val);
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_relational_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_equality_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_equality_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::EQUALITY_EXPRESSION_1:
		{
			AnnotatedAstNode* relational_expression
				= node->get_child();

			visit_relational_expression(
				relational_expression,
				file);

			const Type* equality_expression_type; 
			duplicate_type(
				relational_expression->get_type(), 
				equality_expression_type);
			node->set_type(
				equality_expression_type);

			node->set_symbol(
				relational_expression->get_symbol());

			node->set_is_constant_evaluation(
				relational_expression->get_is_constant_evaluation());
			node->set_constant_val(
				relational_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EQUALITY_EXPRESSION_2:
		case AstNodeAlt::EQUALITY_EXPRESSION_3:
		{
			AnnotatedAstNode* equality_expression
				= node->get_child();
			AnnotatedAstNode* relational_expression
				= equality_expression->get_sibling();

			visit_equality_expression(
				equality_expression,
				file);
			visit_relational_expression(
				relational_expression,
				file);

			const Type* equality_expression_type;
			duplicate_type(
				equality_expression->get_type(), 
				equality_expression_type);
			node->set_type(equality_expression_type);

			const uint64_t equality_expression_val
				= equality_expression->get_constant_val();
			const uint64_t relational_expression_val
				= relational_expression->get_constant_val();

			bool is_constant_evaluation
				= equality_expression->get_is_constant_evaluation()
				  && relational_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);

			if (is_constant_evaluation) {

				switch (node->get_alt()) {

					case AstNodeAlt::EQUALITY_EXPRESSION_2:
						if (equality_expression_val
							== relational_expression_val) {
							node->set_constant_val(1);
						} else {
							node->set_constant_val(0);
						}
						break;

					case AstNodeAlt::EQUALITY_EXPRESSION_3:
						if (equality_expression_val
							!= relational_expression_val) {
							node->set_constant_val(0);
						} else {
							node->set_constant_val(1);
						}
						break;

					default:
						break;
				}
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}	
	report_exit("visit_equality_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_and_expression(
	AnnotatedAstNode* const& and_expression,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_and_expression_1");

	switch (and_expression->get_alt()) {

		case AstNodeAlt::AND_EXPRESSION_1:
		{
			AnnotatedAstNode* equality_expression
				= and_expression->get_child();

			visit_equality_expression(
				equality_expression,
				file);

			const Type* and_expression_type;
			duplicate_type(
				equality_expression->get_type(), 
				and_expression_type);
			and_expression->set_type(
				and_expression_type);

			and_expression->set_symbol(
				equality_expression->get_symbol());

			and_expression->set_is_constant_evaluation(
				equality_expression->get_is_constant_evaluation());
			and_expression->set_constant_val(
				equality_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::AND_EXPRESSION_2:
		{
			AnnotatedAstNode* lower_and_expression
				= and_expression->get_child();
			AnnotatedAstNode* equality_expression
				= lower_and_expression->get_sibling();

			visit_and_expression(
				lower_and_expression,
				file);
			visit_equality_expression(
				equality_expression,
				file);

			const Type* equality_expression_type;
			duplicate_type(
				equality_expression->get_type(), 
				equality_expression_type);
			and_expression->set_type(
				equality_expression_type);

			bool is_constant_evaluation
				= lower_and_expression->get_is_constant_evaluation()
				  && equality_expression->get_is_constant_evaluation();
			and_expression->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {

				uint64_t lower_and_expression_constant_val
					= lower_and_expression->get_constant_val();
				uint64_t equality_expression_constant_val
					= equality_expression->get_constant_val();
				and_expression->set_constant_val(
					lower_and_expression_constant_val
					& equality_expression_constant_val);
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_and_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_exclusive_or_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_exclusive_or_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1:
		{
			AnnotatedAstNode* and_expression
				= node->get_child();

			visit_and_expression(
				and_expression,
				file);

			const Type* exclusive_or_expression_type;
			duplicate_type(
				and_expression->get_type(), 
				exclusive_or_expression_type);
			node->set_type(
				exclusive_or_expression_type);

			node->set_symbol(
				and_expression->get_symbol());

			node->set_is_constant_evaluation(
				and_expression->get_is_constant_evaluation());
			node->set_constant_val(
				and_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2:
		{
			AnnotatedAstNode* exclusive_or_expression
				= node->get_child();
			AnnotatedAstNode* and_expression
				= exclusive_or_expression->get_sibling();

			visit_and_expression(
				and_expression,
				file);

			const Type* exclusive_or_expression_type;
			duplicate_type(
				exclusive_or_expression->get_type(), 
				exclusive_or_expression_type);
			node->set_type(
				exclusive_or_expression_type);

			bool is_constant_evaluation
				= exclusive_or_expression->get_is_constant_evaluation()
				  && and_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {
				node->set_constant_val(
					exclusive_or_expression->get_constant_val()
					^ and_expression->get_constant_val());
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_exclusive_or_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_inclusive_or_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_inclusive_or_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_1:
		{
			AnnotatedAstNode* exclusive_or_expression
				= node->get_child();

			visit_exclusive_or_expression(
				exclusive_or_expression,
				file);

			const Type* inclusive_or_expression_type;
			duplicate_type(
				exclusive_or_expression->get_type(), 
				inclusive_or_expression_type);
			node->set_type(
				inclusive_or_expression_type);

			node->set_symbol(
				exclusive_or_expression->get_symbol());

			node->set_is_constant_evaluation(
				exclusive_or_expression->get_is_constant_evaluation());
			node->set_constant_val(
				exclusive_or_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_2:
		{
			AnnotatedAstNode* inclusive_or_expression
				= node->get_child();
			AnnotatedAstNode* exclusive_or_expression
				= inclusive_or_expression->get_sibling();

			visit_inclusive_or_expression(
				inclusive_or_expression,
				file);
			visit_exclusive_or_expression(
				exclusive_or_expression,
				file);

			const Type* exclusive_or_expression_type;
			duplicate_type(
				exclusive_or_expression->get_type(), 
				exclusive_or_expression_type);
			node->set_type(
				exclusive_or_expression_type);

			bool is_constant_evaluation
				= inclusive_or_expression->get_is_constant_evaluation()
				  | exclusive_or_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				exclusive_or_expression->get_is_constant_evaluation());
			if (is_constant_evaluation) {
				node->set_constant_val(
					inclusive_or_expression->get_constant_val()
					| exclusive_or_expression->get_constant_val());
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_visit("visit_inclusive_or_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_logical_and_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_logical_and_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_1:
		{
			AnnotatedAstNode* inclusive_or_expression
				= node->get_child();

			visit_inclusive_or_expression(
				inclusive_or_expression,
				file);

			const Type* logical_and_expression_type;
			duplicate_type(
				inclusive_or_expression->get_type(), 
				logical_and_expression_type);
			node->set_type(
				logical_and_expression_type);

			node->set_symbol(
				inclusive_or_expression->get_symbol());

			bool is_constant_evaluation
				= inclusive_or_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			node->set_constant_val(
				inclusive_or_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_2:
		{
			AnnotatedAstNode* logical_and_expression
				= node->get_child();
			AnnotatedAstNode* inclusive_or_expression
				= logical_and_expression->get_sibling();

			visit_logical_and_expression(
				logical_and_expression,
				file);

			const Type* logical_and_expression_type;
			duplicate_type(
				logical_and_expression->get_type(), 
				logical_and_expression_type);
			node->set_type(
				logical_and_expression_type);


			bool is_constant_evaluation
				= logical_and_expression->get_is_constant_evaluation()
				  && inclusive_or_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {
				node->set_constant_val(
					logical_and_expression->get_constant_val()
					&& inclusive_or_expression->get_constant_val());
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_logical_and_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_logical_or_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_logical_or_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::LOGICAL_OR_EXPRESSION_1:
		{
			AnnotatedAstNode* logical_and_expression
				= node->get_child();

			visit_logical_and_expression(
				logical_and_expression,
				file);

			const Type* logical_or_expression_type;
			duplicate_type(
				logical_and_expression->get_type(), 
				logical_or_expression_type);
			node->set_type(
				logical_or_expression_type);

			node->set_is_constant_evaluation(
				logical_and_expression->get_is_constant_evaluation());
			node->set_constant_val(
				logical_and_expression->get_constant_val());

			node->set_symbol(
				logical_and_expression->get_symbol());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LOGICAL_OR_EXPRESSION_2:
		{
			AnnotatedAstNode* logical_or_expression
				= node->get_child();
			AnnotatedAstNode* logical_and_expression
				= logical_or_expression->get_sibling();

			visit_logical_or_expression(
				logical_or_expression,
				file);
			visit_logical_and_expression(
				logical_and_expression,
				file);

			const Type* logical_or_expression_type;
			duplicate_type(
				logical_or_expression->get_type(), 
				logical_or_expression_type);
			node->set_type(
				logical_or_expression_type);
			
			bool is_constant_evaluation
				= logical_or_expression->get_is_constant_evaluation()
				  || logical_and_expression->get_is_constant_evaluation();
			if (is_constant_evaluation) {
				node->set_constant_val(
					logical_or_expression->get_constant_val()
					|| logical_and_expression->get_constant_val());
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_logical_or_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_assignment_operator(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_assignment_operator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ASSIGNMENT_OPERATOR_1:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_2:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_3:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_4:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_5:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_6:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_7:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_8:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_9:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_10:
		case AstNodeAlt::ASSIGNMENT_OPERATOR_11:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		default:
			break;

	}
	report_exit("visit_assignment_operator_1");

	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_1:
		{
			AnnotatedAstNode* assignment_expression
				= node->get_child();

			visit_assignment_expression(
				assignment_expression,
				file);

			const Type* expression_type;
			duplicate_type(
				assignment_expression->get_type(), 
				expression_type);
			node->set_type(
				expression_type);

			node->set_symbol(
				assignment_expression->get_symbol());

			node->set_is_constant_evaluation(
				assignment_expression->get_is_constant_evaluation());
			node->set_constant_val(
				assignment_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXPRESSION_2:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			AnnotatedAstNode* assignment_expression
				= expression->get_sibling();

			visit_expression(
				expression,
				file);
			visit_assignment_expression(
				assignment_expression,
				file);

			const Type* expression_type;
			duplicate_type(
				assignment_expression->get_type(), 
				expression_type);
			node->set_type(
				expression_type);

			node->set_is_constant_evaluation(
				assignment_expression->get_is_constant_evaluation());
			node->set_constant_val(
				assignment_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_conditional_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_conditional_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::CONDITIONAL_EXPRESSION_1:
		{
			AnnotatedAstNode* logical_or_expression
				= node->get_child();

			visit_logical_or_expression(
				logical_or_expression,
				file);

			const Type* conditional_expression_type;
			duplicate_type(
				logical_or_expression->get_type(), 
				conditional_expression_type);
			node->set_type(
				conditional_expression_type);

			node->set_symbol(
				logical_or_expression->get_symbol());

			node->set_is_constant_evaluation(
				logical_or_expression->get_is_constant_evaluation());
			node->set_constant_val(
				logical_or_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::CONDITIONAL_EXPRESSION_2:
		{
			AnnotatedAstNode* logical_or_expression
				= node->get_child();
			AnnotatedAstNode* expression
				= logical_or_expression->get_sibling();
			AnnotatedAstNode* conditional_expression
				= expression->get_sibling();

			visit_logical_or_expression(
				logical_or_expression,
				file);
			visit_expression(
				expression,
				file);
			visit_conditional_expression(
				conditional_expression,
				file);

			// TODO; Gather type.
			bool constant_evaluation
				= logical_or_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(constant_evaluation);
			if (constant_evaluation) {
				node->set_constant_val(
					expression->get_constant_val());

			} else {
				node->set_constant_val(
					conditional_expression->get_constant_val());
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_conditional_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_assignment_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_assignment_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ASSIGNMENT_EXPRESSION_1:
		{
			AnnotatedAstNode* conditional_expression
				= node->get_child();

			visit_conditional_expression(
				conditional_expression,
				file);

			const Type* assignment_expression_type;
			duplicate_type(
				conditional_expression->get_type(), 
				assignment_expression_type);
			node->set_type(
				assignment_expression_type);

			node->set_symbol(
				conditional_expression->get_symbol());

			node->set_is_constant_evaluation(
				conditional_expression->get_is_constant_evaluation());
			node->set_constant_val(
				conditional_expression->get_constant_val());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ASSIGNMENT_EXPRESSION_2:
		{
			AnnotatedAstNode* unary_expression
				= node->get_child();
			AnnotatedAstNode* assignment_operator
				= unary_expression->get_sibling();
			AnnotatedAstNode* assignment_expression
				= assignment_operator->get_sibling();

			visit_unary_expression(
				unary_expression,
				file);
			visit_assignment_operator(
				assignment_operator);
			visit_assignment_expression(
				assignment_expression,
				file);

			const Type* assignment_expression_type;
			duplicate_type(
				assignment_expression->get_type(), 
				assignment_expression_type);
			node->set_type(
				assignment_expression_type);

			node->set_is_constant_evaluation(
				false);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_assignment_expression_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_constant_expression(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_constant_expression_1");

	switch (node->get_alt()) {

		case AstNodeAlt::CONSTANT_EXPRESSION_1:
		{
			AnnotatedAstNode* conditional_expression
				= node->get_child();

			visit_conditional_expression(
				conditional_expression,
				file);

			const Type* constant_expression_type;
			duplicate_type(
				conditional_expression->get_type(), 
				constant_expression_type);
			node->set_type(
				constant_expression_type);

			node->set_symbol(
				conditional_expression->get_symbol());
			bool is_constant_evaluation
				= conditional_expression->get_is_constant_evaluation();
			node->set_is_constant_evaluation(
				is_constant_evaluation);
			if (is_constant_evaluation) {
				node->set_constant_val(
					conditional_expression->get_constant_val());
			} else {
				/* Semantic Error on non-constant constant expression. */
				break;
			}
			

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_declaration(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_declaration_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_1:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* init_declarator_list
				= declaration_specifiers->get_sibling();

			const Type* declaration_specifiers_type;
			visit_declaration_specifiers(
				declaration_specifiers,
				declaration_specifiers_type);

			if (init_declarator_list) {
				visit_init_declarator_list(
					init_declarator_list,
					file,
					declaration_scope,
					declaration_specifiers_type);
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_declaration_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_storage_class_specifier(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_storage_class_specifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STORAGE_CLASS_SPECIFIER_1:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STORAGE_CLASS_SPECIFIER_2:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STORAGE_CLASS_SPECIFIER_3:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STORAGE_CLASS_SPECIFIER_4:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STORAGE_CLASS_SPECIFIER_5:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_storage_class_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_type_specifier(
	AnnotatedAstNode* const& node,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_type_specifier_1");

	const Type* type_specifier_type = NULL;

	switch (node->get_alt()) {

		/* incomplete type. */
		case AstNodeAlt::TYPE_SPECIFIER_1:
		{	
			type_specifier_type = construct_void_type();
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		/* basic type. */
		case AstNodeAlt::TYPE_SPECIFIER_2:
		case AstNodeAlt::TYPE_SPECIFIER_3:
		case AstNodeAlt::TYPE_SPECIFIER_4:
		case AstNodeAlt::TYPE_SPECIFIER_5:
		case AstNodeAlt::TYPE_SPECIFIER_6:
		case AstNodeAlt::TYPE_SPECIFIER_7:
		case AstNodeAlt::TYPE_SPECIFIER_8:
		case AstNodeAlt::TYPE_SPECIFIER_9:
		case AstNodeAlt::TYPE_SPECIFIER_10:
		case AstNodeAlt::TYPE_SPECIFIER_11:
		{			
			BasicTypeName basic_type_name;
			bool should_generate = true;
			switch (node->get_alt()) {

				case AstNodeAlt::TYPE_SPECIFIER_2:
					basic_type_name = BasicTypeName::SIGNED_CHAR;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_3:
					basic_type_name = BasicTypeName::SIGNED_SHORT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_4:
					basic_type_name = BasicTypeName::SIGNED_INT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_5:
					basic_type_name = BasicTypeName::SIGNED_LONG; 
					break;

				case AstNodeAlt::TYPE_SPECIFIER_6:
					basic_type_name = BasicTypeName::FLOAT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_7:
					basic_type_name = BasicTypeName::DOUBLE;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_8:
					//TODO;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_9:
					//TODO;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_10:
					basic_type_name = BasicTypeName::BOOL;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_11:
					basic_type_name = BasicTypeName::COMPLEX;
					break;

				default:
					should_generate = false;
					break;

			}
			if (should_generate) {
				type_specifier_type = construct_basic_type(
					basic_type_name,
					TypeQualifiers::UNQUALIFIED);

				exitcode = SemanticAnnotatorExitCode::SUCCESS;
			}
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_12:
		{
			AnnotatedAstNode* struct_or_union_specifier
				= node->get_child();

			visit_struct_or_union_specifier(
				struct_or_union_specifier);

			duplicate_type(
				struct_or_union_specifier->get_type(),
				type_specifier_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_13:
		{
			AnnotatedAstNode* enum_specifier
				= node->get_child();

			visit_enum_specifier(
				enum_specifier);

			duplicate_type(
				enum_specifier->get_type(),
				type_specifier_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_14:
		{
			AnnotatedAstNode* typedef_name
				= node->get_child();

			visit_typedef_name(
				typedef_name);

			duplicate_type(
				typedef_name->get_type(),
				type_specifier_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	synthesized_type = type_specifier_type;
	report_exit("visit_type_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_function_specifier(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_function_specifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::FUNCTION_SPECIFIER_1:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_declaration_specifiers(
	AnnotatedAstNode* const& node,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_declaration_specifiers_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_SPECIFIERS_1:
		{
			AnnotatedAstNode* storage_class_specifier
				= node->get_child();
			AnnotatedAstNode* declaration_specifiers
				= storage_class_specifier->get_sibling();

			visit_storage_class_specifier(
				storage_class_specifier);
			if (declaration_specifiers) {  
				/* TODO; pass storage class specifier */

				const Type* declaration_specifiers_type;
				visit_declaration_specifiers(
					declaration_specifiers,
					declaration_specifiers_type);

				const Type* higher_declaration_specifiers_type;
				duplicate_type(
					declaration_specifiers_type,
					higher_declaration_specifiers_type);
				
				synthesized_type = declaration_specifiers_type;
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DECLARATION_SPECIFIERS_2:
		{
			AnnotatedAstNode* type_specifier
				= node->get_child();
			AnnotatedAstNode* declaration_specifiers
				= type_specifier->get_sibling();

			const Type* type_specifier_type;
			visit_type_specifier(
				type_specifier,
				type_specifier_type);

			const Type* declaration_specifiers_type;
			if (declaration_specifiers) {
				// TODO pass type-specifier
				visit_declaration_specifiers(
					declaration_specifiers,
					declaration_specifiers_type);
			}

			duplicate_type(
				type_specifier_type,
				declaration_specifiers_type);

			synthesized_type = declaration_specifiers_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DECLARATION_SPECIFIERS_3:
		{
			AnnotatedAstNode* type_qualifier
				= node->get_child();
			AnnotatedAstNode* declaration_specifiers
				= type_qualifier->get_sibling();

			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;
			visit_type_qualifier(
				type_qualifier,
				type_qualifiers);

			if (declaration_specifiers) {
				/* TODO; pass type-qualifier */				
				const Type* declaration_specifiers_type;
				visit_declaration_specifiers(
					declaration_specifiers,
					declaration_specifiers_type);

				const Type* higher_declaration_specifiers_type;
				duplicate_type(
					declaration_specifiers_type,
					higher_declaration_specifiers_type);

				synthesized_type 
					= higher_declaration_specifiers_type;
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DECLARATION_SPECIFIERS_4:
		{
			AnnotatedAstNode* function_specifier
				= node->get_child();
			AnnotatedAstNode* declaration_specifiers
				= function_specifier->get_sibling();
			visit_function_specifier(
				function_specifier);

			if (declaration_specifiers) {
				/* TODO; function specifier.*/			    
				const Type* declaration_specifiers_type;
				visit_declaration_specifiers(
					declaration_specifiers,
					declaration_specifiers_type);

			    const Type* higher_declaration_specifiers_type;
				duplicate_type(
					declaration_specifiers_type,
					higher_declaration_specifiers_type);

				synthesized_type 
					= declaration_specifiers_type;
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_function_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_init_declarator(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_init_declarator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_1:
		{
			AnnotatedAstNode* declarator
				= node->get_child();

			const AnnotatedAstNode* unused_parameter_type_list = NULL;

			const Type* declarator_type;
			visit_declarator(
				declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				unused_parameter_type_list,
				declarator_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INIT_DECLARATOR_2:
		{
			AnnotatedAstNode* declarator
				= node->get_child();
			AnnotatedAstNode* initializer
				= declarator->get_sibling();

			const AnnotatedAstNode* unused_parameter_type_list = NULL;

			const Type* declarator_type;
			visit_declarator(
				declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				unused_parameter_type_list,
				declarator_type);
			visit_initializer(
				initializer,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_init_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_init_declarator_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_init_declarator_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_LIST_1:
		{
			AnnotatedAstNode* init_declarator
				= node->get_child();

			visit_init_declarator(
				init_declarator,
				declaration_scope,
				declaration_specifier_type,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INIT_DECLARATOR_LIST_2:
		{
			AnnotatedAstNode* init_declarator_list
				= node->get_child();
			AnnotatedAstNode* init_declarator
				= init_declarator_list->get_sibling();

			visit_init_declarator_list(
				init_declarator_list,
				file,
				declaration_scope,
				declaration_specifier_type);
			visit_init_declarator(
				init_declarator,
				declaration_scope,
				declaration_specifier_type,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_init_declarator_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_enum_specifier(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_enum_specifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::TYPE_SPECIFIER_1:
		case AstNodeAlt::TYPE_SPECIFIER_2:
		case AstNodeAlt::TYPE_SPECIFIER_3:
		case AstNodeAlt::TYPE_SPECIFIER_4:
		case AstNodeAlt::TYPE_SPECIFIER_5:
		case AstNodeAlt::TYPE_SPECIFIER_6:
		case AstNodeAlt::TYPE_SPECIFIER_7:
		case AstNodeAlt::TYPE_SPECIFIER_8:
		case AstNodeAlt::TYPE_SPECIFIER_9:
		case AstNodeAlt::TYPE_SPECIFIER_10:
		case AstNodeAlt::TYPE_SPECIFIER_11:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_12:
		{
			AnnotatedAstNode* struct_or_union_specifier
				= node->get_child();
			visit_struct_or_union_specifier(
				struct_or_union_specifier);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_13:
		{
			AnnotatedAstNode* enum_specifier
				= node->get_child();
			visit_enum_specifier(
				enum_specifier);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_14:
		{
			AnnotatedAstNode* typedef_name
				= node->get_child();
			visit_typedef_name(
				typedef_name);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_enum_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_typedef_name(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_typedef_name_1");

	switch (node->get_alt()) {

		case AstNodeAlt::TYPEDEF_NAME_1:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;


		default:
			break;

	}
	report_exit("visit_typedef_name_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_or_union_specifier(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_or_union_specifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_OR_UNION_SPECIFIER_1:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STRUCT_OR_UNION_SPECIFIER_2:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_struct_or_union_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_or_union(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_or_union_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_OR_UNION_1:
		case AstNodeAlt::STRUCT_OR_UNION_2:
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;

		default:
			break;

	}
	report_exit("visit_struct_or_union_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_declaration_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_declaration_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_DECLARATION_LIST_1:
		{
			AnnotatedAstNode* struct_declaration
				= node->get_child();
			visit_struct_declaration(
				struct_declaration,
				file,
				declaration_scope);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STRUCT_DECLARATION_LIST_2:
		{
			AnnotatedAstNode* struct_declaration_list
				= node->get_child();
			AnnotatedAstNode* struct_declaration
				= struct_declaration_list->get_sibling();
			visit_struct_declaration_list(
				struct_declaration_list,
				file,
				declaration_scope);
			visit_struct_declaration(
				struct_declaration,
				file,
				declaration_scope);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_struct_declaration_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_declaration(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& declaration_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_declaration_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_DECLARATION_1:
		{
			AnnotatedAstNode* specifier_qualifier_list
				= node->get_child();
			AnnotatedAstNode* struct_declarator_list
				= specifier_qualifier_list->get_sibling();
			
			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;

			const Type* specifier_qualifier_list_type;
			visit_specifier_qualifier_list(
				specifier_qualifier_list,
				specifier_qualifier_list_type);

			//qualify_type(
				//synthesized_type, 
				//type_qualifiers);

			visit_struct_declarator_list(
				struct_declarator_list,
				declaration_scope,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_struct_declaration_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_specifier_qualifier_list(
	AnnotatedAstNode* const& node,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_specifier_qualifier_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::SPECIFIER_QUALIFIER_LIST_1:
		{
			AnnotatedAstNode* type_specifier
				= node->get_child();
			AnnotatedAstNode* specifier_qualifier_list
				= type_specifier->get_sibling();

			const Type* type_specifier_type;
			visit_type_specifier(
				type_specifier,
				type_specifier_type);
				
			if (specifier_qualifier_list) {
				visit_specifier_qualifier_list(
					specifier_qualifier_list,
					synthesized_type);
			}

			const Type* specifier_qualifier_list_type;
			duplicate_type(
				type_specifier_type,
				specifier_qualifier_list_type);
			synthesized_type = specifier_qualifier_list_type;
			
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::SPECIFIER_QUALIFIER_LIST_2:
		{
			AnnotatedAstNode* type_qualifier
				= node->get_child();
			AnnotatedAstNode* specifier_qualifier_list
				= type_qualifier->get_sibling();

			TypeQualifiers type_qualifiers = TypeQualifiers::UNQUALIFIED;
			visit_type_qualifier(
				type_qualifier,
				type_qualifiers);

			const Type* specifier_qualifier_list_type;
			if (specifier_qualifier_list) {
				visit_specifier_qualifier_list(
					type_qualifier,
					specifier_qualifier_list_type);
			}

			const Type* higher_specifier_qualifier_list_type;
			duplicate_type(
				higher_specifier_qualifier_list_type,
				specifier_qualifier_list_type);
			synthesized_type = specifier_qualifier_list_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_specifier_qualifier_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_declarator_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& declaration_scope,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_declarator_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_DECLARATOR_LIST_1:
		{
			AnnotatedAstNode* struct_declarator
				= node->get_child();
			const Type* type = NULL;
			visit_struct_declarator(
				struct_declarator,
				declaration_scope,
				type,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STRUCT_DECLARATOR_LIST_2:
		{
			AnnotatedAstNode* struct_declarator_list
				= node->get_child();
			AnnotatedAstNode* struct_declarator
				= struct_declarator->get_sibling();
			const Type* type = NULL;
			visit_struct_declarator_list(
				struct_declarator_list,
				declaration_scope,
				file);
			visit_struct_declarator(
				struct_declarator,
				declaration_scope,
				type,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_struct_declarator_list_1");

	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_struct_declarator(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& declaration_scope,
	const Type*       const& declaration_specifier_type,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_struct_declarator_1");
	
	switch (node->get_alt()) {

		case AstNodeAlt::STRUCT_DECLARATOR_LIST_1:
		{
			AnnotatedAstNode* declarator
				= node->get_child();

			const AnnotatedAstNode* unused_parameter_type_list = NULL;

			const Type* declarator_type;
			visit_declarator(
				declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				unused_parameter_type_list,
				declarator_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STRUCT_DECLARATOR_LIST_2:
		{
			AnnotatedAstNode* declarator
				= (node->get_child()->get_name()
					== AstNodeName::DECLARATOR)
				? node->get_child()
				: NULL;
			AnnotatedAstNode* constant_expression
				= declarator
				? declarator->get_sibling()
				: node->get_child();

			const AnnotatedAstNode* unused_parameter_type_list = NULL;

			if (declarator) {
				const Type* declarator_type;
				visit_declarator(
					declarator,
					file,
					declaration_scope,
					declaration_scope,
					declaration_specifier_type,
					unused_parameter_type_list,
					declarator_type);
			}
			visit_constant_expression(
				constant_expression,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_struct_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_enumerator(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_enumerator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ENUMERATOR_LIST_1:
		{
			AnnotatedAstNode* enumerator
				= node->get_child();
			visit_enumerator(
				enumerator);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ENUMERATOR_LIST_2:
		{
			AnnotatedAstNode* enumerator_list
				= node->get_child();
			AnnotatedAstNode* enumerator
				= enumerator_list->get_sibling();
			visit_enumerator_list(
				enumerator_list);
			visit_enumerator(
				enumerator);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_enumerator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_enumerator_list(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_enumerator_list_1");
	
	switch (node->get_alt()) {

		case AstNodeAlt::ENUMERATOR_LIST_1:
		{
			AnnotatedAstNode* enumerator
				= node->get_child();
			visit_enumerator(
				enumerator);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ENUMERATOR_LIST_2:
		{
			AnnotatedAstNode* enumerator_list
				= node->get_child();
			AnnotatedAstNode* enumerator
				= enumerator_list->get_sibling();
			visit_enumerator_list(
				enumerator_list);
			visit_enumerator(
				enumerator);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_enumerator_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_enumeration_specifier(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_enumeration_specifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ENUM_SPECIFIER_1:
		case AstNodeAlt::ENUM_SPECIFIER_2:
		{
			AnnotatedAstNode* identifier
				= (node->get_child()->get_name()
					== AstNodeName::IDENTIFIER)
				? node->get_child()
				: NULL;
			AnnotatedAstNode* enumerator_list
				= node->get_child();
			visit_enumerator_list(
				enumerator_list);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ENUM_SPECIFIER_3:
		{
			AnnotatedAstNode* identifier
				= node->get_child();
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_enumeration_specifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_type_qualifier(
	AnnotatedAstNode* const& node,
	TypeQualifiers         & type_qualifiers)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_type_qualifier_1");

	switch (node->get_alt()) {

		case AstNodeAlt::TYPE_QUALIFIER_1:
		{
			switch (type_qualifiers) {

				case TypeQualifiers::CONST:
				case TypeQualifiers::CONST_VOLATILE:
				case TypeQualifiers::CONST_RESTRICT:
				case TypeQualifiers::CONST_VOLATILE_RESTRICT:					
					break;

				case TypeQualifiers::UNQUALIFIED:
					type_qualifiers = TypeQualifiers::CONST;
					break;

				case TypeQualifiers::VOLATILE:
					type_qualifiers = TypeQualifiers::CONST_VOLATILE;
					break;

				case TypeQualifiers::VOLATILE_RESTRICT:
					type_qualifiers = TypeQualifiers::CONST_VOLATILE_RESTRICT;
					break;

				case TypeQualifiers::RESTRICT:
					type_qualifiers = TypeQualifiers::CONST_RESTRICT;
					break;

				default:
					break;

			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_QUALIFIER_2:
		{
			switch (type_qualifiers) {

				case TypeQualifiers::RESTRICT:
				case TypeQualifiers::VOLATILE_RESTRICT:
				case TypeQualifiers::CONST_RESTRICT:
				case TypeQualifiers::CONST_VOLATILE_RESTRICT:
					break;

				case TypeQualifiers::UNQUALIFIED:
					type_qualifiers = TypeQualifiers::RESTRICT;
					break;

				case TypeQualifiers::CONST:
					type_qualifiers = TypeQualifiers::CONST_RESTRICT;
					break;

				case TypeQualifiers::CONST_VOLATILE:
					type_qualifiers = TypeQualifiers::CONST_VOLATILE_RESTRICT;
					break;

				case TypeQualifiers::VOLATILE:
					type_qualifiers = TypeQualifiers::VOLATILE_RESTRICT;
					break;

				default:
					break;

			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_QUALIFIER_3:
		{
			switch (type_qualifiers) {

				case TypeQualifiers::VOLATILE:
				case TypeQualifiers::VOLATILE_RESTRICT:
				case TypeQualifiers::CONST_VOLATILE_RESTRICT:
				case TypeQualifiers::CONST_VOLATILE:
					break;

				case TypeQualifiers::RESTRICT:
					type_qualifiers = TypeQualifiers::VOLATILE_RESTRICT;
					break;
				
				case TypeQualifiers::CONST_RESTRICT:
					type_qualifiers = TypeQualifiers::CONST_VOLATILE_RESTRICT;
					break;
				
				case TypeQualifiers::UNQUALIFIED:
					type_qualifiers = TypeQualifiers::VOLATILE;
					break;

				case TypeQualifiers::CONST:
					type_qualifiers = TypeQualifiers::CONST_VOLATILE;
					break;

				default:
					break;

			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}  
	report_exit("visit_type_qualifier_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_declarator(
	AnnotatedAstNode*       const& node,
	SymbolTable*            const& file,
	SymbolTable*            const& declaration_scope,
	SymbolTable*            const& parameter_type_list_scope,
	const Type*             const& declaration_specifier_type,
	const AnnotatedAstNode*      & parameter_list,
	const Type*					 & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_declarator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATOR_1:
		{
			AnnotatedAstNode* pointer
				= (node->get_child()->get_name()
					== AstNodeName::POINTER)
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* direct_declarator
				= pointer
				  ? pointer->get_sibling()
				  : node->get_child();

			const Type* pointer_type = NULL;
			if (pointer) {
				visit_pointer(
					node,
					declaration_specifier_type,
					pointer_type);
			}
			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				parameter_type_list_scope,
				pointer_type ? pointer_type : declaration_specifier_type,
				parameter_list,
				direct_declarator_type);

			node->set_symbol(
				direct_declarator->get_symbol());

			const Type* declarator_type;
			duplicate_type(
				direct_declarator_type,
				declarator_type);
			synthesized_type = declarator_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_direct_declarator(
	AnnotatedAstNode*		const& node,
	SymbolTable*            const& file,
	SymbolTable*            const& declaration_scope,
	SymbolTable*            const& parameter_type_list_scope,
	const Type*             const& declaration_specifier_type,
	const AnnotatedAstNode*      & parameter_list,
	const Type*                  & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_direct_declarator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DIRECT_DECLARATOR_1:  
			{
				AnnotatedAstNode* identifier
					= node->get_child();

				const Token* identifier_terminal
					= identifier->get_terminal();
				const char* identifier_lexeme
					= identifier_terminal->get_lexeme();
				declaration_scope->add_entry(
					identifier_lexeme);
				SymbolTableEntry* e
					= declaration_scope->get_entry(identifier_lexeme);

				duplicate_type(declaration_specifier_type, e->type);
				node->set_symbol(identifier_lexeme);
				synthesized_type = declaration_specifier_type;

				if (is_object_type(declaration_specifier_type)) {
					e->identifier_type = IdentifierClassifier::OBJECT;
				} else if (is_function_type(declaration_specifier_type)) {
					e->identifier_type = IdentifierClassifier::FUNCTION;
				}

				exitcode = SemanticAnnotatorExitCode::SUCCESS;
				break;
			}

		case AstNodeAlt::DIRECT_DECLARATOR_2:
		{
			AnnotatedAstNode* declarator
				= node->get_child();

			const Type* declarator_type;
			visit_declarator(
				declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				declarator_type);

			const Type* direct_declarator_type;
			duplicate_type(
				declarator_type, 
				direct_declarator_type);
			synthesized_type = direct_declarator_type;

			node->set_symbol(declarator->get_symbol());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_3:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* type_qualifier_list
				= direct_declarator->get_sibling()
				  ? (direct_declarator->get_sibling()->get_name()
					 == AstNodeName::TYPE_QUALIFIER_LIST
					 ? direct_declarator->get_sibling()
					 : NULL)
				  : NULL;
			AnnotatedAstNode* assignment_expression
				= type_qualifier_list
				  ? type_qualifier_list->get_sibling()
				  : direct_declarator->get_sibling();

			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				direct_declarator_type);

			TypeQualifiers type_qualifiers 
				= TypeQualifiers::UNQUALIFIED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}
			if (assignment_expression) {
				visit_assignment_expression(
					assignment_expression,
					file);
			}
			node->set_symbol(direct_declarator->get_symbol());

			// TODO; Gather type
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_4:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* type_qualifier_list
				= direct_declarator->get_sibling()
				  ? (direct_declarator->get_sibling()->get_name()
					  == AstNodeName::TYPE_QUALIFIER_LIST
					  ? direct_declarator->get_sibling()
					  : NULL)
		 		  : NULL;
			AnnotatedAstNode* assignment_expression
				= type_qualifier_list
				  ? type_qualifier_list->get_sibling()
				  : direct_declarator->get_sibling();

			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				direct_declarator_type);

			TypeQualifiers type_qualifiers 
				= TypeQualifiers::UNDEFINED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}
			visit_assignment_expression(
				assignment_expression,
				file);

			node->set_symbol(
				direct_declarator->get_symbol());
			// TODO; Gather type

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_5:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* type_qualifier_list
				= direct_declarator->get_sibling()
				  ? (direct_declarator->get_sibling()->get_name()
				     == AstNodeName::TYPE_QUALIFIER_LIST
					 ? direct_declarator->get_sibling()
					 : NULL)
				  : NULL;
			AnnotatedAstNode* assignment_expression
				= type_qualifier_list
				  ? type_qualifier_list->get_sibling()
				  : direct_declarator->get_sibling();

			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				direct_declarator_type);

			TypeQualifiers type_qualifiers = TypeQualifiers::UNQUALIFIED;
			visit_type_qualifier_list(
				type_qualifier_list,
				type_qualifiers);
			// TODO;

			visit_assignment_expression(
				assignment_expression,
				file);

			node->set_symbol(
				direct_declarator->get_symbol());

			// TODO; Gather type
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_6:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* type_qualifier_list
				= direct_declarator->get_sibling()
				  ? (direct_declarator->get_sibling()->get_name()
					 == AstNodeName::TYPE_QUALIFIER_LIST
					? direct_declarator->get_sibling()
				  	: NULL)
				  : NULL;

			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				direct_declarator_type);

			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}

			node->set_symbol(
				direct_declarator->get_symbol());
			// TODO; Gather type
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_7:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* parameter_type_list
				= direct_declarator->get_sibling();

			visit_parameter_type_list(
				parameter_type_list,
				file,
				parameter_type_list_scope);
			
			parameter_list = parameter_type_list->get_child();

			const Type* return_type;
			duplicate_type(
				declaration_specifier_type,
				return_type);

			const Parameter* parameters_type;
			int number_of_parameters
				= convert_parameter_list_to_parameter_type(
					parameter_list,
					parameters_type);

			const Type* function_type
				= construct_function_type(
					return_type,
					number_of_parameters,
					parameters_type);
			
			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				function_type,
				parameter_list,
				direct_declarator_type);

			synthesized_type 
				= function_type;

			node->set_symbol(
				direct_declarator->get_symbol());

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_8:
		{
			AnnotatedAstNode* direct_declarator
				= node->get_child();
			AnnotatedAstNode* identifier_list
				= direct_declarator->get_sibling();

			const Type* direct_declarator_type;
			visit_direct_declarator(
				direct_declarator,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type,
				parameter_list,
				direct_declarator_type);
			if (identifier_list) {
				visit_identifier_list(
					identifier_list);
			}
			node->set_symbol(
				direct_declarator->get_symbol());
			// TODO; Gather type
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_direct_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_pointer(
	AnnotatedAstNode* const& node,
	const Type*       const& referenced_type,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_pointer_1");

	switch (node->get_alt()) {

		case AstNodeAlt::POINTER_1:
		{
			AnnotatedAstNode* type_qualifier_list
				= node->get_child();

			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}
			
			const Type* pointer_type
				= construct_derived_pointer_type(
				        referenced_type, 
						type_qualifiers);
			synthesized_type = pointer_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::POINTER_2:
		{
			AnnotatedAstNode* type_qualifier_list
				= (node->get_child()->get_name()
				   == AstNodeName::TYPE_QUALIFIER_LIST)
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* pointer
				= type_qualifier_list
				  ? type_qualifier_list->get_sibling()
				  : NULL;

			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}

			const Type* pointer_type
				= construct_derived_pointer_type(
					referenced_type,
					type_qualifiers);

			const Type* higher_pointer_type;
			visit_pointer(
				pointer,
				pointer_type,
				higher_pointer_type);

			synthesized_type 
				= higher_pointer_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_pointer_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_type_qualifier_list(
	AnnotatedAstNode* const& node,
	TypeQualifiers         & type_qualifiers)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;	
	
	report_visit("visit_type_qualifier_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::TYPE_QUALIFIER_LIST_1:
		{
			AnnotatedAstNode* type_qualifier
				= node->get_child();
			visit_type_qualifier(
				type_qualifier,
				type_qualifiers);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_QUALIFIER_LIST_2:
		{
			AnnotatedAstNode* type_qualifier_list
				= node->get_child();
			AnnotatedAstNode* type_qualifier
				= type_qualifier_list->get_sibling();
			visit_type_qualifier_list(
				type_qualifier_list,
				type_qualifiers);
			visit_type_qualifier(
				type_qualifier,
				type_qualifiers);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_type_qualifier_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_parameter_type_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file, 
	SymbolTable*      const& function_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_parameter_type_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::PARAMETER_TYPE_LIST_1:
		case AstNodeAlt::PARAMETER_TYPE_LIST_2:
		{
			AnnotatedAstNode* parameter_list
				= node->get_child();

			const Type* unused_parameter_types_list[16];
			const Type** uptl 
				= unused_parameter_types_list;
			visit_parameter_list(
				parameter_list,
				file,
				function_scope,
				uptl);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_parameter_type_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_parameter_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& function_scope,
	const Type**		   & parameter_types_list)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_parameter_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::PARAMETER_LIST_1:
		{
			AnnotatedAstNode* parameter_declaration
				= node->get_child();

			visit_parameter_declaration(
				parameter_declaration,
				function_scope,
				file);

			const Type* parameter_declaration_type
				= parameter_declaration->get_type();

			*parameter_types_list++ = parameter_declaration_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PARAMETER_LIST_2:
		{
			AnnotatedAstNode* parameter_list
				= node->get_child();
			AnnotatedAstNode* parameter_declaration
				= parameter_list->get_child();

			visit_parameter_list(
				parameter_list,
				file,
				function_scope,
				parameter_types_list);
			visit_parameter_declaration(
				parameter_declaration,
				file,
				function_scope);

			const Type* parameter_declaration_type
				= parameter_declaration->get_type();

			*parameter_types_list++ = parameter_declaration_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}	
	report_exit("visit_parameter_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_parameter_declaration(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& function_scope,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_parameter_declaration_1");

	switch (node->get_alt()) {

		case AstNodeAlt::PARAMETER_DECLARATION_1:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* declarator
				= declaration_specifiers->get_sibling();

			const Type* declaration_specifiers_type;
			visit_declaration_specifiers(
				declaration_specifiers,
				declaration_specifiers_type);

			const Type* declarator_type;
			const AnnotatedAstNode* unused_parameter_type_list;
			visit_declarator(
				declarator,
				file,
				function_scope,
				function_scope,
				declaration_specifiers_type,
				unused_parameter_type_list,
				declarator_type);
			
			const Type* parameter_declaration_type;
			duplicate_type(
				declarator_type, 
				parameter_declaration_type);
			node->set_type(parameter_declaration_type);
			
			//destruct_declaration_specifiers_type); TODO free.
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PARAMETER_DECLARATION_2:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* abstract_declarator
				= declaration_specifiers->get_sibling()
				  ? declaration_specifiers->get_sibling()
				  : NULL;

			const Type* declaration_specifiers_type;
			visit_declaration_specifiers(
				declaration_specifiers,
				declaration_specifiers_type);

			const Type* abstract_declarator_type;
			if (abstract_declarator) {
				visit_abstract_declarator(
					abstract_declarator,
					file,
					declaration_specifiers_type,
					abstract_declarator_type);
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}	
	report_exit("visit_parameter_declaration_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_identifier_list(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_identifier_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::IDENTIFIER_LIST_1:
		{
			AnnotatedAstNode* identifier
				= node->get_child();
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::IDENTIFIER_LIST_2:
		{
			AnnotatedAstNode* identifier_list
				= node->get_child();
			AnnotatedAstNode* identifier
				= identifier_list->get_sibling();

			visit_identifier_list(
				identifier_list);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_identifier_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_abstract_declarator(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	const Type*       const& specifier_qualifier_list_type,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_abstract_declarator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::ABSTRACT_DECLARATOR_1:
		{
			AnnotatedAstNode* pointer
				= node->get_child();

			if (pointer) {
				const Type* higher_pointer_type;
				visit_pointer(
					pointer,
					specifier_qualifier_list_type,
					higher_pointer_type);

				const Type* abstract_declarator_type;
				duplicate_type(
					higher_pointer_type,
					abstract_declarator_type);
				synthesized_type 
					= abstract_declarator_type;

			} else {
				const Type* specifier_qualifier_list_type_dup;
				duplicate_type(
					specifier_qualifier_list_type,
					specifier_qualifier_list_type_dup);

				synthesized_type 
					= specifier_qualifier_list_type_dup;
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ABSTRACT_DECLARATOR_2:
		{
			AnnotatedAstNode* pointer
				= node->get_child()->get_name() == AstNodeName::POINTER
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* direct_abstract_declarator
				= pointer
				  ? pointer->get_sibling()
				  : node->get_child();

			const Type* pointer_type = NULL;
			if (pointer) {
				visit_pointer(
					pointer,
					specifier_qualifier_list_type,
					pointer_type);
			}
			const Type* lower_direct_abstract_declarator_type;
			visit_direct_abstract_declarator(
				direct_abstract_declarator,
				file,
				pointer ? pointer_type : specifier_qualifier_list_type,
				lower_direct_abstract_declarator_type);

			const Type* direct_abstract_declarator_type;
			duplicate_type(
				lower_direct_abstract_declarator_type,
				direct_abstract_declarator_type);
			/*if (pointer) {
				const Type* higher_direct_abstract_declarator_type =
					construct_derived_pointer_type(
						direct_abstract_declarator_type,
						TypeQualifiers::UNQUALIFIED);
				direct_abstract_declarator_type
					= higher_direct_abstract_declarator_type;
			}*/
			
			synthesized_type = direct_abstract_declarator_type;
			
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_abstract_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_direct_abstract_declarator(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	const Type*       const& specifier_qualifier_list_type,
	const Type*            & synthesized_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_direct_abstract_declarator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_1:
		{
			AnnotatedAstNode* abstract_declarator
				= node->get_child();

			const Type* abstract_declarator_type = NULL;
			visit_abstract_declarator(
				abstract_declarator,
				file,
				specifier_qualifier_list_type,
				abstract_declarator_type);
			synthesized_type = abstract_declarator_type;

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_2:
		{
			AnnotatedAstNode* direct_abstract_declarator
				= (node->get_child()->get_name()
				   == AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* type_qualifier_list
				= direct_abstract_declarator->get_sibling();

			if (direct_abstract_declarator) {
				const Type* direct_abstract_declarator_type;
				visit_direct_abstract_declarator(
					direct_abstract_declarator,
					file,
					specifier_qualifier_list_type,
					direct_abstract_declarator_type);
			}
			TypeQualifiers type_qualifiers = TypeQualifiers::UNQUALIFIED;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					type_qualifiers);
			}
			// TODO;
			// synthesized_type = ??
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_3:
		{
			AnnotatedAstNode* direct_abstract_declarator
				= (node->get_child()->get_name()
					== AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* type_qualifier_list
				= direct_abstract_declarator
				  ? ((direct_abstract_declarator->get_child()->get_name()
					  == AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
					 ? direct_abstract_declarator->get_sibling()
					 : NULL)
				  : node->get_child();
			AnnotatedAstNode* assignment_expression
				= (node->get_child()->get_name()
				   == AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				  ? node->get_child()
				  : NULL;

			if (direct_abstract_declarator) {
				const Type* direct_abstract_declarator_type;
				visit_direct_abstract_declarator(
					direct_abstract_declarator,
					file,
					specifier_qualifier_list_type,
					direct_abstract_declarator_type);
			}
			TypeQualifiers lesser_type_qualifiers;
			if (type_qualifier_list) {
				visit_type_qualifier_list(
					type_qualifier_list,
					lesser_type_qualifiers);
			}
			visit_assignment_expression(
				assignment_expression,
				file);

			// TODO;
			// synthesized_type = ??

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_4:
		{
			AnnotatedAstNode* direct_abstract_declarator
				= node->get_child();
			AnnotatedAstNode* type_qualifier_list
				= direct_abstract_declarator
				? direct_abstract_declarator->get_sibling()
				: node->get_child();
			AnnotatedAstNode* assignment_expression
				= type_qualifier_list->get_sibling();

			if (direct_abstract_declarator) {
				const Type* direct_abstract_declarator_type;
				visit_direct_abstract_declarator(
					direct_abstract_declarator,
					file,
					specifier_qualifier_list_type,
					direct_abstract_declarator_type);
			}
			TypeQualifiers type_qualifiers
				= TypeQualifiers::UNQUALIFIED;
			visit_type_qualifier_list(
				type_qualifier_list,
				type_qualifiers);
			if (assignment_expression) {
				visit_assignment_expression(
					assignment_expression,
					file);
			}

			// TODO;
			// synthesized_type = ??

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_5:
		{
			AnnotatedAstNode* direct_abstract_declarator
				= (node->get_child()->get_name()
					== AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				  ? node->get_child()
				  : NULL;

			if (direct_abstract_declarator) {
				const Type* direct_abstract_declarator_type;
				visit_direct_abstract_declarator(
					direct_abstract_declarator,
					file,
					specifier_qualifier_list_type,
					direct_abstract_declarator_type);
			}

			// TODO;
			// synthesized_type = ??

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_6:
		{
			AnnotatedAstNode* direct_abstract_declarator
				= (node->get_child()->get_name()
					== AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				  ? node->get_child()
				  : NULL;
			AnnotatedAstNode* parameter_type_list
				= direct_abstract_declarator
				  ? direct_abstract_declarator->get_sibling()
				  : node->get_child();
			
			if (direct_abstract_declarator) {
				const Type* direct_abstract_declarator_type;
				visit_direct_abstract_declarator(
					direct_abstract_declarator,
					file,
					specifier_qualifier_list_type,
					direct_abstract_declarator_type);
			}

			SymbolTable* new_scope = new SymbolTable();
			if (parameter_type_list) {
				visit_parameter_type_list(
					parameter_type_list,
					file,
					new_scope);
			}

			// TODO;
			// synthesized_type = ??

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_direct_abstract_declarator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_initializer(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_initializer_1");

	switch (node->get_alt()) {

		case AstNodeAlt::INITIALIZER_1:
		{
			AnnotatedAstNode* assignment_expression
				= node->get_child();

			visit_assignment_expression(
				assignment_expression,
				file);

			const Type* initializer_type;
			duplicate_type(
				assignment_expression->get_type(), 
				initializer_type);
			node->set_type(initializer_type);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INITIALIZER_2:
		case AstNodeAlt::INITIALIZER_3:
		{
			AnnotatedAstNode* initializer_list;

			visit_initializer_list(
				initializer_list,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_initializer_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	
	report_visit("visit_initializer_list_1");
	
	switch (node->get_alt()) {

		case AstNodeAlt::INITIALIZER_LIST_1:
		{
			AnnotatedAstNode* designation
				= (node->get_child()->get_name()
					== AstNodeName::DESIGNATION)
				? node->get_child()
				: NULL;
			AnnotatedAstNode* initializer
				= designation
				? designation->get_sibling()
				: node->get_child();

			if (designation) {
				visit_designation(
					designation,
					file);
			}
			visit_initializer(
				initializer,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INITIALIZER_LIST_2:
		{
			AnnotatedAstNode* initializer_list
				= node->get_child();
			AnnotatedAstNode* designation
				= (initializer_list->get_sibling()->get_name()
					== AstNodeName::DESIGNATION)
				? initializer_list->get_sibling()
				: NULL;
			AnnotatedAstNode* initializer
				= designation
				? designation->get_sibling()
				: initializer_list->get_sibling();

			visit_initializer_list(
				initializer_list,
				file);
			if (designation) {
				visit_designation(
					designation,
					file);
			}
			visit_initializer(
				initializer,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_initializer_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_designation(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_designation_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DESIGNATION_1:
		{
			AnnotatedAstNode* designator_list
				= node->get_child();
			visit_designator_list(
				designator_list,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_designation_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_designator_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_designation_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DESIGNATOR_LIST_1:
		{
			AnnotatedAstNode* designator
				= node->get_child();

			visit_designator(
				designator,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DESIGNATOR_LIST_2:
		{
			AnnotatedAstNode* designator_list
				= node->get_child();
			AnnotatedAstNode* designator
				= designator_list->get_sibling();

			visit_designator_list(
				designator_list,
				file);
			visit_designator(
				designator,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_designation_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_designator(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_designator_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DESIGNATOR_1:
		{
			AnnotatedAstNode* constant_expression
				= node->get_child();

			visit_constant_expression(
				constant_expression,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DESIGNATOR_2:
		{
			AnnotatedAstNode* identifier
				= node->get_child();

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_designator_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_labeled_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_labeled_statement_1");

	switch (node->get_alt()) {

		case AstNodeAlt::LABELED_STATEMENT_1:
		{
			AnnotatedAstNode* identifier
				= node->get_child();
			AnnotatedAstNode* statement
				= identifier->get_sibling();

			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LABELED_STATEMENT_2:
		{
			AnnotatedAstNode* constant_expression
				= node->get_child();
			AnnotatedAstNode* statement
				= constant_expression->get_sibling();

			visit_constant_expression(
				constant_expression,
				file);
			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LABELED_STATEMENT_3:
		{
			AnnotatedAstNode* statement
				= node->get_child();

			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_labeled_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_statement_1");

	switch (node->get_alt()) {

		case AstNodeAlt::STATEMENT_1:
		{
			AnnotatedAstNode* labeled_statement
				= node->get_child();

			visit_labeled_statement(
				labeled_statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_2:
		{
			AnnotatedAstNode* compound_statement
				= node->get_child();

			visit_compound_statement(
				compound_statement, 
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_3:
		{
			AnnotatedAstNode* expression_statement
				= node->get_child();

			visit_expression_statement(
				expression_statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_4:
		{
			AnnotatedAstNode* selection_statement
				= node->get_child();

			visit_selection_statement(
				selection_statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_5:
		{
			AnnotatedAstNode* iteration_statement
				= node->get_child();

			visit_iteration_statement(
				iteration_statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_6:
		{
			AnnotatedAstNode* jump_statement
				= node->get_child();
			visit_jump_statement(
				jump_statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_compound_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_compound_statement_1");

	if (DEBUG_SEMANTIC_ANNOTATOR_SHOW_SCOPE_ENTRY) {
		cout << "semantic-annotator.cpp:"
			<< " entering new scope: block"
			<< endl;
	}

	node->set_symbol_table(new SymbolTable());

	switch (node->get_alt()) {

		case AstNodeAlt::COMPOUND_STATEMENT_1:
		{
			AnnotatedAstNode* block_item_list
				= node->get_child();

			SymbolTable* block_scope = node->get_symbol_table();
			if (block_item_list) {
				visit_block_item_list(
					block_item_list,
					file,
					block_scope);
			}

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_compound_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_block_item_list(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& block_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_block_item_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::BLOCK_ITEM_LIST_1:
		{
			AnnotatedAstNode* block_item
				= node->get_child();

			visit_block_item(
				block_item,
				file,
				block_scope);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::BLOCK_ITEM_LIST_2:
		{
			AnnotatedAstNode* block_item_list
				= node->get_child();
			AnnotatedAstNode* block_item
				= block_item_list->get_sibling();

			visit_block_item_list(
				block_item_list,
				file,
				block_scope);
			visit_block_item(
				block_item,
				file,
				block_scope);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_block_item_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_block_item(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file,
	SymbolTable*      const& block_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	
	report_visit("visit_block_item_1");

	switch (node->get_alt()) {

		case AstNodeAlt::BLOCK_ITEM_1:
		{
			AnnotatedAstNode* declaration
				= node->get_child();

			visit_declaration(
				declaration,
				file,
				block_scope);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::BLOCK_ITEM_2:
		{
			AnnotatedAstNode* statement
				= node->get_child();

			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_block_item_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_expression_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_expression_statement_1");

	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_STATEMENT_1:
		{
			AnnotatedAstNode* expression
				= node->get_child();

			if (expression) {
				visit_expression(
					expression,
					file);
			}
			break;
		}

		default:
			break;

	}
	report_exit("visit_expression_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_selection_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_selection_statement_1");

	switch (node->get_alt()) {

		case AstNodeAlt::SELECTION_STATEMENT_1:
		case AstNodeAlt::SELECTION_STATEMENT_3:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			AnnotatedAstNode* statement
				= expression->get_sibling();

			visit_expression(
				expression,
				file);
			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::SELECTION_STATEMENT_2:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			AnnotatedAstNode* statement1
				= expression->get_sibling();
			AnnotatedAstNode* statement2
				= statement1->get_sibling();

			visit_expression(
				expression,
				file);
			visit_statement(
				statement1,
				file);
			visit_statement(
				statement2,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_selection_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_iteration_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_iteration_statement_1");

	SymbolTable* scope = new SymbolTable();
	node->set_symbol_table(scope);
	switch (node->get_alt()) {

		case AstNodeAlt::ITERATION_STATEMENT_1:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			AnnotatedAstNode* statement
				= expression->get_sibling();

			visit_expression(
				expression,
				file);
			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ITERATION_STATEMENT_2:
		{
			AnnotatedAstNode* statement
				= node->get_child();
			AnnotatedAstNode* expression
				= statement->get_sibling();

			visit_statement(
				statement,
				file);
			visit_expression(
				expression,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ITERATION_STATEMENT_3:
	/*  case AstNodeAlt::ITERATION_STATEMENT_3_000:
		case AstNodeAlt::ITERATION_STATEMENT_3_001:
		case AstNodeAlt::ITERATION_STATEMENT_3_010:
		case AstNodeAlt::ITERATION_STATEMENT_3_011:
		case AstNodeAlt::ITERATION_STATEMENT_3_100:
		case AstNodeAlt::ITERATION_STATEMENT_3_101:
		case AstNodeAlt::ITERATION_STATEMENT_3_110:
		case AstNodeAlt::ITERATION_STATEMENT_3_111: */
		{
			AnnotatedAstNode* expression1
				= node->get_child();
			AnnotatedAstNode* expression2
				= expression1->get_sibling();
			AnnotatedAstNode* expression3
				= expression2->get_sibling();
			AnnotatedAstNode* statement
				= expression3->get_sibling();

			visit_expression(
				expression1,
				file);
			visit_expression(
				expression2,
				file);
			visit_expression(
				expression3,
				file);
			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ITERATION_STATEMENT_4:
	/* 	case AstNodeAlt::ITERATION_STATEMENT_4_00:
		case AstNodeAlt::ITERATION_STATEMENT_4_01:
		case AstNodeAlt::ITERATION_STATEMENT_4_10:
		case AstNodeAlt::ITERATION_STATEMENT_4_11: */
		{
			AnnotatedAstNode* declaration
				= node->get_child();
			AnnotatedAstNode* expression1
				= declaration->get_sibling();
			AnnotatedAstNode* expression2
				= expression1->get_sibling();
			AnnotatedAstNode* statement
				= expression2->get_sibling();

			visit_declaration(
				declaration,
				file,
				scope);
			visit_expression(
				expression1,
				file);
			visit_expression(
				expression2,
				file);
			visit_statement(
				statement,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_iteration_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_jump_statement(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;	
	
	report_visit("visit_jump_statement_1");

	switch (node->get_alt()) {

		case AstNodeAlt::JUMP_STATEMENT_1:
		case AstNodeAlt::JUMP_STATEMENT_2:
		case AstNodeAlt::JUMP_STATEMENT_3:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::JUMP_STATEMENT_4:
		{
			if (node->get_child()) {
				visit_expression(
					node->get_child(),
					file);
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_jump_statement_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_translation_unit(
	AnnotatedAstNode* const& node,
	SymbolTable*           & file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_translation_unit_1");

	if (DEBUG_SEMANTIC_ANNOTATOR_SHOW_SCOPE_ENTRY) {
		cout << "semantic-annotator.cpp:entering new scope: file"
			<< endl;
	}

	if (file == NULL) {
		file = new SymbolTable();
		node->set_symbol_table(file);
	}

	switch (node->get_alt()) {

		case AstNodeAlt::TRANSLATION_UNIT_1:
		{
			AnnotatedAstNode* external_declaration
				= node->get_child();

			visit_external_declaration(
				external_declaration,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TRANSLATION_UNIT_2:
		{
			AnnotatedAstNode* external_declaration
				= node->get_child();

			visit_external_declaration(
				external_declaration,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_translation_unit_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_external_declaration(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_external_declaration_1");

	switch (node->get_alt()) {

		case AstNodeAlt::EXTERNAL_DECLARATION_1:
		{
			AnnotatedAstNode* function_definition
				= node->get_child();

			visit_function_definition(
				function_definition,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXTERNAL_DECLARATION_2:
		{
			AnnotatedAstNode* declaration
				= node->get_child();

			visit_declaration(
				declaration,
				file,
				file);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_exit("visit_external_declaration_1");
	return exitcode;
}

static inline
int convert_parameter_list_to_parameter_type(
	const AnnotatedAstNode* const& parameter_list,
	const Parameter*             & parameter_type) 
{
	int retval = 0;
	if (parameter_list->get_alt()
		== AstNodeAlt::PARAMETER_LIST_1) {

		const AnnotatedAstNode* parameter_declaration
			= parameter_list->get_child();

		Parameter* parameter      
			= new Parameter();		
		parameter->parameter_name
			= parameter_declaration->get_symbol();
		duplicate_type(
			parameter_declaration->get_type(),
			parameter->parameter_type);
		parameter->next_parameter = NULL;
		retval++;

		parameter_type = parameter;

	} else if (parameter_list->get_alt()
		       == AstNodeAlt::PARAMETER_LIST_2) {
		
		const AnnotatedAstNode* lesser_parameter_list
			= parameter_list->get_child();
		const AnnotatedAstNode* parameter_declaration
			= lesser_parameter_list->get_sibling();

		Parameter* parameter
			= new Parameter();
		parameter->parameter_name 
			= lesser_parameter_list->get_symbol();
		duplicate_type(
			parameter_declaration->get_type(), 
			parameter->parameter_type);
		retval = convert_parameter_list_to_parameter_type(
			lesser_parameter_list,
			parameter->next_parameter);
		retval++;

		parameter_type = parameter;

	} else {

	}
	return retval;
}

static inline
SemanticAnnotatorExitCode visit_function_definition(
	AnnotatedAstNode* const& node,
	SymbolTable*      const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	report_visit("visit_function_definition_1");

	if (DEBUG_SEMANTIC_ANNOTATOR_SHOW_SCOPE_ENTRY) {
		cout << "semantic-annotator.cpp:"
			 << "entering new scope:"
			 << " function"
			 << endl;
	}

	SymbolTable* function = new SymbolTable();
	node->set_symbol_table(function);

	switch (node->get_alt()) {

		case AstNodeAlt::FUNCTION_DEFINITION_1:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* declarator
				= declaration_specifiers->get_sibling();
			AnnotatedAstNode* declaration_list
				= (declarator->get_sibling()->get_name()
					== AstNodeName::DECLARATION_LIST)
				  ? declarator->get_sibling()
				  : NULL;
			AnnotatedAstNode* compound_statement
				= declaration_list
				  ? declaration_list->get_sibling()
				  : declarator->get_sibling();

			const Type* declaration_specifiers_type;
			visit_declaration_specifiers(
				declaration_specifiers,
				declaration_specifiers_type);

			const AnnotatedAstNode* parameter_list = NULL;

			const Type* declarator_type;
			visit_declarator(
				declarator,
				file,
				file,
				function,
				declaration_specifiers_type,
				parameter_list,
				declarator_type);

			if (declaration_list) {
				visit_declaration_list(
					declaration_list,
					file,
					function,
					parameter_list);
			} else {

			}

			visit_compound_statement(
				compound_statement,
				file);
			
			///* Gathering annotation data for this function's type. */
			//const char* declarator_symbol = declarator->get_symbol();
			//SymbolTable* st = file;
			//SymbolTableEntry* e = file->get_entry(declarator_symbol);

			//const Type* return_type;
			//duplicate_type(
			//	declaration_specifiers->get_type(),
			//	return_type);

			//const Parameter* parameters_type;
			//int number_of_parameters 
			//	= convert_parameter_list_to_parameter_type(
			//	      parameter_list,
			//	      parameters_type);

			//const Type* function_type 
			//	= construct_function_type(
			//	      return_type,
			//		  number_of_parameters,
			//		  parameters_type);

			///* Now actually inserting that data 
			//  into the node and symbol table. */
			node->set_type(declarator_type);
			//duplicate_type(function_type, e->type);

			file->get_entry(declarator->get_symbol())->scope
				= Scope::FILE;

			int base_ptr = 0x00000000;
			
			/* Recording annotation data for the variables 
			   that this function influences. */

			/* For each parameter */		
			SymbolTable* sym = node->get_symbol_table();
			SymbolTableEntry* entries[1028] = { 0 };
			sym->get_entries(entries);			
			int number_formal_parameters = 0;

			for (SymbolTableEntry** e = entries; *e != NULL; e++) {
				/* add it to the number encountered so far.  */
				number_formal_parameters++;
				/* record its address */
				(*e)->base_pointer_offset 
					= base_ptr;
				base_ptr 
					+= get_sizeof_type((*e)->type);
				/* record it as a parameter in scope */
				(*e)->scope 
					= Scope::BLOCK;
				/* give it a pointer to its function. */
				(*e)->function_ptr 
					= file->get_entry(declarator->get_symbol());
			}
			file->get_entry(declarator->get_symbol())->number_formal_parameters
				= number_formal_parameters;

			/* For each variable */
			SymbolTableEntry* var_entries[1028] = { 0 };
			compound_statement->get_symbol_table()
				              ->get_entries(var_entries);
	
			for (SymbolTableEntry** e = var_entries; *e != NULL; e++) {
				(*e)->base_pointer_offset = base_ptr;
				base_ptr += get_sizeof_type((*e)->type);
				(*e)->scope = Scope::BLOCK;
			}
			file->get_entry(declarator->get_symbol())->function_frame_size
				= base_ptr;
			for (SymbolTableEntry** e = var_entries; *e != NULL; e++) {
				(*e)->function_ptr 
					= file->get_entry(declarator->get_symbol());
			}		

			return exitcode;
		}

		default:
			break;

	}
	report_exit("visit_function_definition_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode visit_declaration_list(
	AnnotatedAstNode*        const& node,
	SymbolTable*             const& file,
	SymbolTable*             const& declaration_scope,
	const AnnotatedAstNode*         parameter_type_list)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;	
	
	report_visit("visit_declaration_list_1");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_LIST_1:
		{
			AnnotatedAstNode* declaration
				= node->get_child();

			visit_declaration(
				declaration,
				file,
				declaration_scope);

			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DECLARATION_LIST_2:
		{
			AnnotatedAstNode* declaration_list
				= node->get_child();
			AnnotatedAstNode* declaration
				= declaration_list->get_sibling();

			visit_declaration_list(
				declaration_list,
				file,
				declaration_scope,
				parameter_type_list);
			visit_declaration(
				declaration,
				file,
				declaration_scope);

			exitcode 
				= SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	report_visit("exit_declaration_list_1");
	return exitcode;
}

static inline
SemanticAnnotatorExitCode annotate(
	const AstNode*    const& node,
	AnnotatedAstNode*      & anno_node)
{
	construct_unatrributed_annotated_ast(
		node, 
		anno_node);
	SymbolTable* file 
		= NULL;
	visit_translation_unit(
		anno_node,
		file);
	return SemanticAnnotatorExitCode::SUCCESS;
}

#endif