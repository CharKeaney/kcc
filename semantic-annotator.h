
#ifndef SEMANTIC_ANNOTATOR_H
#define SEMANTIC_ANNOTATOR_H 1

#include "symbol-table.h"
#include "ast-node.h"
#include "semantics.h"

typedef enum class SemanticAnnotatorExitCode {
	SUCCESS,
	FAIL
} SemanticAnnotatorExitCode;


static inline SemanticAnnotatorExitCode get_init_declarator_symbol(
	AnnotatedAstNode* init_declarator,
	const char*& lexeme);

static inline SemanticAnnotatorExitCode get_declarator_symbol(
	AnnotatedAstNode* declarator,
	const char*& lexeme);

static inline SemanticAnnotatorExitCode get_init_declarator_symbols(
	AnnotatedAstNode* init_declarator,
	const char**& lexeme);

static inline SemanticAnnotatorExitCode get_init_declarator_type(
	AnnotatedAstNode* init_declarator,
	Type const& declaration_specifier_type,
	Type*& init_declarator_type);

static inline SemanticAnnotatorExitCode get_declaration_specifiers_type(
	AnnotatedAstNode* init_declarator,
	Type& t);

static inline SemanticAnnotatorExitCode get_function_symbol(
	AnnotatedAstNode* function_definition,
	const char*& lexeme);

static inline SemanticAnnotatorExitCode construct_unatrributed_annotated_ast(
	AstNode* const& ast_node,
	AnnotatedAstNode* const& anno_ast_node);

static inline SemanticAnnotatorExitCode visit_primary_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_argument_expression_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_postfix_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_type_name_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_unary_operator_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_cast_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_unary_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_multiplicative_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_additive_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_shift_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_relational_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_equality_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_and_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_exclusive_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_inclusive_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_logical_and_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_logical_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_assignment_operator_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_conditional_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_assignment_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_constant_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_declaration_3(
	AnnotatedAstNode* const& node,
	const char* init_declarator_symbols[32]  );

static inline SemanticAnnotatorExitCode visit_declaration_2(
	AnnotatedAstNode* const& node,
	Type*& const declaration_specifier_type);

static inline SemanticAnnotatorExitCode visit_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope);

static inline SemanticAnnotatorExitCode visit_storage_class_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_type_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_function_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_declaration_specifiers_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_declaration_specifiers_list_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_init_declarator_2(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_init_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& declaration_scope,
	Type*& const declaration_specifier_type,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_init_declarator_list_2(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_init_declarator_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	Type*& const declaration_specifier_type);

static inline SemanticAnnotatorExitCode visit_enum_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_typedef_name_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_struct_or_union_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_struct_or_union_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_struct_declaration_list_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor);

static inline SemanticAnnotatorExitCode visit_struct_declaration_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor);

static inline SemanticAnnotatorExitCode visit_specifier_qualifier_list_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_struct_declarator_list_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_struct_declarator_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor,
	Type*& const declaration_specifier_type,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_enumerator_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_enumerator_list_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_enumeration_specifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_type_qualifier_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_declarator_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol);

static inline SemanticAnnotatorExitCode visit_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	SymbolTable* const& parameter_type_list_scope,
	Type* const& declaration_specifier_type);

static inline SemanticAnnotatorExitCode visit_direct_declarator_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol);

static inline SemanticAnnotatorExitCode visit_direct_declarator_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	SymbolTable* const& parameter_type_list_scope,
	StackDescriptor* const& stack_descriptor,
	Type* const& declaration_specifier_type);

static inline SemanticAnnotatorExitCode visit_pointer_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_type_qualifier_list_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_parameter_type_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& function_scope);

static inline SemanticAnnotatorExitCode visit_parameter_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& function_scope);

static inline SemanticAnnotatorExitCode visit_parameter_declaration_2(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_parameter_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& function_scope,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_identifier_list_1(
	AnnotatedAstNode* const& node);

static inline SemanticAnnotatorExitCode visit_abstract_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_direct_abstract_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_initializer_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_initializer_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_designation_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_designator_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_designator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_labeled_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_compound_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_block_item_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& block_scope);

static inline SemanticAnnotatorExitCode visit_block_item_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& block_scope);

static inline SemanticAnnotatorExitCode visit_expression_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_selection_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_iteration_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_jump_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_translation_unit_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_external_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_function_definition_3(
	AnnotatedAstNode* const& node,
	const char* const& symbol,
	SymbolTable* const& file_scope,
	SymbolTable* const& compound_statement_scope);

static inline SemanticAnnotatorExitCode visit_function_definition_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol);

static inline SemanticAnnotatorExitCode visit_function_definition_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file);

static inline SemanticAnnotatorExitCode visit_declaration_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope);

static inline bool annotate(
	AstNode* node,
	AnnotatedAstNode*& anno_node,
	StackDescriptor* const& stack_descriptor);

/* static inline function definitions. */

static inline SemanticAnnotatorExitCode get_init_declarator_symbol(
	AnnotatedAstNode* init_declarator,
	const char*& lexeme)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* current = init_declarator;
	bool concluded = false;
	while (!concluded) {

		switch (current->get_alt()) {

			case AstNodeAlt::INIT_DECLARATOR_1:
			case AstNodeAlt::INIT_DECLARATOR_2:
				current = current->get_child();
				continue;

			case AstNodeAlt::DECLARATOR_1:
				if (current->get_child()->get_name()
					== AstNodeName::POINTER) {
					current = current->get_child()->get_sibling();
				}
				else {
					current = current->get_child();
				}
				continue;

			case AstNodeAlt::DIRECT_DECLARATOR_1:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::DIRECT_DECLARATOR_2:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::DIRECT_DECLARATOR_3:
			case AstNodeAlt::DIRECT_DECLARATOR_4:
			case AstNodeAlt::DIRECT_DECLARATOR_5:
			case AstNodeAlt::DIRECT_DECLARATOR_6:
			case AstNodeAlt::DIRECT_DECLARATOR_7:
			case AstNodeAlt::DIRECT_DECLARATOR_8:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::TERMINAL:
			{
				Token* tk = current->get_terminal();
				lexeme = tk->get_lexeme();
				exitcode = SemanticAnnotatorExitCode::SUCCESS;
				concluded = true;
				break;
			}

			default:
				concluded = true;
				break;

		}
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode get_declarator_symbol(
	AnnotatedAstNode* declarator,
	const char*& lexeme)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* current = declarator;
	bool concluded = false;
	while (!concluded) {

		switch (current->get_alt()) {

			case AstNodeAlt::DECLARATOR_1:
				if (current->get_child()->get_name()
					== AstNodeName::POINTER) {
					current = current->get_child()->get_sibling();
				}
				else {
					current = current->get_child();
				}
				continue;

			case AstNodeAlt::DIRECT_DECLARATOR_1:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::DIRECT_DECLARATOR_2:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::DIRECT_DECLARATOR_3:
			case AstNodeAlt::DIRECT_DECLARATOR_4:
			case AstNodeAlt::DIRECT_DECLARATOR_5:
			case AstNodeAlt::DIRECT_DECLARATOR_6:
			case AstNodeAlt::DIRECT_DECLARATOR_7:
			case AstNodeAlt::DIRECT_DECLARATOR_8:
			{
				current = current->get_child();
				continue;
			}

			case AstNodeAlt::TERMINAL:
			{
				Token* tk = current->get_terminal();
				lexeme = tk->get_lexeme();
				exitcode = SemanticAnnotatorExitCode::SUCCESS;
				concluded = true;
				break;
			}

			default:
				concluded = true;
				break;

		}
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode get_init_declarator_symbols(
	AnnotatedAstNode* init_declarator,
	const char**& lexeme)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	AnnotatedAstNode* current
		= init_declarator;

	switch (current->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_LIST_1:
		{
			const char* symbol;
			get_init_declarator_symbol(
				current->get_child(),
				symbol);
			*lexeme++ = symbol;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INIT_DECLARATOR_LIST_2:
		{
			get_init_declarator_symbols(
				current->get_child(),
				lexeme);
			const char* symbol;
			get_init_declarator_symbol(
				current->get_child()->get_sibling(),
				symbol);
			*lexeme++ = symbol;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode get_init_declarator_type(
	AnnotatedAstNode* init_declarator,
	Type const& declaration_specifier_type,
	Type*& init_declarator_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* current = init_declarator;

	AnnotatedAstNode* type_specifier_stack[32];
	int si = 0;
	
	bool concluded = false;
	while (!concluded) {

		switch (current->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_1:
			current = current->get_child();
			break;

		case AstNodeAlt::DECLARATOR_1:
			if (current->get_child()->get_name() == AstNodeName::POINTER) {
				Type* higher_init_declarator_type = new Type();
				higher_init_declarator_type->derived_or_basic
					= DerivedOrBasic::DERIVED;
				higher_init_declarator_type->derived_type_name
					= DerivedType::POINTER;
				higher_init_declarator_type->t
					= init_declarator_type;
				init_declarator_type = higher_init_declarator_type;
				current = current->get_child()->get_sibling();
			}
			else {
				current = current->get_child();
			}
			break;

		case AstNodeAlt::DIRECT_DECLARATOR_2:
		case AstNodeAlt::DIRECT_DECLARATOR_3:
		case AstNodeAlt::DIRECT_DECLARATOR_4:
		case AstNodeAlt::DIRECT_DECLARATOR_5:
		case AstNodeAlt::DIRECT_DECLARATOR_6:
		case AstNodeAlt::DIRECT_DECLARATOR_7:
		case AstNodeAlt::DIRECT_DECLARATOR_8:
			current = current->get_child();
			break;

		case AstNodeAlt::TERMINAL:
			concluded = true;
			break;

		default:
			break;

		}
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode get_declaration_specifiers_type(
	AnnotatedAstNode* init_declarator,
	Type& t)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* current = init_declarator;

	AnnotatedAstNode* type_specifier_stack[32];
	int si = 0;

	bool concluded = false;
	while (!concluded) {

		switch (current->get_alt()) {

		case AstNodeAlt::DECLARATION_SPECIFIERS_2:
		{
			type_specifier_stack[si++] = current->get_child();
			if (current->get_child()->get_sibling() != NULL) {
				current = current->get_child()->get_sibling();
			}
			else {
				concluded = true;
				break;
			}
			break;
		}

		case AstNodeAlt::DECLARATION_SPECIFIERS_1:
		case AstNodeAlt::DECLARATION_SPECIFIERS_3:
		case AstNodeAlt::DECLARATION_SPECIFIERS_4:
		{
			current = current->get_child()->get_sibling();
			if (current == NULL) {
				concluded = true;
			}
			break;
		}

		default:
			concluded = true;
			break;
		}
	}

	t.derived_or_basic = DerivedOrBasic::BASIC;

	switch (type_specifier_stack[0]->get_alt()) {

		case AstNodeAlt::TYPE_SPECIFIER_1:
			t.basic = BasicType::VOID;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_2:
			t.basic = BasicType::CHAR;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_3:
			t.basic = BasicType::SHORT;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_4:
			t.basic = BasicType::SIGNED_INT;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_5:
			t.basic = BasicType::SIGNED_LONG;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_6:
			t.basic = BasicType::FLOAT;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_7:
			t.basic = BasicType::DOUBLE;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_8: /* Signed */
		{
			switch (type_specifier_stack[1]->get_alt()) {

				case AstNodeAlt::TYPE_SPECIFIER_2:
					t.basic = BasicType::SIGNED_CHAR;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_3:
					t.basic = BasicType::SIGNED_SHORT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_4:
					t.basic = BasicType::SIGNED_INT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_5:
				{
					switch (type_specifier_stack[2]->get_alt()) {

						case AstNodeAlt::TYPE_SPECIFIER_5:
							t.basic = BasicType::SIGNED_LONG_LONG;

							switch (type_specifier_stack[3]->get_alt()) {

								case AstNodeAlt::TYPE_SPECIFIER_4:
									t.basic = BasicType::SIGNED_LONG_LONG;
									break;

								default:
									break;
							
							 }

						default:
							break;
					}
					t.basic = BasicType::SIGNED_LONG;
					break;
				}

				default:
					break;

			}
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_9: /* Unsigned */
		{
			switch (type_specifier_stack[1]->get_alt()) {

				case AstNodeAlt::TYPE_SPECIFIER_2:
					t.basic = BasicType::UNSIGNED_CHAR;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_3:
					t.basic = BasicType::UNSIGNED_SHORT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_4:
					t.basic = BasicType::UNSIGNED_INT;
					break;

				case AstNodeAlt::TYPE_SPECIFIER_5:
				{

					switch (type_specifier_stack[2]->get_alt()) {

						case AstNodeAlt::TYPE_SPECIFIER_5:
							t.basic = BasicType::UNSIGNED_LONG_LONG;

							switch (type_specifier_stack[3]->get_alt()) {

							case AstNodeAlt::TYPE_SPECIFIER_4:
								t.basic = BasicType::UNSIGNED_LONG_LONG;
								break;

							default:
								break;
							}

						default:
							break;
					}
					t.basic = BasicType::UNSIGNED_LONG;
					break;
				}
			}
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_10:
			t.basic = BasicType::BOOL;
			break;

		case AstNodeAlt::TYPE_SPECIFIER_11:
			t.basic = BasicType::COMPLEX;
			break;

		default:
			break;
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode get_function_symbol(
	AnnotatedAstNode* function_definition,
	const char*& lexeme)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* current = function_definition;
	bool concluded = false;
	while (!concluded) {

		switch (current->get_alt()) {

		case AstNodeAlt::FUNCTION_DEFINITION_1:
			current = current->get_child()->get_sibling();
			continue;

		case AstNodeAlt::DECLARATOR_1:
			if (current->get_child()->get_name()
				== AstNodeName::POINTER) {
				current = current->get_child()->get_sibling();
			}
			else {
				current = current->get_child();
			}
			continue;

		case AstNodeAlt::DIRECT_DECLARATOR_1:
		{
			current = current->get_child();
			continue;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_2:
		{
			current = current->get_child();
			continue;
		}

		case AstNodeAlt::DIRECT_DECLARATOR_3:
		case AstNodeAlt::DIRECT_DECLARATOR_4:
		case AstNodeAlt::DIRECT_DECLARATOR_5:
		case AstNodeAlt::DIRECT_DECLARATOR_6:
		case AstNodeAlt::DIRECT_DECLARATOR_7:
		case AstNodeAlt::DIRECT_DECLARATOR_8:
		{
			current = current->get_child();
			continue;
		}

		case AstNodeAlt::TERMINAL:
		{
			lexeme = current->get_terminal()->get_lexeme();
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			concluded = true;
			break;
		}

		default:
			concluded = true;
			break;
		}
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode construct_unatrributed_annotated_ast(
	AstNode* const& ast_node, 
	AnnotatedAstNode*& anno_ast_node)
{
	SemanticAnnotatorExitCode exitcode = SemanticAnnotatorExitCode::SUCCESS;

	anno_ast_node = new AnnotatedAstNode(ast_node);

	for (AstNode* c = ast_node->get_child();
		c != NULL;
		c = c->get_sibling()) {

		AnnotatedAstNode* anno_c;
		if (construct_unatrributed_annotated_ast(c, anno_c)
			== SemanticAnnotatorExitCode::SUCCESS) {
			anno_ast_node->add_child(anno_c);
		}
		else {
			exitcode = SemanticAnnotatorExitCode::FAIL;
		}
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_primary_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file) 
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::PRIMARY_EXPRESSION_1:
		{
			node->set_symbol(node->get_child()
				                 ->get_terminal()
				                 ->get_lexeme());
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_2:
		{
			TokenValue val =
				node->get_child()
				    ->get_terminal()
				    ->get_val();

			const char* const& symbol 
				= node->get_child()
				      ->get_terminal()
				      ->get_lexeme();

			if (!file->get_entry(symbol)) {
				file->add_entry(symbol);
				file->get_entry(symbol)->value = val.intvalue;
				file->get_entry(symbol)->is_literal = true;
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_3:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_4:
		{
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}


static inline SemanticAnnotatorExitCode visit_argument_expression_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ARGUMENT_EXPRESSION_LIST_1:
	{
		AnnotatedAstNode* assignment_expression
			= node->get_child();
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::ARGUMENT_EXPRESSION_LIST_2:
	{
		AnnotatedAstNode* argument_expression_list
			= node->get_child();
		AnnotatedAstNode* assignment_expression
			= argument_expression_list->get_sibling();
		visit_argument_expression_list_1(
			argument_expression_list,
			stack_descriptor,
			file);
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_postfix_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::POSTFIX_EXPRESSION_1:
	{
		AnnotatedAstNode* primary_expression
			= node->get_child();
		visit_primary_expression_1(
			primary_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_2:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		AnnotatedAstNode* expression
			= postfix_expression->get_sibling();
		visit_postfix_expression_1(
			postfix_expression,
			stack_descriptor,
			file);
		visit_expression_1(
			expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_3:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		AnnotatedAstNode* argument_expression_list
			= postfix_expression->get_sibling();
		visit_postfix_expression_1(
			postfix_expression,
			stack_descriptor,
			file);
		visit_argument_expression_list_1(
			argument_expression_list,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_4:
	case AstNodeAlt::POSTFIX_EXPRESSION_5:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		AnnotatedAstNode* argument_expression_list
			= postfix_expression->get_sibling();
		visit_postfix_expression_1(
			postfix_expression,
			stack_descriptor,
			file);
		if (argument_expression_list) {
			visit_argument_expression_list_1(
				argument_expression_list,
				stack_descriptor,
				file);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_6:
	case AstNodeAlt::POSTFIX_EXPRESSION_7:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		visit_postfix_expression_1(
			postfix_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_8:
	case AstNodeAlt::POSTFIX_EXPRESSION_9:
	{
		AnnotatedAstNode* type_name
			= node->get_child();
		AnnotatedAstNode* initializer_list
			= type_name->get_sibling();
		visit_type_name_1(
			type_name,
			stack_descriptor,
			file);
		visit_initializer_list_1(
			initializer_list,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_type_name_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::TYPE_NAME_1:
	{
		AnnotatedAstNode* specifier_qualifier_list
			= node->get_child();
		AnnotatedAstNode* abstract_declarator
			= specifier_qualifier_list->get_sibling();
		visit_specifier_qualifier_list_1(
			specifier_qualifier_list);
		if (abstract_declarator) {
			visit_abstract_declarator_1(
				abstract_declarator,
				stack_descriptor,
				file);
		}
		break;
	}
	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_unary_operator_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
		break;;

	case AstNodeAlt::UNARY_OPERATOR_6:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_cast_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::CAST_EXPRESSION_1:
	{
		AnnotatedAstNode* unary_expression
			= node->get_child();
		visit_unary_expression_1(
			unary_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::CAST_EXPRESSION_2:
	{
		AnnotatedAstNode* type_name
			= node->get_child();
		AnnotatedAstNode* cast_expression
			= type_name->get_sibling();
		visit_type_name_1(
			type_name,
			stack_descriptor,
			file);
		visit_cast_expression_1(
			cast_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_unary_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::UNARY_EXPRESSION_1:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		visit_postfix_expression_1(
			postfix_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::UNARY_EXPRESSION_2:
	case AstNodeAlt::UNARY_EXPRESSION_3:
	{
		AnnotatedAstNode* unary_expression
			= node->get_child();
		visit_unary_expression_1(
			unary_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::UNARY_EXPRESSION_4:
	{
		AnnotatedAstNode* unary_operator
			= node->get_child();
		AnnotatedAstNode* cast_expression
			= unary_operator->get_sibling();
		visit_unary_operator_1(
			unary_operator);
		visit_cast_expression_1(
			cast_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::UNARY_EXPRESSION_5:
	{
		AnnotatedAstNode* unary_expression
			= node->get_child();
		visit_unary_expression_1(
			unary_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::UNARY_EXPRESSION_6:
	{
		AnnotatedAstNode* type_name
			= node->get_child();
		visit_type_name_1(
			type_name,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_multiplicative_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_1:
		{
			AnnotatedAstNode* cast_expression
				= node->get_child();
			visit_cast_expression_1(
				cast_expression,
				stack_descriptor,
				file);
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
			visit_multiplicative_expression_1(
				multiplicative_expression,
				stack_descriptor,
				file);
			visit_cast_expression_1(
				cast_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_additive_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ADDITIVE_EXPRESSION_1:
	{
		AnnotatedAstNode* multiplicative_expression
			= node->get_child();
		visit_multiplicative_expression_1(
			multiplicative_expression,
			stack_descriptor,
			file);
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
		visit_additive_expression_1(
			additive_expression,
			stack_descriptor,
			file);
		visit_multiplicative_expression_1(
			multiplicative_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_shift_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::SHIFT_EXPRESSION_1:
	{
		AnnotatedAstNode* additive_expression
			= node->get_child();
		visit_additive_expression_1(
			additive_expression,
			stack_descriptor,
			file);
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
		visit_shift_expression_1(
			shift_expression,
			stack_descriptor,
			file);
		visit_additive_expression_1(
			additive_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_relational_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::RELATIONAL_EXPRESSION_1:
	{
		AnnotatedAstNode* shift_expression
			= node->get_child();
		visit_shift_expression_1(
			shift_expression,
			stack_descriptor,
			file);
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
		visit_relational_expression_1(
			relational_expression,
			stack_descriptor,
			file);
		visit_shift_expression_1(
			shift_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_equality_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::EQUALITY_EXPRESSION_1:
	{
		AnnotatedAstNode* relational_expression
			= node->get_child();
		visit_relational_expression_1(
			relational_expression,
			stack_descriptor,
			file);
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
		visit_equality_expression_1(
			equality_expression,
			stack_descriptor,
			file);
		visit_relational_expression_1(
			relational_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_and_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::AND_EXPRESSION_1:
	{
		AnnotatedAstNode* equality_expression
			= node->get_child();
		visit_equality_expression_1(
			equality_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::AND_EXPRESSION_2:
	{
		AnnotatedAstNode* and_expression
			= node->get_child();
		AnnotatedAstNode* equality_expression
			= and_expression->get_sibling();
		visit_and_expression_1(
			and_expression,
			stack_descriptor,
			file);
		visit_equality_expression_1(
			equality_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_exclusive_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1:
		{
			AnnotatedAstNode* and_expression
				= node->get_child();
			visit_and_expression_1(
				and_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2:
		{
			AnnotatedAstNode* exclusive_or_expression
				= node->get_child();
			AnnotatedAstNode* and_expression
				= exclusive_or_expression->get_sibling();
			visit_and_expression_1(
				and_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_inclusive_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_1:
		{
			AnnotatedAstNode* exclusive_or_expression
				= node->get_child();
			visit_exclusive_or_expression_1(
				exclusive_or_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_2:
		{
			AnnotatedAstNode* inclusive_or_expression
				= node->get_child();
			AnnotatedAstNode* exclusive_or_expression
				= inclusive_or_expression->get_sibling();
			visit_inclusive_or_expression_1(
				inclusive_or_expression,
				stack_descriptor,
				file);
			visit_exclusive_or_expression_1(
				exclusive_or_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_logical_and_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_1:
		{
			AnnotatedAstNode* inclusive_or_expression
				= node->get_child();
			visit_inclusive_or_expression_1(
				inclusive_or_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_2:
		{
			AnnotatedAstNode* logical_and_expression
				= node->get_child();
			AnnotatedAstNode* inclusive_or_expression
				= logical_and_expression->get_sibling();
			visit_logical_and_expression_1(
				logical_and_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_logical_or_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::LOGICAL_OR_EXPRESSION_1:
	{
		AnnotatedAstNode* logical_and_expression
			= node->get_child();
		visit_logical_and_expression_1(
			logical_and_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::LOGICAL_OR_EXPRESSION_2:
	{
		AnnotatedAstNode* logical_or_expression
			= node->get_child();
		AnnotatedAstNode* logical_and_expression
			= logical_or_expression->get_sibling();
		visit_logical_or_expression_1(
			logical_or_expression,
			stack_descriptor,
			file);
		visit_logical_and_expression_1(
			logical_and_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_assignment_operator_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_1:
		{
			AnnotatedAstNode* assignment_expression
				= node->get_child();
			visit_assignment_expression_1(
				assignment_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXPRESSION_2:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			AnnotatedAstNode* assignment_expression
				= expression->get_sibling();
			visit_expression_1(
				expression,
				stack_descriptor,
				file);
			visit_assignment_expression_1(
				assignment_expression,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_conditional_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::CONDITIONAL_EXPRESSION_1:
	{
		AnnotatedAstNode* logical_or_expression
			= node->get_child();
		visit_logical_or_expression_1(
			logical_or_expression,
			stack_descriptor,
			file);
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
		visit_logical_or_expression_1(
			logical_or_expression,
			stack_descriptor,
			file);
		visit_expression_1(
			expression,
			stack_descriptor,
			file);
		visit_conditional_expression_1(
			conditional_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_assignment_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ASSIGNMENT_EXPRESSION_1:
	{
		AnnotatedAstNode* conditional_expression
			= node->get_child();
		visit_conditional_expression_1(
			conditional_expression,
			stack_descriptor,
			file);
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
		visit_unary_expression_1(
			unary_expression,
			stack_descriptor,
			file);
		visit_assignment_operator_1(
			assignment_operator);
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_constant_expression_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::CONSTANT_EXPRESSION_1:
	{
		AnnotatedAstNode* conditional_expression
			= node->get_child();
		visit_conditional_expression_1(
			conditional_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declaration_3(
	AnnotatedAstNode* const& node,
	const char* init_declarator_symbols[32])
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	for (const char** s = init_declarator_symbols;
		*s != NULL;
		s++) {

		SymbolTable* st = node->get_symbol_table();

		SymbolTableEntry* e = st->get_entry(*s);

		//Type* init_declarator_type;
		//get_init_declarator_type(
		//	node,
		//	declaration_specifier_type,
		//	init_declarator_type);
		// init_declarator_type;
	}

	switch (node->get_parent()->get_name()) {

		case AstNodeName::DECLARATION_LIST:

			break;

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declaration_2(
	AnnotatedAstNode* const& node,
	Type*& const declaration_specifier_type)
{
	node->set_type(declaration_specifier_type);
}

static inline SemanticAnnotatorExitCode visit_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_1:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* init_declarator_list
				= declaration_specifiers->get_sibling();
			visit_declaration_specifiers_1(
				declaration_specifiers);
			Type* declaration_specifiers_type
				= declaration_specifiers->get_type();
			if (init_declarator_list) {
				visit_init_declarator_list_1(
					init_declarator_list,
					stack_descriptor,
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_storage_class_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_type_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	Type *type = new Type();
	type->derived_or_basic = DerivedOrBasic::BASIC;
	switch (node->get_alt()) {

		case AstNodeAlt::TYPE_SPECIFIER_1:
		{	
			type->basic = BasicType::VOID;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_2:
		{
			type->basic = BasicType::CHAR;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_3:
		{
			type->basic = BasicType::SHORT;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_4:
		{
			type->basic = BasicType::SIGNED_INT;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_5:
		{
			type->basic = BasicType::SIGNED_LONG;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_6:
		{
			type->basic = BasicType::FLOAT;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_7:
		{
			type->basic = BasicType::DOUBLE;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_8:
		{
			//TODO;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_9:
		{			
			//TODO;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_10:
		{
			type->basic = BasicType::BOOL;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_11:
		{
			type->basic = BasicType::COMPLEX;
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
	
		case AstNodeAlt::TYPE_SPECIFIER_12:
		{
			AnnotatedAstNode* struct_or_union_specifier
				= node->get_child();
			visit_struct_or_union_specifier_1(
				struct_or_union_specifier);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_13:
		{
			AnnotatedAstNode* enum_specifier
				= node->get_child();
			visit_enum_specifier_1(
				enum_specifier);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TYPE_SPECIFIER_14:
		{
			AnnotatedAstNode* typedef_name
				= node->get_child();
			visit_typedef_name_1(
				typedef_name);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}
		default:
			break;

	}
	node->set_type(type);
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_function_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_SPECIFIERS_1:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_2:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_3:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_4:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declaration_specifiers_1(
	AnnotatedAstNode* const& node) 
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_SPECIFIERS_1:
	{
		AnnotatedAstNode* storage_class_specifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= storage_class_specifier->get_sibling();
		visit_storage_class_specifier_1(
			storage_class_specifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
			node->set_type(declaration_specifiers->get_type());
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
		visit_type_specifier_1(
			type_specifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
		}
		node->set_type(type_specifier->get_type());
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_3:
	{
		AnnotatedAstNode* type_qualifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= type_qualifier->get_sibling();
		visit_type_qualifier_1(
			type_qualifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);		
			node->set_type(declaration_specifiers->get_type());
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
		visit_function_specifier_1(
			function_specifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
			node->set_type(declaration_specifiers->get_type());
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declaration_specifiers_list_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_SPECIFIERS_1:
	{
		AnnotatedAstNode* storage_class_specifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifers
			= storage_class_specifier->get_sibling();
		visit_storage_class_specifier_1(
			storage_class_specifier);
		if (declaration_specifers) {
			visit_declaration_specifiers_1(
				declaration_specifers);
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
		visit_type_specifier_1(
			type_specifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_3:
	{
		AnnotatedAstNode* type_qualifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= type_qualifier->get_sibling();
		visit_type_qualifier_1(
			type_qualifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
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
		visit_function_specifier_1(
			function_specifier);
		if (declaration_specifiers) {
			visit_declaration_specifiers_1(
				declaration_specifiers);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_init_declarator_2(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_parent()->get_name()) {

	case AstNodeName::INIT_DECLARATOR_LIST:
		//visit_init_declarator_list_2();
		//TODO;
		break;

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_init_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& declaration_scope,
	Type*& const declaration_specifier_type,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::INIT_DECLARATOR_1:
	{
		AnnotatedAstNode* declarator
			= node->get_child();
		visit_declarator_1(
			declarator,
			stack_descriptor,
			file,
			declaration_scope,
			declaration_scope,
			declaration_specifier_type);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::INIT_DECLARATOR_2:
	{
		AnnotatedAstNode* declarator
			= node->get_child();
		AnnotatedAstNode* initializer
			= declarator->get_sibling();
		visit_declarator_1(
			declarator,
			stack_descriptor,
			file,
			declaration_scope,
			declaration_scope,
			declaration_specifier_type);
		visit_initializer_1(
			initializer,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_init_declarator_list_2(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_parent()->get_name()) {

	case AstNodeName::INIT_DECLARATOR_LIST:
		//visit_init_declarator_list_2();
		//TODO;
		break;

	case AstNodeName::DECLARATION:
		//visit_declaration_2();
		//TODO;
		break;

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_init_declarator_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	Type*& const declaration_specifier_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::INIT_DECLARATOR_LIST_1:
	{
		AnnotatedAstNode* init_declarator
			= node->get_child();
		visit_init_declarator_1(
			init_declarator,
			stack_descriptor,
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
		visit_init_declarator_list_1(
			init_declarator_list,
			stack_descriptor,
			file,
			declaration_scope,
			declaration_specifier_type);
		visit_init_declarator_1(
			init_declarator,
			stack_descriptor,
			declaration_scope,
			declaration_specifier_type,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_enum_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {
		//todo
	case AstNodeAlt::TYPE_SPECIFIER_1:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_2:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_3:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_4:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_5:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_6:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_7:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_8:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_9:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_10:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_11:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_12:
	{
		AnnotatedAstNode* struct_or_union_specifier
			= node->get_child();
		visit_struct_or_union_specifier_1(
			struct_or_union_specifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_SPECIFIER_13:
	{
		AnnotatedAstNode* enum_specifier
			= node->get_child();
		visit_enum_specifier_1(
			enum_specifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_SPECIFIER_14:
	{
		AnnotatedAstNode* typedef_name
			= node->get_child();
		visit_typedef_name_1(
			typedef_name);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_typedef_name_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {
		//todo
	case AstNodeAlt::TYPE_SPECIFIER_1:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_2:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_3:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_4:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_5:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_6:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_7:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_8:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_9:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_10:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_11:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	case AstNodeAlt::TYPE_SPECIFIER_12:
	{
		AnnotatedAstNode* struct_or_union_specifier
			= node->get_child();
		visit_struct_or_union_specifier_1(
			struct_or_union_specifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_SPECIFIER_13:
	{
		AnnotatedAstNode* enum_specifier
			= node->get_child();
		visit_enum_specifier_1(
			enum_specifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_SPECIFIER_14:
	{
		AnnotatedAstNode* typedef_name
			= node->get_child();
		visit_typedef_name_1(
			typedef_name);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_or_union_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_or_union_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::STRUCT_OR_UNION_1:
	case AstNodeAlt::STRUCT_OR_UNION_2:
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_declaration_list_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::STRUCT_DECLARATION_LIST_1:
	{
		AnnotatedAstNode* struct_declaration
			= node->get_child();
		visit_struct_declaration_1(
			struct_declaration,
			file,
			declaration_scope,
			stack_descriptor);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STRUCT_DECLARATION_LIST_2:
	{
		AnnotatedAstNode* struct_declaration_list
			= node->get_child();
		AnnotatedAstNode* struct_declaration
			= struct_declaration_list->get_sibling();
		visit_struct_declaration_list_1(
			struct_declaration_list,
			file,
			declaration_scope,
			stack_descriptor);
		visit_struct_declaration_1(
			struct_declaration,
			file,
			declaration_scope,
			stack_descriptor);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_declaration_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::STRUCT_DECLARATION_1:
	{
		AnnotatedAstNode* specifier_qualifier_list
			= node->get_child();
		AnnotatedAstNode* struct_declarator_list
			= specifier_qualifier_list->get_sibling();
		visit_specifier_qualifier_list_1(
			specifier_qualifier_list);
		visit_struct_declarator_list_1(
			struct_declarator_list,
			declaration_scope,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_specifier_qualifier_list_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::SPECIFIER_QUALIFIER_LIST_1:
	{
		AnnotatedAstNode* type_specifier
			= node->get_child();
		AnnotatedAstNode* specifier_qualifier_list
			= type_specifier->get_sibling();
		visit_type_specifier_1(
			type_specifier);
		if (type_specifier) {
			visit_specifier_qualifier_list_1(
				specifier_qualifier_list);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::SPECIFIER_QUALIFIER_LIST_2:
	{
		AnnotatedAstNode* type_qualifier
			= node->get_child();
		AnnotatedAstNode* specifier_qualifier_list
			= type_qualifier->get_sibling();
		if (type_qualifier) {
			visit_specifier_qualifier_list_1(
				specifier_qualifier_list);
		}
		visit_type_qualifier_1(
			type_qualifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_declarator_list_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::STRUCT_DECLARATOR_LIST_1:
	{
		AnnotatedAstNode* struct_declarator
			= node->get_child();
		Type* type = NULL;
		visit_struct_declarator_1(
			struct_declarator,
			declaration_scope,
			stack_descriptor,
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
		Type* type = NULL;
		visit_struct_declarator_list_1(
			struct_declarator_list,
			declaration_scope,
			stack_descriptor,
			file);
		visit_struct_declarator_1(
			struct_declarator,
			declaration_scope,
			stack_descriptor,
			type,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_struct_declarator_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& declaration_scope,
	StackDescriptor* const& stack_descriptor,
	Type*& const declaration_specifier_type,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	switch (node->get_alt()) {

	case AstNodeAlt::STRUCT_DECLARATOR_LIST_1:
	{
		AnnotatedAstNode* declarator
			= node->get_child();
		visit_declarator_1(
			declarator,
			stack_descriptor,
			file,
			declaration_scope,
			declaration_scope,
			declaration_specifier_type);
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
		if (declarator) {
			visit_declarator_1(
				declarator,
				stack_descriptor,
				file,
				declaration_scope,
				declaration_scope,
				declaration_specifier_type);
		}
		visit_constant_expression_1(
			constant_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}


static inline SemanticAnnotatorExitCode visit_enumerator_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ENUMERATOR_LIST_1:
	{
		AnnotatedAstNode* enumerator
			= node->get_child();
		visit_enumerator_1(
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
		visit_enumerator_list_1(
			enumerator_list);
		visit_enumerator_1(
			enumerator);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_enumerator_list_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ENUMERATOR_LIST_1:
	{
		AnnotatedAstNode* enumerator
			= node->get_child();
		visit_enumerator_1(
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
		visit_enumerator_list_1(
			enumerator_list);
		visit_enumerator_1(
			enumerator);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_enumeration_specifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
		visit_enumerator_list_1(
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_type_qualifier_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::TYPE_QUALIFIER_1:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_QUALIFIER_2:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_QUALIFIER_3:
	{
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declarator_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_parent()->get_name()) {

		case AstNodeName::INIT_DECLARATOR:
			//visit_init_declarator_2();
			//TODO;
			break;

		case AstNodeName::STRUCT_DECLARATOR:
			//visit_struct_declarator_2();
			//TODO;
			break;

		case AstNodeName::DIRECT_DECLARATOR:
			//visit_direct_declarator_2();
			break;

		case AstNodeName::PARAMETER_DECLARATION:
			//visit_parameter_declaration_2();
			//TODO;
			break;

		case AstNodeName::FUNCTION_DEFINITION:
			visit_function_definition_2(
				node->get_parent(),
				file,
				symbol);
			break;

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	SymbolTable* const& parameter_type_list_scope,
	Type* const& declaration_specifier_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
			Type* used_type = declaration_specifier_type;
			if (pointer) {
				visit_pointer_1(
					pointer);
				used_type = new Type;
				used_type->derived_or_basic = DerivedOrBasic::DERIVED;
				used_type->t = declaration_specifier_type;
				used_type->derived_type_name = DerivedType::POINTER;
			}
			visit_direct_declarator_1(
				direct_declarator,
				file,
				declaration_scope,
				parameter_type_list_scope,
				stack_descriptor,
				used_type);
			node->set_symbol(direct_declarator->get_symbol());
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	switch (node->get_parent()->get_name()) {

		case AstNodeName::INIT_DECLARATOR:
			//visit_init_declarator_2();
			//TODO;
			break;

		case AstNodeName::STRUCT_DECLARATOR:
			//visit_struct_declarator_2();
			//TODO;
			break;

		case AstNodeName::DIRECT_DECLARATOR:
			//visit_direct_declarator_2();
			//TODO;
			break;

		case AstNodeName::PARAMETER_DECLARATION:
			//visit_parameter_declaration_2();
			//TODO;
			break;

		case AstNodeName::FUNCTION_DEFINITION:
			//visit_function_definition_2();
			//TODO;
			break;

		default:
			break;

	}

	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_direct_declarator_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_parent()->get_name()) {

		case AstNodeName::DIRECT_DECLARATOR:
			visit_direct_declarator_2(
				node->get_parent(),
				file,
				symbol);
			break;

		case AstNodeName::DECLARATOR:
			visit_declarator_2(
				node->get_parent(),
				file,
				symbol);
			break;

		default:
			break;
	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_direct_declarator_1(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope,
	SymbolTable* const& parameter_type_list_scope,
	StackDescriptor* const& stack_descriptor,
	Type* const& declaration_specifier_type)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DIRECT_DECLARATOR_1:
	{
		AnnotatedAstNode* identifier
			= node->get_child();
		Token* identifier_terminal
			= identifier->get_terminal();
		const char* identifier_lexeme
			= identifier_terminal->get_lexeme();
		declaration_scope->add_entry(
			identifier_lexeme);
		SymbolTableEntry* e 
			= declaration_scope->get_entry(identifier_lexeme);
		e->type = declaration_specifier_type;
		visit_direct_declarator_2(
			node,
			declaration_scope,
			identifier_lexeme);
		node->set_symbol(identifier_lexeme);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DIRECT_DECLARATOR_2:
	{
		AnnotatedAstNode* declarator
			= node->get_child();
		visit_declarator_1(
			declarator,
			stack_descriptor,
			file,
			declaration_scope,
			declaration_scope,
			declaration_specifier_type);
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
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		if (assignment_expression) {
			visit_assignment_expression_1(
				assignment_expression,
				stack_descriptor,
				file);
		}
		node->set_symbol(direct_declarator->get_symbol());
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
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		node->set_symbol(direct_declarator->get_symbol());
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
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		visit_type_qualifier_list_1(
			type_qualifier_list);
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		node->set_symbol(direct_declarator->get_symbol());
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
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		node->set_symbol(direct_declarator->get_symbol());
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DIRECT_DECLARATOR_7:
	{
		AnnotatedAstNode* direct_declarator
			= node->get_child();
		AnnotatedAstNode* parameter_type_list
			= direct_declarator->get_sibling();
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		visit_parameter_type_list_1(
			parameter_type_list,
			stack_descriptor,
			file,
			parameter_type_list_scope);
		node->set_symbol(direct_declarator->get_symbol());
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DIRECT_DECLARATOR_8:
	{
		AnnotatedAstNode* direct_declarator
			= node->get_child();
		AnnotatedAstNode* identifier_list
			= direct_declarator->get_sibling();
		visit_direct_declarator_1(
			direct_declarator,
			file,
			declaration_scope,
			declaration_scope,
			stack_descriptor,
			declaration_specifier_type);
		if (identifier_list) {
			visit_identifier_list_1(
				identifier_list);
		}
		node->set_symbol(direct_declarator->get_symbol());
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_pointer_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::POINTER_1:
	{
		AnnotatedAstNode* type_qualifier_list
			= node->get_child();
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POINTER_2:
	{
		AnnotatedAstNode* type_qualifier_list
			= node->get_child()->get_name()
			== AstNodeName::POINTER
			? node->get_child()
			: NULL;
		AnnotatedAstNode* pointer
			= type_qualifier_list
			? node->get_child()
			: NULL;
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_type_qualifier_list_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::TYPE_QUALIFIER_LIST_1:
	{
		AnnotatedAstNode* type_qualifier
			= node->get_child();
		visit_type_qualifier_1(
			type_qualifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::TYPE_QUALIFIER_LIST_2:
	{
		AnnotatedAstNode* type_qualifier_list
			= node->get_child();
		AnnotatedAstNode* type_qualifier
			= type_qualifier_list->get_sibling();
		visit_type_qualifier_list_1(
			type_qualifier_list);
		visit_type_qualifier_1(
			type_qualifier);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_parameter_type_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file, 
	SymbolTable* const& function_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::PARAMETER_TYPE_LIST_1:
	case AstNodeAlt::PARAMETER_TYPE_LIST_2:
	{
		AnnotatedAstNode* parameter_list
			= node->get_child();
		visit_parameter_list_1(
			parameter_list,
			stack_descriptor,
			file,
			function_scope);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_parameter_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& function_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::PARAMETER_LIST_1:
	{
		AnnotatedAstNode* parameter_declaration
			= node->get_child();
		visit_parameter_declaration_1(
			parameter_declaration,
			stack_descriptor,
			function_scope,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::PARAMETER_LIST_2:
	{
		AnnotatedAstNode* parameter_list
			= node->get_child();
		AnnotatedAstNode* parameter_declaration
			= parameter_list->get_child();
		visit_parameter_list_1(
			parameter_list,
			stack_descriptor,
			file,
			function_scope);
		visit_parameter_declaration_1(
			parameter_declaration,
			stack_descriptor,
			file,
			function_scope);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_parameter_declaration_2(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	AnnotatedAstNode* declaration_specifiers
		= node->get_child();
	AnnotatedAstNode* declarator
		= node->get_child()->get_sibling();

	Type declaration_specifier_type;
	get_declaration_specifiers_type(
		declaration_specifiers,
		declaration_specifier_type);

	const char* declarator_symbol;
	get_declarator_symbol(
		declarator,
		declarator_symbol);

	SymbolTable* st = node->get_symbol_table();

	SymbolTableEntry* e = st->get_entry(declarator_symbol);

	//Type* init_declarator_type;
	//get_init_declarator_type(
	//	node,
	//	declaration_specifier_type,
	//	init_declarator_type);

	e->type = new Type(declaration_specifier_type);

	switch (node->get_alt()) {

	case AstNodeAlt::PARAMETER_DECLARATION_1:
		break;

	case AstNodeAlt::PARAMETER_DECLARATION_2:
		break;

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_parameter_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& function_scope,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	switch (node->get_alt()) {

	case AstNodeAlt::PARAMETER_DECLARATION_1:
	{
		AnnotatedAstNode* declaration_specifiers
			= node->get_child();
		AnnotatedAstNode* declarator
			= declaration_specifiers->get_sibling();
		visit_declaration_specifiers_1(
			declaration_specifiers);
		Type* declaration_specifiers_type
			= declaration_specifiers->get_type();
		visit_declarator_1(
			declarator,
			stack_descriptor,
			file,
			function_scope,
			function_scope,
			declaration_specifiers_type);
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
		visit_declaration_specifiers_1(
			declaration_specifiers);
		if (abstract_declarator) {
			visit_abstract_declarator_1(
				abstract_declarator,
				stack_descriptor,
				file);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_identifier_list_1(
	AnnotatedAstNode* const& node)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
		visit_identifier_list_1(
			identifier_list);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_abstract_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::ABSTRACT_DECLARATOR_1:
	{
		AnnotatedAstNode* pointer
			= node->get_child();
		visit_pointer_1(
			pointer);
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
		if (pointer) {
			visit_pointer_1(
				pointer);
		}
		visit_direct_abstract_declarator_1(
			direct_abstract_declarator,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_direct_abstract_declarator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_1:
	{
		AnnotatedAstNode* abstract_declarator
			= node->get_child();
		visit_abstract_declarator_1(
			abstract_declarator,
			stack_descriptor,
			file);
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
		visit_direct_abstract_declarator_1(
			direct_abstract_declarator,
			stack_descriptor,
			file);
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
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
			? (((direct_abstract_declarator->get_child()->get_name()
				== AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
				? direct_abstract_declarator->get_sibling()
				: NULL))
			: node->get_child();
		AnnotatedAstNode* assignment_expression
			= (node->get_child()->get_name()
				== AstNodeName::DIRECT_ABSTRACT_DECLARATOR)
			? node->get_child()
			: NULL;
		if (direct_abstract_declarator) {
			visit_direct_abstract_declarator_1(
				direct_abstract_declarator,
				stack_descriptor,
				file);
		}
		if (type_qualifier_list) {
			visit_type_qualifier_list_1(
				type_qualifier_list);
		}
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
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
			visit_direct_abstract_declarator_1(
				direct_abstract_declarator,
				stack_descriptor,
				file);
		}
		visit_type_qualifier_list_1(
			type_qualifier_list);
		if (assignment_expression) {
			visit_assignment_expression_1(
				assignment_expression,
				stack_descriptor,
				file);
		}
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
			visit_direct_abstract_declarator_1(
				direct_abstract_declarator,
				stack_descriptor,
				file);
		}
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
			: (node->get_child()
				? node->get_child()
				: NULL);
		visit_direct_abstract_declarator_1(
			direct_abstract_declarator,
			stack_descriptor,
			file);
		SymbolTable* new_scope = new SymbolTable();
		if (parameter_type_list) {
			visit_parameter_type_list_1(
				parameter_type_list,
				stack_descriptor,
				file,
				new_scope);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_initializer_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::INITIALIZER_1:
	{
		AnnotatedAstNode* assignment_expression
			= node->get_child();
		visit_assignment_expression_1(
			assignment_expression,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::INITIALIZER_2:
	case AstNodeAlt::INITIALIZER_3:
	{
		AnnotatedAstNode* initializer_list;
		visit_initializer_list_1(
			initializer_list,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}
	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_initializer_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
			visit_designation_1(
				designation,
				stack_descriptor,
				file);
		}
		visit_initializer_1(
			initializer,
			stack_descriptor,
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
		visit_initializer_list_1(
			initializer_list,
			stack_descriptor,
			file);
		if (designation) {
			visit_designation_1(
				designation,
				stack_descriptor,
				file);
		}
		visit_initializer_1(
			initializer,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_designation_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DESIGNATION_1:
	{
		AnnotatedAstNode* designator_list
			= node->get_child();
		visit_designator_list_1(
			designator_list,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_designator_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DESIGNATOR_LIST_1:
	{
		AnnotatedAstNode* designator
			= node->get_child();
		visit_designator_1(
			designator,
			stack_descriptor,
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
		visit_designator_list_1(
			designator_list,
			stack_descriptor,
			file);
		visit_designator_1(
			designator,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}
	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_designator_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::DESIGNATOR_1:
	{
		AnnotatedAstNode* constant_expression
			= node->get_child();
		visit_constant_expression_1(
			constant_expression,
			stack_descriptor,
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
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_labeled_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::LABELED_STATEMENT_1:
	{
		AnnotatedAstNode* identifier
			= node->get_child();
		AnnotatedAstNode* statement
			= identifier->get_sibling();
		visit_statement_1(
			statement,
			stack_descriptor,
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
		visit_constant_expression_1(
			constant_expression,
			stack_descriptor,
			file);
		visit_statement_1(
			statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::LABELED_STATEMENT_3:
	{
		AnnotatedAstNode* statement
			= node->get_child();
		visit_statement_1(
			statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::STATEMENT_1:
	{
		AnnotatedAstNode* labeled_statement
			= node->get_child();
		visit_labeled_statement_1(
			labeled_statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_2:
	{
		/*AnnotatedAstNode* compound_statement
			= node->get_child();
		visit_compound_statement_1(
			compound_statement,
			stack_descriptor);*/
		//TODO;
		/*exitcode = SemanticAnnotatorExitCode::SUCCESS;*/
		break;
	}

	case AstNodeAlt::STATEMENT_3:
	{
		AnnotatedAstNode* expression_statement
			= node->get_child();
		visit_expression_statement_1(
			expression_statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_4:
	{
		AnnotatedAstNode* selection_statement
			= node->get_child();
		visit_selection_statement_1(
			selection_statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_5:
	{
		AnnotatedAstNode* iteration_statement
			= node->get_child();
		visit_iteration_statement_1(
			iteration_statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_6:
	{
		AnnotatedAstNode* jump_statement
			= node->get_child();
		visit_jump_statement_1(
			jump_statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_compound_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	cout << "semantic-annotator.cpp:"
		<< " entering new scope: block"
		<< endl;

	node->set_symbol_table(new SymbolTable());

	switch (node->get_alt()) {

		case AstNodeAlt::COMPOUND_STATEMENT_1:
		{
			AnnotatedAstNode* block_item_list
				= node->get_child();
			SymbolTable* block_scope = node->get_symbol_table();
			if (block_item_list) {
				visit_block_item_list_1(
					block_item_list,
					stack_descriptor,
					file,
					block_scope);
			}
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_block_item_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& block_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::BLOCK_ITEM_LIST_1:
	{
		AnnotatedAstNode* block_item
			= node->get_child();
		visit_block_item_1(
			block_item,
			stack_descriptor,
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
		visit_block_item_list_1(
			block_item_list,
			stack_descriptor,
			file,
			block_scope);
		visit_block_item_1(
			block_item,
			stack_descriptor,
			file,
			block_scope);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_block_item_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& block_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::BLOCK_ITEM_1:
		{
			AnnotatedAstNode* declaration
				= node->get_child();
			visit_declaration_1(
				declaration,
				stack_descriptor,
				file,
				block_scope);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::BLOCK_ITEM_2:
		{
			AnnotatedAstNode* statement
				= node->get_child();
			visit_statement_1(
				statement,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_expression_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_STATEMENT_1:
		{
			AnnotatedAstNode* expression
				= node->get_child();
			if (expression) {
				visit_expression_1(
					expression,
					stack_descriptor,
					file);
			}
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_selection_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

	case AstNodeAlt::SELECTION_STATEMENT_1:
	case AstNodeAlt::SELECTION_STATEMENT_3:
	{
		AnnotatedAstNode* expression
			= node->get_child();
		AnnotatedAstNode* statement
			= expression->get_sibling();
		visit_expression_1(
			expression,
			stack_descriptor,
			file);
		visit_statement_1(
			statement,
			stack_descriptor,
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
		visit_expression_1(
			expression,
			stack_descriptor,
			file);
		visit_statement_1(
			statement1,
			stack_descriptor,
			file);
		visit_statement_1(
			statement2,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}
	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_iteration_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	SymbolTable* scope = new SymbolTable();
	node->set_symbol_table(scope);
	switch (node->get_alt()) {

	case AstNodeAlt::ITERATION_STATEMENT_1:
	{
		AnnotatedAstNode* expression
			= node->get_child();
		AnnotatedAstNode* statement
			= expression->get_sibling();
		visit_expression_1(
			expression,
			stack_descriptor,
			file);
		visit_statement_1(
			statement,
			stack_descriptor,
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
		visit_statement_1(
			statement,
			stack_descriptor,
			file);
		visit_expression_1(
			expression,
			stack_descriptor,
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
		visit_expression_1(
			expression1,
			stack_descriptor,
			file);
		visit_expression_1(
			expression2,
			stack_descriptor,
			file);
		visit_expression_1(
			expression3,
			stack_descriptor,
			file);
		visit_statement_1(
			statement,
			stack_descriptor,
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
		visit_declaration_1(
			declaration,
			stack_descriptor,
			file,
			scope);
		visit_expression_1(
			expression1,
			stack_descriptor,
			file);
		visit_expression_1(
			expression2,
			stack_descriptor,
			file);
		visit_statement_1(
			statement,
			stack_descriptor,
			file);
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_jump_statement_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
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
			visit_expression_1(
				node->get_child(),
				stack_descriptor,
				file);
		}
		exitcode = SemanticAnnotatorExitCode::SUCCESS;
		break;
	}

	default:
		break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_translation_unit_1(
	AnnotatedAstNode*& const node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable*& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	cout << "semantic-annotator.cpp:entering new scope: file"
		 << endl;

	if (file == NULL) {
		file = new SymbolTable();
		node->set_symbol_table(file);
	}

	switch (node->get_alt()) {

		case AstNodeAlt::TRANSLATION_UNIT_1:
		{
			AnnotatedAstNode* external_declaration
				= node->get_child();
			visit_external_declaration_1(
				external_declaration,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TRANSLATION_UNIT_2:
		{
			AnnotatedAstNode* external_declaration
				= node->get_child();
			visit_external_declaration_1(
				external_declaration,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_external_declaration_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::EXTERNAL_DECLARATION_1:
		{
			AnnotatedAstNode* function_definition
				= node->get_child();
			visit_function_definition_1(
				function_definition,
				stack_descriptor,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXTERNAL_DECLARATION_2:
		{
			AnnotatedAstNode* declaration
				= node->get_child();
			visit_declaration_1(
				declaration,
				stack_descriptor,
				file,
				file);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_function_definition_3(
	AnnotatedAstNode* const& node,
	const char* const& symbol,
	SymbolTable* const& file_scope,
	SymbolTable* const& compound_statement_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
			
	
}

static inline SemanticAnnotatorExitCode visit_function_definition_2(
	AnnotatedAstNode* const& node,
	SymbolTable* const& file,
	const char* const& symbol)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	cout << "semantic-annotator.cpp:entering new scope: function"
		<< endl;

	AnnotatedAstNode* declaration_specifiers
		= node->get_child();
	AnnotatedAstNode* declarator
		= declaration_specifiers->get_sibling();
	AnnotatedAstNode* declaration_list
		= declarator->get_sibling()->get_name() == AstNodeName::DECLARATION_LIST
		  ? declarator->get_sibling()
		  : NULL;
	AnnotatedAstNode* compound_statement
		= declaration_list 
		  ? declaration_list->get_sibling()
		  : declarator->get_sibling();
	Type* declaration_specifier_type
		= declaration_specifiers->get_type();

	const char* declarator_symbol;
	get_declarator_symbol(declarator, declarator_symbol);

	SymbolTable* st = file;
	SymbolTableEntry* e = file->get_entry(declarator_symbol);

	//Type* declarator_type;
	//get_declarator_type(
	//	node,
	//	declaration_specifier_type,
	//	init_declarator_type);

	Type* function_returns = new Type();
	function_returns->derived_or_basic = DerivedOrBasic::DERIVED;
	function_returns->derived_type_name = DerivedType::FUNCTION;
	function_returns->t = declaration_specifier_type;
	e->type = function_returns;

	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_function_definition_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;

	cout << "semantic-annotator.cpp:"
		<< "entering new scope:"
		<< " function"
		<< endl;

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
			visit_declaration_specifiers_1(
				declaration_specifiers);
			Type* declaration_specifiers_type
				= declaration_specifiers->get_type();
			visit_declarator_1(
				declarator,
				stack_descriptor,
				file,
				file,
				function,
				declaration_specifiers_type);
			if (declaration_list) {
				visit_declaration_list_1(
					declaration_list,
					stack_descriptor,
					file,
					function);
			}
			visit_compound_statement_1(
				compound_statement,
				stack_descriptor,
				file);

			int number_formal_parameters = 0;

			/* For each parameter */
			SymbolTable* sym = node->get_symbol_table();
			int base_ptr = 0x0000;
			SymbolTableEntry* entries[1028] = { 0 };
			sym->get_entries(entries);
			for (SymbolTableEntry** e = entries; *e != NULL; e++) {
				number_formal_parameters++;
				(*e)->base_pointer_offset = base_ptr;
				base_ptr += sizeof_map[(int)(*e)->type->basic];
			}
			file->get_entry(declarator->get_symbol())->number_formal_parameters
				= number_formal_parameters;

			/* For each variable */
			SymbolTableEntry* var_entries[1028] = { 0 };
			compound_statement->get_symbol_table()->get_entries(var_entries);
	
			for (SymbolTableEntry** e = var_entries; *e != NULL; e++) {
				(*e)->base_pointer_offset = base_ptr;
				base_ptr += sizeof_map[(int)(*e)->type->basic];
				(*e)->scope = Scope::FUNCTION;
			}
			file->get_entry(declarator->get_symbol())->function_frame_size
				= base_ptr;
			for (SymbolTableEntry** e = var_entries; *e != NULL; e++) {
				(*e)->function_ptr = file->get_entry(declarator->get_symbol());
			}			
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline SemanticAnnotatorExitCode visit_declaration_list_1(
	AnnotatedAstNode* const& node,
	StackDescriptor* const& stack_descriptor,
	SymbolTable* const& file,
	SymbolTable* const& declaration_scope)
{
	SemanticAnnotatorExitCode exitcode
		= SemanticAnnotatorExitCode::FAIL;
	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_LIST_1:
		{
			AnnotatedAstNode* declaration
				= node->get_child();
			visit_declaration_1(
				declaration,
				stack_descriptor,
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
			visit_declaration_list_1(
				declaration_list,
				stack_descriptor,
				file,
				declaration_scope);
			visit_declaration_1(
				declaration,
				stack_descriptor,
				file,
				declaration_scope);
			exitcode = SemanticAnnotatorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline bool annotate(
	AstNode* node,
	AnnotatedAstNode*& anno_node,
	StackDescriptor*& stack_descriptor)
{
	construct_unatrributed_annotated_ast(
		node, anno_node
	);
	stack_descriptor = new StackDescriptor();
	SymbolTable* file = NULL;
	visit_translation_unit_1(
		anno_node,
		stack_descriptor,
		file);
	return true;
}

#endif