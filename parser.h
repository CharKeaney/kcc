
#ifndef PARSER_H
#define PARSER_H 1

#include "ast-node.h"
#include "symbol-table.h"
#include "parser-lookahead.h"

#define DEBUG_PARSER_SHOW_ATTEMPTS 1

#define parser_report_attempt( s, t )						\
			cout << "parser.cpp:" s ":"						\
				 << "attempting to produce tree on lexeme "	\
				 << t->get_lexeme()							\
				 << "."										\
				 << endl

#define parse_report_success( s, a, t )						\
		if (DEBUG_PARSER_SHOW_ATTEMPTS)						\
			cout << "parser.cpp:" s ":"						\
				 << "produced tree with form "				\
				 << (size_t) f								\
				 << " and lexeme "							\
				 << l										\
				 << "."										\
				 << endl

#define parse(tokens, root) parse_translation_unit(tokens, root)

enum class ParserExitCode {
	SUCCESS,
	FAIL,
};

ParserExitCode parse_primary_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_postfix_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_type_name(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_unary_operator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_cast_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_unary_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_multiplicative_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_additive_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_shift_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_relational_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_equality_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_and_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_exclusive_or_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_inclusive_or_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_logical_and_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_logical_or_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_assignment_operator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_conditional_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_assignment_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_constant_expression(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_declaration(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_declaration_specifiers(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_init_declarator_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_init_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_type_specifier(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_or_union_specifier(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_or_union(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_declaration_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_declaration(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_specifier_qualifier_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_declarator_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_struct_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_enumerator_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_enumeration_specifier(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_type_qualifier(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_direct_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_pointer(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_type_qualifier_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_parameter_type_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_parameter_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_parameter_declaration(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_identifier_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_abstract_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_direct_abstract_declarator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_initializer(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_initializer_list(SymbolTable *&, Token*&, AstNode*& );
ParserExitCode parse_designation(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_designator_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_designator(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_compound_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_block_item_list(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_block_item(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_expression_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_selection_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_iteration_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_jump_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_translation_unit_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_external_declaration_statement(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_function_definition(SymbolTable *&, Token*&, AstNode*&);
ParserExitCode parse_declaration_list(SymbolTable*&, Token*&, AstNode*&);

static inline ParserExitCode parse_primary_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& primary_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_primary_expression", tokens);
	}

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	switch (tokens->get_name()) {

	case TokenName::IDENTIFIER:
		stack[si++] = construct_terminal(tokens++);
		should_generate = true;
		alt = AstNodeAlt::PRIMARY_EXPRESSION_1;
		break;

	case TokenName::CONSTANT:
		stack[si++] = construct_terminal(tokens++);
		should_generate = true;
		alt = AstNodeAlt::PRIMARY_EXPRESSION_2;
		break;

	case TokenName::STRING_LITERAL:
		stack[si++] = construct_terminal(tokens++);
		should_generate = true;
		alt = AstNodeAlt::PRIMARY_EXPRESSION_3;
		break;

	case TokenName::PUNCTUATOR:
	{
		if (tokens->get_form() == TokenForm::OPEN_PAREN) {
			tokens++;
			if (lookup(
				first_of_expression,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* expression;
				if (parse_expression(sym, tokens, expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression;

					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
						tokens++;
						alt = AstNodeAlt::PRIMARY_EXPRESSION_4;
						should_generate = true;
					}
				}
			}
		}
		break;
	}

	default:
		break;
	}
	if (should_generate) {
		primary_expression = new AstNode(
			AstNodeName::PRIMARY_EXPRESSION,
			alt,
			NULL
		);
		primary_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_argument_expression_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& argument_expression_list)
{
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ARGUMENT_EXPRESSION_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* assignment_expression;
			if (parse_assignment_expression(sym, tokens, assignment_expression)
				== ParserExitCode::SUCCESS) {

				argument_expression_list = new AstNode(
					AstNodeName::ARGUMENT_EXPRESSION_LIST,
					AstNodeAlt::ARGUMENT_EXPRESSION_LIST_1,
					NULL
				);
				argument_expression_list->add_child(assignment_expression);

				state = ARGUMENT_EXPRESSION_LIST;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case ARGUMENT_EXPRESSION_LIST:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;

				AstNode* assignment_expression;
				if (parse_assignment_expression(
					sym,
					tokens,
					assignment_expression)
					== ParserExitCode::SUCCESS) {

					AstNode* higher_argument_expression_list;
					higher_argument_expression_list = new AstNode(
						AstNodeName::ARGUMENT_EXPRESSION_LIST,
						AstNodeAlt::ARGUMENT_EXPRESSION_LIST_2,
						NULL
					);
					higher_argument_expression_list->add_child(
						argument_expression_list);
					higher_argument_expression_list->add_child(
						assignment_expression);
					argument_expression_list =
						higher_argument_expression_list;
					continue;
				}
			}
			break;

		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_postfix_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& postfix_expression)
{
	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		POSTFIX_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* primary_expression;;
			if (parse_primary_expression(sym, tokens, primary_expression)
				== ParserExitCode::SUCCESS) {

				postfix_expression = new AstNode(
					AstNodeName::POSTFIX_EXPRESSION,
					AstNodeAlt::POSTFIX_EXPRESSION_1,
					NULL
				);
				postfix_expression->add_child(primary_expression);

				state = POSTFIX_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;

			}
			else if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN) {
				tokens++;
				AstNode* type_name;;
				if (parse_type_name(sym, tokens, type_name)
					== ParserExitCode::SUCCESS) {
					stack[si++] = type_name;
				}
				else {
					break;
				}
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
					tokens++;
				}
				else {
					break;
				}
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
					tokens++;
				}
				else {
					break;
				}
				AstNode* initializer_list;;
				if (parse_initializer_list(sym, tokens, initializer_list)
					== ParserExitCode::SUCCESS) {
					stack[si++] = initializer_list;
				}
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
					tokens++;

					postfix_expression = new AstNode(
						AstNodeName::POSTFIX_EXPRESSION,
						AstNodeAlt::POSTFIX_EXPRESSION_8,
						NULL
					);
					postfix_expression->add_child(primary_expression);

					exitcode = ParserExitCode::SUCCESS;
					should_generate = true;
				}
				else if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::COMMA) {
					tokens++;
					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
						tokens++;

						postfix_expression = new AstNode(
							AstNodeName::POSTFIX_EXPRESSION,
							AstNodeAlt::POSTFIX_EXPRESSION_9,
							NULL
						);
						postfix_expression->add_child(primary_expression);

						exitcode = ParserExitCode::SUCCESS;
						should_generate = true;
					}
				}
				break;
			}
			break;
		}

		case POSTFIX_EXPRESSION:
		{
			AstNode* stack[15];
			int si = 0;

			bool should_append = false;

			if (tokens->get_name() != TokenName::PUNCTUATOR) {
				break;
			}
			switch (tokens->get_form()) {

			case TokenForm::OPEN_SQUARE_BRACKET:
				tokens++;
				AstNode* expression;
				if (parse_expression(sym, tokens, expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression;
					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
						tokens++;
						alt = AstNodeAlt::POSTFIX_EXPRESSION_2;
						should_append = true;
					}
				}
				break;

			case TokenForm::OPEN_PAREN:
				tokens++;
				AstNode* argument_expression_list;
				if (parse_argument_expression_list(sym, tokens, argument_expression_list)
					== ParserExitCode::SUCCESS) {
					stack[si++] = argument_expression_list;
				}
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
					tokens++;
					alt = AstNodeAlt::POSTFIX_EXPRESSION_3;
					should_append = true;
				}
				break;

			case TokenForm::DOT:
				tokens++;
				AstNode* identifier;
				if (tokens->get_name() == TokenName::IDENTIFIER) {
					stack[si++] = construct_terminal(tokens++);
				}
				alt = AstNodeAlt::POSTFIX_EXPRESSION_4;
				should_append = true;
				break;

			case TokenForm::RIGHT_ARROW:
				tokens++;
				if (tokens->get_name() == TokenName::IDENTIFIER) {
					stack[si++] = construct_terminal(tokens++);
				}
				alt = AstNodeAlt::POSTFIX_EXPRESSION_5;
				should_append = true;
				break;

			case TokenForm::INCREMENT:
				tokens++;
				alt = AstNodeAlt::POSTFIX_EXPRESSION_6;
				should_append = true;
				break;

			case TokenForm::DECREMENT:
				tokens++;
				alt = AstNodeAlt::POSTFIX_EXPRESSION_7;
				should_append = true;
				break;

			default:
				break;
			}
			if (should_append) {
				AstNode* higher_postfix_expression;
				higher_postfix_expression = new AstNode(
					AstNodeName::POSTFIX_EXPRESSION,
					alt,
					NULL
				);
				higher_postfix_expression->add_child(
					postfix_expression);
				higher_postfix_expression->add_children(stack, si);
				postfix_expression = higher_postfix_expression;
				continue;
			}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_type_name(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& type_name)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_type_name", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	AstNode* specifier_qualifier_list;
	if (parse_specifier_qualifier_list(
		sym,
		tokens,
		specifier_qualifier_list)
		== ParserExitCode::SUCCESS) {
		stack[si++] = specifier_qualifier_list;
		should_generate = true;
	}
	if (lookup(
		first_of_abstract_declarator,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* abstract_declarator;
		if (parse_abstract_declarator(
			sym,
			tokens,
			abstract_declarator)
			== ParserExitCode::SUCCESS) {
			stack[si++] = abstract_declarator;
		}
	}
	if (should_generate) {
		type_name = new AstNode(
			AstNodeName::TYPE_NAME,
			AstNodeAlt::TYPE_NAME_1,
			NULL
		);
		type_name->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_unary_operator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& unary_operator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_unary_operator", tokens);
	}

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (tokens->get_name() == TokenName::PUNCTUATOR) {
		switch (tokens->get_form()) {

		case TokenForm::AMPERSAND:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_1;
			break;

		case TokenForm::ASTERIX:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_2;
			break;

		case TokenForm::PLUS:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_3;
			break;

		case TokenForm::MINUS:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_4;
			break;

		case TokenForm::TILDE:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_5;
			break;

		case TokenForm::EXCLAMATION_MARK:
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			alt = AstNodeAlt::UNARY_OPERATOR_6;
			break;

		default:
			break;
		}
	}
	if (should_generate) {
		unary_operator = new AstNode(
			AstNodeName::UNARY_EXPRESSION,
			alt,
			NULL
		);
		unary_operator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_cast_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& cast_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_cast_expression", tokens);
	}

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::OPEN_PAREN
		&& lookup(
			first_of_type_name_list,
			(tokens + 1)->get_name(),
			(tokens + 1)->get_form())
		&& ((tokens + 1)->get_name() != TokenName::IDENTIFIER
			|| (sym->get_entry((tokens + 1)->get_lexeme())
				&& (sym->get_entry((tokens + 1)->get_lexeme())->is_typedef)))) {
		tokens++;

		AstNode* type_name;
		if (parse_type_name(sym, tokens, type_name)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_name;

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
				tokens++;

				AstNode* cast_expression;
				if (parse_cast_expression(sym, tokens, cast_expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = cast_expression;

					should_generate = true;
					alt = AstNodeAlt::CAST_EXPRESSION_2;
				}
			}
		}
	}
	else if (lookup(
		first_of_unary_expression,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* unary_expression;
		if (parse_unary_expression(sym, tokens, unary_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = unary_expression;

			should_generate = true;
			alt = AstNodeAlt::CAST_EXPRESSION_1;
		}
	}

	if (should_generate) {
		cast_expression = new AstNode(
			AstNodeName::CAST_EXPRESSION,
			alt,
			NULL
		);
		cast_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_unary_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& unary_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_unary_expression", tokens);
	}

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (lookup(
		first_of_postfix_expression,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* postfix_expression;
		if (parse_postfix_expression(sym, tokens, postfix_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = postfix_expression;

			should_generate = true;
			alt = AstNodeAlt::UNARY_EXPRESSION_1;
		}

	}
	else if (tokens->get_name() == TokenName::PUNCTUATOR) {
		switch (tokens->get_form()) {

			/* ++ unary-expression */
		case TokenForm::INCREMENT:
		{
			tokens++;
			AstNode* unary_expression;
			if (parse_unary_expression(sym, tokens, unary_expression)
				== ParserExitCode::SUCCESS) {
				stack[si++] = unary_expression;

				should_generate = true;
				alt = AstNodeAlt::UNARY_EXPRESSION_2;
			}
			break;
		}

		/* -- unary-expression */
		case TokenForm::DECREMENT:
		{
			tokens++;
			AstNode* unary_expression;
			if (parse_unary_expression(sym, tokens, unary_expression)
				== ParserExitCode::SUCCESS) {
				stack[si++] = unary_expression;
				should_generate = true;
				alt = AstNodeAlt::UNARY_EXPRESSION_3;
			}
			break;
		}

		/* unary-operator cast-expression*/
		case TokenForm::AMPERSAND:
		case TokenForm::ASTERIX:
		case TokenForm::PLUS:
		case TokenForm::MINUS:
		case TokenForm::TILDE:
		case TokenForm::EXCLAMATION_MARK:

			AstNode* unary_operator;
			if (parse_unary_operator(sym, tokens, unary_operator)
				== ParserExitCode::SUCCESS) {

				stack[si++] = unary_operator;

				AstNode* cast_expression;
				if (parse_cast_expression(sym, tokens, cast_expression)
					== ParserExitCode::SUCCESS) {

					stack[si++] = cast_expression;
					should_generate = true;
					alt = AstNodeAlt::UNARY_EXPRESSION_4;
				}
			}
			break;

		default:
			break;

		}

	}
	else if (tokens->get_name() == TokenName::IDENTIFIER
		&& tokens->get_form() == TokenForm::SIZEOF) {
		tokens++;

		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::OPEN_PAREN) {
			tokens++;

			AstNode* type_name;
			if (parse_type_name(sym, tokens, type_name)
				== ParserExitCode::SUCCESS) {
				stack[si++] = type_name;

				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
					tokens++;

					should_generate = true;
					alt = AstNodeAlt::UNARY_EXPRESSION_6;
				}
			}

		}
		else if (parse_unary_expression(sym, tokens, unary_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = unary_expression;

			should_generate = true;
			alt = AstNodeAlt::UNARY_EXPRESSION_5;
		}
	}
	if (should_generate) {
		unary_expression = new AstNode(
			AstNodeName::UNARY_EXPRESSION,
			alt,
			NULL
		);
		unary_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_multiplicative_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& multiplicative_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_multiplicative_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		MULTIPLICATIVE_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* cast_expression;
			if (parse_cast_expression(sym, tokens, cast_expression)
				== ParserExitCode::SUCCESS) {

				state = MULTIPLICATIVE_EXPRESSION;

				multiplicative_expression = new AstNode(
					AstNodeName::MULTIPLICATIVE_EXPRESSION,
					AstNodeAlt::MULTIPLICATIVE_EXPRESSION_1,
					NULL
				);
				multiplicative_expression->add_child(cast_expression);
				state = MULTIPLICATIVE_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case MULTIPLICATIVE_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)
				switch (tokens->get_form()) {
				case TokenForm::ASTERIX:
				{
					tokens++;
					AstNode* cast_expression;
					if (parse_cast_expression(sym, tokens, cast_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_multiplicative_expression;
						higher_multiplicative_expression = new AstNode(
							AstNodeName::MULTIPLICATIVE_EXPRESSION,
							AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2,
							NULL
						);
						higher_multiplicative_expression->add_child(
							multiplicative_expression);
						higher_multiplicative_expression->add_child(
							cast_expression);
						multiplicative_expression =
							higher_multiplicative_expression;
						continue;
					}
				}
				break;

				case TokenForm::FORWARD_SLASH:
				{
					tokens++;
					AstNode* cast_expression;
					if (parse_cast_expression(sym, tokens, cast_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_multiplicative_expression;
						higher_multiplicative_expression = new AstNode(
							AstNodeName::MULTIPLICATIVE_EXPRESSION,
							AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3,
							NULL
						);
						higher_multiplicative_expression->add_child(
							multiplicative_expression);
						higher_multiplicative_expression->add_child(
							cast_expression);
						multiplicative_expression =
							higher_multiplicative_expression;
						continue;
					}
				}
				break;


				case TokenForm::MODULO:
				{
					tokens++;
					AstNode* cast_expression;
					if (parse_cast_expression(sym, tokens, cast_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_multiplicative_expression;
						higher_multiplicative_expression = new AstNode(
							AstNodeName::MULTIPLICATIVE_EXPRESSION,
							AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4,
							NULL
						);
						higher_multiplicative_expression->add_child(
							multiplicative_expression);
						higher_multiplicative_expression->add_child(
							cast_expression);
						multiplicative_expression =
							higher_multiplicative_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_additive_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& additive_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_additive_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ADDITIVE_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* multiplicative_expression;
			if (parse_multiplicative_expression(
				sym,
				tokens,
				multiplicative_expression)
				== ParserExitCode::SUCCESS) {

				state = ADDITIVE_EXPRESSION;

				additive_expression = new AstNode(
					AstNodeName::ADDITIVE_EXPRESSION,
					AstNodeAlt::ADDITIVE_EXPRESSION_1,
					NULL
				);
				additive_expression->add_child(multiplicative_expression);
				state = ADDITIVE_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case ADDITIVE_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)
				switch (tokens->get_form()) {
				case TokenForm::PLUS:
				{
					tokens++;
					AstNode* multiplicative_expression;
					if (parse_multiplicative_expression(
						sym,
						tokens,
						multiplicative_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_additive_expression;
						higher_additive_expression = new AstNode(
							AstNodeName::ADDITIVE_EXPRESSION,
							AstNodeAlt::ADDITIVE_EXPRESSION_2,
							NULL
						);
						higher_additive_expression->add_child(
							additive_expression);
						higher_additive_expression->add_child(
							multiplicative_expression);
						additive_expression =
							higher_additive_expression;
						continue;
					}
				}
				break;

				case TokenForm::MINUS:
				{
					tokens++;
					AstNode* multiplicative_expression;
					if (parse_multiplicative_expression(
						sym,
						tokens,
						multiplicative_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_additive_expression;
						higher_additive_expression = new AstNode(
							AstNodeName::ADDITIVE_EXPRESSION,
							AstNodeAlt::ADDITIVE_EXPRESSION_3,
							NULL
						);
						higher_additive_expression->add_child(
							additive_expression);
						higher_additive_expression->add_child(
							multiplicative_expression);
						additive_expression =
							higher_additive_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_shift_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& shift_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_shift_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		SHIFT_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* additive_expression;
			if (parse_additive_expression(sym, tokens, additive_expression)
				== ParserExitCode::SUCCESS) {

				state = SHIFT_EXPRESSION;

				shift_expression = new AstNode(
					AstNodeName::SHIFT_EXPRESSION,
					AstNodeAlt::SHIFT_EXPRESSION_1,
					NULL
				);
				shift_expression->add_child(additive_expression);
				state = SHIFT_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case SHIFT_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)
				switch (tokens->get_form()) {

				case TokenForm::LEFT_SHIFT:
				{
					tokens++;
					AstNode* additive_expression;
					if (parse_additive_expression(sym, tokens, additive_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_shift_expression;
						higher_shift_expression = new AstNode(
							AstNodeName::SHIFT_EXPRESSION,
							AstNodeAlt::SHIFT_EXPRESSION_2,
							NULL
						);
						higher_shift_expression->add_child(
							shift_expression);
						higher_shift_expression->add_child(
							additive_expression);
						shift_expression =
							higher_shift_expression;
						continue;

					}
				}
				break;

				case TokenForm::RIGHT_SHIFT:
				{
					tokens++;
					AstNode* additive_expression;
					if (parse_additive_expression(sym, tokens, additive_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_shift_expression;
						higher_shift_expression = new AstNode(
							AstNodeName::SHIFT_EXPRESSION,
							AstNodeAlt::SHIFT_EXPRESSION_3,
							NULL
						);
						higher_shift_expression->add_child(
							shift_expression);
						higher_shift_expression->add_child(
							additive_expression);
						shift_expression =
							higher_shift_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_relational_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& relational_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_relational_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		RELATIONAL_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* shift_expression;
			if (parse_shift_expression(sym, tokens, shift_expression)
				== ParserExitCode::SUCCESS) {

				relational_expression = new AstNode(
					AstNodeName::RELATIONAL_EXPRESSION,
					AstNodeAlt::RELATIONAL_EXPRESSION_1,
					NULL
				);
				relational_expression->add_child(shift_expression);

				state = RELATIONAL_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case RELATIONAL_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR) {
				switch (tokens->get_form()) {

				case TokenForm::LESS_THAN:
				{
					tokens++;
					AstNode* shift_expression;
					if (parse_shift_expression(sym, tokens, shift_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_relational_expression;
						higher_relational_expression = new AstNode(
							AstNodeName::RELATIONAL_EXPRESSION,
							AstNodeAlt::RELATIONAL_EXPRESSION_2,
							NULL
						);
						higher_relational_expression->add_child(
							relational_expression);
						higher_relational_expression->add_child(
							shift_expression);
						relational_expression =
							higher_relational_expression;
						continue;
					}
				}
				break;

				case TokenForm::GREATER_THAN:
				{
					tokens++;
					AstNode* shift_expression;
					if (parse_shift_expression(sym, tokens, shift_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_relational_expression;
						higher_relational_expression = new AstNode(
							AstNodeName::RELATIONAL_EXPRESSION,
							AstNodeAlt::RELATIONAL_EXPRESSION_3,
							NULL
						);
						higher_relational_expression->add_child(
							relational_expression);
						higher_relational_expression->add_child(
							shift_expression);
						relational_expression =
							higher_relational_expression;
						continue;
					}
				}
				break;

				case TokenForm::LESS_THAN_EQUAL:
				{
					tokens++;
					AstNode* shift_expression;
					if (parse_shift_expression(sym, tokens, shift_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_relational_expression;
						higher_relational_expression = new AstNode(
							AstNodeName::RELATIONAL_EXPRESSION,
							AstNodeAlt::RELATIONAL_EXPRESSION_4,
							NULL
						);
						higher_relational_expression->add_child(
							relational_expression);
						higher_relational_expression->add_child(
							shift_expression);
						relational_expression =
							higher_relational_expression;
						continue;
					}
				}
				break;

				case TokenForm::GREATER_THAN_EQUAL:
				{
					tokens++;
					AstNode* shift_expression;
					if (parse_shift_expression(sym, tokens, shift_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_relational_expression;
						higher_relational_expression = new AstNode(
							AstNodeName::RELATIONAL_EXPRESSION,
							AstNodeAlt::RELATIONAL_EXPRESSION_5,
							NULL
						);
						higher_relational_expression->add_child(
							relational_expression);
						higher_relational_expression->add_child(
							shift_expression);
						relational_expression =
							higher_relational_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
			}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_equality_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& equality_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_equality_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		EQUALITY_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* relational_expression;
			if (parse_relational_expression(sym, tokens, relational_expression)
				== ParserExitCode::SUCCESS) {

				equality_expression = new AstNode(
					AstNodeName::EQUALITY_EXPRESSION,
					AstNodeAlt::EQUALITY_EXPRESSION_1,
					NULL
				);
				equality_expression->add_child(relational_expression);

				state = EQUALITY_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;
		}

		case EQUALITY_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)
				switch (tokens->get_form()) {

				case TokenForm::EQUAL:
				{
					tokens++;
					AstNode* relational_expression;
					if (parse_relational_expression(sym, tokens, relational_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_equality_expression;
						higher_equality_expression = new AstNode(
							AstNodeName::EQUALITY_EXPRESSION,
							AstNodeAlt::EQUALITY_EXPRESSION_2,
							NULL
						);
						higher_equality_expression->add_child(
							equality_expression);
						higher_equality_expression->add_child(
							relational_expression);
						equality_expression =
							higher_equality_expression;
						continue;
					}
				}
				break;

				case TokenForm::NOT_EQUAL:
				{
					tokens++;
					AstNode* relational_expression;
					if (parse_relational_expression(sym, tokens, relational_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_equality_expression;
						higher_equality_expression = new AstNode(
							AstNodeName::EQUALITY_EXPRESSION,
							AstNodeAlt::EQUALITY_EXPRESSION_3,
							NULL
						);
						higher_equality_expression->add_child(
							equality_expression);
						higher_equality_expression->add_child(
							relational_expression);
						equality_expression =
							higher_equality_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_and_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& and_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_and_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		AND_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* equality_expression;
			if (parse_equality_expression(sym, tokens, equality_expression)
				== ParserExitCode::SUCCESS) {

				and_expression = new AstNode(
					AstNodeName::AND_EXPRESSION,
					AstNodeAlt::AND_EXPRESSION_1,
					NULL
				);
				and_expression->add_child(equality_expression);

				state = AND_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;
		}

		case AND_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::AMPERSAND:
				{
					tokens++;
					AstNode* equality_expression;
					if (parse_equality_expression(sym, tokens, equality_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_and_expression;
						higher_and_expression = new AstNode(
							AstNodeName::AND_EXPRESSION,
							AstNodeAlt::AND_EXPRESSION_2,
							NULL
						);
						higher_and_expression->add_child(
							and_expression);
						higher_and_expression->add_child(
							equality_expression);
						and_expression =
							higher_and_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_exclusive_or_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& exclusive_or_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_exclusive_or_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		EXCLUSIVE_OR_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* and_expression;
			if (parse_and_expression(sym, tokens, and_expression)
				== ParserExitCode::SUCCESS) {

				exclusive_or_expression = new AstNode(
					AstNodeName::EXCLUSIVE_OR_EXPRESSION,
					AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1,
					NULL
				);
				exclusive_or_expression->add_child(and_expression);

				state = EXCLUSIVE_OR_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case EXCLUSIVE_OR_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::XOR:
				{
					tokens++;
					AstNode* and_expression;
					if (parse_and_expression(sym, tokens, and_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_exclusive_or_expression;
						higher_exclusive_or_expression = new AstNode(
							AstNodeName::EXCLUSIVE_OR_EXPRESSION,
							AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2,
							NULL
						);
						higher_exclusive_or_expression->add_child(
							exclusive_or_expression);
						higher_exclusive_or_expression->add_child(
							and_expression);
						exclusive_or_expression =
							higher_exclusive_or_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;


		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_inclusive_or_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& inclusive_or_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_inclusive_or_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		EXCLUSIVE_OR_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* exclusive_or_expression;
			if (parse_exclusive_or_expression(sym, tokens, exclusive_or_expression)
				== ParserExitCode::SUCCESS) {

				inclusive_or_expression = new AstNode(
					AstNodeName::INCLUSIVE_OR_EXPRESSION,
					AstNodeAlt::INCLUSIVE_OR_EXPRESSION_1,
					NULL
				);
				inclusive_or_expression->add_child(exclusive_or_expression);

				state = EXCLUSIVE_OR_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case EXCLUSIVE_OR_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::OR:
				{
					tokens++;
					AstNode* exclusive_or_expression;
					if (parse_exclusive_or_expression(sym, tokens, exclusive_or_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_inclusive_or_expression;
						higher_inclusive_or_expression = new AstNode(
							AstNodeName::INCLUSIVE_OR_EXPRESSION,
							AstNodeAlt::INCLUSIVE_OR_EXPRESSION_2,
							NULL
						);
						higher_inclusive_or_expression->add_child(
							inclusive_or_expression);
						higher_inclusive_or_expression->add_child(
							exclusive_or_expression);
						inclusive_or_expression =
							higher_inclusive_or_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_logical_and_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& logical_and_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_logical_and_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		LOGICAL_AND_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* inclusive_or_expression;
			if (parse_inclusive_or_expression(sym, tokens, inclusive_or_expression)
				== ParserExitCode::SUCCESS) {

				logical_and_expression = new AstNode(
					AstNodeName::LOGICAL_AND_EXPRESSION,
					AstNodeAlt::LOGICAL_AND_EXPRESSION_1,
					NULL
				);
				logical_and_expression->add_child(inclusive_or_expression);

				state = LOGICAL_AND_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case LOGICAL_AND_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::DOUBLE_AMPERSAND:
				{
					tokens++;
					AstNode* inclusive_or_expression;
					if (parse_inclusive_or_expression(sym, tokens, inclusive_or_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_inclusive_or_expression;
						higher_inclusive_or_expression = new AstNode(
							AstNodeName::INCLUSIVE_OR_EXPRESSION,
							AstNodeAlt::LOGICAL_AND_EXPRESSION_2,
							NULL
						);
						higher_inclusive_or_expression->add_child(
							logical_and_expression);
						higher_inclusive_or_expression->add_child(
							inclusive_or_expression);
						logical_and_expression =
							higher_inclusive_or_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_logical_or_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& logical_or_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_logical_or_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		LOGICAL_OR_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* logical_and_expression;
			if (parse_logical_and_expression(sym, tokens, logical_and_expression)
				== ParserExitCode::SUCCESS) {

				logical_or_expression = new AstNode(
					AstNodeName::LOGICAL_OR_EXPRESSION,
					AstNodeAlt::LOGICAL_OR_EXPRESSION_1,
					NULL
				);
				logical_or_expression->add_child(logical_and_expression);

				state = LOGICAL_OR_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case LOGICAL_OR_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::DOUBLE_OR:
				{
					tokens++;
					AstNode* logical_and_expression;
					if (parse_logical_and_expression(sym, tokens, logical_and_expression)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_logical_or_expression;
						higher_logical_or_expression = new AstNode(
							AstNodeName::LOGICAL_OR_EXPRESSION,
							AstNodeAlt::LOGICAL_OR_EXPRESSION_2,
							NULL
						);
						higher_logical_or_expression->add_child(
							logical_or_expression);
						higher_logical_or_expression->add_child(
							logical_and_expression);
						logical_or_expression =
							higher_logical_or_expression;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_assignment_operator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& assignment_operator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_assignment_operator", tokens);
	}
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::PUNCTUATOR) {
		switch (tokens->get_form()) {
		case TokenForm::ASSIGN:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_1;
			should_generate = true;
			break;
		case TokenForm::MULTIPLY_EQUAL:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_2;
			should_generate = true;
			break;
		case TokenForm::MODULO_EQUALS:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_3;
			should_generate = true;
			break;
		case TokenForm::PLUS_EQUALS:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_4;
			should_generate = true;
			break;
		case TokenForm::MINUS_EQUALS:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_5;
			should_generate = true;
			break;
		case TokenForm::LEFT_SHIFT_EQUALS:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_6;
			should_generate = true;
			break;
		case TokenForm::RIGHT_SHIFT_EQUALS:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_7;
			should_generate = true;
			break;
		case TokenForm::AMPERSAND_EQUAL:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_8;
			should_generate = true;
			break;
		case TokenForm::XOR_EQUAL:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_9;
			should_generate = true;
			break;
		case TokenForm::NOT_EQUAL:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::ASSIGNMENT_OPERATOR_10;
			should_generate = true;
			break;
		default:
			break;
		}
	}
	if (should_generate) {
		assignment_operator = new AstNode(
			AstNodeName::ASSIGNMENT_OPERATOR,
			alt,
			NULL
		);
		assignment_operator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ASSIGNMENT_EXPRESSION
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* assignment_expression;
			if (parse_assignment_expression(sym, tokens, assignment_expression)
				== ParserExitCode::SUCCESS) {

				expression = new AstNode(
					AstNodeName::EXPRESSION,
					AstNodeAlt::EXPRESSION_1,
					NULL
				);
				expression->add_child(assignment_expression);

				state = ASSIGNMENT_EXPRESSION;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case ASSIGNMENT_EXPRESSION:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {

				tokens++;
				AstNode* assignment_expression;
				if (parse_assignment_expression(
					sym,
					tokens,
					assignment_expression)
					== ParserExitCode::SUCCESS) {

					AstNode* higher_expression;
					higher_expression = new AstNode(
						AstNodeName::EXPRESSION,
						AstNodeAlt::EXPRESSION_2,
						NULL
					);
					higher_expression->add_child(
						expression);
					higher_expression->add_child(
						assignment_expression);
					expression = higher_expression;
					continue;
				}
			}
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_conditional_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& conditional_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_conditional_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		CONDITIONAL_EXPRESSION
	};

	ParsingState state = START;
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	bool should_generate = false;

	AstNode* logical_or_expression;
	if (parse_logical_or_expression(sym, tokens, logical_or_expression)
		== ParserExitCode::SUCCESS) {
		stack[si++] = logical_or_expression;

		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::QUESTION_MARK) {
			tokens++;

			AstNode* expression;
			if (parse_expression(sym, tokens, expression)
				== ParserExitCode::SUCCESS) {
				stack[si++] = expression;

				AstNode* conditional_expression;
				if (parse_conditional_expression(sym, tokens, conditional_expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = conditional_expression;

					should_generate = true;
					alt = AstNodeAlt::CONDITIONAL_EXPRESSION_2;
				}
			}
		}
		else {
			should_generate = true;
			alt = AstNodeAlt::CONDITIONAL_EXPRESSION_1;
		}
	}
	if (should_generate) {
		conditional_expression = new AstNode(
			AstNodeName::CONDITIONAL_EXPRESSION,
			alt,
			NULL
		);
		conditional_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si > 0) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_assignment_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& assignment_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_assignment_expression", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		CONDITIONAL_EXPRESSION
	};

	ParsingState state = START;
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	Token* backtrack = tokens;

	bool should_generate = false;
	if (lookup(
		first_of_unary_expression,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* unary_expression;
		if (parse_unary_expression(
			sym,
			tokens,
			unary_expression)
			== ParserExitCode::SUCCESS) {

			stack[si++] = unary_expression;

			AstNode* assignment_operator;
			if (parse_assignment_operator(
				sym,
				tokens,
				assignment_operator)
				== ParserExitCode::SUCCESS) {

				stack[si++] = assignment_operator;

				AstNode* assignment_expression;
				if (parse_assignment_expression(
					sym,
					tokens,
					assignment_expression)
					== ParserExitCode::SUCCESS) {

					stack[si++] = assignment_expression;
					should_generate = true;
					alt = AstNodeAlt::ASSIGNMENT_EXPRESSION_2;
				}
			}
		}
	}
	if (!should_generate) {
		tokens = backtrack;
		while (si) {
			delete stack[--si];
		}
	}
	if (!should_generate && lookup(
		first_of_conditional_expression,
		tokens->get_name(),
		tokens->get_form())) {

		cout << "ast-node.cpp:"
			<< "parse_assignment_expression:"
			<< " backtracking."
			<< endl;

		AstNode* conditional_expression;
		if (parse_conditional_expression(
			sym,
			tokens,
			conditional_expression)
			== ParserExitCode::SUCCESS) {

			alt = AstNodeAlt::ASSIGNMENT_EXPRESSION_1;
			stack[si++] = conditional_expression;
			should_generate = true;
		}

	}
	if (should_generate) {
		assignment_expression = new AstNode(
			AstNodeName::ASSIGNMENT_EXPRESSION,
			alt,
			NULL
		);
		assignment_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}


static inline ParserExitCode parse_constant_expression(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& constant_expression)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_constant_expression", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	bool should_generate = false;
	if (lookup(
		first_of_conditional_expression,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* conditional_expression;
		if (parse_conditional_expression(
			sym,
			tokens,
			conditional_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = conditional_expression;
			should_generate = true;
		}
	}
	if (should_generate) {
		constant_expression = new AstNode(
			AstNodeName::CONDITIONAL_EXPRESSION,
			AstNodeAlt::CONSTANT_EXPRESSION_1,
			NULL
		);
		constant_expression->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_declaration(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& declaration)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_declaration", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		CONDITIONAL_EXPRESSION
	};

	ParsingState state = START;
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	bool should_generate = false;

	AstNode* declaration_specifiers;
	if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
		== ParserExitCode::SUCCESS) {
		stack[si++] = declaration_specifiers;

		if (lookup(
			first_of_init_declarator_list,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* init_declarator_list;
			if (parse_init_declarator_list(
				sym,
				tokens,
				init_declarator_list)
				== ParserExitCode::SUCCESS) {

				stack[si++] = init_declarator_list;
			}
		}
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::SEMI_COLON) {
			tokens++;
			should_generate = true;
		}
	}
	if (should_generate) {
		declaration = new AstNode(
			AstNodeName::DECLARATION,
			AstNodeAlt::DECLARATION_1,
			NULL
		);
		declaration->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}


static inline ParserExitCode parse_storage_class_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& storage_class_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_storage_class_specifier", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[15];
	int si = 0;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::KEYWORD) {
		switch (tokens->get_form()) {
		case TokenForm::TYPEDEF:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::STORAGE_CLASS_SPECIFIER_1;
			should_generate = true;
			break;
		case TokenForm::EXTERN:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::STORAGE_CLASS_SPECIFIER_2;
			should_generate = true;
			break;
		case TokenForm::STATIC:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::STORAGE_CLASS_SPECIFIER_3;
			should_generate = true;
			break;
		case TokenForm::AUTO:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::STORAGE_CLASS_SPECIFIER_4;
			should_generate = true;
			break;
		case TokenForm::REGISTER:
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::STORAGE_CLASS_SPECIFIER_5;
			should_generate = true;
			break;
		default:
			break;
		}
	}
	if (should_generate) {
		storage_class_specifier = new AstNode(
			AstNodeName::STORAGE_CLASS_SPECIFIER,
			alt,
			NULL
		);
		storage_class_specifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}


static inline ParserExitCode parse_function_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& function_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_function_specifier", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;
	if (tokens->get_name() == TokenName::KEYWORD
		&& tokens->get_form() == TokenForm::INLINE) {
		function_specifier = new AstNode(
			AstNodeName::STORAGE_CLASS_SPECIFIER,
			AstNodeAlt::FUNCTION_SPECIFIER_1,
			NULL
		);
		function_specifier->add_child(construct_terminal(tokens++));
		exitcode = ParserExitCode::SUCCESS;
	}
	return exitcode;
}

static inline ParserExitCode parse_declaration_specifiers(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& declaration_specifiers)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_declaration_specifiers", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (lookup(
		first_of_storage_class_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* storage_class_specifier;
		if (parse_storage_class_specifier(
			sym,
			tokens,
			storage_class_specifier)
			== ParserExitCode::SUCCESS) {

			stack[si++] = storage_class_specifier;

			if (lookup(
				first_of_declaration_specifiers,
				tokens->get_name(),
				tokens->get_form())) {

				if (tokens->get_name() != TokenName::IDENTIFIER
					|| (sym->get_entry(tokens->get_lexeme())
						&& (sym->get_entry(tokens->get_lexeme())->is_typedef))) {

					AstNode* declaration_specifiers;
					if (parse_declaration_specifiers(
						sym,
						tokens,
						declaration_specifiers)
						== ParserExitCode::SUCCESS) {
						stack[si++] = declaration_specifiers;
					}
				}
			}
			alt = AstNodeAlt::DECLARATION_SPECIFIERS_1;
			should_generate = true;
		}
	}
	else if (lookup(
		first_of_type_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* type_specifier;
		if (parse_type_specifier(sym, tokens, type_specifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_specifier;

			if (tokens->get_name() != TokenName::IDENTIFIER
				|| (sym->get_entry(tokens->get_lexeme()))
				&& (sym->get_entry(tokens->get_lexeme())->is_typedef)) {

				AstNode* declaration_specifiers;
				if (parse_declaration_specifiers(
					sym,
					tokens,
					declaration_specifiers)
					== ParserExitCode::SUCCESS) {
					stack[si++] = declaration_specifiers;
				}
			}
			alt = AstNodeAlt::DECLARATION_SPECIFIERS_2;
			should_generate = true;
		}
	}
	else if (lookup(
		first_of_type_qualifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* type_qualifier;
		if (parse_type_qualifier(sym, tokens, type_qualifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_qualifier;

			if (tokens->get_name() != TokenName::IDENTIFIER
				|| (sym->get_entry(tokens->get_lexeme())
					&& (sym->get_entry(tokens->get_lexeme())->is_typedef))) {

				AstNode* declaration_specifiers;
				if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
					== ParserExitCode::SUCCESS) {
					stack[si++] = declaration_specifiers;
				}
			}
			alt = AstNodeAlt::DECLARATION_SPECIFIERS_3;
			should_generate = true;
		}
	}
	else if (lookup(
		first_of_function_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* function_specifier;
		if (parse_function_specifier(
			sym,
			tokens,
			function_specifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = function_specifier;


			if (tokens->get_name() != TokenName::IDENTIFIER
				|| (sym->get_entry(tokens->get_lexeme())
					&& (sym->get_entry(tokens->get_lexeme())->is_typedef))) {

				AstNode* declaration_specifiers;
				if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
					== ParserExitCode::SUCCESS) {
					stack[si++] = declaration_specifiers;
				}
			}
			alt = AstNodeAlt::DECLARATION_SPECIFIERS_4;
			should_generate = true;
		}
	}
	else if (lookup(
		first_of_type_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* type_specifier;
		if (parse_type_specifier(sym, tokens, type_specifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_specifier;


			if (tokens->get_name() != TokenName::IDENTIFIER
				|| (sym->get_entry(tokens->get_lexeme())
					&& (sym->get_entry(tokens->get_lexeme())->is_typedef))) {

				AstNode* declaration_specifiers;
				if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
					== ParserExitCode::SUCCESS) {
					stack[si++] = declaration_specifiers;
				}
			}
		}
	}
	if (should_generate) {
		declaration_specifiers = new AstNode(
			AstNodeName::DECLARATION_SPECIFIERS,
			alt,
			NULL
		);
		declaration_specifiers->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_init_declarator_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& init_declarator_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_init_declarator_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		INIT_DECLARATOR
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* init_declarator;
			if (parse_init_declarator(sym, tokens, init_declarator)
				== ParserExitCode::SUCCESS) {

				init_declarator_list = new AstNode(
					AstNodeName::INIT_DECLARATOR_LIST,
					AstNodeAlt::INIT_DECLARATOR_LIST_1,
					NULL
				);
				init_declarator_list->add_child(init_declarator);

				state = INIT_DECLARATOR;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case INIT_DECLARATOR:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR)

				switch (tokens->get_form()) {

				case TokenForm::COMMA:
				{
					tokens++;
					AstNode* init_declarator;
					if (parse_init_declarator(sym, tokens, init_declarator)
						== ParserExitCode::SUCCESS) {

						AstNode* higher_init_declarator_list;
						higher_init_declarator_list = new AstNode(
							AstNodeName::INIT_DECLARATOR_LIST,
							AstNodeAlt::INIT_DECLARATOR_LIST_2,
							NULL
						);
						higher_init_declarator_list->add_child(
							init_declarator_list);
						higher_init_declarator_list->add_child(
							init_declarator);
						init_declarator_list =
							higher_init_declarator_list;
						continue;
					}
				}
				break;

				default:
					break;
				}
		}
		break;


		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_init_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& init_declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_init_declarator", tokens);
	}
	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* declarator;
	if (parse_declarator(sym, tokens, declarator)
		== ParserExitCode::SUCCESS) {
		stack[si++] = declarator;

		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::ASSIGN) {
			tokens++;

			AstNode* initializer;
			if (parse_initializer(sym, tokens, initializer)
				== ParserExitCode::SUCCESS) {
				stack[si++] = initializer;
				alt = AstNodeAlt::INIT_DECLARATOR_2;
				should_generate = true;
			}
		}
		else {
			alt = AstNodeAlt::INIT_DECLARATOR_1;
			should_generate = true;
		}
	}
	if (should_generate) {
		init_declarator = new AstNode(
			AstNodeName::INIT_DECLARATOR,
			alt,
			NULL
		);
		init_declarator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_enum_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& enum_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_enum_specifier", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::KEYWORD
		&& tokens->get_form() == TokenForm::ENUM) {
		tokens++;

		if (tokens->get_name() == TokenName::IDENTIFIER) {
			stack[si++] = construct_terminal(tokens++);

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
				tokens++;

				AstNode* enumerator_list;
				if (parse_enumerator_list(
					sym,
					tokens,
					enumerator_list)
					== ParserExitCode::SUCCESS) {
					stack[si++] = enumerator_list;

					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
						tokens++;

						alt = AstNodeAlt::ENUM_SPECIFIER_1;
						should_generate = true;

					}
					else if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::COMMA) {
						tokens++;

						if (tokens->get_name() == TokenName::PUNCTUATOR
							&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
							tokens++;

							alt = AstNodeAlt::ENUM_SPECIFIER_2;
							should_generate = true;
						}
					}
				}
			}
			else {
				alt = AstNodeAlt::ENUM_SPECIFIER_3;
				should_generate = true;
			}

		}
		else {
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
				tokens++;

				AstNode* enumerator_list;
				if (parse_enumerator_list(
					sym,
					tokens,
					enumerator_list)
					== ParserExitCode::FAIL) {
					stack[si++] = enumerator_list;

					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
						tokens++;
						alt = AstNodeAlt::ENUM_SPECIFIER_1;
						should_generate = true;

					}
					else if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::COMMA) {
						tokens++;

						if (tokens->get_name() == TokenName::PUNCTUATOR
							&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
							tokens++;
							alt = AstNodeAlt::ENUM_SPECIFIER_2;
							should_generate = true;
						}
					}
				}
			}
		}
	}
	if (should_generate) {
		enum_specifier = new AstNode(
			AstNodeName::ENUM_SPECIFIER,
			alt,
			NULL
		);
		enum_specifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si > 0) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_typedef_name(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& typedef_name)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_typedef_name", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::IDENTIFIER) {
		typedef_name = construct_terminal(tokens++);
		exitcode = ParserExitCode::SUCCESS;
	}
	return exitcode;
}

static inline ParserExitCode parse_type_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& type_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_type_specifier", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (lookup(
		first_of_struct_or_union,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* struct_or_union;
		if (parse_struct_or_union(sym, tokens, struct_or_union)
			== ParserExitCode::SUCCESS) {
			stack[si++] = struct_or_union;
		}
		alt = AstNodeAlt::TYPE_SPECIFIER_12;
		should_generate = true;

	}
	else if (lookup(
		first_of_enum_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* enum_specifier;
		if (parse_enum_specifier(
			sym,
			tokens,
			enum_specifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = enum_specifier;
		}
		alt = AstNodeAlt::TYPE_SPECIFIER_13;
		should_generate = true;

	}
	else if (lookup(
		first_of_typedef_name,
		tokens->get_name(),
		tokens->get_form())) {
		/* typedef-name */
		AstNode* typedef_name;
		if (parse_typedef_name(
			sym,
			tokens,
			typedef_name)
			== ParserExitCode::SUCCESS) {
			stack[si++] = typedef_name;
		}
		alt = AstNodeAlt::TYPE_SPECIFIER_14;
		should_generate = true;
	}
	else {
		if (tokens->get_name() == TokenName::KEYWORD) {

			switch (tokens->get_form()) {

			case TokenForm::VOID: alt = AstNodeAlt::TYPE_SPECIFIER_1; break;
			case TokenForm::CHAR: alt = AstNodeAlt::TYPE_SPECIFIER_2; break;
			case TokenForm::SHORT: alt = AstNodeAlt::TYPE_SPECIFIER_3; break;
			case TokenForm::INT: alt = AstNodeAlt::TYPE_SPECIFIER_4; break;
			case TokenForm::LONG: alt = AstNodeAlt::TYPE_SPECIFIER_5; break;
			case TokenForm::FLOAT: alt = AstNodeAlt::TYPE_SPECIFIER_6; break;
			case TokenForm::DOUBLE: alt = AstNodeAlt::TYPE_SPECIFIER_7; break;
			case TokenForm::SIGNED: alt = AstNodeAlt::TYPE_SPECIFIER_8; break;
			case TokenForm::UNSIGNED: alt = AstNodeAlt::TYPE_SPECIFIER_9; break;
			case TokenForm::_BOOL: alt = AstNodeAlt::TYPE_SPECIFIER_10; break;
			case TokenForm::_COMPLEX: alt = AstNodeAlt::TYPE_SPECIFIER_11; break;
			default: break;
			}
		}
		tokens++;
		should_generate = true;
	}
	if (should_generate) {
		type_specifier = new AstNode(
			AstNodeName::TYPE_SPECIFIER,
			alt,
			NULL
		);
		type_specifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_or_union_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_or_union_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_or_union_specifier", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	AstNode* struct_or_union;
	if (lookup(
		first_of_struct_or_union,
		tokens->get_name(),
		tokens->get_form())
		&& (parse_struct_or_union(
			sym,
			tokens,
			struct_or_union)
			== ParserExitCode::SUCCESS)) {

		if (tokens->get_name() == TokenName::IDENTIFIER) {
			stack[si++] = construct_terminal(tokens++);

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
				tokens++;

				AstNode* struct_declaration_list;
				if (lookup(
					first_of_struct_declarator_list,
					tokens->get_name(),
					tokens->get_form())
					&& (parse_struct_declaration_list(
						sym,
						tokens,
						struct_declaration_list)
						== ParserExitCode::SUCCESS)) {

					stack[si++] = struct_declaration_list;

					if ((tokens->get_name()
						== TokenName::PUNCTUATOR)
						&& (tokens->get_form()
							== TokenForm::CLOSE_CURLY_BRACKET)) {
						tokens++;

						alt = AstNodeAlt::STRUCT_OR_UNION_SPECIFIER_1;
						should_generate = true;
					}
				}
			}
			else {
				alt = AstNodeAlt::STRUCT_OR_UNION_SPECIFIER_1;
				should_generate = true;
			}

		}
		else {
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
				tokens++;

				AstNode* struct_declaration_list;
				if (lookup(
					first_of_struct_declarator_list,
					tokens->get_name(),
					tokens->get_form())
					&& (parse_struct_declaration_list(
						sym,
						tokens,
						struct_declaration_list)
						== ParserExitCode::SUCCESS)) {

					stack[si++] = struct_declaration_list;

					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
						tokens++;

						alt = AstNodeAlt::STRUCT_OR_UNION_SPECIFIER_1;
						should_generate = true;
					}
				}
			}
		}
	}
	if (should_generate) {
		struct_or_union_specifier = new AstNode(
			AstNodeName::STRUCT_OR_UNION_SPECIFIER,
			alt,
			NULL
		);
		struct_or_union_specifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_or_union(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_or_union)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_or_union", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	if (tokens->get_name() == TokenName::KEYWORD) {

		switch (tokens->get_form()) {

		case TokenForm::STRUCT:
			struct_or_union = new AstNode(
				AstNodeName::STRUCT_OR_UNION,
				AstNodeAlt::STRUCT_OR_UNION_1,
				NULL);
			struct_or_union->add_child(construct_terminal(tokens++));
			exitcode = ParserExitCode::SUCCESS;
			break;

		case TokenForm::UNION:
			struct_or_union = new AstNode(
				AstNodeName::STRUCT_OR_UNION,
				AstNodeAlt::STRUCT_OR_UNION_2,
				NULL);
			struct_or_union->add_child(construct_terminal(tokens++));
			exitcode = ParserExitCode::SUCCESS;
			break;
		default:
			break;

		}
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_declaration_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_declaration_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_declaration_list", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		STRUCT_DECLARATION_LIST
	};

	ParsingState state = START;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	while (true) {

		switch (state) {

		case START:
			AstNode* struct_declaration;
			if (parse_struct_declaration(
				sym,
				tokens,
				struct_declaration)
				== ParserExitCode::FAIL) {

				struct_declaration_list = new AstNode(
					AstNodeName::STRUCT_DECLARATION_LIST,
					AstNodeAlt::STRUCT_DECLARATION_LIST_1,
					NULL);
				struct_declaration_list->add_child(struct_declaration);
				state = ParsingState::STRUCT_DECLARATION_LIST;
				continue;
			}
			break;

		case STRUCT_DECLARATION_LIST:
		{
			if (lookup(
				first_of_struct_declaration,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* struct_declaration;
				if (parse_struct_declaration(
					sym,
					tokens,
					struct_declaration)
					== ParserExitCode::FAIL) {
					stack[si++] = struct_declaration;

					AstNode* higher_struct_declaration_list = new AstNode(
						AstNodeName::STRUCT_DECLARATION_LIST,
						AstNodeAlt::STRUCT_DECLARATION_LIST_2,
						NULL
					);

					higher_struct_declaration_list->add_child(
						struct_declaration_list);
					higher_struct_declaration_list->add_child(
						struct_declaration);
					struct_declaration_list = higher_struct_declaration_list;
					continue;
				}
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_declaration(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_declaration)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_declaration", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	AstNode* stack[16];
	int si = 0;

	bool should_generate = true;

	if (lookup(
		first_of_specifier_qualifier_list,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* specifier_qualifier_list;
		if (parse_specifier_qualifier_list(
			sym,
			tokens,
			specifier_qualifier_list)
			== ParserExitCode::SUCCESS) {
			stack[si++] = specifier_qualifier_list;

			AstNode* struct_declarator_list;
			if (parse_struct_declarator_list(
				sym,
				tokens,
				struct_declarator_list)
				== ParserExitCode::SUCCESS) {
				stack[si++] = struct_declarator_list;

				should_generate = true;
			}
		}
	}
	if (should_generate) {
		struct_declaration = new AstNode(
			AstNodeName::STRUCT_DECLARATION,
			AstNodeAlt::STRUCT_DECLARATION_1,
			NULL
		);
		struct_declaration->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_specifier_qualifier_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& specifier_qualifier_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_specifier_qualifier_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (lookup(
		first_of_type_specifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* type_specifier;
		if (parse_type_specifier(
			sym,
			tokens,
			type_specifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_specifier;

			alt = AstNodeAlt::SPECIFIER_QUALIFIER_LIST_1;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_type_qualifier,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* type_qualifier;
		if (parse_type_qualifier(
			sym,
			tokens,
			type_qualifier)
			== ParserExitCode::SUCCESS) {
			stack[si++] = type_qualifier;

			alt = AstNodeAlt::SPECIFIER_QUALIFIER_LIST_2;
			should_generate = true;
		}
	}
	if (lookup(
		first_of_specifier_qualifier_list,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* specifier_qualifier_list;
		if (parse_specifier_qualifier_list(
			sym,
			tokens,
			specifier_qualifier_list)
			== ParserExitCode::SUCCESS) {
			stack[si++] = specifier_qualifier_list;

			should_generate = true;
		}
	}
	if (should_generate) {
		specifier_qualifier_list = new AstNode(
			AstNodeName::SPECIFIER_QUALIFIER_LIST,
			alt,
			NULL
		);
		specifier_qualifier_list->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_declarator_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_declarator_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_declarator_list", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	enum ParsingState {
		START,
		STRUCT_DECLARATOR_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* struct_declarator;
			if (parse_struct_declarator(
				sym,
				tokens,
				struct_declarator)
				== ParserExitCode::FAIL) {

				struct_declarator_list = new AstNode(
					AstNodeName::STRUCT_DECLARATOR_LIST,
					AstNodeAlt::STRUCT_DECLARATOR_LIST_1,
					NULL);
				struct_declarator_list->add_child(struct_declarator);

				state = ParsingState::STRUCT_DECLARATOR_LIST;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case STRUCT_DECLARATOR_LIST:
		{
			if (lookup(
				first_of_struct_declarator,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* struct_declarator;
				if (parse_struct_declarator(
					sym,
					tokens,
					struct_declarator)
					== ParserExitCode::FAIL) {
					stack[si++] = struct_declarator;

					AstNode* higher_struct_declarator_list = new AstNode(
						AstNodeName::STRUCT_DECLARATOR_LIST,
						AstNodeAlt::STRUCT_DECLARATOR_LIST_2,
						NULL
					);

					higher_struct_declarator_list->add_child(
						struct_declarator_list);
					higher_struct_declarator_list->add_child(
						struct_declarator);
					struct_declarator = higher_struct_declarator_list;
					continue;
				}
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_struct_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& struct_declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_struct_declarator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (lookup(
		first_of_declarator,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* declarator;
		if (parse_declarator(
			sym,
			tokens,
			declarator)
			== ParserExitCode::SUCCESS) {
			stack[si++] = declarator;

			alt = AstNodeAlt::STRUCT_DECLARATOR_1;
			should_generate = true;
		}

	}
	else {
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::COLON) {
			tokens++;

			AstNode* constant_expression;
			if (parse_constant_expression(
				sym,
				tokens,
				constant_expression)
				== ParserExitCode::FAIL) {
				stack[si++] = constant_expression;

				alt = AstNodeAlt::STRUCT_DECLARATOR_2;
				should_generate = true;
			}
		}
	}
	if (should_generate) {
		struct_declarator = new AstNode(
			AstNodeName::STRUCT_DECLARATOR,
			alt,
			NULL
		);
		struct_declarator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_enumeration_constant(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& enumeration_constant)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_enumerator", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ENUMERATOR,
		ENUMERATOR_LIST
	};

	if (tokens->get_name() == TokenName::IDENTIFIER) {
		enumeration_constant = new AstNode(
			AstNodeName::ENUMERATION_CONSTANT,
			AstNodeAlt::ENUMERATION_CONSTANT_1,
			NULL
		);
		enumeration_constant->add_child(construct_terminal(tokens++));
		exitcode = ParserExitCode::SUCCESS;
	}
	return exitcode;
}

static inline ParserExitCode parse_enumerator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& enumerator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_enumerator", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ENUMERATOR,
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* enumeration_constant;
			if (parse_enumeration_constant(sym, tokens, enumeration_constant)
				== ParserExitCode::SUCCESS) {

				enumerator = new AstNode(
					AstNodeName::ENUMERATOR,
					AstNodeAlt::ENUMERATOR_1,
					NULL
				);
				enumerator->add_child(enumeration_constant);
				state = ENUMERATOR;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;
		}

		case ENUMERATOR:
		{
			AstNode* enumeration_constant;
			if (parse_enumeration_constant(sym, tokens, enumeration_constant)
				== ParserExitCode::SUCCESS) {

				AstNode* higher_enumerator = new AstNode(
					AstNodeName::ENUMERATOR,
					AstNodeAlt::ENUMERATOR_2,
					NULL
				);

				higher_enumerator->add_child(enumerator);
				higher_enumerator->add_child(enumeration_constant);
				enumerator = higher_enumerator;
				continue;
			}
			break;
		}

		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_enumerator_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& enumerator_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_enumerator_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ENUMERATOR_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* enumerator;
			if (parse_enumerator(sym, tokens, enumerator)
				== ParserExitCode::SUCCESS) {

				enumerator_list = new AstNode(
					AstNodeName::ENUMERATOR_LIST,
					AstNodeAlt::ENUMERATOR_LIST_1,
					NULL
				);
				enumerator_list->add_child(enumerator);
				state = ENUMERATOR_LIST;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;
		}

		case ENUMERATOR_LIST:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;

				AstNode* enumerator;
				if (parse_enumerator(sym, tokens, enumerator)
					== ParserExitCode::SUCCESS) {
					AstNode* higher_enumerator_list = new AstNode(
						AstNodeName::ENUMERATOR_LIST,
						AstNodeAlt::ENUMERATOR_LIST_2,
						NULL
					);

					higher_enumerator_list->add_child(enumerator_list);
					higher_enumerator_list->add_child(enumerator);
					enumerator_list = higher_enumerator_list;
					continue;
				}
			}
			break;
		}

		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_enumeration_specifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& enumeration_specifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_enumeration_specifier", tokens);
	}
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (tokens->get_name() == TokenName::KEYWORD
		&& tokens->get_form() == TokenForm::ENUM) {
		tokens++;

		if (tokens->get_name() == TokenName::IDENTIFIER) {
			stack[si++] = construct_terminal(tokens++);
		}
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::OPEN_PAREN) {

			AstNode* enumerator_list;
			if ((parse_enumerator_list(sym, tokens, enumerator_list))
				== ParserExitCode::SUCCESS) {
				stack[si++] = enumerator_list;

				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::COMMA) {
					tokens++;
					alt = AstNodeAlt::ENUM_SPECIFIER_2;
				}
				else {
					alt = AstNodeAlt::ENUM_SPECIFIER_1;
				}

				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
					tokens++;
					should_generate = true;
				}
			}
		}
		else {
			alt = AstNodeAlt::ENUM_SPECIFIER_3;
			should_generate = true;
		}
	}
	if (should_generate) {
		enumeration_specifier = new AstNode(
			AstNodeName::ENUMERATION_SPECIFIER,
			alt,
			NULL
		);
		enumeration_specifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_type_qualifier(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& type_qualifier)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_type_qualifier", tokens);
	}
	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (tokens->get_name() == TokenName::KEYWORD) {
		switch (tokens->get_form()) {

		case TokenForm::CONST:
			alt = AstNodeAlt::TYPE_QUALIFIER_1;
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			break;

		case TokenForm::RESTRICT:
			alt = AstNodeAlt::TYPE_QUALIFIER_2;
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			break;

		case TokenForm::VOLATILE:
			alt = AstNodeAlt::TYPE_QUALIFIER_3;
			stack[si++] = construct_terminal(tokens++);
			should_generate = true;
			break;

		default: break;
		}
	}
	if (should_generate) {
		type_qualifier = new AstNode(
			AstNodeName::TYPE_QUALIFIER,
			alt,
			NULL
		);
		type_qualifier->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_parameter_type_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& parameter_type_list)
{
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[15];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	bool should_generate = false;

	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_parameter_type_list", tokens);
	}
	AstNode* parameter_list;
	if (parse_parameter_list(sym, tokens, parameter_list)
		== ParserExitCode::SUCCESS) {
		stack[si++] = parameter_list;

		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::COMMA) {

			if ((tokens + 1)->get_name() == TokenName::PUNCTUATOR
				&& (tokens + 1)->get_form() == TokenForm::TRIPLE_DOT) {
				tokens += 2;

				alt = AstNodeAlt::PARAMETER_TYPE_LIST_1;
				should_generate = true;
			}
		}
		else {
			alt = AstNodeAlt::PARAMETER_TYPE_LIST_2;
			should_generate = true;
		}
	}
	if (should_generate) {
		parameter_type_list = new AstNode(
			AstNodeName::PARAMETER_TYPE_LIST,
			alt,
			NULL
		);
		parameter_type_list->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_direct_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& direct_declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_direct_declarator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		DIRECT_DECLARATOR
	};
	ParsingState state = START;

	while (true) {

		switch (state) {

		case START:
			if (tokens->get_name() == TokenName::IDENTIFIER) {

				direct_declarator = new AstNode(
					AstNodeName::DIRECT_DECLARATOR,
					AstNodeAlt::DIRECT_DECLARATOR_1,
					NULL
				);
				direct_declarator->add_child(construct_terminal(tokens++));
				state = DIRECT_DECLARATOR;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			else if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN) {

				tokens++;
				AstNode* declarator;
				if (parse_declarator(sym, tokens, declarator)
					== ParserExitCode::SUCCESS) {

					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
						tokens++;

						direct_declarator = new AstNode(
							AstNodeName::DIRECT_DECLARATOR,
							AstNodeAlt::DIRECT_DECLARATOR_2,
							NULL
						);
						direct_declarator->add_child(declarator);
						state = DIRECT_DECLARATOR;
						exitcode = ParserExitCode::SUCCESS;
						continue;
					}
				}
			}
			break;

		case DIRECT_DECLARATOR:
		{
			bool should_append = false;
			AstNodeAlt appended_alt = AstNodeAlt::ERROR;

			AstNode* stack[16];
			int si = 0;

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
				tokens++;

				if (lookup(
					first_of_type_qualifier_list,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* type_qualifier_list;
					if (parse_type_qualifier_list(
						sym,
						tokens,
						type_qualifier_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = type_qualifier_list;
					}

					if (tokens->get_name() == TokenName::IDENTIFIER
						&& tokens->get_form() == TokenForm::STATIC) {
						tokens++;
					}
					else if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::ASTERIX) {
						tokens++;
						appended_alt = AstNodeAlt::DIRECT_DECLARATOR_6;
						should_append = true;
					}
					AstNode* assignment_expression;
					if (parse_assignment_expression(
						sym,
						tokens,
						assignment_expression)
						== ParserExitCode::SUCCESS) {
						stack[si++] = assignment_expression;
					}
					if (tokens->get_name() == TokenName::PUNCTUATOR
						|| tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
						tokens++;
						appended_alt =
							AstNodeAlt::DIRECT_DECLARATOR_1;
						should_append = true;
					}
					break;

				}
				else if (tokens->get_name() == TokenName::KEYWORD
					&& tokens->get_form() == TokenForm::STATIC) {

					AstNode* type_qualifier_list;
					if (parse_type_qualifier_list(
						sym,
						tokens,
						type_qualifier_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = type_qualifier_list;
					}
					AstNode* assignment_expression;
					if (parse_assignment_expression(
						sym,
						tokens,
						assignment_expression)
						== ParserExitCode::SUCCESS) {
						stack[si++] = assignment_expression;

						if (tokens->get_name() == TokenName::PUNCTUATOR
							|| tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
							tokens++;
							appended_alt = AstNodeAlt::DIRECT_DECLARATOR_4;
							should_append = true;
						}
					}
				}
			}
			else if (tokens->get_form() == TokenForm::OPEN_PAREN) {
				tokens++;

				if (lookup(
					first_of_parameter_type_list,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* parameter_type_list;
					if (parse_parameter_type_list(sym, tokens, parameter_type_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = parameter_type_list;
						/*identifier */
						if (tokens->get_name() == TokenName::PUNCTUATOR
							&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
							tokens++;

							should_append = true;
							appended_alt = AstNodeAlt::DIRECT_DECLARATOR_7;
						}
					}
				}
				else if (lookup(
					first_of_identifier_list,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* identifier_list;
					if (parse_identifier_list(sym, tokens, identifier_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = identifier_list;
					}
					should_append = true;
					appended_alt = AstNodeAlt::DIRECT_DECLARATOR_8;

				}
				if (should_append) {
					AstNode* higher_direct_declarator = new AstNode(
						AstNodeName::DIRECT_DECLARATOR,
						appended_alt,
						NULL
					);
					higher_direct_declarator->add_child(direct_declarator);
					higher_direct_declarator->add_children(stack, si);
					direct_declarator = higher_direct_declarator;
					continue;
				}
				else {
					/* Free unused ast nodes generated. */
					while (si) {
						delete stack[--si];
					}
					break;
				}
				break;
			}
			break;
		}
		break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_declarator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::ASTERIX) {

		AstNode* pointer;
		if (parse_pointer(sym, tokens, pointer)
			== ParserExitCode::SUCCESS) {
			stack[si++] = pointer;
		}
	}
	if (tokens->get_name() == TokenName::IDENTIFIER) {
		AstNode* direct_declarator;
		if (parse_direct_declarator(sym, tokens, direct_declarator)
			== ParserExitCode::SUCCESS) {
			stack[si++] = direct_declarator;
			should_generate = true;
		}
	}
	if (should_generate) {
		declarator = new AstNode(
			AstNodeName::DECLARATOR,
			AstNodeAlt::DECLARATOR_1,
			NULL
		);
		declarator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_type_qualifier_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& type_qualifier_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_type_qualifier_list", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	enum ParsingState {
		START,
		TYPE_QUALIFIER_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* type_qualifier;
			if (parse_type_qualifier(
				sym,
				tokens,
				type_qualifier)
				== ParserExitCode::FAIL) {

				type_qualifier_list = new AstNode(
					AstNodeName::TYPE_QUALIFIER_LIST,
					AstNodeAlt::TYPE_QUALIFIER_LIST_1,
					NULL);
				type_qualifier_list->add_child(type_qualifier);
				state = ParsingState::TYPE_QUALIFIER_LIST;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			break;

		case TYPE_QUALIFIER_LIST:
		{
			if (lookup(
				first_of_type_qualifier,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* type_qualifier;
				if (parse_type_qualifier(
					sym,
					tokens,
					type_qualifier)
					== ParserExitCode::FAIL) {
					stack[si++] = type_qualifier;

					AstNode* higher_type_qualifier_list = new AstNode(
						AstNodeName::TYPE_QUALIFIER_LIST,
						AstNodeAlt::TYPE_QUALIFIER_LIST_2,
						NULL
					);

					higher_type_qualifier_list->add_child(
						type_qualifier_list);
					higher_type_qualifier_list->add_child(
						type_qualifier);
					type_qualifier_list = higher_type_qualifier_list;
					continue;
				}
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_pointer(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& pointer)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_pointer", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::ASTERIX) {
		tokens++;

		if (lookup(
			first_of_type_qualifier_list,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* type_qualifier_list;
			if (parse_type_qualifier_list(
				sym,
				tokens,
				type_qualifier_list)
				== ParserExitCode::SUCCESS) {
				stack[si++] = type_qualifier_list;

				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::ASTERIX) {
					tokens++;

					alt = AstNodeAlt::POINTER_2;
					should_generate = true;

				}
				else {

					alt = AstNodeAlt::POINTER_1;
					should_generate = true;
				}
			}

		}
		else {

			if (lookup(
				first_of_pointer,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* pointer;
				if (parse_pointer(
					sym,
					tokens,
					pointer)
					== ParserExitCode::SUCCESS) {

					stack[si++] = pointer;
					should_generate = true;
				}
			}
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_parameter_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& parameter_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_parameter_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		PARAMETER_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* parameter_declaration;
			if (parse_parameter_declaration(
				sym,
				tokens,
				parameter_declaration)
				== ParserExitCode::SUCCESS) {

				parameter_list = new AstNode(
					AstNodeName::PARAMETER_LIST,
					AstNodeAlt::PARAMETER_LIST_1,
					NULL
				);
				parameter_list->add_child(parameter_declaration);
				exitcode = ParserExitCode::SUCCESS;
				state = PARAMETER_LIST;
				continue;
			}
			exitcode = ParserExitCode::SUCCESS;
			break;

		case PARAMETER_LIST:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;

				AstNode* parameter_declaration;
				if (parse_parameter_declaration(
					sym,
					tokens,
					parameter_declaration)
					== ParserExitCode::SUCCESS) {

					AstNode* higher_parameter_list = new AstNode(
						AstNodeName::PARAMETER_LIST,
						AstNodeAlt::PARAMETER_LIST_2,
						NULL
					);
					higher_parameter_list->add_child(parameter_list);
					higher_parameter_list->add_child(parameter_declaration);
					parameter_list = higher_parameter_list;
					continue;
				}
			}
			break;
		}
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_parameter_declaration(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& parameter_declaration)
{
	ParserExitCode exitcode = ParserExitCode::FAIL;

	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_parameter_declaration", tokens);
	}

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = true;

	AstNode* declaration_specifiers;
	if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
		== ParserExitCode::SUCCESS) {
		stack[si++] = declaration_specifiers;

		if (lookup(
			first_of_declarator,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* declarator;
			if (parse_declarator(sym, tokens, declarator)
				== ParserExitCode::SUCCESS) {
				stack[si++] = declarator;
				alt = AstNodeAlt::PARAMETER_DECLARATION_1;
				should_generate = true;
			}

		}
		else if (lookup(
			first_of_abstract_declarator,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* abstract_declarator;
			if (parse_abstract_declarator(sym, tokens, abstract_declarator)
				== ParserExitCode::SUCCESS) {
				stack[si++] = abstract_declarator;
				alt = AstNodeAlt::PARAMETER_DECLARATION_2;
				should_generate = true;
			}
		}
	}
	if (should_generate) {
		parameter_declaration = new AstNode(
			AstNodeName::PARAMETER_DECLARATION,
			alt,
			NULL
		);
		parameter_declaration->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_identifier_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& identifier_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_identifier_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		IDENTIFIER_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			if (tokens->get_name() == TokenName::IDENTIFIER) {
				AstNode* identifier = construct_terminal(tokens++);

				identifier_list = new AstNode(
					AstNodeName::IDENTIFIER_LIST,
					AstNodeAlt::IDENTIFIER_LIST_2,
					NULL
				);
				identifier_list->add_child(identifier);
				exitcode = ParserExitCode::SUCCESS;
				state = IDENTIFIER_LIST;
				continue;
			}
			exitcode = ParserExitCode::SUCCESS;
			break;

		case IDENTIFIER_LIST:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;

				if (tokens->get_name() == TokenName::IDENTIFIER) {
					AstNode* identifier = construct_terminal(tokens++);

					AstNode* higher_identifier_list = new AstNode(
						AstNodeName::IDENTIFIER_LIST,
						AstNodeAlt::IDENTIFIER_LIST_2,
						NULL
					);
					higher_identifier_list->add_child(identifier_list);
					higher_identifier_list->add_child(identifier);
					identifier_list = higher_identifier_list;
					continue;
				}
			}
			break;
		}
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_abstract_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& abstract_declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_abstract_declarator", tokens);
	}

	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (lookup(
		first_of_direct_abstract_declarator,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* direct_declarator;
		if (parse_direct_declarator(sym, tokens, direct_declarator)
			== ParserExitCode::SUCCESS) {
			stack[si++] = direct_declarator;
			alt = AstNodeAlt::ABSTRACT_DECLARATOR_2;
			should_generate = true;
		}

	}
	else if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::ASTERIX) {
		tokens++;

		if (lookup(
			first_of_direct_abstract_declarator,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* direct_declarator;
			if (parse_direct_declarator(sym, tokens, direct_declarator)
				== ParserExitCode::SUCCESS) {
				stack[si++] = direct_declarator;
				alt = AstNodeAlt::ABSTRACT_DECLARATOR_2;
				should_generate = true;
			}

		}
		else {
			alt = AstNodeAlt::ABSTRACT_DECLARATOR_1;
			should_generate = true;
		}

	}
	if (should_generate) {
		abstract_declarator = new AstNode(
			AstNodeName::ABSTRACT_DECLARATOR,
			alt,
			NULL
		);
		abstract_declarator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_direct_abstract_declarator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& direct_abstract_declarator)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_direct_abstract_declarator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		ABSTRACT_DIRECT_DECLARATOR
	};
	ParsingState state = START;

	while (true) {

		switch (state) {

		case START:
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN) {

				direct_abstract_declarator = new AstNode(
					AstNodeName::DIRECT_ABSTRACT_DECLARATOR,
					AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_1,
					NULL
				);
				direct_abstract_declarator->add_child(construct_terminal(tokens++));
				exitcode = ParserExitCode::SUCCESS;
			}
			/* Intentional passover since matching of
			   direct-abstract-declarator is optional. */
			state = ABSTRACT_DIRECT_DECLARATOR;
			continue;

		case ABSTRACT_DIRECT_DECLARATOR:
		{
			bool should_append = false;
			AstNodeAlt appended_alt = AstNodeAlt::ERROR;

			AstNode* stack[16];
			int si = 0;

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
				tokens++;

				if (lookup(
					first_of_type_qualifier_list,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* type_qualifier_list;
					if (parse_type_qualifier_list(
						sym,
						tokens,
						type_qualifier_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = type_qualifier_list;
					}

					if (lookup(
						first_of_assignment_expression,
						tokens->get_name(),
						tokens->get_form())) {

						AstNode* assignment_expression;
						if (parse_assignment_expression(
							sym,
							tokens,
							assignment_expression)
							== ParserExitCode::SUCCESS) {
							stack[si++] = assignment_expression;
						}
					}
					else if (tokens->get_name() == TokenName::KEYWORD
						&& tokens->get_form() == TokenForm::STATIC) {
						tokens++;

						AstNode* assignment_expression;
						if (parse_assignment_expression(
							sym,
							tokens,
							assignment_expression)
							== ParserExitCode::SUCCESS) {
							stack[si++] = assignment_expression;
						}
						else {
							break;
						}
						if (tokens->get_name() == TokenName::PUNCTUATOR
							&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
							tokens++;

							appended_alt = AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_4;
							should_append = true;
						}
						break;
					}
					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
						tokens++;
						appended_alt = AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_2;
						should_append = true;
					}

				}
				else if (tokens->get_name() == TokenName::KEYWORD
					&& tokens->get_form() == TokenForm::STATIC) {
					tokens++;

					if (lookup(
						first_of_type_qualifier_list,
						tokens->get_name(),
						tokens->get_form())) {

						AstNode* type_qualifier_list;
						if (parse_type_qualifier_list(
							sym,
							tokens,
							type_qualifier_list)
							== ParserExitCode::SUCCESS) {
							stack[si++] = type_qualifier_list;
						}
					}
					AstNode* assignment_expression;
					if (parse_assignment_expression(
						sym,
						tokens,
						assignment_expression)
						== ParserExitCode::SUCCESS) {
						stack[si++] = assignment_expression;
					}
					else {
						break;
					}
					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
						tokens++;

						appended_alt = AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_3;
						should_append = true;
					}

				}
				else if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::ASTERIX) {
					tokens++;
					if (tokens->get_name() == TokenName::PUNCTUATOR
						&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
						tokens++;
						appended_alt = AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_5;
						should_append = true;
					}
				}

			}
			else if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN) {
				tokens++;

				if (lookup(
					first_of_parameter_type_list,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* parameter_type_list;
					if (parse_parameter_type_list(
						sym,
						tokens,
						parameter_type_list)
						== ParserExitCode::SUCCESS) {
						stack[si++] = parameter_type_list;
					}
				}
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::CLOSE_PAREN) {
					tokens++;
					appended_alt = AstNodeAlt::DIRECT_ABSTRACT_DECLARATOR_6;
					should_append = true;
				}
			}
			if (should_append) {
				AstNode* higher_direct_abstract_declarator = new AstNode(
					AstNodeName::DIRECT_ABSTRACT_DECLARATOR,
					appended_alt,
					NULL
				);
				if (direct_abstract_declarator) {
					higher_direct_abstract_declarator->add_child(
						direct_abstract_declarator
					);
				}
				higher_direct_abstract_declarator->add_children(stack, si);
				if (direct_abstract_declarator) {
					direct_abstract_declarator = higher_direct_abstract_declarator;
				}
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
			else {
				/* Free unused ast nodes generated. */
				while (si) {
					delete stack[--si];
				}
				break;
			}
			break;
		}
		break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_initializer(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& initializer)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_initializer", tokens);
	}
	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
		tokens++;
		AstNode* initializer_list;
		if (parse_initializer_list(sym, tokens, initializer_list)
			== ParserExitCode::SUCCESS) {
			stack[si++] = initializer_list;
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
				tokens++;
				alt = AstNodeAlt::INITIALIZER_2;
				should_generate = true;
			}
			else if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
					tokens++;
					alt = AstNodeAlt::INITIALIZER_3;
					should_generate = true;
				}
			}
		}
	}
	else {
		AstNode* assignment_expression;
		if (parse_assignment_expression(sym, tokens, assignment_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = assignment_expression;
			alt = AstNodeAlt::INITIALIZER_1;
			should_generate = true;
		}
	}
	if (should_generate) {
		initializer = new AstNode(
			AstNodeName::INITIALIZER,
			alt,
			NULL
		);
		initializer->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_initializer_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& initializer_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_initializer_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		INITIALIZER_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* start_stack[15];
			int start_si = 0;

			if (lookup(
				first_of_designation,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* designation;
				if (parse_designation(
					sym,
					tokens,
					designation)
					== ParserExitCode::SUCCESS) {

					start_stack[start_si++] = designation;
				}
			}
			AstNode* initializer;
			if (parse_initializer(
				sym,
				tokens,
				initializer)
				== ParserExitCode::SUCCESS) {
				start_stack[start_si++] = initializer;
			}
			else {
				break;
			}
			initializer_list = new AstNode(
				AstNodeName::INITIALIZER_LIST,
				AstNodeAlt::INITIALIZER_LIST_1,
				NULL
			);
			initializer_list->add_children(start_stack, start_si);
			exitcode = ParserExitCode::SUCCESS;
			state = INITIALIZER_LIST;
			continue;
		}

		case INITIALIZER_LIST:
		{
			AstNode* append_stack[15];
			int append_si = 0;
			bool should_append = false;

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COMMA) {
				tokens++;

				if (lookup(
					first_of_designation,
					tokens->get_name(),
					tokens->get_form())) {

					AstNode* designation;
					if (parse_designation(
						sym,
						tokens,
						designation)
						== ParserExitCode::SUCCESS) {
						append_stack[append_si++] = designation;
					}
				}
			}
			AstNode* initializer;
			if (parse_initializer(
				sym,
				tokens,
				initializer)
				== ParserExitCode::SUCCESS) {
				append_stack[append_si++] = initializer;
				should_append = true;
			}
			if (should_append) {

				AstNode* higher_initializer_list = new AstNode(
					AstNodeName::INITIALIZER_LIST,
					AstNodeAlt::INITIALIZER_LIST_2,
					NULL
				);
				higher_initializer_list->add_children(append_stack, append_si);
				initializer_list = higher_initializer_list;
				continue;
			}
			else {
				/* Free unused ast nodes generated. */
				while (append_si > 0) {
					delete append_stack[--append_si];
				}
			}
		}

		default:
			break;
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_designation(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& designation)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_designation", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[15];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	bool should_generate = false;

	AstNode* designator_list;
	if (parse_designator_list(
		sym,
		tokens,
		designator_list)
		== ParserExitCode::SUCCESS) {
		stack[si++] = designator_list;

		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::ASSIGN) {
			tokens++;

			alt = AstNodeAlt::DESIGNATOR_LIST_1;
			should_generate = true;
		}
	}
	if (should_generate) {
		designation = new AstNode(
			AstNodeName::DESIGNATION,
			alt,
			NULL
		);
		designation->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_designator_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& designator_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_designator_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		DESIGNATOR_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* start_stack[15];
			int start_si = 0;

			if (lookup(
				first_of_designator,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* designator;
				if (parse_designator(
					sym,
					tokens,
					designator)
					== ParserExitCode::SUCCESS) {

					start_stack[start_si++] = designator;
					exitcode = ParserExitCode::SUCCESS;
				}
			}
			state = DESIGNATOR_LIST;
			continue;
		}

		case DESIGNATOR_LIST:
		{
			AstNode* designator;
			if (parse_designator(
				sym,
				tokens,
				designator)
				== ParserExitCode::SUCCESS) {

				AstNode* higher_designator_list = new AstNode(
					AstNodeName::DESIGNATOR_LIST,
					AstNodeAlt::DESIGNATOR_LIST_2,
					NULL
				);
				higher_designator_list->add_child(designator_list);
				higher_designator_list->add_child(designator);
				designator_list = higher_designator_list;
				continue;
			}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_designator(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& designator) {

	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_designator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[15];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	bool should_generate = false;


	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::OPEN_SQUARE_BRACKET) {
		tokens++;
		AstNode* constant_expression;
		if (parse_constant_expression(
			sym,
			tokens,
			constant_expression)
			== ParserExitCode::FAIL) {
			stack[si++] = constant_expression;
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_SQUARE_BRACKET) {
				tokens++;
				alt = AstNodeAlt::DESIGNATOR_1;
				should_generate = true;
			}
		}
	}
	else if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::DOT) {
		tokens++;
		if (tokens->get_name() == TokenName::IDENTIFIER) {
			stack[si++] = construct_terminal(tokens++);
			alt = AstNodeAlt::DESIGNATOR_2;
			should_generate = true;
		}
	}
	if (should_generate) {
		designator = new AstNode(
			AstNodeName::DESIGNATOR,
			alt,
			NULL
		);
		designator->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_labeled_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& labeled_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_designator", tokens);
	}

	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[15];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::IDENTIFIER) {
		tokens++;
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::COLON) {
			tokens++;
			AstNode* statement;
			if (parse_statement(
				sym,
				tokens,
				statement)
				== ParserExitCode::SUCCESS) {
				stack[si++] = statement;
				alt = AstNodeAlt::LABELED_STATEMENT_1;
				should_generate = true;
			}
		}
	}
	else if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::CASE) {
		tokens++;
		AstNode* constant_expression;
		if (parse_constant_expression(
			sym,
			tokens,
			constant_expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = constant_expression;
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COLON) {
				tokens++;
				AstNode* statement;
				if (parse_statement(
					sym,
					tokens,
					statement)
					== ParserExitCode::SUCCESS) {
					stack[si++] = statement;
					alt = AstNodeAlt::LABELED_STATEMENT_2;
					should_generate = true;
				}
			}
		}
	}
	else if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::DEFAULT) {
		tokens++;
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::COLON) {
			tokens++;
			AstNode* statement;
			if (parse_statement(
				sym,
				tokens,
				statement)
				== ParserExitCode::SUCCESS) {
				stack[si++] = statement;
				alt = AstNodeAlt::LABELED_STATEMENT_3;
				should_generate = true;
			}
		}
	}
	if (should_generate) {
		labeled_statement = new AstNode(
			AstNodeName::LABELED_STATEMENT,
			alt,
			NULL
		);
		labeled_statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_statement", tokens);
	}
	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (lookup(
		first_of_labeled_statement,
		tokens->get_name(),
		tokens->get_form())
		&& (tokens->get_name() != TokenName::IDENTIFIER
			|| (sym->get_entry(tokens->get_lexeme())
				&& (sym->get_entry(tokens->get_lexeme())->is_typedef)))) {

		AstNode* labeled_statement;
		if (parse_labeled_statement(sym, tokens, labeled_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = labeled_statement;
			alt = AstNodeAlt::STATEMENT_1;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_compound_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* compound_statement;
		if (parse_compound_statement(sym, tokens, compound_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = compound_statement;
			alt = AstNodeAlt::STATEMENT_2;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_expression_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* expression_statement;
		if (parse_expression_statement(sym, tokens, expression_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = expression_statement;
			alt = AstNodeAlt::STATEMENT_3;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_selection_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* selection_statement;
		if (parse_selection_statement(sym, tokens, selection_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = selection_statement;
			alt = AstNodeAlt::STATEMENT_4;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_iteration_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* iteration_statement;
		if (parse_iteration_statement(sym, tokens, iteration_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = iteration_statement;
			alt = AstNodeAlt::STATEMENT_5;
			should_generate = true;
		}

	}
	else if (lookup(
		first_of_jump_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* jump_statement;
		if (parse_jump_statement(sym, tokens, jump_statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = jump_statement;
			alt = AstNodeAlt::STATEMENT_6;
			should_generate = true;
		}

	}
	if (should_generate) {
		statement = new AstNode(
			AstNodeName::STATEMENT,
			alt,
			NULL
		);
		statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_compound_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& compound_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_compound_statement", tokens);
	}

	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::OPEN_CURLY_BRACKET) {
		tokens++;

		if (lookup(
			first_of_block_item_list,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* block_item_list;
			if (parse_block_item_list(sym, tokens, block_item_list)
				== ParserExitCode::SUCCESS) {
				stack[si++] = block_item_list;
			}
		}
		if (tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::CLOSE_CURLY_BRACKET) {
			tokens++;
			should_generate = true;
		}
	}
	if (should_generate) {
		compound_statement = new AstNode(
			AstNodeName::COMPOUND_STATEMENT,
			AstNodeAlt::COMPOUND_STATEMENT_1,
			NULL
		);
		compound_statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si > 0) {
			delete stack[--si];
		}
	}
	return exitcode;
}

static inline ParserExitCode parse_block_item_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& block_item_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_parameter_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		BLOCK_ITEM_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
			AstNode* block_item;
			if (parse_block_item(
				sym,
				tokens,
				block_item)
				== ParserExitCode::SUCCESS) {

				block_item_list = new AstNode(
					AstNodeName::BLOCK_ITEM_LIST,
					AstNodeAlt::BLOCK_ITEM_LIST_1,
					NULL
				);
				block_item_list->add_child(block_item);
				exitcode = ParserExitCode::SUCCESS;
				state = BLOCK_ITEM_LIST;
				continue;
			}
			exitcode = ParserExitCode::SUCCESS;
			break;

		case BLOCK_ITEM_LIST:
		{
			AstNode* block_item;
			if (parse_block_item(
				sym,
				tokens,
				block_item)
				== ParserExitCode::SUCCESS) {

				AstNode* higher_block_item_list = new AstNode(
					AstNodeName::BLOCK_ITEM_LIST,
					AstNodeAlt::BLOCK_ITEM_LIST_2,
					NULL
				);
				higher_block_item_list->add_child(block_item_list);
				higher_block_item_list->add_child(block_item);
				block_item_list = higher_block_item_list;
				continue;
			}
			break;
		}

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_block_item(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& block_item)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_block_item", tokens);
	}

	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	Token* backtrack_ptr = tokens;

	if (lookup(
		first_of_declaration,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* declaration;
		if (parse_declaration(sym, tokens, declaration)
			== ParserExitCode::SUCCESS) {
			stack[si++] = declaration;
			alt = AstNodeAlt::BLOCK_ITEM_1;
			should_generate = true;
		}
		else {
			tokens = backtrack_ptr;
			AstNode* statement;
			if (parse_statement(sym, tokens, statement)
				== ParserExitCode::SUCCESS) {
				stack[si++] = statement;
				alt = AstNodeAlt::BLOCK_ITEM_2;
				should_generate = true;
			}
		}

	}
	else if (lookup(
		first_of_statement,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* statement;
		if (parse_statement(sym, tokens, statement)
			== ParserExitCode::SUCCESS) {
			stack[si++] = statement;
			alt = AstNodeAlt::BLOCK_ITEM_2;
			should_generate = true;
		}
	}
	if (should_generate) {
		block_item = new AstNode(
			AstNodeName::BLOCK_ITEM,
			alt,
			NULL
		);
		block_item->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}

	return exitcode;
}

static inline ParserExitCode parse_expression_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& expression_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_expression_statement", tokens);
	}

	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (lookup(
		first_of_expression,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* expression;
		if (parse_expression(sym, tokens, expression)
			== ParserExitCode::SUCCESS) {
			stack[si++] = expression;
		}

	}
	if (tokens->get_name() == TokenName::PUNCTUATOR
		&& tokens->get_form() == TokenForm::SEMI_COLON) {
		tokens++;
		should_generate = true;
	}
	if (should_generate) {
		expression_statement = new AstNode(
			AstNodeName::EXPRESSION_STATEMENT,
			AstNodeAlt::EXPRESSION_STATEMENT_1,
			NULL
		);
		expression_statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}

	return exitcode;
}

static inline ParserExitCode parse_selection_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& selection_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_selection_statement", tokens);
	}
	AstNode* stack[16];
	int si = 0;

	AstNodeAlt alt = AstNodeAlt::ERROR;

	ParserExitCode exitcode = ParserExitCode::FAIL;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::IDENTIFIER) {

		switch (tokens->get_form()) {

		case TokenForm::IF:
		{
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
				break;
			}
			tokens++;

			AstNode* expression;
			if (parse_expression(sym, tokens, expression)
				!= ParserExitCode::SUCCESS) {
				break;
			}
			stack[si++] = expression;

			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
				break;
			}
			tokens++;

			AstNode* statement;
			if (!(parse_statement(sym, tokens, statement)
				== ParserExitCode::SUCCESS)) {
				break;
			}
			stack[si++] = statement;

			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::ELSE) {
				tokens++;

				AstNode* statement;
				if (parse_statement(sym, tokens, statement)
					== ParserExitCode::SUCCESS) {
					stack[si++] = statement;
					alt = AstNodeAlt::SELECTION_STATEMENT_2;
					should_generate = true;
				}
			}
			else {
				alt = AstNodeAlt::SELECTION_STATEMENT_1;
				should_generate = true;
			}
			break;
		}

		case TokenForm::SWITCH:
		{
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
				break;
			}
			tokens++;

			AstNode* expression;
			if (parse_expression(sym, tokens, expression)
				!= ParserExitCode::SUCCESS) {
				break;
			}
			stack[si++] = expression;

			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
				break;
			}
			tokens++;

			AstNode* statement;
			if (!(parse_statement(sym, tokens, statement)
				== ParserExitCode::SUCCESS)) {
				break;
			}
			stack[si++] = statement;
			alt = AstNodeAlt::SELECTION_STATEMENT_3;
			should_generate = true;
			break;
		}

		default:
			break;
		}
	}
	if (should_generate) {
		selection_statement = new AstNode(
			AstNodeName::SELECTION_STATEMENT,
			alt,
			NULL
		);
		selection_statement->add_children(stack, si);
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
	}

	return exitcode;
}

static inline ParserExitCode parse_iteration_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& iteration_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_iteration_statement", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	switch (tokens->get_form()) {

	case TokenForm::WHILE:
	{
		tokens++;

		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
			break;
		}
		tokens++;

		AstNode* expression;
		if (!(parse_expression(sym, tokens, expression)
			== ParserExitCode::SUCCESS)) {
			break;
		}
		stack[si++] = expression;

		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
			break;
		}
		AstNode* statement;

		if (!(parse_statement(sym, tokens, statement)
			== ParserExitCode::SUCCESS)) {
			break;
		}
		stack[si++] = statement;

		alt = AstNodeAlt::ITERATION_STATEMENT_1;
		should_generate = true;
		break;
	}

	case TokenForm::DO:
		tokens++;

		AstNode* statement1;
		if (!(parse_statement(sym, tokens, statement1)
			== ParserExitCode::SUCCESS)) {
			break;
		}
		stack[si++] = statement1;

		if (!(tokens->get_name() == TokenName::IDENTIFIER
			&& tokens->get_form() == TokenForm::WHILE)) {
			break;
		}
		tokens++;

		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
			break;
		}
		tokens++;

		AstNode* statement2;
		if (!(parse_statement(sym, tokens, statement2)
			== ParserExitCode::SUCCESS)) {
			break;
		}
		stack[si++] = statement2;

		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
			break;
		}
		tokens++;

		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::SEMI_COLON)) {
			break;
		}
		tokens++;

		alt = AstNodeAlt::ITERATION_STATEMENT_2;
		should_generate = true;
		break;

	case TokenForm::FOR:
		tokens++;
		if (!(tokens->get_name() == TokenName::PUNCTUATOR
			&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
			break;
		}
		tokens++;
		if (lookup(
			first_of_expression,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* expression1;
			if (parse_expression(sym, tokens, expression1)
				== ParserExitCode::SUCCESS) {
				stack[si++] = expression1;
			}
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
				break;
			}
			tokens++;
			if (lookup(
				first_of_expression,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* expression2;
				if (parse_expression(sym, tokens, expression2)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression2;
				}
			}
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::OPEN_PAREN)) {
				break;
			}
			tokens++;
			if (lookup(
				first_of_expression,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* expression3;
				if (parse_expression(sym, tokens, expression3)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression3;
				}
			}
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
				break;
			}
			tokens++;
			if (lookup(
				first_of_statement,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* statement;
				if (parse_statement(sym, tokens, statement)
					== ParserExitCode::SUCCESS) {
					stack[si++] = statement;
				}
			}
			else {
				break;
			}
			should_generate = true;
			alt = AstNodeAlt::ITERATION_STATEMENT_3;
			break;

		}
		else if (lookup(
			first_of_declaration,
			tokens->get_name(),
			tokens->get_form())) {

			AstNode* declaration;
			if (parse_declaration(sym, tokens, declaration)
				== ParserExitCode::SUCCESS) {
				stack[si++] = declaration;
			}
			else {
				break;
			}
			if (lookup(
				first_of_expression,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* expression;
				if (parse_expression(sym, tokens, expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression;
				}
			}
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::SEMI_COLON)) {
				break;
			}
			tokens++;
			if (lookup(
				first_of_expression,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* expression;
				if (parse_expression(sym, tokens, expression)
					== ParserExitCode::SUCCESS) {
					stack[si++] = expression;
				}
			}
			if (!(tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::CLOSE_PAREN)) {
				break;
			}
			tokens++;
			if (lookup(
				first_of_statement,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* statement;
				if (parse_statement(sym, tokens, statement)
					== ParserExitCode::SUCCESS) {
					stack[si++] = statement;
				}
			}
			else {
				break;
			}
			should_generate = true;
			alt = AstNodeAlt::ITERATION_STATEMENT_3;
			break;
		}

	default:
		break;
	}
	if (should_generate) {
		iteration_statement = new AstNode(
			AstNodeName::ITERATION_STATEMENT,
			alt,
			NULL
		);
		iteration_statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
		exitcode = ParserExitCode::FAIL;
	}
	return exitcode;
}

static inline ParserExitCode parse_jump_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& jump_statement)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_jump_statement", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNodeAlt alt = AstNodeAlt::ERROR;
	AstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	if (tokens->get_name() == TokenName::KEYWORD) {
		switch (tokens->get_form()) {
		case TokenForm::GOTO:
			tokens++;
			if (tokens->get_name() == TokenName::IDENTIFIER) {
				stack[si++] = construct_terminal(tokens++);
				if (tokens->get_name() == TokenName::PUNCTUATOR
					&& tokens->get_form() == TokenForm::COLON) {
					tokens++;
				}
			}
			else {
				break;
			}
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::SEMI_COLON) {
				tokens++;
				alt = AstNodeAlt::JUMP_STATEMENT_1;
				should_generate = true;
				break;
			}
			break;
		case TokenForm::CONTINUE:
			tokens++;
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COLON) {
				tokens++;
			}
			else {
				break;
			}
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::SEMI_COLON) {
				tokens++;
				alt = AstNodeAlt::JUMP_STATEMENT_2;
				should_generate = true;
				break;
			}
			break;
		case TokenForm::BREAK:
			tokens++;
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::COLON) {
				tokens++;
			}
			else {
				break;
			}
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::SEMI_COLON) {
				tokens++;
				alt = AstNodeAlt::JUMP_STATEMENT_3;
				should_generate = true;
				break;
			}
			break;
		case TokenForm::RETURN:
			tokens++;
			AstNode* expression;
			if (parse_expression(sym, tokens, expression)
				== ParserExitCode::SUCCESS) {
				stack[si++] = expression;
			}
			else {
				break;
			}
			if (tokens->get_name() == TokenName::PUNCTUATOR
				&& tokens->get_form() == TokenForm::SEMI_COLON) {
				tokens++;
				alt = AstNodeAlt::JUMP_STATEMENT_4;
				should_generate = true;
				break;
			}
			break;
		default:
			break;
		}
	}
	if (should_generate) {
		jump_statement = new AstNode(
			AstNodeName::JUMP_STATEMENT,
			alt,
			NULL
		);
		jump_statement->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
		exitcode = ParserExitCode::FAIL;
	}
	return exitcode;
}

static inline ParserExitCode parse_translation_unit_statement(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& translation_unit)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_translation_unit_statement", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		TRANSLATION_UNIT
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* external_declaration;
			if (parse_external_declaration_statement(
				sym,
				tokens,
				external_declaration)
				== ParserExitCode::SUCCESS) {

				translation_unit = new AstNode(
					AstNodeName::TRANSLATION_UNIT,
					AstNodeAlt::TRANSLATION_UNIT_1,
					NULL
				);
				translation_unit->add_child(external_declaration);

				state = TRANSLATION_UNIT;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case TRANSLATION_UNIT:
		{
			if (tokens->get_name() != TokenName::PUNCTUATOR) {
				break;
			}
			AstNode* external_declaration;
			if ((parse_external_declaration_statement(
				sym,
				tokens,
				external_declaration))
				== ParserExitCode::SUCCESS) {

				AstNode* higher_translation_unit;
				higher_translation_unit = new AstNode(
					AstNodeName::TRANSLATION_UNIT,
					AstNodeAlt::TRANSLATION_UNIT_2,
					NULL
				);
				higher_translation_unit->add_child(
					translation_unit);
				higher_translation_unit->add_child(
					external_declaration);
				translation_unit =
					higher_translation_unit;
				continue;
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_function_definition(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& function_definition)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_function_definition", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	AstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	AstNode* declaration_specifiers;
	if (parse_declaration_specifiers(sym, tokens, declaration_specifiers)
		== ParserExitCode::SUCCESS) {
		stack[si++] = declaration_specifiers;

		AstNode* declarator;
		if (parse_declarator(sym, tokens, declarator)
			== ParserExitCode::SUCCESS) {
			stack[si++] = declarator;

			if (lookup(
				first_of_compound_statement,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* compound_statement;
				if (parse_compound_statement(sym, tokens, compound_statement)
					== ParserExitCode::SUCCESS) {
					stack[si++] = compound_statement;
					should_generate = true;
				}
			}
			else if (lookup(
				first_of_declaration_list,
				tokens->get_name(),
				tokens->get_form())) {

				AstNode* declaration_list;
				if (parse_declaration_list(
					sym,
					tokens,
					declaration_list)
					== ParserExitCode::SUCCESS) {
					stack[si++] = declaration_list;
				}
			}
		}
	}
	if (should_generate) {
		function_definition = new AstNode(
			AstNodeName::FUNCTION_DEFINITION,
			AstNodeAlt::FUNCTION_DEFINITION_1,
			NULL
		);
		function_definition->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
		exitcode = ParserExitCode::FAIL;
	}
	return exitcode;
}

static inline ParserExitCode parse_declaration_list(
	SymbolTable*& sym,
	Token*& tokens,
	AstNode*& declaration_list)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_declaration_list", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	enum ParsingState {
		START,
		DECLARATION_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* declaration;
			if (parse_declaration(
				sym,
				tokens,
				declaration)
				== ParserExitCode::SUCCESS) {

				declaration_list = new AstNode(
					AstNodeName::DECLARATION_LIST,
					AstNodeAlt::DECLARATION_LIST_1,
					NULL
				);
				declaration_list->add_child(declaration);

				state = DECLARATION_LIST;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case DECLARATION_LIST:
		{
			if (tokens->get_name() == TokenName::PUNCTUATOR) {
				AstNode* declaration;
				if (parse_declaration(sym, tokens, declaration)
					== ParserExitCode::SUCCESS) {

					AstNode* higher_declaration_list;
					higher_declaration_list = new AstNode(
						AstNodeName::DECLARATION_LIST,
						AstNodeAlt::DECLARATION_LIST_2,
						NULL
					);
					higher_declaration_list->add_child(
						declaration_list);
					higher_declaration_list->add_child(
						declaration);
					declaration_list =
						higher_declaration_list;
					continue;
				}
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

static inline ParserExitCode parse_external_declaration(
	Token*& tokens,
	AstNode*& external_declaration)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_external_declaration", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	SymbolTable* sym = new SymbolTable();

	enum ParsingState {
		START,
		DECLARATION_LIST
	};

	Token* backtrack_ptr = tokens;

	AstNode* stack[16];
	int si = 0;
	ParsingState state = START;
	AstNodeAlt alt = AstNodeAlt::ERROR;
	bool should_generate = false;

	if (lookup(
		first_of_function_definition,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* function_definition;
		if (parse_function_definition(
			sym,
			tokens,
			function_definition)
			== ParserExitCode::SUCCESS) {

			stack[si++] = function_definition;
			alt = AstNodeAlt::EXTERNAL_DECLARATION_1;
			should_generate = true;
		}
		else {
			tokens = backtrack_ptr;
			AstNode* declaration;
			if (parse_declaration(
				sym,
				tokens,
				declaration)
				== ParserExitCode::SUCCESS) {
				stack[si++] = declaration;
				alt = AstNodeAlt::EXTERNAL_DECLARATION_2;
				should_generate = true;
			}
		}

	}
	else if (lookup(
		first_of_declaration,
		tokens->get_name(),
		tokens->get_form())) {

		AstNode* declaration;
		if (parse_declaration(
			sym,
			tokens,
			declaration)
			== ParserExitCode::SUCCESS) {
			stack[si++] = declaration;
			alt = AstNodeAlt::EXTERNAL_DECLARATION_2;
			should_generate = true;
		}
	}
	if (should_generate) {
		external_declaration = new AstNode(
			AstNodeName::EXTERNAL_DECLARATION,
			alt,
			NULL
		);
		external_declaration->add_children(stack, si);
		exitcode = ParserExitCode::SUCCESS;
	}
	else {
		/* Free unused ast nodes generated. */
		while (si) {
			delete stack[--si];
		}
		exitcode = ParserExitCode::FAIL;
	}
	return exitcode;
}

static inline ParserExitCode parse_translation_unit(
	Token*& tokens,
	AstNode*& translation_unit)
{
	if (DEBUG_PARSER_SHOW_ATTEMPTS) {
		parser_report_attempt("parse_translation_unit", tokens);
	}
	ParserExitCode exitcode = ParserExitCode::FAIL;

	SymbolTable* sym = new SymbolTable();

	enum ParsingState {
		START,
		TRANSLATION_UNIT
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

		case START:
		{
			AstNode* external_declaration;
			if (parse_external_declaration(
				tokens,
				external_declaration)
				== ParserExitCode::SUCCESS) {

				translation_unit = new AstNode(
					AstNodeName::TRANSLATION_UNIT,
					AstNodeAlt::TRANSLATION_UNIT_1,
					NULL
				);
				translation_unit->add_child(external_declaration);

				state = TRANSLATION_UNIT;
				exitcode = ParserExitCode::SUCCESS;
				continue;
			}
		}
		break;

		case TRANSLATION_UNIT:
		{
			if (lookup(
				first_of_external_declaration,
				tokens->get_name(),
				tokens->get_form())) {
				AstNode* external_declaration;
				if (parse_external_declaration(
					tokens,
					external_declaration)
					== ParserExitCode::SUCCESS) {

					AstNode* higher_translation_unit;
					higher_translation_unit = new AstNode(
						AstNodeName::TRANSLATION_UNIT,
						AstNodeAlt::TRANSLATION_UNIT_2,
						NULL
					);
					higher_translation_unit->add_child(
						translation_unit);
					higher_translation_unit->add_child(
						external_declaration);
					translation_unit =
						higher_translation_unit;
					continue;
				}
			}
		}
		break;

		default:
			break;
		}
		break;
	}
	return exitcode;
}

#endif