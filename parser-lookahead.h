
#ifndef PARSER_LOOKAHEAD_H
#define PARSER_LOOKAHEAD_H 1

#include "token.h"

class LookaheadTable {
public:
	bool lookahead[NUM_TOKEN_NAMES * NUM_TOKEN_FORMS];
};

static inline bool lookup(
	LookaheadTable table,
	TokenName name,  
	TokenForm form)
{
	bool* addr  = 
		table.lookahead
		+ (int) name * NUM_TOKEN_FORMS 
		+ (int) form;
	return *(addr);
}

static inline LookaheadTable construct_lookahead_table(
	const TokenName n)   
{
	LookaheadTable table = { {0} };
	for (int f = 0; f < NUM_TOKEN_FORMS; f++) {
		int h = (int) n * NUM_TOKEN_FORMS + (int)f;
		bool* addr = table.lookahead + h;
		*(addr) = true;
	}
	return table;
}

static inline LookaheadTable construct_lookahead_table(
	const TokenName n,
	const TokenForm f) 
{
	LookaheadTable table = { {0} };
	bool* addr = 
		table.lookahead 
		+ (int) n * NUM_TOKEN_FORMS 
		+ (int) f;
	*addr = true;
	return table;
}

static inline LookaheadTable merge_first_of(
	const LookaheadTable * const* tables)
{
	LookaheadTable table = { {0} };

	for (int i = 0; i < NUM_TOKEN_NAMES * NUM_TOKEN_FORMS; i++) {

		for (const LookaheadTable* const* t = tables; *t != NULL; t++) {

			if (*((*t)->lookahead + i) == true) {
				*(table.lookahead + i) = true;
				break;
			}
		}
	}
	return table;
}

static const LookaheadTable first_of_char =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::CHAR);

static const LookaheadTable first_of_short =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::SHORT);

static const LookaheadTable first_of_int =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::INT);

static const LookaheadTable first_of_long =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::LONG);

static const LookaheadTable first_of_float =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::FLOAT);

static const LookaheadTable first_of_double =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::DOUBLE);

static const LookaheadTable first_of_signed =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::SIGNED);

static const LookaheadTable first_of_bool =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::_BOOL);

static const LookaheadTable first_of_complex =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::_COMPLEX);

static const LookaheadTable first_of_identifier =
	construct_lookahead_table(TokenName::IDENTIFIER);

static const LookaheadTable first_of_constant =
	construct_lookahead_table(TokenName::CONSTANT);

static const LookaheadTable first_of_string_literal =
	construct_lookahead_table(TokenName::STRING_LITERAL);

static const LookaheadTable first_of_open_paren =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::OPEN_PAREN);

static const LookaheadTable first_of_increment =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::INCREMENT);

static const LookaheadTable first_of_decrement =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::DECREMENT);

static const LookaheadTable first_of_sizeof =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::SIZEOF);

static const LookaheadTable first_of_tilde =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::TILDE);

static const LookaheadTable first_of_ampersand =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::AMPERSAND);

static const LookaheadTable first_of_asterix =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::ASTERIX);

static const LookaheadTable first_of_plus =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::PLUS);

static const LookaheadTable first_of_minus =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::MINUS);

static const LookaheadTable first_of_exclamation_mark =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::EXCLAMATION_MARK);

static const LookaheadTable first_of_assign =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::ASSIGN);

static const LookaheadTable first_of_multiply_equal =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::MULTIPLY_EQUAL);

static const LookaheadTable first_of_divide_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::DIVIDE_EQUALS);

static const LookaheadTable first_of_modulo_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::MODULO_EQUALS);

static const LookaheadTable first_of_plus_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::PLUS_EQUALS);

static const LookaheadTable first_of_minus_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::MINUS_EQUALS);

static const LookaheadTable first_of_left_shift_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::LEFT_SHIFT_EQUALS);

static const LookaheadTable first_of_right_shift_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::RIGHT_SHIFT_EQUALS);

static const LookaheadTable first_of_ampersand_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::AMPERSAND_EQUAL);

static const LookaheadTable first_of_xor_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::XOR_EQUAL);

static const LookaheadTable first_of_not_equals =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::NOT_EQUAL);

static const LookaheadTable first_of_void =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::VOID);

static const LookaheadTable first_of_unsigned =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::UNSIGNED);

static const LookaheadTable first_of_volatile =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::VOLATILE);

static const LookaheadTable first_of_enumeration_constant =
	construct_lookahead_table(
		TokenName::CONSTANT,
		TokenForm::ENUMERATION_CONSTANT);

static const LookaheadTable first_of_typedef =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::TYPEDEF);

static const LookaheadTable first_of_extern =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::EXTERN);

static const LookaheadTable first_of_static =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::STATIC);

static const LookaheadTable first_of_auto =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::AUTO);

static const LookaheadTable first_of_register =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::REGISTER);

static const LookaheadTable first_of_struct =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::STRUCT);

static const LookaheadTable first_of_union =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::UNION);

static const LookaheadTable first_of_colon =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::COLON);

static const LookaheadTable first_of_enum =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::ENUM);

static const LookaheadTable first_of_const =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::CONST);

static const LookaheadTable first_of_restrict =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::RESTRICT);

static const LookaheadTable first_of_inline =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::INLINE);

static const LookaheadTable first_of_open_bracket =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::INLINE);

static const LookaheadTable first_of_open_curly_bracket =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::OPEN_CURLY_BRACKET);

static const LookaheadTable first_of_dot =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::DOT);

static const LookaheadTable first_of_case =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::CASE);

static const LookaheadTable first_of_default =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::DEFAULT);

static const LookaheadTable first_of_goto =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::GOTO);

static const LookaheadTable first_of_continue =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::CONTINUE);

static const LookaheadTable first_of_break =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::BREAK);

static const LookaheadTable first_of_return =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::RETURN);

static const LookaheadTable first_of_while =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::WHILE);

static const LookaheadTable first_of_do =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::DO);

static const LookaheadTable first_of_for =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::FOR);

static const LookaheadTable first_of_if =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::IF);

static const LookaheadTable first_of_switch =
	construct_lookahead_table(
		TokenName::KEYWORD,
		TokenForm::SWITCH);

static const LookaheadTable first_of_semicolon =
	construct_lookahead_table(
		TokenName::PUNCTUATOR,
		TokenForm::SEMI_COLON);

static const LookaheadTable *first_of_primary_expression_subtables[] {
	&first_of_identifier,
	&first_of_constant,
	&first_of_string_literal,
	&first_of_open_paren,
	NULL
};

static const LookaheadTable first_of_primary_expression =
	merge_first_of(first_of_primary_expression_subtables);

static const LookaheadTable* first_of_postfix_expression_subtables[] = {
	&first_of_primary_expression,
	&first_of_open_paren,
	NULL
};

static const LookaheadTable first_of_postfix_expression =
	merge_first_of(first_of_postfix_expression_subtables);

static const LookaheadTable* first_of_unary_operator_subtables[] = {
	&first_of_ampersand,
	&first_of_asterix,
	&first_of_plus,
	&first_of_minus,
	&first_of_tilde,
	&first_of_exclamation_mark,
	NULL
};

static const LookaheadTable first_of_unary_operator =
	merge_first_of(first_of_unary_operator_subtables);

static const LookaheadTable* first_of_unary_expression_subtables[] = {
	&first_of_postfix_expression,
	&first_of_increment,
	&first_of_decrement,
	&first_of_unary_operator,
	&first_of_sizeof,
	NULL
};

static const LookaheadTable first_of_unary_expression =
	merge_first_of(first_of_unary_expression_subtables);

static const LookaheadTable* first_of_cast_expression_subtables[] = {
	&first_of_unary_expression,
	&first_of_open_paren,
	NULL
};

static const LookaheadTable first_of_cast_expression =
	merge_first_of(first_of_cast_expression_subtables);

static const LookaheadTable* first_of_multiplicative_expression_subtables[] = {
	&first_of_cast_expression,
	NULL
};

static const LookaheadTable first_of_multiplicative_expression =
	merge_first_of(first_of_multiplicative_expression_subtables);

static const LookaheadTable* first_of_additive_expression_subtables[] = {
	&first_of_multiplicative_expression,
	NULL
};

static const LookaheadTable first_of_additive_expression =
	merge_first_of(first_of_additive_expression_subtables);

static const LookaheadTable* first_of_shift_expression_subtables[] = {
	&first_of_additive_expression,
	NULL
};

static const LookaheadTable first_of_shift_expression =
	merge_first_of(first_of_shift_expression_subtables);

static const LookaheadTable* first_of_relational_expression_subtables[] = {
	&first_of_shift_expression,
	NULL
};

static const LookaheadTable first_of_relational_expression =
	merge_first_of(first_of_relational_expression_subtables);

static const LookaheadTable* first_of_equality_expression_subtables[] = {
	&first_of_relational_expression,
	NULL
};

static LookaheadTable first_of_equality_expression =
	merge_first_of(first_of_equality_expression_subtables);

static const LookaheadTable* first_of_and_expression_subtables[] = {
	&first_of_equality_expression,
	NULL
};

static const LookaheadTable first_of_and_expression =
	merge_first_of(first_of_and_expression_subtables);

static const LookaheadTable* first_of_exclusive_or_expression_subtables[] = {
	&first_of_and_expression,
	NULL
};

static const LookaheadTable first_of_exclusive_or_expression =
	merge_first_of(first_of_exclusive_or_expression_subtables);

static const LookaheadTable* first_of_inclusive_or_expression_subtables[] = {
	&first_of_exclusive_or_expression,
	NULL
};

static const LookaheadTable first_of_inclusive_or_expression =
	merge_first_of(first_of_inclusive_or_expression_subtables);

static const LookaheadTable* first_of_logical_and_expression_subtables[] = {
	&first_of_inclusive_or_expression,
	NULL
};

static const LookaheadTable first_of_logical_and_expression =
	merge_first_of(first_of_logical_and_expression_subtables);

static const LookaheadTable* first_of_logical_or_expression_subtables[] = {
	&first_of_inclusive_or_expression,
	NULL
};

static const LookaheadTable first_of_logical_or_expression =
	merge_first_of(first_of_logical_or_expression_subtables);

static const LookaheadTable* first_of_conditional_expression_subtables[] = {
	&first_of_logical_or_expression,
	NULL
};

static const LookaheadTable first_of_conditional_expression =
	merge_first_of(first_of_conditional_expression_subtables);

static const LookaheadTable* first_of_assignment_expression_subtables[] = {
	&first_of_conditional_expression,
	&first_of_unary_expression,
	NULL
};

static const LookaheadTable first_of_assignment_expression =
	merge_first_of(first_of_assignment_expression_subtables);

static const LookaheadTable* first_of_argument_expression_list_subtables[] = {
	&first_of_assignment_expression,
	NULL
};

static const LookaheadTable first_of_argument_expression_list =
	merge_first_of(first_of_primary_expression_subtables);

static const LookaheadTable* first_of_assignment_operator_subtables[] = {
	&first_of_assign,
	&first_of_multiply_equal,
	&first_of_divide_equals,
	&first_of_modulo_equals,
	&first_of_plus_equals,
	&first_of_minus_equals,
	&first_of_left_shift_equals,
	&first_of_right_shift_equals,
	&first_of_ampersand_equals,
	&first_of_xor_equals,
	&first_of_divide_equals,
	NULL
};

static const LookaheadTable first_of_assignment_operator =
	merge_first_of(first_of_assignment_operator_subtables);

static const LookaheadTable* first_of_direct_declarator_subtables[] = {
	&first_of_open_paren,
	&first_of_identifier,
	NULL
};

static const LookaheadTable first_of_direct_declarator =
	merge_first_of(first_of_direct_declarator_subtables);

static const LookaheadTable* first_of_pointer_subtables[] = {
	&first_of_asterix,
	NULL
};

static const LookaheadTable first_of_pointer =
	merge_first_of(first_of_pointer_subtables);

static const LookaheadTable* first_of_declarator_subtables[] = {
	&first_of_pointer,
	&first_of_direct_declarator,
	NULL
};

static const LookaheadTable first_of_declarator =
	merge_first_of(first_of_declarator_subtables);

static const LookaheadTable* first_of_init_declarator_subtables[] = {
	&first_of_declarator,
	NULL
};

static const LookaheadTable first_of_init_declarator =
	merge_first_of(first_of_init_declarator_subtables);

static const LookaheadTable* first_of_constant_expression_subtables[] = {
	&first_of_conditional_expression,
	NULL
};

static const LookaheadTable first_of_constant_expression =
	merge_first_of(first_of_constant_expression_subtables);


static const LookaheadTable* first_of_init_declarator_list_subtables[] = {
	&first_of_init_declarator,
	NULL
};

static const LookaheadTable first_of_init_declarator_list =
	merge_first_of(first_of_init_declarator_list_subtables);


static const LookaheadTable* first_of_storage_class_specifier_subtables[] = {
	&first_of_typedef,
	&first_of_extern,
	&first_of_static,
	&first_of_auto,
	&first_of_register,
	NULL
};

static const LookaheadTable first_of_storage_class_specifier =
	merge_first_of(first_of_storage_class_specifier_subtables);

static const LookaheadTable* first_of_struct_or_union_subtables[] = {
	&first_of_struct,
	&first_of_union,
	NULL
};

static const LookaheadTable first_of_struct_or_union =
	merge_first_of(first_of_struct_or_union_subtables);

static const LookaheadTable* first_of_struct_or_union_specifier_subtables[] = {
	&first_of_struct_or_union,
	NULL
};

static const LookaheadTable first_of_struct_or_union_specifier =
	merge_first_of(first_of_struct_or_union_specifier_subtables);

static const LookaheadTable* first_of_enum_specifier_subtables[] = {
	&first_of_enum,
	NULL
};

static const LookaheadTable first_of_enum_specifier =
	merge_first_of(first_of_enum_specifier_subtables);

static const LookaheadTable* first_of_typedef_name_subtables[] = {
	&first_of_identifier,
	NULL
};

static const LookaheadTable first_of_typedef_name =
	merge_first_of(first_of_typedef_name_subtables);

static const LookaheadTable* first_of_type_specifier_subtables[] = {
	&first_of_void,
	&first_of_char,
	&first_of_short,
	&first_of_int,
	&first_of_long,
	&first_of_float,
	&first_of_double,
	&first_of_signed,
	&first_of_unsigned,
	&first_of_bool,
	&first_of_complex,
	&first_of_struct_or_union_specifier,
	&first_of_enum_specifier,
	&first_of_typedef_name,
	NULL
};

static const LookaheadTable first_of_type_specifier =
	merge_first_of(first_of_type_specifier_subtables);

static const LookaheadTable* first_of_type_qualifier_subtables[] = {
	&first_of_const,
	&first_of_restrict,
	&first_of_volatile,
	NULL
};

static const LookaheadTable first_of_type_qualifier =
	merge_first_of(first_of_type_qualifier_subtables);


static const LookaheadTable* first_of_specifier_qualifier_list_subtables[] = {
	&first_of_type_specifier,
	&first_of_type_qualifier,
	NULL
};

static const LookaheadTable first_of_specifier_qualifier_list =
	merge_first_of(first_of_specifier_qualifier_list_subtables);

static const LookaheadTable* first_of_struct_declaration_subtables[] = {
	&first_of_specifier_qualifier_list,
	NULL
};

static const LookaheadTable first_of_struct_declaration =
merge_first_of(first_of_struct_declaration_subtables);

static const LookaheadTable* first_of_struct_declaration_list_subtables[] = {
	&first_of_struct_declaration,
	NULL
};

static const LookaheadTable first_of_struct_declaration_list =
	merge_first_of(first_of_struct_declaration_list_subtables);

static const LookaheadTable* first_of_function_specifier_subtables[] = {
	&first_of_inline,
	NULL
};

static const LookaheadTable first_of_function_specifier =
merge_first_of(first_of_function_specifier_subtables);

static const LookaheadTable* first_of_declaration_specifiers_subtables[] = {
	&first_of_storage_class_specifier,
	&first_of_type_specifier,
	&first_of_type_qualifier,
	&first_of_function_specifier,
	NULL
};

static const LookaheadTable first_of_declaration_specifiers =
	merge_first_of(first_of_declaration_specifiers_subtables);

static const LookaheadTable* first_of_declaration_subtables[] = {
	&first_of_declaration_specifiers,
	NULL
};

static const LookaheadTable first_of_declaration =
merge_first_of(first_of_declaration_subtables);

static const LookaheadTable* first_of_struct_declarator_subtables[] = {
	&first_of_declarator,
	NULL
};

static const LookaheadTable first_of_struct_declarator =
	merge_first_of(first_of_struct_declarator_subtables);

static const LookaheadTable* first_of_struct_declarator_list_subtables[] = {
	&first_of_struct_declarator,
	NULL
};

static const LookaheadTable first_of_struct_declarator_list =
	merge_first_of(first_of_struct_declarator_list_subtables);

static const LookaheadTable* first_of_enumerator_subtables[] = {
	&first_of_enumeration_constant,
	NULL
};
static const LookaheadTable first_of_enumerator =
	merge_first_of(first_of_enumerator_subtables);

static const LookaheadTable* first_of_enumerator_list_subtables[] = {
	&first_of_enumerator,
	NULL
};

static const LookaheadTable first_of_enumerator_list =
	merge_first_of(first_of_enumerator_list_subtables);

static const LookaheadTable* first_of_type_qualifier_list_subtables[] = {
	&first_of_type_qualifier,
	NULL
};

static const LookaheadTable first_of_type_qualifier_list =
	merge_first_of(first_of_type_qualifier_list_subtables);

static const LookaheadTable* first_of_parameter_declaration_subtables[] = {
	&first_of_declaration_specifiers,
	NULL
};

static const LookaheadTable first_of_parameter_declaration =
	merge_first_of(first_of_parameter_declaration_subtables);


static const LookaheadTable* first_of_parameter_list_subtables[] = {
	&first_of_parameter_declaration,
	NULL
};

static const LookaheadTable first_of_parameter_list =
	merge_first_of(first_of_parameter_list_subtables);

static const LookaheadTable* first_of_parameter_type_list_subtables[] = {
	&first_of_parameter_list,
	NULL
};

static const LookaheadTable first_of_parameter_type_list =
	merge_first_of(first_of_parameter_type_list_subtables);

static const LookaheadTable* first_of_identifier_list_subtables[] = {
	&first_of_identifier,
	NULL
};

static const LookaheadTable first_of_identifier_list =
	merge_first_of(first_of_identifier_list_subtables);

static const LookaheadTable* first_of_type_name_subtables[] = {
	&first_of_specifier_qualifier_list,
	NULL
};

static const LookaheadTable first_of_type_name_list =
	merge_first_of(first_of_type_name_subtables);


static const LookaheadTable* first_of_direct_abstract_declarator_subtables[] = {
	&first_of_open_paren,
	&first_of_open_bracket,
	NULL
};

static const LookaheadTable first_of_direct_abstract_declarator =
	merge_first_of(first_of_direct_abstract_declarator_subtables);

static const LookaheadTable* first_of_abstract_declarator_subtables[] = {
	&first_of_pointer,
	&first_of_direct_abstract_declarator,
	NULL
};

static const LookaheadTable first_of_abstract_declarator =
	merge_first_of(first_of_abstract_declarator_subtables);

static const LookaheadTable* first_of_initializer_subtables[] = {
	&first_of_assignment_expression,
	&first_of_open_curly_bracket,
	NULL
};

static const LookaheadTable first_of_initializer =
	merge_first_of(first_of_initializer_subtables);


static const LookaheadTable* first_of_designator_subtables[] = {
	&first_of_open_bracket,
	&first_of_dot,
	NULL
};

static const LookaheadTable first_of_designator =
	merge_first_of(first_of_designator_subtables);

static const LookaheadTable* first_of_designator_list_subtables[] = {
	&first_of_designator,
	NULL
};

static const LookaheadTable first_of_designator_list =
	merge_first_of(first_of_designator_list_subtables);

static const LookaheadTable* first_of_designation_subtables[] = {
	&first_of_designator_list,
	NULL
};

static const LookaheadTable first_of_designation =
	merge_first_of(first_of_designation_subtables);

static const LookaheadTable* first_of_initializer_list_subtables[] = {
	&first_of_designation,
	&first_of_initializer,
	NULL
};

static const LookaheadTable first_of_initializer_list =
	merge_first_of(first_of_initializer_list_subtables);

static const LookaheadTable* first_of_jump_statement_subtables[] = {
	&first_of_goto,
	&first_of_continue,
	&first_of_break,
	&first_of_return,
	NULL
};

static const LookaheadTable first_of_jump_statement =
	merge_first_of(first_of_jump_statement_subtables);

static const LookaheadTable* first_of_iteration_statement_subtables[] = {
	&first_of_while,
	&first_of_do,
	&first_of_for,
	NULL
};

static const LookaheadTable first_of_iteration_statement =
	merge_first_of(first_of_iteration_statement_subtables);

static const LookaheadTable* first_of_selection_statement_subtables[] = {
	&first_of_if,
	&first_of_switch,
	NULL
};

static const LookaheadTable first_of_selection_statement =
	merge_first_of(first_of_selection_statement_subtables);

static const LookaheadTable* first_of_expression_subtables[] = {
	&first_of_assignment_expression,
	NULL
};

static const LookaheadTable first_of_expression =
	merge_first_of(first_of_expression_subtables);

static const LookaheadTable* first_of_expression_statement_subtables[] = {
	&first_of_expression,
	&first_of_semicolon,
	NULL
};

static const LookaheadTable first_of_expression_statement =
	merge_first_of(first_of_expression_statement_subtables);

static const LookaheadTable* first_of_compound_statement_subtables[] = {
	&first_of_open_curly_bracket,
	NULL
};

static const LookaheadTable first_of_compound_statement =
	merge_first_of(first_of_compound_statement_subtables);

static const LookaheadTable* first_of_labeled_statement_subtables[] = {
	&first_of_identifier,
	&first_of_case,
	&first_of_default,
	NULL
};

static const LookaheadTable first_of_labeled_statement =
	merge_first_of(first_of_labeled_statement_subtables);

static const LookaheadTable* first_of_statement_subtables[] = {
	&first_of_labeled_statement,
	&first_of_compound_statement,
	&first_of_expression_statement,
	&first_of_selection_statement,
	&first_of_iteration_statement,
	&first_of_jump_statement,
	NULL
};

static const LookaheadTable first_of_statement =
	merge_first_of(first_of_statement_subtables);

static const LookaheadTable* first_of_block_item_subtables[] = {
	&first_of_declaration,
	&first_of_statement,
	NULL
};

static const LookaheadTable first_of_block_item =
	merge_first_of(first_of_block_item_subtables);

static const LookaheadTable* first_of_block_item_list_subtables[] = {
	&first_of_block_item,
	NULL
};

static const LookaheadTable first_of_block_item_list =
	merge_first_of(first_of_block_item_list_subtables);

static const LookaheadTable* first_of_function_definition_subtables[] = {
	&first_of_declaration_specifiers,
	NULL
};

static const LookaheadTable first_of_function_definition =
	merge_first_of(first_of_function_definition_subtables);

static const LookaheadTable* first_of_external_declaration_subtables[] = {
	&first_of_function_definition,
	&first_of_declaration,
	NULL
};

static const LookaheadTable first_of_external_declaration =
	merge_first_of(first_of_external_declaration_subtables);

static const LookaheadTable* first_of_translation_unit_subtables[] = {
	&first_of_external_declaration,
	NULL
};

static const LookaheadTable first_of_translation_unit =
	merge_first_of(first_of_translation_unit_subtables);

static const LookaheadTable* first_of_declaration_list_subtables[] = {
	&first_of_declaration,
	NULL
};

static const LookaheadTable first_of_declaration_list =
merge_first_of(first_of_declaration_list_subtables);


#endif