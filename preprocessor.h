
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H 1

#include <iostream>

using namespace std;

#include "preprocessing-token.h"

#define DEBUG_ENABLE_PREPROCESSOR_REPORT 1

#define preprocessor_report_failure( s, f, l )				\
		if (DEBUG_ENABLE_PREPROCESSOR_REPORT)				\
			cout << "lexer.cpp:" s ":"						\
				 << "recognised erroneous token with form "	\
				 << (size_t) f								\
				 << " and lexeme "							\
				 << l										\
				 << "."										\
				 << endl

#define preprocessor_report_success( s, f, l )				\
		if (DEBUG_ENABLE_PREPROCESSOR_REPORT)				\
				cout << "lexer.cpp:" s ":"					\
					 << "produced token with form "			\
					 << (size_t) f							\
					 << " and lexeme "						\
					 << l									\
				     << "."									\
					 << endl

/* Used to store the result of a preprocessor procedure */
enum class PreprocessorExitCode {
	SUCCESS,
	FAILURE
};

/**
* Used to construct a lexeme from the characters between
* the start and and of a given (input) string.
* @param lexeme_start The start of the slice.
* @param lexeme_start The end of the slice.
* @return Returns the constructed lexeme.
**/
static inline   const char* construct_lexeme(
	const char* const& lexeme_start,
	const char* const& lexeme_end)
{
	char* lexeme = new char[lexeme_end - lexeme_start + 1];
	for (int i = 0; i < lexeme_end - lexeme_start + 1; i++) {
		*(lexeme + i) = *(lexeme_start + i);
	}
	*(lexeme + (lexeme_end - lexeme_start)) = NULL;
	return lexeme;
}

/**
* Used to preprocess a header name.
* @param input The input to preprocess.
* @param fld The input's file location descriptor.
* @param header_name The produced header_name pptoken.
**/
static inline  PreprocessorExitCode preprocess_header_name(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& header_name)
{
	enum PreprocessingState {
		START,

		H_HEADER,
		Q_HEADER,

		END_FAIL,
		END_SUCCESS
	};

	PreprocessingState state
		= PreprocessingState::START;

	PreprocessorExitCode exitcode =
		PreprocessorExitCode::FAILURE;

	const char* chr = input;

	bool conclusive = false;

	PreprocessingTokenForm form =
		PreprocessingTokenForm::SIMPLE;

	while (!conclusive) {

		switch (*chr++) {

		case START:

			switch (*chr++) {

			case '<':
			{
				bool c_char_sequence_present = false;
				while (*chr != '\n' && *chr != '>') {
					c_char_sequence_present = true;
					chr++;
				}
				if (c_char_sequence_present
					&& *chr == '>') {
					chr++;
					state = H_HEADER;
				}
				else {
					state = END_FAIL;
				}
				break;
			}

			case '\"':
			{
				bool q_char_sequence_present = false;
				while (*chr != '\n' && *chr != '>') {
					q_char_sequence_present = true;
					chr++;
				}
				if (q_char_sequence_present
					&& *chr == '>') {
					chr++;
					state = Q_HEADER;
				}
				else {
					state = END_FAIL;
				}
				break;
			}
			default: state = END_FAIL; break;
			}
			break;

		case H_HEADER:
			form = PreprocessingTokenForm::H_HEADER;
			state = END_SUCCESS;
			break;

		case Q_HEADER:
			form = PreprocessingTokenForm::Q_HEADER;
			state = END_SUCCESS;
			break;

		case END_SUCCESS:
		{
			char* lexeme = new char[chr - input + 1];
			const char* i = input;
			char* o = lexeme;
			while (i < chr) {
				*o++ = *i++;
			}
			(*(lexeme + (chr - input))) = 0;

			preprocessor_report_success(
				"preprocess_header_name",
				form,
				lexeme);


			*header_name++ = PreprocessingToken(
				lexeme,
				PreprocessingTokenName::HEADER_NAME,
				fld,
				form);

			exitcode = PreprocessorExitCode::SUCCESS;
			conclusive = true;
			break;
		}

		default:
		case END_FAIL:
			char* lexeme = new char[chr - input + 1];
			const char* i = input;
			char* o = lexeme;
			while (i < chr) {
				*o++ = *i++;
			}
			(*(lexeme + (chr - input))) = 0;

			preprocessor_report_failure(
				"preprocess_header_name",
				form,
				lexeme);

			*header_name++ = PreprocessingToken(
				lexeme,
				PreprocessingTokenName::ERROR,
				fld,
				form);

			exitcode = PreprocessorExitCode::FAILURE;
			conclusive = true;
			break;
		}
	}
	return exitcode;
}

/**
* Used to preprocess an identifier name.
* @param input The input to preprocess.
* @param fld The input's file location descriptor.
* @param identifier_name The produced identifier_name pptoken.
**/
static inline  PreprocessorExitCode preprocess_identifier_name(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& identifier_name)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	const char* lexeme_start = input;

	enum PreprocessingState {
		START,

		IDENTIFIER,
		IDENTIFIER_NONDIGIT,

		END_FAIL,
		END_SUCCESS
	};

	PreprocessingState state
		= PreprocessingState::START;

	PreprocessingTokenForm form
		= PreprocessingTokenForm::SIMPLE;

	bool preprocessed_identifier = false;

	while (true) {

		switch (state) {

		case START:

			switch (*input) {

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
				input++;
				state = IDENTIFIER_NONDIGIT;
				continue;

			default:
				break;
			}
			preprocessed_identifier = false;
			break;

		case IDENTIFIER_NONDIGIT:

			switch (*input) {

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

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
			case '0':

				// TODO: UNIVERSAL-CHARACTER-NAME
				input++;
				continue;

			default: break;
			}
			preprocessed_identifier = true;
			break;
		}
		break;
	}

	if (preprocessed_identifier) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_success(
			"preprocess_identifier_name",
			form,
			lexeme);

		*identifier_name++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::IDENTIFIER,
			fld,
			form);

		exitcode = PreprocessorExitCode::SUCCESS;
	}
	else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_failure(
			"preprocess_identifier_name",
			form,
			lexeme);

		*identifier_name++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);

		exitcode = PreprocessorExitCode::FAILURE;
	}
	return exitcode;
}

/**
* Used to preprocess a pp-number.
* @param input The input from which to preprocess.
* @param fld The input's file location descriptor.
* @param pp_number The produced pp-number pptoken.
**/
static inline  PreprocessorExitCode preprocess_pp_number(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& pp_number)
{
	const char* lexeme_start = input;

	enum PreprocessingState {
		START,
		PP_NUMBER,
		END_FAIL,
		END_SUCCESS
	};

	PreprocessingState state
		= PreprocessingState::START;

	PreprocessorExitCode exitcode =
		PreprocessorExitCode::FAILURE;

	bool conclusive = false;

	PreprocessingTokenForm form =
		PreprocessingTokenForm::SIMPLE;

	while (!conclusive) {

		switch (state) {

		case START:
			if (*input >= '0' && *input <= '9') {
				input++;
				state = PP_NUMBER;
				continue;
			}
			else if (*input == '.') {
				input++;
				if (*input >= '0' && *input <= '9') {
					input++;
					state = PP_NUMBER;
					continue;
				}
			}
			break;

		case PP_NUMBER:
			switch (*input) {

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
			case '0':
				input++;
				continue;

			case '_':
			case 'a': case 'b': case 'c':
			case 'd': case 'f':
			case 'g': case 'h': case 'i':
			case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o':
			case 'q': case 'r':
			case 's': case 't': case 'u':
			case 'v': case 'w': case 'x':
			case 'y': case 'z':
			case 'A': case 'B': case 'C':
			case 'D': case 'F':
			case 'G': case 'H': case 'I':
			case 'J': case 'K':
			case 'M': case 'N': case 'O':
			case 'Q': case 'R':
			case 'S': case 'T': case 'U':
			case 'V': case 'W': case 'X':
			case 'Y': case 'Z':
				input++;
				continue;

			case 'e': case 'E':
			case 'p': case 'P':
				input++;
				if (*input == '+'
					|| *input == '-') {
					input++;
				}
				continue;

			case '.':
				input++;
				continue;

			default:
				break;
			}
			state = END_SUCCESS;
			break;

		case END_SUCCESS:
		{
			const char* lexeme
				= construct_lexeme(lexeme_start, input);

			preprocessor_report_success(
				"preprocess_pp_number",
				form,
				lexeme);


			*pp_number++ = PreprocessingToken(
				lexeme,
				PreprocessingTokenName::PP_NUMBER,
				fld,
				form);

			exitcode = PreprocessorExitCode::SUCCESS;
			conclusive = true;
			break;
		}

		default:
		case END_FAIL:
			const char* lexeme
				= construct_lexeme(lexeme_start, input);


			preprocessor_report_failure(
				"preprocess_pp_number",
				form,
				lexeme);

			*pp_number++ = PreprocessingToken(
				lexeme,
				PreprocessingTokenName::ERROR,
				fld,
				form);

			exitcode = PreprocessorExitCode::FAILURE;
			conclusive = true;
			break;
		}
	}
	return exitcode;
}

#define is_hex_digit(c) ((c >= '0' && c <= '9')		\
						 && (c >= 'a' && c <= 'f')	\
						 && (c >= 'A' && c <= 'F'))	\

/**
* Used to preprocess a character-constant.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param character_constant The reference to where to place
*        the produced character_constant pptoken.
**/
static inline  PreprocessorExitCode preprocess_character_constant(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& identifier_output)
{
	const char* lexeme_start = input;

	bool found_preprocess = false;

	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;
	PreprocessingTokenForm form
		= PreprocessingTokenForm::SIMPLE;

	if (*input == 'L') {
		input++;
	}

	if (*input == '\'') {
		input++;
		while (true) {

			switch (*input) {

			case '\\':
				input++;
				switch (*input) {

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
					input++;
					continue;

				case 'x':
				{
					bool found_hex = false;
					while (is_hex_digit(*input)) {
						input++;
						found_hex = true;
					}
					if (found_hex) {
						input++;

						if (*input == NULL) {
							input++;
							found_preprocess = true;
						}
						else {
							found_preprocess = false;
						}
					}
					else {
						found_preprocess = false;
					}
					continue;
				}

				case '0':
				case '1': case '2': case '3':
				case '4': case '5': case '6':
				case '7':
				{
					input++;
					int num_encountered = 1;

					while (!(*input >= '0'
						&& *input <= '7')) {
						input++;
						num_encountered++;
					}

					if (num_encountered >= 3) {
						found_preprocess = false;
					}
					break;
				}
				}
				continue;

			case '\n':
				found_preprocess = false;
				break;

			case '\'':
				input++;
				found_preprocess = true;
				break;

			default:
				input++;
				continue;
			}
			break;
		}
	}
	if (found_preprocess) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		*identifier_output++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::CHARACTER_CONSTANT,
			fld,
			form);

		exitcode = PreprocessorExitCode::SUCCESS;
	}
	else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);


		preprocessor_report_failure(
			"preprocess_pp_number",
			form,
			lexeme);

		*identifier_output++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);

		exitcode = PreprocessorExitCode::FAILURE;
	}
	return exitcode;
}

/**
* Used to preprocess a string-literal.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param string_literal The reference to where to place
*        the produced string-literal pptoken.
**/
static inline  PreprocessorExitCode preprocess_string_literal(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& string_literal)
{
	const char* lexeme_start = input;
	bool found_preprocess = false;

	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;
	PreprocessingTokenForm form
		= PreprocessingTokenForm::SIMPLE;

	if (*input == 'L') input++;

	if (*input == '\"') {

		input++;
		while (true) {

			switch (*input) {

			case '\\':
				input++;
				switch (*input) {

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
					input++;
					continue;

				case 'x':
				{
					bool found_hex = false;
					while (is_hex_digit(*input)) {
						input++;
						found_hex = true;
					}
					if (found_hex) {
						input++;
						if (*input == NULL) {
							input++;
							found_preprocess = true;
						}
					}
					continue;
				}

				case '0':
				case '1': case '2': case '3':
				case '4': case '5': case '6':
				case '7':
				{
					input++;
					int num_encountered = 1;

					while (!(*input >= '0'
						&& *input <= '7')) {
						input++;
						num_encountered++;
					}

					if (num_encountered >= 3) {
						found_preprocess = false;
					}
					break;
				}
				}
				continue;

			case '\n':
				found_preprocess = false;
				break;

			case '\"':
				input++;
				found_preprocess = true;
				break;

			default:
				input++;
				continue;
			}
			break;
		}
	}
	if (found_preprocess) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		*string_literal++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::STRING_LITERAL,
			fld,
			form);

		exitcode = PreprocessorExitCode::SUCCESS;
	}
	else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);


		preprocessor_report_failure(
			"preprocess_pp_number",
			form,
			lexeme);

		*string_literal++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);

		exitcode = PreprocessorExitCode::FAILURE;
	}
	return exitcode;
}

/**
* Used to preprocess a punctuator.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param punctuator The reference to where to place
*        the produced punctuator pptoken.
**/
static inline  PreprocessorExitCode preprocess_punctuator(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& punctuator)
{
	const char* lexeme_start = input;

	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	PreprocessingTokenForm form
		= PreprocessingTokenForm::SIMPLE;

	bool found_punctuator = false;
	switch (*input++) {

	case '[': found_punctuator = true; break;
	case ']': found_punctuator = true; break;
	case '(': found_punctuator = true; break;
	case ')': found_punctuator = true; break;
	case '{': found_punctuator = true; break;
	case '}': found_punctuator = true; break;

	case '.':
		if (*input == '.' && *(input + 1) == '.') {
			input += 2;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '&':
		if (*input == '&') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '=') {
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '*':
		if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '+':
		if (*input == '+') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '-':
		if (*input == '-') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '>') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '~': found_punctuator = true; break;

	case '!':
		input += (*input == '=');
		found_punctuator = true;
		break;

	case '/':
		if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '#':
		input += (*input == '#');
		found_punctuator = true;
		break;

	case '%':
		if (*input == '>') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else if (*input == ':') {
			input++;
			if (*input == '%'
				&& *(input + 1) == ':') {
				input += 2;
				found_punctuator = true;
			}
			else {
				found_punctuator = true;
			}
		}
		else {
			found_punctuator = true;
		}
		break;

	case '<':
		if (*input == '<') {
			input++;
			if (*(input + 1) == '=') {
				input++;
				found_punctuator = true;
			}
			else {
				found_punctuator = true;
			}
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else if (*input == ':') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '%') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '>':
		if (*input == '>') {
			input++;
			if (*input == '=') {
				input++;
				found_punctuator = true;
			}
			else {
				found_punctuator = true;
			}
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '^':
		if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '|':
		if (*input == '|') {
			input++;
			found_punctuator = true;
		}
		else if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case '?': found_punctuator = true; break;

	case ':':
		if (*input == '>') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
		}
		break;

	case ';': found_punctuator = true; break;

	case '=':
		if (*input == '=') {
			input++;
			found_punctuator = true;
		}
		else {
			found_punctuator = true;
			break;
		}

	case ',': found_punctuator = true; break;

	default:
		break;
	};
	if (found_punctuator) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_success(
			"preprocess_punctuator",
			form,
			lexeme);

		*punctuator++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::PUNCTUATOR,
			fld,
			form);

		exitcode = PreprocessorExitCode::SUCCESS;
	}
	else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);

		preprocessor_report_failure(
			"preprocess_punctuator",
			form,
			lexeme);

		*punctuator++ = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);

		exitcode = PreprocessorExitCode::FAILURE;
	}
	return exitcode;
}

/**
* Used to preprocess a character string (char*) input.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param punctuator The reference to where to place
*					the produced pptokens.
**/
static inline  PreprocessorExitCode preprocess(
	const char*& input,
	const FileLocationDescriptor& fld,
	PreprocessingToken*& identifier_output)
{
	enum LexingState {
		START,
		END_SUCCESS
	};

	LexingState state = LexingState::START;

	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	bool in_comment = false;

	bool conclusive = false;
	while (!conclusive) {

		switch (*input) {

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
		case 'J': case 'K':
		case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R':
		case 'S': case 'T': case 'U':
		case 'V': case 'W': case 'X':
		case 'Y': case 'Z':
			preprocess_identifier_name(
				input,
				fld,
				identifier_output);
			break;

		case 'L':
			if (*(input + 1) == '\"') {
				preprocess_identifier_name(
					input,
					fld,
					identifier_output);
			}
			else {
				preprocess_string_literal(
					input,
					fld,
					identifier_output);
			}
			break;

		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
		case '0':
			preprocess_pp_number(
				input,
				fld,
				identifier_output);
			break;

		case '\'':
			preprocess_character_constant(
				input,
				fld,
				identifier_output);
			break;

		case '\"':
			preprocess_string_literal(
				input,
				fld,
				identifier_output);
			break;

		case '/':
			if (*(input + 1) == '*') {
				input += 2;
				while ((*input != '*')
					|| (*(input + 1) != '/')) {
					input++;
				}
				input += 2;
			}
			else if (*(input + 1) == '/') {
				input += 2;
				while (*input != '\n') {
					input++;
				}
				input++;
			}
			else {
				preprocess_punctuator(
					input,
					fld,
					identifier_output);
			}
			break;

		case '[': case ']':
		case '(': case ')':
		case '{':  case '}': case ':':
		case '.':
		case '&': case '+': case '-':
		case '~': case '!': case '#':
		case '%': case '<': case '>':
		case '^': case '|': case '?':
		case ';': case '=': case ',':
		case '*':
			preprocess_punctuator(
				input,
				fld,
				identifier_output);
			break;

		case '\\':
			input++;
			if (*input == '\n') {
				conclusive = true;
			}
			break;

		case ' ':
		case '\t':
		case '\n':
		case '\r':
			input++;
			break;

		case NULL:
		case EOF:
			exitcode = PreprocessorExitCode::SUCCESS;
			conclusive = true;
			break;

		default:
			break;
		}
	}
	return exitcode;
}

#endif