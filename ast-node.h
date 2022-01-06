
#ifndef AST_NODE_CPP
#define AST_NODE_CPP 1

#include "token.h"
#include <cstddef>
#include <iostream>

using namespace std;

enum class AstNodeName {
	/* Error */
	ERROR = 0,
	/* Terminals */
	KEYWORD,
	IDENTIFIER,
	CONSTANT,
	STRING_LITERAL,
	PUNCTUATOR,
	/* Nonterminals */
	PRIMARY_EXPRESSION,
	EXPRESSION,
	POSTFIX_EXPRESSION,
	ARGUMENT_EXPRESSION_LIST,
	ASSIGNMENT_EXPRESSION,
	TYPE_NAME,
	INITIALIZER_LIST,
	UNARY_EXPRESSION,
	CAST_EXPRESSION,
	UNARY_OPERATOR,
	MULTIPLICATIVE_EXPRESSION,
	ADDITIVE_EXPRESSION,
	SHIFT_EXPRESSION,
	RELATIONAL_EXPRESSION,
	EQUALITY_EXPRESSION,
	AND_EXPRESSION,
	EXCLUSIVE_OR_EXPRESSION,
	LOGICAL_AND_EXPRESSION,
	INCLUSIVE_OR_EXPRESSION,
	LOGICAL_OR_EXPRESSION,
	CONDITIONAL_EXPRESSION,
	ASSIGNMENT_OPERATOR,
	CONSTANT_EXPRESSION,
	DECLARATION,
	DECLARATION_SPECIFIERS,
	INIT_DECLARATOR_LIST,
	STORAGE_CLASS_SPECIFIER,
	TYPE_SPECIFIER,
	TYPE_QUALIFIER,
	FUNCTION_SPECIFIER,
	INIT_DECLARATOR,
	INITIALIZER,
	STRUCT_OR_UNION,
	STRUCT_OR_UNION_SPECIFIER,
	STRUCT_DECLARATION_LIST,
	STRUCT_DECLARATION,
	STRUCT_DECLARATOR_LIST,
	STRUCT_DECLARATOR,
	SPECIFIER_QUALIFIER_LIST,
	ENUM_SPECIFIER,
	ENUMERATOR_LIST,
	ENUMERATOR,
	ENUMERATION_CONSTANT,
	TYPEDEF_NAME,
	POINTER,
	DIRECT_DECLARATOR,
	TYPE_QUALIFIER_LIST,
	PARAMETER_TYPE_LIST,
	PARAMETER_LIST,
	PARAMETER_DECLARATION,
	DECLARATION_SPECIFIER,
	IDENTIFIER_LIST,
	DIRECT_ABSTRACT_DECLARATOR,
	ABSTRACT_DECLARATOR,
	DESIGNATION,
	DESIGNATOR_LIST,
	DESIGNATOR,
	STATEMENT,
	LABELED_STATEMENT,
	COMPOUND_STATEMENT,
	EXPRESSION_STATEMENT,
	SELECTION_STATEMENT,
	ITERATION_STATEMENT,
	JUMP_STATEMENT,
	TRANSLATION_UNIT,
	EXTERNAL_DECLARATION,
	FUNCTION_DEFINITION,
	PREPROCESSING_FILE,
	GROUP,
	GROUP_PART,
	IF_SECTION,
	TEXT_LINE,
	NON_DIRECTIVE,
	IF_GROUP,
	ELIF_GROUPS,
	ELIF_GROUP,
	ELSE_GROUP,
	ENDIF_LINE,
	CONTROL_LINE,
	PP_TOKENS,
	NEW_LINE,
	LPAREN,
	REPLACEMENT_LIST,
	ENUMERATION_SPECIFIER,
	DECLARATION_LIST,
	DECLARATOR,
	BLOCK_ITEM_LIST,
	BLOCK_ITEM
};

static const char* ast_form_string_reprs[] {
	"ERROR",
	"KEYWORD",
	"IDENTIFIER",
	"CONSTANT",
	"STRING_LITERAL",
	"PUNCTUATOR",
	"PRIMARY_EXPRESSION",
	"EXPRESSION",
	"POSTFIX_EXPRESSION",
	"ARGUMENT_EXPRESSION_LIST",
	"ASSIGNMENT_EXPRESSION",
	"TYPE_NAME",
	"INITIALIZER_LIST",
	"UNARY_EXPRESSION",
	"CAST_EXPRESSION",
	"UNARY_OPERATOR",
	"MULTIPLICATIVE_EXPRESSION",
	"ADDITIVE_EXPRESSION",
	"SHIFT_EXPRESSION",
	"RELATIONAL_EXPRESSION",
	"EQUALITY_EXPRESSION",
	"AND_EXPRESSION",
	"EXCLUSIVE_OR_EXPRESSION",
	"LOGICAL_AND_EXPRESSION",
	"INCLUSIVE_OR_EXPRESSION",
	"LOGICAL_OR_EXPRESSION",
	"CONDITIONAL_EXPRESSION",
	"ASSIGNMENT_OPERATOR",
	"CONSTANT_EXPRESSION",
	"DECLARATION",
	"DECLARATION_SPECIFIERS",
	"INIT_DECLARATOR_LIST",
	"STORAGE_CLASS_SPECIFIER",
	"TYPE_SPECIFIER",
	"TYPE_QUALIFIER",
	"FUNCTION_SPECIFIER",
	"INIT_DECLARATOR",
	"INITIALIZER",
	"STRUCT_OR_UNION",
	"STRUCT_OR_UNION_SPECIFIER",
	"STRUCT_DECLARATION_LIST",
	"STRUCT_DECLARATION",
	"STRUCT_DECLARATOR_LIST",
	"STRUCT_DECLARATOR",
	"SPECIFIER_QUALIFIER_LIST",
	"ENUM_SPECIFIER",
	"ENUMERATOR_LIST",
	"ENUMERATOR",
	"ENUMERATION_CONSTANT",
	"TYPEDEF_NAME",
	"POINTER",
	"DIRECT_DECLARATOR",
	"TYPE_QUALIFIER_LIST",
	"PARAMETER_TYPE_LIST",
	"PARAMETER_LIST",
	"PARAMETER_DECLARATION",
	"DECLARATION_SPECIFIER",
	"IDENTIFIER_LIST",
	"DIRECT_ABSTRACT_DECLARATOR",
	"ABSTRACT_DECLARATOR",
	"DESIGNATION",
	"DESIGNATOR_LIST",
	"DESIGNATOR",
	"STATEMENT",
	"LABELED_STATEMENT",
	"COMPOUND_STATEMENT",
	"EXPRESSION_STATEMENT",
	"SELECTION_STATEMENT",
	"ITERATION_STATEMENT",
	"JUMP_STATEMENT",
	"TRANSLATION_UNIT",
	"EXTERNAL_DECLARATION",
	"FUNCTION_DEFINITION",
	"PREPROCESSING_FILE",
	"GROUP",
	"GROUP_PART",
	"IF_SECTION",
	"TEXT_LINE",
	"NON_DIRECTIVE",
	"IF_GROUP",
	"ELIF_GROUPS",
	"ELIF_GROUP",
	"ELSE_GROUP",
	"ENDIF_LINE",
	"CONTROL_LINE",
	"PP_TOKENS",
	"NEW_LINE",
	"LPAREN",
	"REPLACEMENT_LIST",
	"ENUMERATION_SPECIFIER",
	"DECLARATION_LIST",
	"DECLARATOR",
	"BLOCK_ITEM_LIST",
	"BLOCK_ITEM"
};

enum class AstNodeAlt {
	ERROR = 0,
	/* terminal */
	TERMINAL,
	ENUMERATION_CONSTANT_1,
	/* primary-expression */
	PRIMARY_EXPRESSION_1, /* identifier */
	PRIMARY_EXPRESSION_2, /* constant */
	PRIMARY_EXPRESSION_3, /* string-literal */
	PRIMARY_EXPRESSION_4, /* ( expression ) */
	/* postfix-expression */
	POSTFIX_EXPRESSION_1, /* primary-expression */
	POSTFIX_EXPRESSION_2, /* postfix-expression [ expression ] */
	POSTFIX_EXPRESSION_3, /* postfix-expression ( argument-expression-listopt ) */
	POSTFIX_EXPRESSION_4, /* postfix-expression . identifier */
	POSTFIX_EXPRESSION_5, /* postfix-expression -> identifier */
	POSTFIX_EXPRESSION_6, /* postfix-expression ++ */
	POSTFIX_EXPRESSION_7, /* postfix-expression -- */
	POSTFIX_EXPRESSION_8, /* ( type-name ) { initializer-list } */
	POSTFIX_EXPRESSION_9, /* ( type-name ) { initializer-list , } */
	/* argument-expression-list */
	ARGUMENT_EXPRESSION_LIST_1, /* assignment-expression */
	ARGUMENT_EXPRESSION_LIST_2, /* argument-expression-list , assignment-expression */
	/* unary-expression */
	UNARY_EXPRESSION_1, /* postfix-expression */
	UNARY_EXPRESSION_2, /* ++ unary-expression */
	UNARY_EXPRESSION_3, /* -- unary-expression */
	UNARY_EXPRESSION_4, /* unary-operator cast-expression */
	UNARY_EXPRESSION_5, /* sizeof unary-expression */
	UNARY_EXPRESSION_6, /* sizeof ( type-name ) */
	/* unary-operator */
	UNARY_OPERATOR_1, /* & */
	UNARY_OPERATOR_2, /* * */
	UNARY_OPERATOR_3, /* + */
	UNARY_OPERATOR_4, /* - */
	UNARY_OPERATOR_5, /* ~ */
	UNARY_OPERATOR_6, /* ! */
	/* cast-expression */
	CAST_EXPRESSION_1, /* unary-expression */
	CAST_EXPRESSION_2, /* ( type-name ) cast-expression */
	/* multiplicative-expression */
	MULTIPLICATIVE_EXPRESSION_1, /* cast-expression */
	MULTIPLICATIVE_EXPRESSION_2, /* multiplicative-expression * cast-expression */
	MULTIPLICATIVE_EXPRESSION_3, /* multiplicative-expression / cast-expression */
	MULTIPLICATIVE_EXPRESSION_4, /* multiplicative-expression % cast-expression */
	/* additive-expression */
	ADDITIVE_EXPRESSION_1, /* multiplicative-expression */
	ADDITIVE_EXPRESSION_2, /* additive-expression + multiplicative-expression */
	ADDITIVE_EXPRESSION_3, /* additive-expression - multiplicative-expression */
	/* shift-expression */
	SHIFT_EXPRESSION_1, /* additive-expression */
	SHIFT_EXPRESSION_2, /* shift-expression << additive-expression */
	SHIFT_EXPRESSION_3, /* shift-expression >> additive-expression */
	/* relational-expression */
	RELATIONAL_EXPRESSION_1, /* shift-expression */
	RELATIONAL_EXPRESSION_2, /* relational-expression < shift-expression */
	RELATIONAL_EXPRESSION_3, /* relational-expression > shift-expression */
	RELATIONAL_EXPRESSION_4, /* relational-expression <= shift-expression */
	RELATIONAL_EXPRESSION_5, /* relational-expression >= shift-expression */
	/* equality-expression */
	EQUALITY_EXPRESSION_1, /* relational-expression */
	EQUALITY_EXPRESSION_2, /* equality-expression == relational-expression */
	EQUALITY_EXPRESSION_3, /* equality-expression != relational-expression */
	/* AND-expression */
	AND_EXPRESSION_1, /* equality-expression */
	AND_EXPRESSION_2, /* AND-expression & equality-expression */
	/* exclusive-OR-expression */
	EXCLUSIVE_OR_EXPRESSION_1, /* AND-expression */
	EXCLUSIVE_OR_EXPRESSION_2, /* exclusive-OR-expression ^ AND-expression */
	/* inclusive-OR-expression */
	INCLUSIVE_OR_EXPRESSION_1, /* exclusive-OR-expression */
	INCLUSIVE_OR_EXPRESSION_2, /* inclusive-OR-expression | exclusive-OR-expression */
	/* logical-AND-expression */
	LOGICAL_AND_EXPRESSION_1, /* inclusive-OR-expression */
	LOGICAL_AND_EXPRESSION_2, /* logical-AND-expression && inclusive-OR-expression */
	/* logical-OR-expression */
	LOGICAL_OR_EXPRESSION_1, /* logical-AND-expression */
	LOGICAL_OR_EXPRESSION_2, /* logical-OR-expression || logical-AND-expression */
	/* conditional-expression */
	CONDITIONAL_EXPRESSION_1, /* logical-OR-expression */
	CONDITIONAL_EXPRESSION_2, /* logical-OR-expression ? expression : conditional-expression */
	/* assignment-expression */ 
	ASSIGNMENT_EXPRESSION_1, /* conditional-expression */
	ASSIGNMENT_EXPRESSION_2, /* unary-expression assignment-operator assignment-expression */
	/*  assignment-operator */
	ASSIGNMENT_OPERATOR_1, /* = */
	ASSIGNMENT_OPERATOR_2, /* *= */
	ASSIGNMENT_OPERATOR_3, /* /= */
	ASSIGNMENT_OPERATOR_4, /* %= */
	ASSIGNMENT_OPERATOR_5, /* += */
	ASSIGNMENT_OPERATOR_6, /* -= */
	ASSIGNMENT_OPERATOR_7, /* <<= */
	ASSIGNMENT_OPERATOR_8, /* >>= */
	ASSIGNMENT_OPERATOR_9, /* &= */
	ASSIGNMENT_OPERATOR_10, /* ^= */
	ASSIGNMENT_OPERATOR_11, /* |= */
	/* expression */
	EXPRESSION_1, /* assignment-expression */
	EXPRESSION_2, /* expression , assignment-expression */
	/* constant-expression */
	CONSTANT_EXPRESSION_1, /* conditional-expression */
	/* declaration */
	DECLARATION_1, /* declaration-specifiers init-declarator-listopt ; */
	/* declaration-specifiers */ 
	DECLARATION_SPECIFIERS_1, /* storage-class-specifier declaration-specifiersopt */
	DECLARATION_SPECIFIERS_2, /* type-specifier declaration-specifiersopt */
	DECLARATION_SPECIFIERS_3, /* type-qualifier declaration-specifiersopt */
	DECLARATION_SPECIFIERS_4, /* function-specifier declaration-specifiersopt */
	/* init-declarator-list */
	INIT_DECLARATOR_LIST_1, /* init-declarator */
	INIT_DECLARATOR_LIST_2, /* init-declarator-list , init-declarator */
	/* init-declarator */ 
	INIT_DECLARATOR_1, /* declarator */
	INIT_DECLARATOR_2, /* declarator = initializer */
	/* storage-class-specifier */
	STORAGE_CLASS_SPECIFIER_1, /* typedef */
	STORAGE_CLASS_SPECIFIER_2, /* extern */
	STORAGE_CLASS_SPECIFIER_3, /* static */
	STORAGE_CLASS_SPECIFIER_4, /* auto */
	STORAGE_CLASS_SPECIFIER_5, /* register */
	/* type-specifier */	
	TYPE_SPECIFIER_1, /* void */
	TYPE_SPECIFIER_2, /* char */
	TYPE_SPECIFIER_3, /* short */
	TYPE_SPECIFIER_4, /* int */
	TYPE_SPECIFIER_5, /* long */
	TYPE_SPECIFIER_6, /* float */
	TYPE_SPECIFIER_7, /* double */
	TYPE_SPECIFIER_8, /* signed */
	TYPE_SPECIFIER_9, /* unsigned */
	TYPE_SPECIFIER_10, /* _Bool */
	TYPE_SPECIFIER_11, /* _Complex */
	TYPE_SPECIFIER_12, /* struct-or-union-specifier */
	TYPE_SPECIFIER_13, /* enum-specifier */
	TYPE_SPECIFIER_14, /* typedef-name */
	/* struct-or-union-specifier */ 
	STRUCT_OR_UNION_SPECIFIER_1, /* struct-or-union identifieropt { struct-declaration-list } */
	STRUCT_OR_UNION_SPECIFIER_2, /* struct-or-union identifier */
	/* struct-or-union */ 
	STRUCT_OR_UNION_1, /* struct */
	STRUCT_OR_UNION_2, /* union */
	/* struct-declaration-list */ 
	STRUCT_DECLARATION_LIST_1, /* struct-declaration */
	STRUCT_DECLARATION_LIST_2, /* struct-declaration-list struct-declaration */
	/* struct-declaration */ 
	STRUCT_DECLARATION_1, /* specifier-qualifier-list struct-declarator-list ; */
	/* specifier-qualifier-list */
	SPECIFIER_QUALIFIER_LIST_1, /* type-specifier specifier-qualifier-listopt */
	SPECIFIER_QUALIFIER_LIST_2, /* type-qualifier specifier-qualifier-listopt */
	/* struct-declarator-list */
	STRUCT_DECLARATOR_LIST_1, /* struct-declarator */
	STRUCT_DECLARATOR_LIST_2, /* struct-declarator-list , struct-declarator */
	/* struct-declarator */
	STRUCT_DECLARATOR_1, /* declarator */
	STRUCT_DECLARATOR_2, /* declaratoropt : constant-expression */
	/* enum-specifier */
	ENUM_SPECIFIER_1, /* enum identifieropt { enumerator-list } */
	ENUM_SPECIFIER_2, /* enum identifieropt { enumerator-list , } */
	ENUM_SPECIFIER_3, /* enum identifier */
	/* enumerator-list */
	ENUMERATOR_LIST_1, /* enumerator */
	ENUMERATOR_LIST_2, /* enumerator-list , enumerator */
	/* enumerator */
	ENUMERATOR_1, /* enumeration-constant */
	ENUMERATOR_2, /* enumeration-constant = constant-expression */
	/* type-qualifier */
	TYPE_QUALIFIER_1, /* const */
	TYPE_QUALIFIER_2, /* restrict */
	TYPE_QUALIFIER_3, /* volatile */
	/* function-specifier */
	FUNCTION_SPECIFIER_1, /* inline */
	/* declarator */
	DECLARATOR_1, /* pointeropt direct-declarator */
	/* direct-declarator */
	DIRECT_DECLARATOR_1, /*identifier*/
	DIRECT_DECLARATOR_2, /*(declarator)*/
	DIRECT_DECLARATOR_3, /*direct-declarator[type-qualifier-listopt assignment-expressionopt]*/
	DIRECT_DECLARATOR_4, /*direct-declarator[static type-qualifier - listopt assignment-expression] */ 
	DIRECT_DECLARATOR_5, /*direct-declarator[type-qualifier-list static assignment-expression] */
	DIRECT_DECLARATOR_6,/*direct-declarator[type-qualifier-listopt*]*/
	DIRECT_DECLARATOR_7,/*direct-declarator(parameter-type-list)*/
	DIRECT_DECLARATOR_8,/*direct-declarator(identifier-listopt)*/
	/* pointer */
	POINTER_1, /* * type-qualifier-listopt */
	POINTER_2, /* * type-qualifier-listopt pointer */
	/* type-qualifier-list */
	TYPE_QUALIFIER_LIST_1, /* type-qualifier */
	TYPE_QUALIFIER_LIST_2, /* type-qualifier-list type-qualifier */
	/* parameter-type-list */
	PARAMETER_TYPE_LIST_1, /* parameter-list */
	PARAMETER_TYPE_LIST_2, /* parameter-list , ... */
	/* parameter-list */
	PARAMETER_LIST_1, /* parameter-declaration */
	PARAMETER_LIST_2, /* parameter-list , parameter-declaration */
	/* parameter-declaration */
	PARAMETER_DECLARATION_1, /* declaration-specifiers declarator */
	PARAMETER_DECLARATION_2, /* declaration-specifiers abstract-declaratoropt */
	/* identifier-list */
	IDENTIFIER_LIST_1, /* identifier */
	IDENTIFIER_LIST_2, /* identifier-list , identifier */
	/* type-name */
	TYPE_NAME_1, /* specifier-qualifier-list abstract-declaratoropt */
	/* abstract-declarator */
	ABSTRACT_DECLARATOR_1, /* pointer */
	ABSTRACT_DECLARATOR_2, /* pointeropt direct-abstract-declarator */
	/* direct-abstract-declarator */
	DIRECT_ABSTRACT_DECLARATOR_1, /* (abstract-declarator) */
	DIRECT_ABSTRACT_DECLARATOR_2, /* direct-abstract-declaratoropt[
										type-qualifier-listopt assignment-expressionopt] */
	DIRECT_ABSTRACT_DECLARATOR_3, /* direct-abstract-declaratoropt[
									 static type-qualifier-listopt assignment-expression] */
	DIRECT_ABSTRACT_DECLARATOR_4, /* direct-abstract-declaratoropt[
									 type-qualifier-list static assignment - expression]*/
	DIRECT_ABSTRACT_DECLARATOR_5, /* direct-abstract-declaratoropt[*] */
	DIRECT_ABSTRACT_DECLARATOR_6, /* direct-abstract-declaratoropt(parameter-type -listopt) */
	/* typedef-name */
	TYPEDEF_NAME_1,
	/* initializer */
	INITIALIZER_1,
	INITIALIZER_2,
	INITIALIZER_3,
	/* initializer-list */
	INITIALIZER_LIST_1,
	INITIALIZER_LIST_2,
	/* designation */
	DESIGNATION_1,
	/* designator-list */
	DESIGNATOR_LIST_1,
	DESIGNATOR_LIST_2,
	/* designator */
	DESIGNATOR_1,
	DESIGNATOR_2,
	/* statement */
	STATEMENT_1, /* labeled-statement */
	STATEMENT_2, /* compound-statement */
	STATEMENT_3, /* expression-statement */
	STATEMENT_4, /* selection-statement */
	STATEMENT_5, /* iteration-statement */
	STATEMENT_6, /* jump-statement */
	/* labeled-statement */
	LABELED_STATEMENT_1, /* identifier : statement */
	LABELED_STATEMENT_2, /* case constant-expression : statement */
	LABELED_STATEMENT_3, /* default : statement */
	/* compound-statement */
	COMPOUND_STATEMENT_1, /* { block - item - listopt } */
	/*  block-item-list */
	BLOCK_ITEM_LIST_1, /* block-item */
	BLOCK_ITEM_LIST_2, /* block-item-list block-item */
	/* block-item */
	BLOCK_ITEM_1, /* declaration */
	BLOCK_ITEM_2, /* statement */
	/* expression-statement */
	EXPRESSION_STATEMENT_1, /* expressionopt ; */
	/* selection-statement */
	SELECTION_STATEMENT_1, /* if ( expression ) statement */
	SELECTION_STATEMENT_2, /* if ( expression ) statement else statement */
	SELECTION_STATEMENT_3, /* switch ( expression ) statement */
	/* iteration-statement */
	ITERATION_STATEMENT_1, /* while ( expression ) statement */
	ITERATION_STATEMENT_2, /* do statement while ( expression ) ; */
	ITERATION_STATEMENT_3, /* for ( expressionopt ; 
									expressionopt ; 
									expressionopt ) statement */
	ITERATION_STATEMENT_4, /* for ( declaration expressionopt ; 
									expressionopt ) statement*/
	/* jump-statement */
	JUMP_STATEMENT_1, /* goto identifier ; */
	JUMP_STATEMENT_2, /* continue ; */
	JUMP_STATEMENT_3, /* break ; */
	JUMP_STATEMENT_4, /* return expressionopt ; */
	/* translation-unit */
	TRANSLATION_UNIT_1, /* external-declaration */
	TRANSLATION_UNIT_2, /* translation-unit external-declaration */
	/* external-declaration */
	EXTERNAL_DECLARATION_1, /* function-definition */
	EXTERNAL_DECLARATION_2, /* declaration */
	/* function-definition */
	FUNCTION_DEFINITION_1,
	/* declaration-list */
	DECLARATION_LIST_1, /* declaration */
	DECLARATION_LIST_2, /* declaration-list declaration */
};

static const char* ast_node_alt_string_reprs[] {
	"ERROR",
	"TERMINAL",
	"PRIMARY_EXPRESSION_1",
	"PRIMARY_EXPRESSION_2",
	"PRIMARY_EXPRESSION_3",
	"PRIMARY_EXPRESSION_4",
	"POSTFIX_EXPRESSION_1",
	"POSTFIX_EXPRESSION_2",
	"POSTFIX_EXPRESSION_3",
	"POSTFIX_EXPRESSION_4",
	"POSTFIX_EXPRESSION_5",
	"POSTFIX_EXPRESSION_6",
	"POSTFIX_EXPRESSION_7",
	"POSTFIX_EXPRESSION_8",
	"POSTFIX_EXPRESSION_9",
	"ARGUMENT_EXPRESSION_LIST_1",
	"ARGUMENT_EXPRESSION_LIST_2",
	"UNARY_EXPRESSION_1",
	"UNARY_EXPRESSION_2",
	"UNARY_EXPRESSION_3",
	"UNARY_EXPRESSION_4",
	"UNARY_EXPRESSION_5",
	"UNARY_EXPRESSION_6",
	"UNARY_OPERATOR_1",
	"UNARY_OPERATOR_2",
	"UNARY_OPERATOR_3",
	"UNARY_OPERATOR_4",
	"UNARY_OPERATOR_5",
	"UNARY_OPERATOR_6",
	"CAST_EXPRESSION_1",
	"CAST_EXPRESSION_2",
	"MULTIPLICATIVE_EXPRESSION_1",
	"MULTIPLICATIVE_EXPRESSION_2",
	"MULTIPLICATIVE_EXPRESSION_3",
	"MULTIPLICATIVE_EXPRESSION_4",
	"ADDITIVE_EXPRESSION_1",
	"ADDITIVE_EXPRESSION_2",
	"ADDITIVE_EXPRESSION_3",
	"SHIFT_EXPRESSION_1",
	"SHIFT_EXPRESSION_2",
	"SHIFT_EXPRESSION_3",
	"RELATIONAL_EXPRESSION_1",
	"RELATIONAL_EXPRESSION_2",
	"RELATIONAL_EXPRESSION_3",
	"RELATIONAL_EXPRESSION_4",
	"RELATIONAL_EXPRESSION_5",
	"EQUALITY_EXPRESSION_1",
	"EQUALITY_EXPRESSION_2",
	"EQUALITY_EXPRESSION_3",
	"AND_EXPRESSION_1",
	"AND_EXPRESSION_2",
	"EXCLUSIVE_OR_EXPRESSION_1",
	"EXCLUSIVE_OR_EXPRESSION_2",
	"INCLUSIVE_OR_EXPRESSION_1",
	"INCLUSIVE_OR_EXPRESSION_2",
	"LOGICAL_AND_EXPRESSION_1",
	"LOGICAL_AND_EXPRESSION_2",
	"LOGICAL_OR_EXPRESSION_1",
	"LOGICAL_OR_EXPRESSION_2",
	"CONDITIONAL_EXPRESSION_1",
	"CONDITIONAL_EXPRESSION_2",
	"ASSIGNMENT_EXPRESSION_1",
	"ASSIGNMENT_EXPRESSION_2",
	"ASSIGNMENT_OPERATOR_1",
	"ASSIGNMENT_OPERATOR_2",
	"ASSIGNMENT_OPERATOR_3",
	"ASSIGNMENT_OPERATOR_4",
	"ASSIGNMENT_OPERATOR_5",
	"ASSIGNMENT_OPERATOR_6",
	"ASSIGNMENT_OPERATOR_7",
	"ASSIGNMENT_OPERATOR_8",
	"ASSIGNMENT_OPERATOR_9",
	"ASSIGNMENT_OPERATOR_10",
	"ASSIGNMENT_OPERATOR_11",
	"EXPRESSION_1",
	"EXPRESSION_2",
	"CONSTANT_EXPRESSION_1",
	"DECLARATION_1",
	"DECLARATION_SPECIFIERS_1",
	"DECLARATION_SPECIFIERS_2",
	"DECLARATION_SPECIFIERS_3",
	"DECLARATION_SPECIFIERS_4",
	"INIT_DECLARATOR_LIST_1",
	"INIT_DECLARATOR_LIST_2",
	"INIT_DECLARATOR_1",
	"INIT_DECLARATOR_2",
	"STORAGE_CLASS_SPECIFIER_1",
	"STORAGE_CLASS_SPECIFIER_2",
	"STORAGE_CLASS_SPECIFIER_3",
	"STORAGE_CLASS_SPECIFIER_4",
	"STORAGE_CLASS_SPECIFIER_5",
	"TYPE_SPECIFIER_1",
	"TYPE_SPECIFIER_2",
	"TYPE_SPECIFIER_3",
	"TYPE_SPECIFIER_4",
	"TYPE_SPECIFIER_5",
	"TYPE_SPECIFIER_6",
	"TYPE_SPECIFIER_7",
	"TYPE_SPECIFIER_8",
	"TYPE_SPECIFIER_9",
	"TYPE_SPECIFIER_10",
	"TYPE_SPECIFIER_11",
	"TYPE_SPECIFIER_12",
	"TYPE_SPECIFIER_13",
	"TYPE_SPECIFIER_14",	
	"STRUCT_OR_UNION",
	"STRUCT_OR_UNION_SPECIFIER_1",
	"STRUCT_OR_UNION_SPECIFIER_2",
	"STRUCT_OR_UNION_1",
	"STRUCT_OR_UNION_2",
	"STRUCT_DECLARATION_LIST_1",
	"STRUCT_DECLARATION_LIST_2",
	"STRUCT_DECLARATION_1",
	"SPECIFIER_QUALIFIER_LIST_1",
	"SPECIFIER_QUALIFIER_LIST_2",
	"STRUCT_DECLARATOR_LIST_1",
	"STRUCT_DECLARATOR_LIST_2",
	"STRUCT_DECLARATOR_1",
	"STRUCT_DECLARATOR_2",
	"ENUM_SPECIFIER_1",
	"ENUM_SPECIFIER_2",
	"ENUM_SPECIFIER_3",
	"ENUMERATOR_LIST_1",
	"ENUMERATOR_LIST_2",
	"ENUMERATOR_1",
	"ENUMERATOR_2",
	"TYPE_QUALIFIER_1",
	"TYPE_QUALIFIER_2",
	"TYPE_QUALIFIER_3",
	"FUNCTION_SPECIFIER_1",
	"DECLARATOR_1",
	"DIRECT_DECLARATOR_1",
	"DIRECT_DECLARATOR_2",
	"DIRECT_DECLARATOR_3",
	"DIRECT_DECLARATOR_4",
	"DIRECT_DECLARATOR_5",
	"DIRECT_DECLARATOR_6",
	"DIRECT_DECLARATOR_7",
	"DIRECT_DECLARATOR_8",
	"POINTER_1",
	"POINTER_2",
	"TYPE_QUALIFIER_LIST_1",
	"TYPE_QUALIFIER_LIST_2",
	"PARAMETER_TYPE_LIST_1",
	"PARAMETER_TYPE_LIST_2",
	"PARAMETER_LIST_1",
	"PARAMETER_LIST_2",
	"PARAMETER_DECLARATION_1",
	"PARAMETER_DECLARATION_2",
	"IDENTIFIER_LIST_1",
	"IDENTIFIER_LIST_2",
	"TYPE_NAME_1",
	"ABSTRACT_DECLARATOR_1",
	"ABSTRACT_DECLARATOR_2",
	"DIRECT_ABSTRACT_DECLARATOR_1",
	"DIRECT_ABSTRACT_DECLARATOR_2",
	"DIRECT_ABSTRACT_DECLARATOR_3",
	"DIRECT_ABSTRACT_DECLARATOR_4",
	"DIRECT_ABSTRACT_DECLARATOR_5",
	"DIRECT_ABSTRACT_DECLARATOR_6",
	"TYPEDEF_NAME_1",
	"INITIALIZER_1",
	"INITIALIZER_2",
	"INITIALIZER_3",
	"INITIALIZER_LIST_1",
	"INITIALIZER_LIST_2",
	"DESIGNATION_1",
	"DESIGNATOR_LIST_1",
	"DESIGNATOR_LIST_2",
	"DESIGNATOR_1",
	"DESIGNATOR_2",
	"STATEMENT_1",
	"STATEMENT_2",
	"STATEMENT_3",
	"STATEMENT_4",
	"STATEMENT_5",
	"STATEMENT_6",
	"LABELED_STATEMENT_1",
	"LABELED_STATEMENT_2",
	"LABELED_STATEMENT_3",
	"COMPOUND_STATEMENT_1",
	"BLOCK_ITEM_LIST_1",
	"BLOCK_ITEM_LIST_2",
	"BLOCK_ITEM_1",
	"BLOCK_ITEM_2",
	"EXPRESSION_STATEMENT_1",
	"SELECTION_STATEMENT_1",
	"SELECTION_STATEMENT_2",
	"SELECTION_STATEMENT_3",
	"ITERATION_STATEMENT_1",
	"ITERATION_STATEMENT_2",
	"ITERATION_STATEMENT_3",
	"ITERATION_STATEMENT_4",
	"JUMP_STATEMENT_1",
	"JUMP_STATEMENT_2",
	"JUMP_STATEMENT_3",
	"JUMP_STATEMENT_4",
	"TRANSLATION_UNIT_1",
	"TRANSLATION_UNIT_2",
	"EXTERNAL_DECLARATION_1",
	"EXTERNAL_DECLARATION_2",
	"FUNCTION_DEFINITION_1",
	"DECLARATION_LIST_1",
	"DECLARATION_LIST_2",
};

class AstNode {
private:
	AstNodeName name;
	AstNodeAlt alt;	
	Token* terminal;
	AstNode* child;	
	AstNode* sibling;
public:
	inline AstNode(
		AstNodeName const& n,
		AstNodeAlt  const& a,
		Token* const& t) :
		name(n), 
		alt(a), 
		terminal(t), 
		child(NULL), 
		sibling(NULL) { 
	}

	inline AstNode() :
		name(AstNodeName::ERROR),
		alt(AstNodeAlt::ERROR),
		terminal(NULL),
		child(NULL),
		sibling(NULL) {
	}

	inline AstNodeName get_name() const 
	{
		return name;
	};

	inline AstNodeAlt get_alt() const
	{
		return alt;
	};

	inline Token* get_terminal() const
	{
		return terminal;
	};

	inline AstNode* get_child() const
	{
		return child;
	};

	inline AstNode* get_sibling() const
	{
		return sibling;
	};

	inline void add_child(AstNode* node) 
	{
		if (child == NULL) {
			child = node;
		} else {
			AstNode* current = child;
			while (current->sibling) {
				current = current->sibling;
			}
			current->sibling = node;
		}
	}

	inline void add_children(AstNode** nodes, int count)
	{
		for (AstNode** n = nodes;
			n < nodes + count;
			n++) {
			add_child(*n);
		}
		/*print();*/
	}

	inline void print(
		string parent_prefix = "", 
		string child_prefix = "") 
	{
		cout << parent_prefix
			 << "name="
			 << ast_form_string_reprs[(int) name]
			 << ",alt="
			 <<	ast_node_alt_string_reprs[(int) alt];
		if (terminal) terminal->print();
		cout << endl;
		AstNode* node = child;
		for (;node; node = node->sibling) {
			if (node->sibling) {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "|    ";
				node->print(appended_p, appended_c);
			} else {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "     ";
				node->print(appended_p, appended_c);
			}
		}
	}
};

static inline AstNode* construct_terminal(
	Token* t) 
{
	cout << "ast-node.cpp:construct_terminal:"
		 << " constructing terminal from the following token, ";
	t->print();
	cout << endl;
	AstNodeName name;
	switch (t->get_name()) {
		case TokenName::KEYWORD: 
			name = AstNodeName::KEYWORD;
			break;
		case TokenName::IDENTIFIER: 
			name = AstNodeName::IDENTIFIER; 
			break;
		case TokenName::CONSTANT: 
			name = AstNodeName::CONSTANT; 
			break;
		case TokenName::STRING_LITERAL: 
			name = AstNodeName::STRING_LITERAL; 
			break;
		case TokenName::PUNCTUATOR: 
			name = AstNodeName::PUNCTUATOR; 
			break;
		default: 
			name = AstNodeName::ERROR;
			break;
	}
	AstNode* terminal = new AstNode(
		name, 
		AstNodeAlt::TERMINAL, 
		t
	);
	return terminal;
}

#endif