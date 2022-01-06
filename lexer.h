
#ifndef LEXER_H
#define LEXER_H 1

#include <cstdlib>
#include <string>
#include <iostream>
#include <cinttypes>

#include "preprocessing-token.h"
#include "token.h"

using namespace std;

enum class LexerExitCode {
	SUCCESS,
	FAILURE
};

#define DEBUG_ENABLE_LEXER_REPORT 1

#define lexer_report_failure( s, f, l )					\
	if (DEBUG_ENABLE_LEXER_REPORT) {					\
		cout << "lexer.cpp:" s ":"						\
			 << "recognised erroneous token with form "	\
			 << (size_t) f								\
			 << " and lexeme "							\
			 << l										\
			 << "."										\
			 << endl;									\
	}

#define lexer_report_success( s, f, l )					\
	if (DEBUG_ENABLE_LEXER_REPORT) {					\
		cout << "lexer.cpp:" s ":"						\
			 << "produced token with form "				\
			 << (size_t) f								\
			 << " and lexeme "							\
			 << l										\
			 << "."										\
			 << endl;									\
	}

static inline LexerExitCode lex_keyword(
	const PreprocessingToken& pp_token,
	Token*& identifier_output)
{
	enum LexingState {
		START,

		AUTO,
		BREAK,
		C,
		CASE,
		CHAR,
		CON,
		CONST,
		CONTINUE,
		D,
		DEFAULT,
		DO,
		DOUBLE,
		E,
		ELSE,
		ENUM,
		EXTERN,
		F,
		FLOAT,
		FOR,
		GOTO,
		I,
		IF,
		IN,
		INLINE,
		INT,
		LONG,
		RE,
		REGISTER,
		RESTRICT,
		RETURN,
		S,
		SHORT,
		SI,
		SIGNED,
		SIZEOF,
		ST,
		STATIC,
		STRUCT,
		SWITCH,
		TYPEDEF,
		UN,
		UNION,
		UNSIGNED,
		WHILE,
		VO,
		VOID,
		VOLATILE,
		_,
		_BOOL,
		_COMPLEX,
		_IMAGINARY,

		END_FAIL,
		END_SUCCESS
	};
	LexingState state = LexingState::START;
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	const char* lexeme = pp_token.get_lexeme();
	const char* chr = lexeme;

	TokenForm form = TokenForm::SIMPLE;

	bool conclusive = false;
	while (!conclusive) {
		switch (state) {

		case START:
			switch (*chr++) {
			case 'a':
				if (*chr++ == 'u'
					&& *chr++ == 't'
					&& *chr++ == 'o') {
					state = AUTO;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'b':
				if (*chr++ == 'r'
					&& *chr++ == 'e'
					&& *chr++ == 'a'
					&& *chr++ == 'k') {
					state = BREAK;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'c': state = C; break;
			case 'd': state = D; break;
			case 'e': state = E; break;
			case 'f': state = F; break;
			case 'g':
				if (*chr++ == 'o'
					&& *chr++ == 't'
					&& *chr++ == 'o') {
					state = GOTO;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'i': state = I; break;
			case 'l':
				if (*chr++ == 'o'
					&& *chr++ == 'n'
					&& *chr++ == 'g') {
					state = LONG;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'r':
				if (*chr++ == 'e') {
					state = RE;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 's': state = S; break;
			case 't':
				if (*chr++ == 'y'
					&& *chr++ == 'p'
					&& *chr++ == 'e'
					&& *chr++ == 'd'
					&& *chr++ == 'e'
					&& *chr++ == 'f') {
					state = TYPEDEF;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'u':
				if (*chr++ == 'n') {
					state = UN;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'w':
				if (*chr++ == 'h'
					&& *chr++ == 'i'
					&& *chr++ == 'l'
					&& *chr++ == 'e') {
					state = WHILE;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'v':
				if (*chr++ == 'o') {
					state = VO;
				}
				else {
					state = END_FAIL;
				}
				break;
			case '_': state = _; break;
			default: state = END_FAIL; break;
			}
			break;

		case AUTO:
			if (*chr++ == NULL) {
				form = TokenForm::AUTO;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case BREAK:
			if (*chr++ == NULL) {
				form = TokenForm::BREAK;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case C:
			switch (*chr++) {
			case 'a':
				if (*chr++ == 's'
					&& *chr++ == 'e') {
					state = CASE;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'h':
				if (*chr++ == 'a'
					&& *chr++ == 'r') {
					state = CHAR;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'o':
				if (*chr++ == 'n') {
					state = CON;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case CASE:
			if (*chr++ == NULL) {
				form = TokenForm::CASE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;


		case CHAR:
			if (*chr++ == NULL) {
				form = TokenForm::CHAR;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case CON:
			switch (*chr++) {
			case 's':
				if (*chr++ == 't') {
					state = CONST;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 't':
				if (*chr++ == 'i'
					&& *chr++ == 'n'
					&& *chr++ == 'u'
					&& *chr++ == 'e') {
					state = CONTINUE;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case CONST:
			if (*chr++ == NULL) {
				form = TokenForm::CONST;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case CONTINUE:
			if (*chr++ == NULL) {
				form = TokenForm::CONTINUE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case D:
			switch (*chr++) {
			case 'e':
				if (*chr++ == 'f'
					&& *chr++ == 'a'
					&& *chr++ == 'u'
					&& *chr++ == 'l'
					&& *chr++ == 't') {
					state = DEFAULT;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'o': state = DO; break;
			default: state = END_FAIL; break;
			}
			break;

		case DEFAULT:
			if (*chr == NULL) {
				form = TokenForm::DEFAULT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case DO:
			if (*chr == NULL) {
				form = TokenForm::DO;
				state = END_SUCCESS;
			}
			else if (*chr++ == 'u'
				&& *chr++ == 'b'
				&& *chr++ == 'l'
				&& *chr++ == 'e') {
				state = DOUBLE;
			}
			else {
				state = END_FAIL;
			}
			break;

		case DOUBLE:
			if (*chr++ == NULL) {
				form = TokenForm::DOUBLE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case E:
			switch (*chr++) {
			case 'l':
				if (*chr++ == 's'
					&& *chr++ == 'e') {
					state = ELSE;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'n':
				if (*chr++ == 'u'
					&& *chr++ == 'm') {
					state = ENUM;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'x':
				if (*chr++ == 't'
					&& *chr++ == 'e'
					&& *chr++ == 'r'
					&& *chr++ == 'n') {
					state = EXTERN;
				}
				else {
					state = END_FAIL;
				}
				break;
			default:
				state = END_FAIL;
				break;
			}
			break;

		case ELSE:
			if (*chr++ == NULL) {
				form = TokenForm::ELSE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case ENUM:
			if (*chr++ == NULL) {
				form = TokenForm::ENUM;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case EXTERN:
			if (*chr++ == NULL) {
				form = TokenForm::EXTERN;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case F:
			switch (*chr++) {
			case 'l':
				if (*chr++ == 'o'
					&& *chr++ == 'a'
					&& *chr++ == 't') {
					state = FLOAT;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'o':
				if (*chr++ == 'r') {
					state = FOR;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case FLOAT:
			if (*chr++ == NULL) {
				form = TokenForm::FLOAT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case FOR:
			if (*chr++ == NULL) {
				form = TokenForm::FOR;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case GOTO:
			if (*chr++ == NULL) {
				form = TokenForm::GOTO;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case I:
			switch (*chr++) {
			case 'f': state = IF; break;
			case 'n': state = IN; break;
			default: state = END_FAIL; break;
			}
			break;

		case IF:
			if (*chr++ == NULL) {
				form = TokenForm::IF;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case IN:
			switch (*chr++) {
			case 'l':
				if (*chr++ == 'i'
					&& *chr++ == 'n'
					&& *chr++ == 'e') {
					state = INLINE;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 't': state = INT;
			}
			break;

		case INLINE:
			if (*chr++ == NULL) {
				form = TokenForm::INLINE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case INT:
			if (*chr++ == NULL) {
				form = TokenForm::INT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case LONG:
			if (*chr++ == NULL) {
				form = TokenForm::LONG;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case RE:
			switch (*chr++) {
			case 'g':
				if (*chr++ == 'i'
					&& *chr++ == 's'
					&& *chr++ == 't'
					&& *chr++ == 'e'
					&& *chr++ == 'r') {
					state = REGISTER;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 's':
				if (*chr++ == 't'
					&& *chr++ == 'r'
					&& *chr++ == 'i'
					&& *chr++ == 'c'
					&& *chr++ == 't') {
					state = RESTRICT;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 't':
				if (*chr++ == 'u'
					&& *chr++ == 'r'
					&& *chr++ == 'n') {
					state = RETURN;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case REGISTER:
			if (*chr++ == NULL) {
				form = TokenForm::REGISTER;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case RESTRICT:
			if (*chr++ == NULL) {
				form = TokenForm::RESTRICT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case RETURN:
			if (*chr++ == NULL) {
				form = TokenForm::RETURN;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case S:
			switch (*chr++) {
			case 'h':
				if (*chr++ == 'o'
					&& *chr++ == 'r'
					&& *chr++ == 't') {
					state = SHORT;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'i': state = SI; break;
			case 't': state = ST; break;
			case 'w':
				if (*chr++ == 'i'
					&& *chr++ == 't'
					&& *chr++ == 'c'
					&& *chr++ == 'h') {
					state = SWITCH;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case SHORT:
			if (*chr++ == NULL) {
				form = TokenForm::SHORT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case SI:
			switch (*chr++) {
			case 'g':
				if (*chr++ == 'n'
					&& *chr++ == 'e'
					&& *chr++ == 'd') {
					state = SIGNED;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'z':
				if (*chr++ == 'e'
					&& *chr++ == 'o'
					&& *chr++ == 'f') {
					state = SIZEOF;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case SIGNED:
			if (*chr++ == NULL) {
				form = TokenForm::SIGNED;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case SIZEOF:
			if (*chr++ == NULL) {
				form = TokenForm::SIZEOF;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case ST:
			switch (*chr++) {
			case 'a':
				if (*chr++ == 't'
					&& *chr++ == 'i'
					&& *chr++ == 'c') {
					state = STATIC;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'r':
				if (*chr++ == 'u'
					&& *chr++ == 'c'
					&& *chr++ == 't') {
					state = STRUCT;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case STATIC:
			if (*chr++ == NULL) {
				form = TokenForm::STATIC;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case STRUCT:
			if (*chr++ == NULL) {
				form = TokenForm::STRUCT;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case SWITCH:
			if (*chr++ == NULL) {
				form = TokenForm::SWITCH;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case TYPEDEF:
			if (*chr++ == NULL) {
				form = TokenForm::TYPEDEF;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case UN:
			switch (*chr++) {
			case 'i':
				if (*chr++ == 'o'
					&& *chr++ == 'n') {
					state = UNION;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 's':
				if (*chr++ == 'i'
					&& *chr++ == 'g'
					&& *chr++ == 'n'
					&& *chr++ == 'e'
					&& *chr++ == 'd') {
					state = UNSIGNED;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case UNION:
			if (*chr++ == NULL) {
				form = TokenForm::UNION;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case UNSIGNED:
			if (*chr++ == NULL) {
				form = TokenForm::UNSIGNED;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case WHILE:
			if (*chr++ == NULL) {
				form = TokenForm::WHILE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case VO:
			switch (*chr++) {
			case 'i':
				if (*chr++ == 'd') {
					state = VOID;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'l':
				if (*chr++ == 'a'
					&& *chr++ == 't'
					&& *chr++ == 'i'
					&& *chr++ == 'l'
					&& *chr++ == 'e') {
					state = VOLATILE;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case VOID:
			if (*chr++ == NULL) {
				form = TokenForm::VOID;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case VOLATILE:
			if (*chr++ == NULL) {
				form = TokenForm::VOLATILE;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case _:
			switch (*chr++) {
			case 'B':
				if (*chr++ == 'o'
					&& *chr++ == 'o'
					&& *chr++ == 'l') {
					state = _BOOL;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'C':
				if (*chr++ == 'o'
					&& *chr++ == 'm'
					&& *chr++ == 'p'
					&& *chr++ == 'l'
					&& *chr++ == 'e'
					&& *chr++ == 'x') {
					state = _COMPLEX;
				}
				else {
					state = END_FAIL;
				}
				break;
			case 'I':
				if (*chr++ == 'm'
					&& *chr++ == 'a'
					&& *chr++ == 'g'
					&& *chr++ == 'i'
					&& *chr++ == 'n'
					&& *chr++ == 'a'
					&& *chr++ == 'r'
					&& *chr++ == 'y') {
					state = _IMAGINARY;
				}
				else {
					state = END_FAIL;
				}
				break;
			default: state = END_FAIL; break;
			}
			break;

		case _BOOL:
			if (*chr == NULL) {
				form = TokenForm::_BOOL;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case _COMPLEX:
			if (*chr == NULL) {
				form = TokenForm::_COMPLEX;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case _IMAGINARY:
			if (*chr == NULL) {
				form = TokenForm::_IMAGINARY;
				state = END_SUCCESS;
			}
			else {
				state = END_FAIL;
			}
			break;

		case END_FAIL:
			lexer_report_failure(
				"lex_keyword",
				form,
				lexeme);

			*identifier_output = Token(
				TokenName::ERROR,
				form,
				{ 0 },
				lexeme);

			conclusive = true;
			exitcode = LexerExitCode::FAILURE;
			break;

		case END_SUCCESS:
			lexer_report_success(
				"lex_keyword",
				form,
				lexeme);

			*identifier_output++ = Token(
				TokenName::KEYWORD,
				form,
				{ 0 },
				lexeme);

			conclusive = true;
			exitcode = LexerExitCode::SUCCESS;
			break;

		default:
			conclusive = true;
			exitcode = LexerExitCode::FAILURE;
			break;
		}
	}
	return exitcode;
}

static inline LexerExitCode lex_identifier(
	const PreprocessingToken& pp_token,
	Token*& identifier_output)
{
	enum LexingState {
		START,

		IDENTIFIER,
		IDENTIFIER_NONDIGIT,

		END_FAIL,
		END_SUCCESS
	};

	LexingState state = LexingState::START;
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	const char* lexeme = pp_token.get_lexeme();
	const char* chr = lexeme;

	TokenForm form = TokenForm::SIMPLE;

	bool conclusive = false;

	while (!conclusive) {

		switch (state) {

		case START:

			switch (*chr) {

			case '_':

			case 'a': case 'b': case 'c':
			case 'd': case 'e': case 'f':
			case 'g': case 'h': case 'i':
			case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r':
			case 's': case 't': case 'u':
			case 'v': case 'w': case 'x':
			case 'y': case 'z':

			case 'A': case 'B': case 'C':
			case 'D': case 'E': case 'F':
			case 'G': case 'H': case 'I':
			case 'J': case 'K': case 'L':
			case 'M': case 'N': case 'O':
			case 'P': case 'Q': case 'R':
			case 'S': case 'T': case 'U':
			case 'V': case 'W': case 'X':
			case 'Y': case 'Z':

				chr++;
				state = IDENTIFIER_NONDIGIT;
				continue;

			default:
				break;
			}
			state = END_FAIL;
			continue;

		case IDENTIFIER_NONDIGIT:

			switch (*chr) {

			case '_':

			case 'a': case 'b': case 'c':
			case 'd': case 'e': case 'f':
			case 'g': case 'h': case 'i':
			case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r':
			case 's': case 't': case 'u':
			case 'v': case 'w': case 'x':
			case 'y': case 'z':

			case 'A': case 'B': case 'C':
			case 'D': case 'E': case 'F':
			case 'G': case 'H': case 'I':
			case 'J': case 'K': case 'L':
			case 'M': case 'N': case 'O':
			case 'P': case 'Q': case 'R':
			case 'S': case 'T': case 'U':
			case 'V': case 'W': case 'X':
			case 'Y': case 'Z':

				// TODO: UNIVERSAL-CHARACTER-NAME
				chr++;
				continue;

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
			case '0':

				chr++;
				continue;

			case '\0': {
				state = IDENTIFIER;
				continue;
			}

			default:
				break;
			}
			state = END_FAIL;
			continue;

		case IDENTIFIER:

			switch (*chr) {

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
			case '0':

				chr++;
				continue;

			case '\0':
				state = END_SUCCESS;
				continue;

			default:
				break;
			}
			state = END_FAIL;
			continue;

		case END_FAIL:
			lexer_report_failure(
				"lex_identifier",
				form,
				lexeme);

			*identifier_output++ = Token(
				TokenName::ERROR,
				form,
				{ 0 },
				lexeme);
			exitcode = LexerExitCode::FAILURE;
			conclusive = true;
			break;

		case END_SUCCESS:
			lexer_report_success(
				"lex_identifier",
				form,
				lexeme);

			*identifier_output++ = Token(
				TokenName::IDENTIFIER,
				form,
				{ 0 },
				lexeme);
			exitcode = LexerExitCode::SUCCESS;
			conclusive = true;
			break;

		default:
			break;
		}
		if (conclusive) break;
	}
	return exitcode;
}

static inline LexerExitCode lex_constant(
	const PreprocessingToken& pp_token,
	Token*& identifier_output)
{
	enum LexingState {
		START,

		INTEGER_CONSTANT,
		DECIMAL_CONSTANT,
		OCTAL_CONSTANT,
		HEXADECIMAL_CONSTANT,
		HEXADECIMAL_PREFIX,

		FLOATING_CONSTANT,
		DECIMAL_FLOATING_CONSTANT,
		HEXADECIMAL_FLOATING_CONSTANT,
		FRACTIONAL_CONSTANT,
		EXPONENT_PART,
		SIGN,
		DIGIT_SEQUENCE,
		HEXADECIMAL_DIGIT_SEQUENCE,
		HEXADECIMAL_FRACTIONAL_CONSTANT,

		ENUMERATION_CONSTANT,

		CHARACTER_CONSTANT,
		C_CHAR_SEQUENCE,
		C_CHAR,
		ESCAPE_SEQUENCE,
		SIMPLE_ESCAPE_SEQUENCE,
		OCTAL_ESCAPE_SEQUENCE,
		HEXADECIMAL_ESCAPE_SEQUENCE,

		END_FAIL,
		END_SUCCESS
	};

	LexingState state = LexingState::START;
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	const char* lexeme = pp_token.get_lexeme();
	const char* chr = lexeme;

	TokenForm form = TokenForm::SIMPLE;

	TokenValue tvalue = {};
	int base = 10;

	bool conclusive = false;

	while (!conclusive) {

		switch (state) {

		case START:

			switch (*chr) {

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
				chr++;
				state = DIGIT_SEQUENCE;
				continue;

			case '.':
			{
				chr++;
				bool found_digit_sequence = false;
				while (true) {
					switch (*chr) {
					case '0':
					case '1': case '2': case '3':
					case '4': case '5': case '6':
					case '7': case '8': case '9':
						found_digit_sequence = true;
						chr++;
						continue;
					default:
						break;
					}
					break;
				}
				if (found_digit_sequence) {
					state = FRACTIONAL_CONSTANT;
					continue;
				}
				break;
			}

			case '0':
				chr++;
				if (*chr == 'x' || *chr == 'X') {
					chr++;
					state = HEXADECIMAL_PREFIX;
				}
				else {
					while (*chr >= '0' && *chr <= '7') {
						chr++;
					}
					if (*chr == '\0') {
						state = OCTAL_CONSTANT;
					}
					else {
						while (*chr >= '0'
							&& *chr <= '9') {
							chr++;
						}
						if (*chr == '.'
							|| *chr == 'p'
							|| *chr == 'P'
							|| *chr == 'e'
							|| *chr == 'E') {
							state = DIGIT_SEQUENCE;
						}
						else {
							state = END_FAIL;
						}
					}
				}
				continue;

			case 'L':
				chr++; /* L may preclude '\' */
			case '\'':
			{
				if (*chr == '\'') {
					state = END_FAIL;
					continue;
				}

				chr++;
				while (true) {

					switch (*chr) {

					case '\\':
						chr++;
						switch (*chr) {

						case '\'':
						case '\"':
						case '?':
						case '\\':
						case 'a':
						case 'b':
						case 'f':
						case 'n':
						case 'r':
						case 't':
						case 'v':
							chr++;
							continue;

						case 'x':
						{
							bool found_hex = false;
							while ((*chr >= '0' && *chr <= '9')
								&& (*chr >= 'a' && *chr <= 'f')
								&& (*chr >= 'A' && *chr <= 'F')) {
								chr++;
								found_hex = true;
							}
							if (found_hex) {
								chr++;
								if (*chr == NULL) {
									chr++;
									state = CHARACTER_CONSTANT;
								}
								else {
									state = END_FAIL;
								}
							}
							else {
								state = END_FAIL;
							}
							continue;
						}

						case '0':
						case '1': case '2': case '3':
						case '4': case '5': case '6':
						case '7':
						{
							chr++;
							int num_encountered = 1;

							while (!(*chr >= '0'
								&& *chr <= '7')) {
								chr++;
								num_encountered++;
							}

							if (num_encountered >= 3) {
								state = END_FAIL;
							}
							break;
						}

						default:
							break;
						}
						continue;

					case '\n':
						state = END_FAIL;
						break;

					case '\'':
						chr++;
						state = CHARACTER_CONSTANT;
						break;

					default:
						chr++;
						continue;
					}
					break;
				}
				/* Intentional runover. */
				continue;
			}
			}

		case CHARACTER_CONSTANT:
			form = TokenForm::CHARACTER_CONSTANT;
			state = END_SUCCESS;
			continue;

		case DECIMAL_CONSTANT:
			base = 10;
			state = INTEGER_CONSTANT;
			continue;

		case OCTAL_CONSTANT:
			base = 8;
			state = INTEGER_CONSTANT;
			continue;

		case HEXADECIMAL_CONSTANT:
			base = 16;
			state = INTEGER_CONSTANT;
			continue;

		case INTEGER_CONSTANT: {

			bool u = false;
			bool l = false;
			bool ll = false;

			switch (*chr) {

			case 'u':
			case 'U':
				if (!u) {
					u = true;
					chr++;
					continue;
				}
				else {
					break;
				}

			case 'l':
			case 'L':
				if (!l) {
					l = true;
					chr++;
					continue;
				}
				else if (!ll) {
					ll = true;
					chr++;
					continue;
				}
				else {
					break;
				}

			case '\0': {
				uintmax_t val = strtoimax(
					lexeme,
					NULL,
					base);
				state = END_SUCCESS;
				form = TokenForm::INTEGER_CONSTANT;
				tvalue.intvalue = val;
				continue;
			}

			default:
				break;
			}
			state = END_FAIL;
			continue;
		}

		case DIGIT_SEQUENCE:
		{
			switch (*chr) {

			case '0':
			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
				chr++;
				continue;

			case '.':
				chr++;
				state = FRACTIONAL_CONSTANT;
				continue;

			case 'e':
			case 'E':
			{
				chr++;

				if (*chr != '+' && *chr != '-') {
					state = FLOATING_CONSTANT;
					continue;
				}
				chr++;

				bool found_digit_sequence = false;
				while (true) {
					switch (*chr) {
					case '0':
					case '1': case '2': case '3':
					case '4': case '5': case '6':
					case '7': case '8': case '9':
						chr++;
						found_digit_sequence = true;
						continue;
					default:
						break;
					}
					break;
				}
				if (found_digit_sequence) {
					switch (*chr) {
					case 'f': case 'F':
					case 'l': case 'L':
						chr++;
						break;
					default:
						break;
					}
					if (*chr == NULL) {
						state = FLOATING_CONSTANT;
					}
					else {
						state = END_FAIL;
					}
					continue;
				}
			}

			case 'u':
			case 'U':
			case 'l':
			case 'L':
			case '\0':
				state = DECIMAL_CONSTANT;
				continue;

			default:
				break;
			}
			state = END_FAIL;
			continue;
		}

		case HEXADECIMAL_DIGIT_SEQUENCE:
		{
			switch (*chr) {

			case '0':
			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
				chr++;
				continue;

			case '.':
				chr++;
				state = HEXADECIMAL_FRACTIONAL_CONSTANT;
				continue;

			case 'p':
			case 'P':
			{
				chr++;

				if (*chr != '+' && *chr != '-') {
					state = HEXADECIMAL_FLOATING_CONSTANT;
					continue;
				}
				chr++;

				bool found_digit_sequence = false;
				while (true) {
					switch (*chr) {
					case '0':
					case '1': case '2': case '3':
					case '4': case '5': case '6':
					case '7': case '8': case '9':
						chr++;
						found_digit_sequence = true;
						continue;
					default:
						break;
					}
					break;
				}
				if (found_digit_sequence) {
					switch (*chr) {
					case 'f': case 'F':
					case 'l': case 'L':
						chr++;
						break;
					default:
						break;
					}
					if (chr == NULL) {
						state = HEXADECIMAL_FLOATING_CONSTANT;
					}
					else {
						state = END_FAIL;
					}
					continue;
				}
			}

			case 'u':
			case 'U':
			case 'l':
			case 'L':
			case '\0':
				state = HEXADECIMAL_CONSTANT;
				continue;

			default:
				break;
			}
			state = END_FAIL;
			continue;
		}

		case HEXADECIMAL_PREFIX:
		{
			bool encountered_digit = false;
			while (true) {
				switch (*chr) {
				case '0':
				case '1': case '2': case '3':
				case '4': case '5': case '6':
				case '7': case '8': case '9':
				case 'a': case 'b': case 'c':
				case 'd': case 'e': case 'f':
				case 'A': case 'B': case 'C':
				case 'D': case 'E': case 'F':
					encountered_digit = true;
					chr++;
					continue;
				default:
					break;
				}
				break;
			}
			if (!encountered_digit) {
				state = state = END_FAIL;
				continue;
			}

			switch (*chr) {

			case '.':
				chr++;
				state = HEXADECIMAL_FRACTIONAL_CONSTANT;
				continue;

			case 'p':
			case 'P':
				state = HEXADECIMAL_FRACTIONAL_CONSTANT;
				continue;

			case '\0':
				state = HEXADECIMAL_CONSTANT;
				continue;

			default:
				break;
			}
			state = END_FAIL;
			continue;
		}

		case FRACTIONAL_CONSTANT:
		{
			if (*chr == NULL) {
				state = DECIMAL_FLOATING_CONSTANT;
				continue;

			}

			if (*chr != 'e' && *chr != 'E') {

				bool found_digit_sequence = false;
				while (true) {
					if (*chr >= '0' && *chr <= '9') {
						found_digit_sequence = true;
						chr++;
						continue;
					}
					break;
				}
				if (found_digit_sequence) {
					continue;
				}
			}
			else {
				chr++;
			}

			if (*chr != '+' && *chr != '-') {
				state = DECIMAL_FLOATING_CONSTANT;
				continue;
			}
			else {
				chr++;
			}


			bool found_digit_sequence = false;
			while (true) {
				if (*chr >= '0' && *chr <= '9') {
					chr++;
					found_digit_sequence = true;
					continue;
				}
				break;
			}
			if (found_digit_sequence) {
				state = DECIMAL_FLOATING_CONSTANT;
				continue;
			}
			state = END_FAIL;
			continue;
		}

		case HEXADECIMAL_FRACTIONAL_CONSTANT:
		{
			if (*chr != 'p' && *chr != 'P') {
				state = HEXADECIMAL_FLOATING_CONSTANT;
				continue;
			}
			chr++;

			if (*chr != '+' && *chr != '-') {
				state = HEXADECIMAL_FLOATING_CONSTANT;
				continue;
			}
			chr++;

			bool found_digit_sequence = false;
			while (true) {
				switch (*chr) {
				case '0':
				case '1': case '2': case '3':
				case '4': case '5': case '6':
				case '7': case '8': case '9':
					chr++;
					found_digit_sequence = true;
					continue;
				}
				break;
			}
			if (found_digit_sequence) {
				state = HEXADECIMAL_FLOATING_CONSTANT;
				continue;
			}
			state = END_FAIL;
			continue;
		}

		case END_FAIL:
		{
			lexer_report_failure(
				"lex_constant",
				form,
				lexeme);

			*identifier_output = Token(
				TokenName::ERROR,
				form,
				tvalue,
				lexeme);

			exitcode = LexerExitCode::FAILURE;
			conclusive = true;
			break;
		}

		case FLOATING_CONSTANT:
		{
			if (*chr == 'f'
				|| *chr == 'F'
				|| *chr == 'l'
				|| *chr == 'L') {
				chr++;
			}
			if (*chr != NULL) {
				state = END_FAIL;
				continue;
			}

			long double val = strtold(
				lexeme,
				NULL);

			state = END_SUCCESS;
			form = TokenForm::FLOATING_CONSTANT;
			tvalue.floatvalue = val;
			continue;
		}

		case DECIMAL_FLOATING_CONSTANT:
			base = 10;
			state = FLOATING_CONSTANT;
			continue;

		case HEXADECIMAL_FLOATING_CONSTANT:
			base = 16;
			state = FLOATING_CONSTANT;
			continue;


		case END_SUCCESS:
		{
			lexer_report_success(
				"lex_constant",
				form,
				lexeme);

			*identifier_output++ = Token(
				TokenName::CONSTANT,
				form,
				tvalue,
				lexeme);

			exitcode = LexerExitCode::SUCCESS;
			conclusive = true;
			break;
		}

		default:
			break;
		}
	}
	return exitcode;

}

static inline LexerExitCode lex_string_literal(
	const PreprocessingToken& pp_token,
	Token*& identifier_output)
{
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	const char* lexeme = pp_token.get_lexeme();
	const char* chr = lexeme;

	TokenForm form = TokenForm::SIMPLE;

	TokenValue tvalue = {};
	int base = 10;

	bool conclusive = false;

	if (*chr == 'L') {
		chr++;
	}

	bool found_string_literal = false;

	if (*chr == '\"') {
		chr++;

		while (true) {

			switch (*chr) {

			case '\\':
				chr++;

				switch (*chr) {

				case '\'':
				case '\"':
				case '?':
				case '\\':
				case 'a':
				case 'b':
				case 'f':
				case 'n':
				case 'r':
				case 't':
				case 'v':
					chr++;
					continue;

				case 'x':
				{
					bool found_hex = false;
					while ((*chr >= '0' && *chr <= '9')
						&& (*chr >= 'a' && *chr <= 'f')
						&& (*chr >= 'A' && *chr <= 'F')) {
						chr++;
						found_hex = true;
					}
					if (found_hex) {
						chr++;
						if (*chr == NULL) {
							chr++;
							found_string_literal = true;
						}
						else {
							found_string_literal = false;
						}
					}
					else {
						found_string_literal = false;
					}
					continue;

				}

				case '0':
				case '1': case '2': case '3':
				case '4': case '5': case '6':
				case '7':
				{
					chr++;
					int num_encountered = 1;

					while (!(*chr >= '0'
						&& *chr <= '7')) {
						chr++;
						num_encountered++;
					}

					if (num_encountered >= 3) {
						found_string_literal = false;
					}
					break;
				}
				}
				continue;

			case '\n':
				found_string_literal = false;
				break;

			case '\"':
				chr++;
				found_string_literal = true;
				break;

			default:
				chr++;
				continue;
			}
			break;
		}
	}
	if (found_string_literal) {
		lexer_report_success(
			"lex_constant",
			form,
			lexeme);

		*identifier_output++ = Token(
			TokenName::STRING_LITERAL,
			form,
			tvalue,
			lexeme);

		exitcode = LexerExitCode::SUCCESS;

	}
	else {
		lexer_report_failure(
			"lex_constant",
			form,
			lexeme);

		*identifier_output++ = Token(
			TokenName::ERROR,
			form,
			tvalue,
			lexeme);

		exitcode = LexerExitCode::FAILURE;
	}
	return exitcode;
}

static inline LexerExitCode lex_punctuator(
	const PreprocessingToken& pp_token,
	Token*& identifier_output)
{
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	const char* lexeme = pp_token.get_lexeme();
	const char* chr = lexeme;

	TokenForm form = TokenForm::SIMPLE;

	TokenValue tvalue = {};
	int base = 10;

	bool found_punctuator = false;
	switch (*chr++) {

	case '[':
		if (*chr == NULL) {
			form = TokenForm::OPEN_SQUARE_BRACKET;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case ']':
		if (*chr == NULL) {
			form = TokenForm::CLOSE_SQUARE_BRACKET;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '(':
		if (*chr == NULL) {
			form = TokenForm::OPEN_PAREN;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case ')':
		if (*chr == NULL) {
			form = TokenForm::CLOSE_PAREN;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '{':
		if (*chr == NULL) {
			form = TokenForm::OPEN_CURLY_BRACKET;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '}':
		if (*chr == NULL) {
			form = TokenForm::CLOSE_CURLY_BRACKET;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '.':
		if (*chr == '.' && *(chr + 1) == '.' && *(chr + 2) == NULL) {
			form = TokenForm::TRIPLE_DOT;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::DOT;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '&':
		if (*chr == NULL) {
			form = TokenForm::AMPERSAND;
			found_punctuator = true;
		}
		else if (*chr == '&' && *(chr + 1) == NULL) {
			form = TokenForm::DOUBLE_AMPERSAND;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::AMPERSAND_EQUAL;
			found_punctuator = true;
		}
		break;

	case '*':
		if (*chr == NULL) {
			form = TokenForm::ASTERIX;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::MULTIPLY_EQUAL;
			found_punctuator = true;
		}
		break;

	case '+':
		if (*chr == '+' && *(chr + 1) == NULL) {
			form = TokenForm::INCREMENT;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::PLUS_EQUALS;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::PLUS;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '-':
		if (*chr == '-' && *(chr + 1) == NULL) {
			form = TokenForm::DECREMENT;
			found_punctuator = true;
		}
		else if (*chr == '>' && *(chr + 1) == NULL) {
			form = TokenForm::RIGHT_ARROW;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::MINUS_EQUALS;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::MINUS;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '~':
		if (*chr == NULL) {
			form = TokenForm::TILDE;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '!':
		if (*chr == NULL) {
			form = TokenForm::EXCLAMATION_MARK;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::NOT_EQUAL;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '/':
		if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::DIVIDE_EQUALS;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::FORWARD_SLASH;
			found_punctuator = true;
		}
		break;

	case '#':
		if (*chr == '#' && *(chr + 1) == NULL) {
			form = TokenForm::DOUBLE_HASHTAG;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::HASHTAG;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '%':
		if (*chr == NULL) {
			form = TokenForm::MODULO;
			found_punctuator = true;
		}
		else if (*chr == '>' && *(chr + 1) == NULL) {
			form = TokenForm::ANTIQUATED_CLOSE_CURLY_BRACKET;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::MODULO_EQUALS;
			found_punctuator = true;
		}
		else if (*chr == ':') {
			chr++;
			if (*chr == NULL) {
				form = TokenForm::ANTIQUATED_HASHTAG;
				found_punctuator = true;
			}
			else if (*chr == '%'
				&& *(chr + 1) == ':'
				&& *(chr + 2) == NULL) {
				form = TokenForm::ANTIQUATED_DOUBLE_HASHTAG;
				found_punctuator = true;
			}
			else {
				found_punctuator = false;
			}
		}
		break;

	case '<':
		if (*chr == '<') {
			if (*(chr + 1) == '=' && *(chr + 2) == NULL) {
				form = TokenForm::LEFT_SHIFT_EQUALS;
				found_punctuator = true;
			}
			else if (*(chr + 1) == NULL) {
				form = TokenForm::LEFT_SHIFT;
				found_punctuator = true;
			}
			else {
				found_punctuator = false;
			}
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::LESS_THAN_EQUAL;
			found_punctuator = true;
		}
		else if (*chr == ':' && *(chr + 1) == NULL) {
			form = TokenForm::ANTIQUATED_OPEN_SQUARE_BRACKET;
			found_punctuator = true;
		}
		else if (*chr == '%' && *(chr + 1) == NULL) {
			form = TokenForm::ANTIQUATED_OPEN_CURLY_BRACKET;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::LESS_THAN;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '>':
		if (*chr == '>') {
			if (*(chr + 1) == '=' && *(chr + 2) == NULL) {
				form = TokenForm::RIGHT_SHIFT_EQUALS;
				found_punctuator = true;
			}
			else if (*(chr + 1) == NULL) {
				form = TokenForm::RIGHT_SHIFT;
				found_punctuator = true;
			}
			else {
				found_punctuator = false;
			}
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::GREATER_THAN_EQUAL;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::GREATER_THAN;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '^':
		if (*chr == '=') {
			form = TokenForm::XOR_EQUAL;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::XOR;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '|':
		if (*chr == NULL) {
			form = TokenForm::OR;
			found_punctuator = true;
		}
		else if (*chr == '|' && *(chr + 1) == NULL) {
			form = TokenForm::DOUBLE_OR;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::OR_EQUAL;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '?':
		if (*chr == NULL) {
			form = TokenForm::QUESTION_MARK;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case ':':
		if (*chr == '>' && *(chr + 1) == NULL) {
			form = TokenForm::ANTIQUATED_CLOSE_SQUARE_BRACKET;
			found_punctuator = true;
		}
		else if (*chr == NULL) {
			form = TokenForm::COLON;
			found_punctuator = true;
		}
		break;

	case ';':
		if (*chr == NULL) {
			form = TokenForm::SEMI_COLON;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;

	case '=':
		if (*chr == NULL) {
			form = TokenForm::ASSIGN;
			found_punctuator = true;
		}
		else if (*chr == '=' && *(chr + 1) == NULL) {
			form = TokenForm::EQUAL;
			found_punctuator = true;
		}
		else {
			found_punctuator = false;
		}
		break;


	case ',':
		if (*chr == NULL) {
			form = TokenForm::COMMA;
			found_punctuator = true;
			break;
		}
		else {
			found_punctuator = false;
		}
		break;

	default:
		break;
	};
	if (found_punctuator) {
		lexer_report_success(
			"lex_punctuator",
			form,
			lexeme);

		*identifier_output++ = Token(
			TokenName::PUNCTUATOR,
			form,
			tvalue,
			lexeme);

		exitcode = LexerExitCode::SUCCESS;
	}
	else {
		lexer_report_failure(
			"lex_punctuator",
			form,
			lexeme);

		*identifier_output++ = Token(
			TokenName::ERROR,
			form,
			tvalue,
			lexeme);

		exitcode = LexerExitCode::FAILURE;
	}
	return exitcode;
}


static inline LexerExitCode lex(
	PreprocessingToken*& pp_tokens,
	Token*& identifier_output,
	int count)
{
	LexerExitCode exitcode = LexerExitCode::FAILURE;

	bool terminate_unsuccesfully = false;

	for (PreprocessingToken* ppt = pp_tokens;
		ppt < pp_tokens + count;
		ppt++) {

		switch (ppt->get_name()) {

		case PreprocessingTokenName::IDENTIFIER:
		{
			LexerExitCode found_kw
				= lex_keyword(*ppt, identifier_output);

			if (found_kw != LexerExitCode::SUCCESS) {

				LexerExitCode found_id
					= lex_identifier(*ppt, identifier_output);

				if (found_id != LexerExitCode::SUCCESS) {
					terminate_unsuccesfully = true;
				}
			}
			break;
		}

		case PreprocessingTokenName::CHARACTER_CONSTANT:
		case PreprocessingTokenName::PP_NUMBER:
		{
			LexerExitCode found_cnst
				= lex_constant(*ppt, identifier_output);

			if (found_cnst != LexerExitCode::SUCCESS) {
				terminate_unsuccesfully = true;
			}
			break;
		}

		case PreprocessingTokenName::STRING_LITERAL:
		{
			LexerExitCode found_string_literal
				= lex_string_literal(*ppt, identifier_output);

			if (found_string_literal != LexerExitCode::SUCCESS) {
				terminate_unsuccesfully = true;
			}
			break;
		}

		case PreprocessingTokenName::PUNCTUATOR:
		{
			LexerExitCode found_punctuator
				= lex_punctuator(*ppt, identifier_output);

			if (found_punctuator != LexerExitCode::SUCCESS) {
				terminate_unsuccesfully = true;
			}
			break;
		}

		default: terminate_unsuccesfully = true; break;
		}
		if (terminate_unsuccesfully) {
			exitcode = LexerExitCode::FAILURE;
			break;
		}
	}
	if (!terminate_unsuccesfully) {
		exitcode = LexerExitCode::SUCCESS;
	}
	return exitcode;
}

#endif