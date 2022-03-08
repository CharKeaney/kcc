
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H 1

#include <iostream>

#include "preprocessing-token.h"
#include "error.h"

/* All of the following used for constant-expressions. */
#include "token.h"
#include "lexer.h"
#include "ast-node.h"
#include "parser.h"
#include "annotated-ast-node.h"
#include "semantic-annotator.h"

using namespace std;

#define DEBUG_ENABLE_PREPROCESSOR_REPORT 0

#define preprocessor_report_failure( s, f, l )				\
		if (DEBUG_ENABLE_PREPROCESSOR_REPORT) {				\
			cout << "lexer.cpp:" s ":"						\
				 << "recognised erroneous token with form "	\
				 << (size_t) f								\
				 << " and lexeme "							\
				 << l										\
				 << "."										\
				 << endl;									\
		}

#define preprocessor_report_success( s, f, l )				\
		if (DEBUG_ENABLE_PREPROCESSOR_REPORT) {				\
				cout << "lexer.cpp:" s ":"					\
					 << "produced token with form "			\
					 << (size_t) f							\
					 << " and lexeme "						\
					 << l									\
				     << "."									\
					 << endl;								\
		}


#define pp_free_stack(s, si) while (si > 0) { delete s[--si]; } 

/* Used to store the result of a preprocessor procedure */
enum class PreprocessorExitCode {
	SUCCESS,
	FAILURE
};

enum Directives {
	IF,
	IFDEF,
	IFNDEF,
	ELIF,
	ELSE,
	ENDIF,
	INCLUDE,
	DEFINE,
	UNDEF,
	LINE,
	ERROR,
	PRAGMA
};

const char* directives_string_repr[]{
	"if",
	"ifdef",
	"ifndef",
	"elif",
	"else",
	"endif",
	"include",
	"define",
	"undef",
	"line",
	"error",
	"pragma"
};

enum class PreprocessingAstNodeName {
	/* Error */
	ERROR = 0,
	/* Terminals */
	PREPROCESSING_FILE,
	GROUP,
	GROUP_PART,
	IF_SECTION,
	IF_GROUP,
	ELIF_GROUPS,
	ELIF_GROUP,
	ELSE_GROUP,
	ENDIF_LINE,
	CONTROL_LINE,
	TEXT_LINE,
	NON_DIRECTIVE,
	LPAREN,
	REPLACEMENT_LIST,
	PP_TOKENS,
	PREPROCESSING_TOKEN,
	NEW_LINE,
	IDENTIFIER_LIST,
	CONSTANT_EXPRESSION
};

static const char* preprocessing_ast_name_string_reprs[]{
	"ERROR",
	"PREPROCESSING_FILE",
	"GROUP",
	"GROUP_PART",
	"IF_SECTION",
	"IF_GROUP",
	"ELIF_GROUPS",
	"ELIF_GROUP",
	"ELSE_GROUP",
	"ENDIF_LINE",
	"CONTROL_LINE",
	"TEXT_LINE",
	"NON_DIRECTIVE",
	"LPAREN",
	"REPLACEMENT_LIST",
	"PP_TOKENS",
	"PREPROCESSING_TOKEN",
	"NEW_LINE",
	"IDENTIFIER_LIST",
	"CONSTANT_EXPRESSION"
};

enum class PreprocessingAstNodeAlt {
	ERROR = 0,
	/* terminal */
	PREPROCESSING_FILE_1,
	GROUP_1,
	GROUP_2,
	GROUP_PART_1,
	GROUP_PART_2,
	GROUP_PART_3,
	GROUP_PART_4,
	IF_SECTION_1,
	IF_GROUP_1,
	IF_GROUP_2,
	IF_GROUP_3,
	ELIF_GROUPS_1,
	ELIF_GROUPS_2,
	ELIF_GROUP_1,
	ELSE_GROUP_1,
	ENDIF_LINE_1,
	CONTROL_LINE_1,
	CONTROL_LINE_2,
	CONTROL_LINE_3,
	CONTROL_LINE_4,
	CONTROL_LINE_5,
	CONTROL_LINE_6,
	CONTROL_LINE_7,
	CONTROL_LINE_8,
	CONTROL_LINE_9,
	CONTROL_LINE_10,
	TEXT_LINE_1,
	NON_DIRECTIVE_1,
	LPAREN_1,
	REPLACEMENT_LIST_1,
	PP_TOKENS_1,
	PP_TOKENS_2,
	PREPROCESSING_TOKEN_1,
	NEW_LINE_1,
	IDENTIFIER_LIST_1,
	IDENTIFIER_LIST_2,
	CONSTANT_EXPRESSION_1
};

static const char* preprocessing_ast_form_string_reprs[]{
	"ERROR",
	"PREPROCESSING_FILE_1",
	"GROUP_1",
	"GROUP_2",
	"GROUP_PART_1",
	"GROUP_PART_2",
	"GROUP_PART_3",
	"GROUP_PART_4",
	"IF_SECTION_1",
	"IF_GROUP_1",
	"IF_GROUP_2",
	"IF_GROUP_3",
	"ELIF_GROUPS_1",
	"ELIF_GROUPS_2",
	"ELIF_GROUP_1",
	"ELSE_GROUP_1",
	"ENDIF_LINE_1",
	"CONTROL_LINE_1",
	"CONTROL_LINE_2",
	"CONTROL_LINE_3",
	"CONTROL_LINE_4",
	"CONTROL_LINE_5",
	"CONTROL_LINE_6",
	"CONTROL_LINE_7",
	"CONTROL_LINE_8",
	"CONTROL_LINE_9",
	"CONTROL_LINE_10",
	"TEXT_LINE_1",
	"NON_DIRECTIVE_1",
	"LPAREN_1",
	"REPLACEMENT_LIST_1",
	"PP_TOKENS_1",
	"PP_TOKENS_2",
	"PREPROCESSING_TOKEN_1",
	"NEW_LINE_1",
	"IDENTIFIER_LIST_1",
	"IDENTIFIER_LIST_2",
	"CONSTANT_EXPRESSION_1"
};

class PreprocessingAstNode {
private:
	PreprocessingAstNodeName name;
	PreprocessingAstNodeAlt  alt;
	PreprocessingToken*      terminal;
	PreprocessingAstNode*    child;
	PreprocessingAstNode*    sibling;
	uint64_t                 val;
public:
	inline PreprocessingAstNode(
		PreprocessingAstNodeName const& n,
		PreprocessingAstNodeAlt  const& a,
		PreprocessingToken*      const& t) :
		name(n),
		alt(a),
		terminal(t),
		child(NULL),
		sibling(NULL) {
	}

	inline PreprocessingAstNode() :
		name(PreprocessingAstNodeName::ERROR),
		alt(PreprocessingAstNodeAlt::ERROR),
		terminal(NULL),
		child(NULL),
		sibling(NULL) {
	}

	inline PreprocessingAstNodeName get_name() const
	{
		return name;
	};

	inline PreprocessingAstNodeAlt get_alt() const
	{
		return alt;
	};

	inline PreprocessingToken* get_terminal() const
	{
		return terminal;
	};

	inline PreprocessingAstNode* get_child() const
	{
		return child;
	};

	inline PreprocessingAstNode* get_sibling() const
	{
		return sibling;
	};

	inline void add_child(PreprocessingAstNode* node)
	{
		if (child == NULL) {
			child = node;
		}
		else {
			PreprocessingAstNode* current = child;
			while (current->sibling) {
				current = current->sibling;
			}
			current->sibling = node;
		}
	}

	inline void add_children(
		PreprocessingAstNode** const& nodes,
		int                    const& count)
	{
		for (PreprocessingAstNode** n = nodes;
			n < nodes + count;
			n++) {
			add_child(*n);
		}
		/*print();*/
	}

	inline void print(
		string parent_prefix = "",
		string child_prefix  = "")
	{
		cout << parent_prefix
			 << "name="
			 << preprocessing_ast_name_string_reprs[(int)name]
			 << ",alt="
			 << preprocessing_ast_form_string_reprs[(int)alt];
		if (terminal) terminal->print();
		cout << endl;
		PreprocessingAstNode* node = child;
		for (; node; node = node->sibling) {
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

static inline PreprocessingAstNode* construct_node_from_children(
	PreprocessingAstNodeName const& name,
	PreprocessingAstNodeAlt  const& alt,
	PreprocessingAstNode**   const& children,
	int                      const& count)
{
	PreprocessingAstNode* node = new PreprocessingAstNode(
		name,
		alt,
		NULL
	);
	node->add_children(
		children, 
		count);
	return node;
}

static inline const char* construct_lexeme(
	const char* const& lexeme_start,
	const char* const& lexeme_end);

static inline PreprocessorExitCode pp_lex_header_name(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & header_name);

static inline PreprocessorExitCode pp_lex_identifier_name(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_name,
	AlertList              & bkl);

static inline  PreprocessorExitCode pp_lex_pp_number(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & pp_number,
	AlertList              & bkl);

static inline PreprocessorExitCode pp_lex_character_constant(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_output,
	AlertList              & bkl);

static inline PreprocessorExitCode pp_lex_string_literal(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & string_literal,
	AlertList              & bkl);

static inline  PreprocessorExitCode pp_lex_punctuator(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & punctuator,
	AlertList              & bkl);

static inline PreprocessorExitCode preprocess(
	const char*              & input,
	const char**             & produced_lexema,
	const char*         const& filename,
	AlertList                & bkl,
	PreprocessingToken*      & output);

static inline PreprocessorExitCode pp_parse_pp_tokens(
	const char*                 & input,
	const char**                & produced_lexema,
	FileLocationDescriptor      & file_location_descriptor,
	PreprocessingAstNode*       & pp_tokens,
	AlertList                   & bkl,
	bool			       const& in_directive);

static inline PreprocessorExitCode pp_parse_preprocessing_file(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & preprocessing_file);

static inline PreprocessorExitCode pp_parse_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group);

static inline PreprocessorExitCode pp_parse_group_part(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group_part);

static inline PreprocessorExitCode pp_parse_if_section(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_section);

static inline PreprocessorExitCode pp_parse_if_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_group);

static inline PreprocessorExitCode pp_parse_elif_groups(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_groups);

static inline PreprocessorExitCode pp_parse_constant_expression(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & constant_expression);

static inline PreprocessorExitCode pp_parse_elif_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_group);

static inline PreprocessorExitCode pp_parse_else_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & else_group);

static inline PreprocessorExitCode pp_parse_endif_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & endif_line);

static inline PreprocessorExitCode pp_parse_control_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & control_line);

static inline PreprocessorExitCode pp_parse_text_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & text_line);

static inline PreprocessorExitCode pp_parse_new_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & new_line);

static inline PreprocessorExitCode pp_parse_non_directive(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & non_directive);

static inline PreprocessorExitCode pp_parse_lparen(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & lparen);

static inline PreprocessorExitCode pp_parse_replacement_list(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & replacement_list);

static inline PreprocessorExitCode pp_gen_preprocessing_file(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_group(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_group_part(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_if_section(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_elif_groups(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_elif_group(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_else_group(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_endif(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_control_line(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_text_line(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_non_directive(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_lparen(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_replacement_list(
	PreprocessingAstNode* const& replacement_list,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_pp_tokens(
	PreprocessingAstNode* const& pp_tokens,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_new_line(
	PreprocessingAstNode* const& new_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

static inline PreprocessorExitCode pp_gen_preprocessing_token(
	PreprocessingAstNode* const& preprocessing_token,
	PreprocessingToken*        & output,
	AlertList                  & bkl);

/**
* Used to construct a lexeme from the characters between
* the start and and of a given (input) string.
* @param lexeme_start The start of the slice.
* @param lexeme_start The end of the slice.
* @return Returns the constructed lexeme.
**/
static inline const char* construct_lexeme(
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
static inline  PreprocessorExitCode pp_lex_header_name(
	const char*            & input, 
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & header_name)
{
	enum PreprocessingState {
		START,

		HEADER_NAME_1,
		HEADER_NAME_2,

		END_FAIL,
		END_SUCCESS
	};

	PreprocessingState state
		= PreprocessingState::START;

	PreprocessorExitCode exitcode =
		PreprocessorExitCode::FAILURE;

	const char* chr 
		= input;

	bool conclusive 
		= false;

	PreprocessingTokenForm form =
		PreprocessingTokenForm::UNDEFINED;

	while (!conclusive) {

		switch (*chr++) {

			case START:
			{
				switch (*chr++) {

					case '<':
					{
						bool c_char_sequence_present = false;
						while (*chr != '\n' && *chr != '>') {
							c_char_sequence_present = true;
							chr++;
						} if (c_char_sequence_present
							&& *chr == '>') {
							chr++;
							state = HEADER_NAME_1;
						} else {
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
							state = HEADER_NAME_2;
						} else {
							state = END_FAIL;
						}
						break;
					}

					default:
						state = END_FAIL;
						break;
				}
				break;
			}

			case HEADER_NAME_1:
				form  = PreprocessingTokenForm::HEADER_NAME_1;
				state = END_SUCCESS;
				break;

			case HEADER_NAME_2:
				form  = PreprocessingTokenForm::HEADER_NAME_2;
				state = END_SUCCESS;
				break;

			case END_SUCCESS:
			{
				char* const lexeme 
					= new char[chr - input + 1];

				const char* input_ptr  = input;
			    char*       buffer_ptr = lexeme;
				while (input_ptr < chr) {
					*buffer_ptr++ = *input_ptr++;
				}
				(*(lexeme + (chr - input))) = 0;

				preprocessor_report_success(
					"preprocess_header_name",
					form,
					lexeme);

				fld.lexeme_length = chr - input;
				*header_name = PreprocessingToken(
					lexeme,
					PreprocessingTokenName::HEADER_NAME,
					fld,
					form);
				fld.character_number += (chr - input);

				exitcode = PreprocessorExitCode::SUCCESS;
				conclusive = true;
				break;
			}

			case END_FAIL:
			default:
			{
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

				fld.lexeme_length = chr - input;
				*header_name = PreprocessingToken(
					lexeme,
					PreprocessingTokenName::ERROR,
					fld,
					form);
				Error* error
					= construct_error_book(
						ErrorCode::ERR_PP_INVALID_HEADER,
						"This header name could not be recognised. Did you mispell it?",
						fld);
				fld.character_number += (chr - input);

				exitcode = PreprocessorExitCode::FAILURE;
				conclusive = true;
				break;
			}
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
static inline PreprocessorExitCode pp_lex_identifier_name(
	const char*            & input, 
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_name,
	AlertList              & bkl)
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
		= PreprocessingTokenForm::UNDEFINED;

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

					default: 
						break;

				}
				preprocessed_identifier = true;
				break;

			default:
				break;

		}
		break;
	}

	if (preprocessed_identifier) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);
		*produced_lexema++ = lexeme;

		preprocessor_report_success(
			"preprocess_identifier_name",
			form,
			lexeme);

		fld.lexeme_length = input - lexeme_start;
		*identifier_name = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::IDENTIFIER,
			fld,
			form);
		fld.character_number += (input - lexeme_start);


		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);
		*produced_lexema++ = lexeme;

		preprocessor_report_failure(
			"preprocess_identifier_name",
			form,
			lexeme);

		fld.lexeme_length = input - lexeme_start;
		*identifier_name = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);
		Error* error
			= construct_error_book(
				ErrorCode::ERR_PP_INVALID_IDENTIFIER,
				"This identifier could not be recognised. Did you mispell it?",
				fld);
		fld.character_number += (input - lexeme_start);

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
static inline  PreprocessorExitCode pp_lex_pp_number(
	const char*            & input, 
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & pp_number,
	AlertList              & bkl)
{
	const char* lexeme_start 
		= input;

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
		PreprocessingTokenForm::UNDEFINED;

	while (!conclusive) {

		switch (state) {

			case START:
				if (*input >= '0' 
					&& *input <= '9') {
					input++;
					state = PP_NUMBER;
					continue;
				} else if (*input == '.') {
					input++;
					if (*input >= '0' 
						&& *input <= '9') {
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
					= construct_lexeme(
						lexeme_start, 
						input);
				*produced_lexema++ = lexeme;

				preprocessor_report_success(
					"preprocess_pp_number",
					form,
					lexeme);

				fld.lexeme_length 
					= input - lexeme_start;
				*pp_number = PreprocessingToken(
					lexeme,
					PreprocessingTokenName::PP_NUMBER,
					fld,
					form);
				fld.character_number 
					+= (input - lexeme_start);

				exitcode = PreprocessorExitCode::SUCCESS;
				conclusive = true;
				break;
			}

			case END_FAIL:
			default:
			{
				const char* lexeme
					= construct_lexeme(
						lexeme_start, 
						input);
				*produced_lexema++ 
					= lexeme;

				preprocessor_report_failure(
					"preprocess_pp_number",
					form,
					lexeme);

				fld.lexeme_length  
					= input - lexeme_start;
				*pp_number 
					= PreprocessingToken(
					      lexeme,
						  PreprocessingTokenName::ERROR,
						  fld,
						form);
				Error* error
					= construct_error_book(
						ErrorCode::ERR_PP_INVALID_PP_NUMBER,
						"This number could not be recognised. Did you mispell it?",
						fld);
				fld.character_number 
					+= (input - lexeme_start);

				exitcode = PreprocessorExitCode::FAILURE;
				conclusive = true;
				break;
			}
		}
		
	}
	return exitcode;
}

#define is_hex_digit(c) ((c >= '0' && c <= '9')		\
						 && (c >= 'a' && c <= 'f')	\
						 && (c >= 'A' && c <= 'F'))

/**
* Used to preprocess a character-constant.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param character_constant The reference to where to place
*        the produced character_constant pptoken.
**/
static inline PreprocessorExitCode pp_lex_character_constant(
	const char*            & input, 
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_output,
	AlertList              & bkl)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	const char* lexeme_start 
		= input;
	bool found_preprocess 
		= false;

	PreprocessingTokenForm form
		= PreprocessingTokenForm::UNDEFINED;

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
								} else {
									found_preprocess = false;
								}
							} else {
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

						default:
							break;
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
			= construct_lexeme(
				lexeme_start, 
				input);
		*produced_lexema++ 
			= lexeme;

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*identifier_output 
			= PreprocessingToken(
			      lexeme,
			      PreprocessingTokenName::CHARACTER_CONSTANT,
			      fld,
			      form);
		fld.character_number 
			+= (input - lexeme_start);

		exitcode = PreprocessorExitCode::SUCCESS;

	} else {
		const char* lexeme
			= construct_lexeme(
				  lexeme_start, 
			      input);		
		*produced_lexema++ 
			= lexeme;

		preprocessor_report_failure(
			"preprocess_pp_number",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*identifier_output 
			= PreprocessingToken(
			      lexeme,
			      PreprocessingTokenName::ERROR,
			      fld,
			      form);
		Error* error
			= construct_error_book(
				ErrorCode::ERR_PP_INVALID_CONSTANT,
				"This header name could not be recognised. Did you mispell it?",
				fld);
		fld.character_number 
			+= (input - lexeme_start);

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
static inline PreprocessorExitCode pp_lex_string_literal(
	const char*            & input, 
	const char**           & produced_lexema,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & string_literal,
	AlertList              & bkl)
{
	const char* lexeme_start 
		= input;
	bool found_preprocess 
		= false;

	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;
	PreprocessingTokenForm form
		= PreprocessingTokenForm::UNDEFINED;

	if (*input == 'L') {
		input++;

	} if (*input == '\"') {
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

					default:
						break;
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
		*produced_lexema++ 
			= lexeme;

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*string_literal = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::STRING_LITERAL,
			fld,
			form);
		fld.character_number 
			+= (input - lexeme_start);

		exitcode = PreprocessorExitCode::SUCCESS;

	} else {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);
		*produced_lexema++ = lexeme;

		preprocessor_report_failure(
			"preprocess_pp_number",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*string_literal = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);
		Error* error
			= construct_error_book(
				ErrorCode::ERR_PP_INVALID_STRING_LITERAL,
				"This string literal could not be recognised. Did you mispell it?",
				fld);
		fld.character_number 
			+= (input - lexeme_start);

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
static inline  PreprocessorExitCode pp_lex_punctuator(
	const char*            & input,
	const char**           & lexeme_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & punctuator,
	AlertList              & bkl)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	PreprocessingTokenForm form
		= PreprocessingTokenForm::UNDEFINED;

	bool found_punctuator 
		= false;	
	
	const char* lexeme_start 
		= input;

	switch (*input++) {
		
		case '[':
			form = PreprocessingTokenForm::OPEN_BRACKET;
			found_punctuator = true;
			break;

		case ']':
			form = PreprocessingTokenForm::CLOSE_BRACKET;
			found_punctuator = true;
			break;

		case '(':
			form = PreprocessingTokenForm::OPEN_PAREN;
			found_punctuator = true;
			break;

		case ')':
			form = PreprocessingTokenForm::CLOSE_PAREN;
			found_punctuator = true;
			break;

		case '{':
			form = PreprocessingTokenForm::OPEN_CURLY_BRACKET;
			found_punctuator = true;
			break;

		case '}':
			form = PreprocessingTokenForm::CLOSE_CURLY_BRACKET;
			found_punctuator = true;
			break;

		case '.':
			if (*input == '.' 
				&& *(input + 1) == '.') {
				input += 2;
				form = PreprocessingTokenForm::TRIPLE_DOT;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::DOT;
				found_punctuator = true;
			} 
			break;

		case '&':
			if (*input == '&') {
				input++;
				form = PreprocessingTokenForm::DOUBLE_AMPERSAND;
				found_punctuator = true;
				
			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::AMPERSAND_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::AMPERSAND;
				found_punctuator = true;
				break;
			}
			break;

		case '*':
			if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::MULTIPLY_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::ASTERIX;
				found_punctuator = true;
			}
			break;

		case '+':
			if (*input == '+') {
				input++;
				form = PreprocessingTokenForm::INCREMENT;
				found_punctuator = true;

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::PLUS_EQUALS;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::PLUS;
				found_punctuator = true;
			} 
			break;

		case '-':
			if (*input == '-') {
				input++;
				form = PreprocessingTokenForm::DECREMENT;
				found_punctuator = true;

			} else if (*input == '>') {
				input++;
				form = PreprocessingTokenForm::RIGHT_ARROW;
				found_punctuator = true;

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::MINUS_EQUALS;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::MINUS;
				found_punctuator = true;
			} 
			break;

		case '~':
			form = PreprocessingTokenForm::TILDE;
			found_punctuator = true;
			break;

		case '!':
			if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::NOT_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::EXCLAMATION_MARK;
				found_punctuator = true;
			}
			break;

		case '/':
			if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::DIVIDE_EQUALS;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::FORWARD_SLASH;
				found_punctuator = true;
			}
			break;

		case '#':
			if (*input == '#') {
				input++;
				form = PreprocessingTokenForm::DOUBLE_HASHTAG;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::HASHTAG;
				found_punctuator = true;
			}
			break;

		case '%':
			if (*input == '>' ) {
				input++;
				form = PreprocessingTokenForm::BIGRAPH_CLOSE_CURLY_BRACKET;
				found_punctuator = true;

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::MODULO_EQUALS;
				found_punctuator = true;

			} else if (*input == ':') {
				input++;
				if (*input == '%'
					&& *(input + 1) == ':') {
					input += 2;
					form = PreprocessingTokenForm::BIGRAPH_DOUBLE_HASHTAG;
					found_punctuator = true;

				} else {
					form = PreprocessingTokenForm::BIGRAPH_HASHTAG;
					found_punctuator = true;
				}

			} else {
				form = PreprocessingTokenForm::MODULO;
				found_punctuator = true;
			}
			break;

		case '<':
			if (*input == '<') {
				input++;
				if (*input == '=') {
					input++;
					form = PreprocessingTokenForm::LEFT_SHIFT_EQUALS;
					found_punctuator = true;

				} else {
					form = PreprocessingTokenForm::LEFT_SHIFT;
					found_punctuator = true;

				}

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::LESS_THAN_EQUAL;
				found_punctuator = true;

			} else if (*input == ':') {
				input++;
				form = PreprocessingTokenForm::BIGRAPH_OPEN_BRACKET;
				found_punctuator = true;

			} else if (*input == '%') {
				input++;
				form = PreprocessingTokenForm::BIGRAPH_OPEN_CURLY_BRACKET;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::LESS_THAN;
				found_punctuator = true;
			} 
			break;

		case '>':
			if (*input == '>') {
				input++;

				if (*input == '=') {
					input++;
					form = PreprocessingTokenForm::RIGHT_SHIFT_EQUALS;
					found_punctuator = true;

				} else {
					form = PreprocessingTokenForm::RIGHT_SHIFT;
					found_punctuator = true;
				}

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::GREATER_THAN_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::GREATER_THAN;
				found_punctuator = true;
			} 
			break;

		case '^':
			if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::XOR_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::XOR;
				found_punctuator = true;
			}
			break;

		case '|':
			if (*input == '|') {
				input++;
				form = PreprocessingTokenForm::DOUBLE_OR;
				found_punctuator = true;

			} else if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::OR_EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::OR;
				found_punctuator = true;
			}
			break;

		case '?':
			form = PreprocessingTokenForm::QUESTION_MARK;
			found_punctuator = true;
			break;

		case ':':
			if (*input == '>') {
				input++;
				form = PreprocessingTokenForm::BIGRAPH_CLOSE_BRACKET;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::COLON;
				found_punctuator = true;
			} 
			break;

		case ';':
			form = PreprocessingTokenForm::SEMI_COLON;
			found_punctuator = true;
			break;

		case '=':
			if (*input == '=') {
				input++;
				form = PreprocessingTokenForm::EQUAL;
				found_punctuator = true;

			} else {
				form = PreprocessingTokenForm::ASSIGN;
				found_punctuator = true;
			}
			break;

		case ',':
			form = PreprocessingTokenForm::COMMA;
			found_punctuator = true;
			break;

		default:
			break;
	};
	if (found_punctuator) {
		const char* lexeme
			= construct_lexeme(lexeme_start, input);
		*lexeme_pool++ 
			= lexeme;

		preprocessor_report_success(
			"preprocess_punctuator",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*punctuator = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::PUNCTUATOR,
			fld,
			form);
		fld.character_number 
			+= (input - lexeme_start);

		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		const char* lexeme
			= construct_lexeme(
				lexeme_start, 
				input);
		*lexeme_pool++ = lexeme;

		preprocessor_report_failure(
			"preprocess_punctuator",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*punctuator = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			form);
		const char* const error_msg
			= "This punctuator could not be recognised."
			  "Did you mispell it?";
		Error* error
			= construct_error_book(
				ErrorCode::ERR_PP_INVALID_PUNCTUATOR,
				error_msg,
				fld);
		fld.character_number 
			+= (input - lexeme_start);

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
static inline PreprocessorExitCode pp_parse_preprocessing_token(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & preprocessing_token)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	bool should_generate 
		= false;
	PreprocessingToken* token 
		= new PreprocessingToken();

	bool finished_preprocessed_word = false;
	while (!finished_preprocessed_word) {
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
				if (pp_lex_identifier_name(
					input,
					produced_lexema,
					file_location_descriptor,
					token,
					bkl)
					== PreprocessorExitCode::SUCCESS) {
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case 'L':
				if (*(input + 1) == '\"') {
					if (pp_lex_identifier_name(
						input,
						produced_lexema,
						file_location_descriptor,
						token,
						bkl) 
						== PreprocessorExitCode::SUCCESS) {
						finished_preprocessed_word = true;
						should_generate = true;
					}
				}
				else {
					if (pp_lex_string_literal(
						input,
						produced_lexema,
						file_location_descriptor,
						token,
						bkl) 
						== PreprocessorExitCode::SUCCESS) {
						finished_preprocessed_word = true;
						should_generate = true;
					}
				}
				break;

			case '1': case '2': case '3':
			case '4': case '5': case '6':
			case '7': case '8': case '9':
			case '0':
				if (pp_lex_pp_number(
					input,
					produced_lexema,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '\'':
				if (pp_lex_character_constant(
					input,
					produced_lexema,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '\"':
				if (pp_lex_string_literal(
					input,
					produced_lexema,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '/':
				if (*(input + 1) == '*') {
					input += 2;
					while ((*input != '*')
						|| (*(input + 1) != '/')) {
						input++;
					}
					input += 2;

				} else if (*(input + 1) == '/') {
					input += 2;
					while (*input != '\n') {
						input++;
					}
					input++;

				} else {
					if (pp_lex_punctuator(
						input,
						produced_lexema,
						file_location_descriptor,
						token,
						bkl) 
						== PreprocessorExitCode::SUCCESS) {
						finished_preprocessed_word = true;
						should_generate = true;
					}
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
				if (pp_lex_punctuator(
					input,
					produced_lexema,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '\\':
				input++;
				if (*input == '\n') {
					break;
				}
				break;

			case NULL:
			case EOF:
				*token = PreprocessingToken(
					_strdup(""),
					PreprocessingTokenName::END_OF_FILE,
					file_location_descriptor,
					PreprocessingTokenForm::UNDEFINED);				
				finished_preprocessed_word = true;
				break;

			default:
				finished_preprocessed_word = true;
				break;
		}
	}
	if (should_generate) {
		preprocessing_token
			= new PreprocessingAstNode(
				PreprocessingAstNodeName::PREPROCESSING_TOKEN,
				PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_1,
				token++);
		exitcode = PreprocessorExitCode::SUCCESS;
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
static inline PreprocessorExitCode pp_parse_pp_tokens(
	const char*                 & input,
	const char**                & produced_lexema,
	FileLocationDescriptor      & file_location_descriptor,
	PreprocessingAstNode*       & pp_tokens,
	AlertList                   & bkl,
	bool				   const& within_directive)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	enum ParsingState {
		START,
		PP_TOKENS
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

			case START:
			{
				bool terminated = false;
				while (!terminated) {
					switch (*input) {

						case '\n':
							file_location_descriptor.line_number++;
							file_location_descriptor.character_number = 0;
							terminated = true;
							break;

						case ' ':
							file_location_descriptor.character_number++;
							input++;
							break;

						case '\t':
							file_location_descriptor.character_number += 4;
							input++;
							break;

						case '\r':
							file_location_descriptor.character_number = 0;
							input++;
							break;

						default:
							PreprocessingAstNode* preprocessing_token;
							if (pp_parse_preprocessing_token(
								input,
								produced_lexema,
								file_location_descriptor,
								bkl,
								preprocessing_token)
								== PreprocessorExitCode::SUCCESS) {

								pp_tokens = new PreprocessingAstNode(
									PreprocessingAstNodeName::PP_TOKENS,
									PreprocessingAstNodeAlt::PP_TOKENS_1,
									NULL);
								pp_tokens->add_child(
									preprocessing_token);

								state = PP_TOKENS;
								exitcode = PreprocessorExitCode::SUCCESS;
							}
							terminated = true;
					}
				}
				if (state == PP_TOKENS) {
					continue;
				} else {
					break;
				} // TODO; mess fix this.
			}

			case PP_TOKENS:
			{				
				bool terminated = false;

				while (!terminated) {

					switch (*input) {

						case '\n':
							file_location_descriptor.line_number++;
							file_location_descriptor.character_number = 0;
							terminated = true;
							break;

						case ' ':
							file_location_descriptor.character_number++;
							input++;
							break;

						case '\t':
							file_location_descriptor.character_number += 4;
							input++;
							break;

						case '\r':
							file_location_descriptor.character_number = 0;
							input++;
							break;

						default:
							PreprocessingAstNode* preprocessing_token;
							if (pp_parse_preprocessing_token(
								input,
								produced_lexema,
								file_location_descriptor,
								bkl,
								preprocessing_token)
								== PreprocessorExitCode::SUCCESS) {

								PreprocessingAstNode* higher_pp_tokens;
								higher_pp_tokens
									= new PreprocessingAstNode(
										PreprocessingAstNodeName::PP_TOKENS,
										PreprocessingAstNodeAlt::PP_TOKENS_2,
										NULL);
								higher_pp_tokens->add_child(
									pp_tokens);
								higher_pp_tokens->add_child(
									preprocessing_token);
								pp_tokens =
									higher_pp_tokens;

							} else {
								terminated = true;
							}
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

static inline PreprocessorExitCode pp_parse_preprocessing_file(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & preprocessing_file)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	preprocessing_file = new PreprocessingAstNode(
		PreprocessingAstNodeName::PREPROCESSING_FILE,
		PreprocessingAstNodeAlt::PREPROCESSING_FILE_1,
		NULL);

	PreprocessingAstNode* group;
	if (pp_parse_group(
		input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		group)
		== PreprocessorExitCode::SUCCESS) {
		preprocessing_file->add_child(
			group);
	}

	exitcode = PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	enum ParsingState {
		START,
		GROUP
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

			case START:
			{
				PreprocessingAstNode* group_part;
				if (pp_parse_group_part(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					group_part)
					== PreprocessorExitCode::SUCCESS) {

					group = new PreprocessingAstNode(
						PreprocessingAstNodeName::GROUP,
						PreprocessingAstNodeAlt::GROUP_1,
						NULL);
					group->add_child(
						group_part);

					state = GROUP;
					exitcode = PreprocessorExitCode::SUCCESS;
					continue;
				}
				break;
			}

			case GROUP:
			{
				PreprocessingAstNode* group_part;
				if (pp_parse_group_part(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					group_part)
					== PreprocessorExitCode::SUCCESS) {

					PreprocessingAstNode* higher_group;
					higher_group
						= new PreprocessingAstNode(
							PreprocessingAstNodeName::GROUP,
							PreprocessingAstNodeAlt::GROUP_2,
							NULL);
					higher_group->add_child(
						group);
					higher_group->add_child(
						group_part);
					group =
						higher_group;

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

static inline PreprocessorExitCode pp_parse_group_part(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group_part)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	const char* backtrack_ptr = input;

	PreprocessingAstNode* stack[16];
	int si = 0;

	PreprocessingAstNodeAlt alt
		= PreprocessingAstNodeAlt::ERROR;

	bool should_generate = false;

	if (*input == '#') {

		PreprocessingAstNode* if_section;
		PreprocessingAstNode* control_line;
		PreprocessingAstNode* non_directive;
		PreprocessingAstNode* pp_token;
		if (pp_parse_if_section(
				input, 
				produced_lexema,
				file_location_descriptor,
				bkl,
				if_section)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = if_section;

			alt = PreprocessingAstNodeAlt::GROUP_PART_1;
			should_generate = true;

		} else if (pp_parse_control_line(
			           input,
			           produced_lexema,
			           file_location_descriptor,
			           bkl, 
			           control_line)
			       == PreprocessorExitCode::SUCCESS) {
			stack[si++] = control_line;

			alt = PreprocessingAstNodeAlt::GROUP_PART_2;
			should_generate = true;

		} else if (pp_parse_preprocessing_token(
			           input,
			           produced_lexema,
			           file_location_descriptor,
			           bkl, 
			           pp_token)
			       == PreprocessorExitCode::SUCCESS) {

			if ((pp_token->get_name() 
				== PreprocessingAstNodeName::PREPROCESSING_TOKEN)
				&& (pp_token->get_terminal()->get_form() 
				   == PreprocessingTokenForm::HASHTAG)) {
				
				if (pp_parse_non_directive(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					non_directive)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = non_directive;

					alt = PreprocessingAstNodeAlt::GROUP_PART_4;
					should_generate = true;
				}
			}
		}

	} else {

		PreprocessingAstNode* text_line;
		if (pp_parse_text_line(
				input,
				produced_lexema,
				file_location_descriptor,
				bkl, 
				text_line)
				== PreprocessorExitCode::SUCCESS) {
			stack[si++] = text_line;

			alt = PreprocessingAstNodeAlt::GROUP_PART_3;
			should_generate = true;

		}
	}
	if (should_generate) {
		group_part = construct_node_from_children(
			PreprocessingAstNodeName::GROUP_PART,
			alt,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = backtrack_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_if_section(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_section)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	PreprocessingAstNode* if_group;
	if (pp_parse_if_group(
		input, 
		produced_lexema,
		file_location_descriptor,
		bkl, 
		if_group)
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = if_group;

		PreprocessingAstNode* elif_groups;
		if (pp_parse_elif_groups(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl, 
			elif_groups)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = elif_groups;
		}

		PreprocessingAstNode* else_group;
		if (pp_parse_else_group(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl, 
			else_group)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = else_group;
		}

		PreprocessingAstNode* endif_line;
		if (pp_parse_endif_line(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl, 
			endif_line)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = endif_line;
			should_generate = true;
		}
	}
	if (should_generate) {
		if_section = construct_node_from_children(
			PreprocessingAstNodeName::IF_SECTION,
			PreprocessingAstNodeAlt::IF_SECTION_1,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_if_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	const char* back_track_ptr 
		= input;

	PreprocessingAstNodeAlt alt;
	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	PreprocessingAstNode* preprocessing_token_1;
	if (pp_parse_preprocessing_token(
		input, 
		produced_lexema, 
		file_location_descriptor, 
		bkl, 
		preprocessing_token_1) 
		== PreprocessorExitCode::SUCCESS
		&& preprocessing_token_1->get_terminal()->get_name() 
		   == PreprocessingTokenName::PUNCTUATOR
		&& preprocessing_token_1->get_terminal()->get_form() 
		   == PreprocessingTokenForm::HASHTAG) {
		stack[si++] = preprocessing_token_1;

		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) == PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()
			                        ->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			stack[si++] = preprocessing_token_2;

			const char* lexeme 
				= preprocessing_token_2->get_terminal()
				                       ->get_lexeme();
			if (strcmp(lexeme, "if") == 0) {

				PreprocessingAstNode* constant_expression;
				if (pp_parse_constant_expression(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl,
					constant_expression)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = constant_expression;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl, 
						new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input,
							produced_lexema,
							file_location_descriptor,
							bkl, 
							group)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = group;
						}
						alt = PreprocessingAstNodeAlt::IF_GROUP_1;
						should_generate = true;
					}
				}

			} else if (strcmp(lexeme, "ifdef") == 0) {

				PreprocessingAstNode* preprocessing_token;
				if (pp_parse_preprocessing_token(input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					preprocessing_token) 
					== PreprocessorExitCode::SUCCESS) {
					stack[si++];

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl, 
						new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input,
							produced_lexema,
							file_location_descriptor,
							bkl, 
							group) 
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = group;
						}
						alt = PreprocessingAstNodeAlt::IF_GROUP_2;
						should_generate = true;
					}
				}

			} else if (strcmp(lexeme, "ifndef") == 0) {

				PreprocessingAstNode* preprocessing_token;
				if (pp_parse_preprocessing_token(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl, 
					preprocessing_token) 
					== PreprocessorExitCode::SUCCESS
					&& (preprocessing_token->get_terminal()
					                       ->get_name() 
					   == PreprocessingTokenName::IDENTIFIER)) {
					stack[si++];

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl, 
						new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input,
							produced_lexema,
							file_location_descriptor,
							bkl, 
							group) 
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = group;
						}
						alt = PreprocessingAstNodeAlt::IF_GROUP_3;
						should_generate = true;
					}
				}

			} else {

			}
		}
	}
	if (should_generate) {
		if_group = construct_node_from_children(
			PreprocessingAstNodeName::IF_GROUP,
			alt,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = back_track_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_elif_groups(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_groups)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;
	const char* backtrack_ptr 
		= input;

	PreprocessingAstNode* stack[16];
	int si = 0;

	bool should_generate = false;

	enum ParsingState {
		START,
		ELIF_GROUP
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

			case START:
			{
				PreprocessingAstNode* elif_group;
				if (pp_parse_elif_group(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					elif_group)
					== PreprocessorExitCode::SUCCESS) {

					elif_groups = new PreprocessingAstNode(
						PreprocessingAstNodeName::ELIF_GROUPS,
						PreprocessingAstNodeAlt::ELIF_GROUPS_1,
						NULL);
					elif_groups->add_child(
						elif_group);

					state = ELIF_GROUP;
					exitcode = PreprocessorExitCode::SUCCESS;
					continue;
				}
				break;
			}

			case ELIF_GROUP:
			{
				PreprocessingAstNode* elif_group;
				if (pp_parse_elif_group(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					elif_group)
					== PreprocessorExitCode::SUCCESS) {

					PreprocessingAstNode* higher_elif_groups
						= new PreprocessingAstNode(
							PreprocessingAstNodeName::ELIF_GROUPS,
							PreprocessingAstNodeAlt::ELIF_GROUPS_2,
							NULL);
					higher_elif_groups->add_child(
						elif_groups);
					higher_elif_groups->add_child(
						elif_group);
					elif_groups =
						higher_elif_groups;
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

static inline PreprocessorExitCode pp_parse_identifier_list(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & identifier_list)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	enum ParsingState {
		START,
		IDENTIFIER_LIST
	};

	ParsingState state = START;
	while (true) {

		switch (state) {

			case START:
			{
				PreprocessingAstNode* preprocessing_token;
				if (pp_parse_preprocessing_token(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					preprocessing_token) 
					== PreprocessorExitCode::SUCCESS) {

					identifier_list = new PreprocessingAstNode(
						PreprocessingAstNodeName::IDENTIFIER_LIST,
						PreprocessingAstNodeAlt::IDENTIFIER_LIST_1,
						NULL);
					identifier_list->add_child(
						preprocessing_token);

					state = IDENTIFIER_LIST;
					exitcode = PreprocessorExitCode::SUCCESS;
					continue;

				}
				break;
			}

			case IDENTIFIER_LIST:
			{
				PreprocessingAstNode* preprocessing_token;
				if (pp_parse_preprocessing_token(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					preprocessing_token)
					== PreprocessorExitCode::SUCCESS) {

					PreprocessingAstNode* preprocessing_token;
					if (pp_parse_preprocessing_token(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl,
						preprocessing_token)
						== PreprocessorExitCode::SUCCESS) {

						PreprocessingAstNode* higher_identifier_list;
						higher_identifier_list = new PreprocessingAstNode(
							PreprocessingAstNodeName::IDENTIFIER_LIST,
							PreprocessingAstNodeAlt::IDENTIFIER_LIST_2,
							NULL);
						higher_identifier_list->add_child(
							identifier_list);
						higher_identifier_list->add_child(
							preprocessing_token);
						identifier_list =
							higher_identifier_list;

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

//PreprocessingToken preprocessing_tokens[16]
//= { };
//PreprocessingToken* preprocessing_tokens_ptr
//= preprocessing_tokens;
//
///* Get the Tokens within the conditional expression. */
//pp_gen_pp_tokens(
//	pp_ast_pp_tokens,
//	preprocessing_tokens_ptr,
//	bkl);
//int num_preprocessing_tokens
//= preprocessing_tokens_ptr - preprocessing_tokens;
//
//preprocessing_tokens_ptr
//= preprocessing_tokens;
//Token tokens[16]
//= { };
//Token* tokens_ptr
//= tokens;
//
//lex(
//	preprocessing_tokens_ptr,
//	tokens_ptr,
//	num_preprocessing_tokens,
//	bkl);
//
///* Get the Abstract Syntax Tree associated
//	with the conditional expression. */
//const Token* new_tokens_ptr
//= tokens;
//AstNode* ast_constant_expression;
//parse_constant_expression(
//	NULL,
//	new_tokens_ptr,
//	ast_constant_expression);
//
///* Annotate the abstract syntax tree associated
//	with the conditional expression. */
//AnnotatedAstNode* anno_ast_constant_expression;
//construct_unatrributed_annotated_ast(
//	ast_constant_expression,
//	anno_ast_constant_expression);
//SymbolTable* symtab = new SymbolTable();
//visit_constant_expression_1(
//	anno_ast_constant_expression,
//	symtab);
//
//uint64_t constant_expression_val
//= 0;
//constant_expression_val
//= anno_ast_constant_expression->get_constant_val()
//!= 0;

static inline PreprocessorExitCode pp_parse_constant_expression(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & constant_expression)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNodeAlt alt;

	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	/* Get the Preprocessing tokens within 
		the conditional expression. */
	PreprocessingAstNode* pp_ast_pp_tokens; 
	if (pp_parse_pp_tokens(
		input,
		produced_lexema,
		file_location_descriptor,
		pp_ast_pp_tokens,
		bkl,
		true) 
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = pp_ast_pp_tokens;

		constant_expression
			= construct_node_from_children(
				PreprocessingAstNodeName::CONSTANT_EXPRESSION,
				PreprocessingAstNodeAlt::CONSTANT_EXPRESSION_1,
				stack,
				si);
		exitcode = PreprocessorExitCode::SUCCESS;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_elif_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	const char* backtrack_ptr 
		= input;

	PreprocessingAstNodeAlt alt;

	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	PreprocessingAstNode* preprocessing_token_1;
	if (pp_parse_preprocessing_token(
		input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		preprocessing_token_1) 
		== PreprocessorExitCode::SUCCESS
		&& preprocessing_token_1->get_terminal()->get_name() 
		   == PreprocessingTokenName::PUNCTUATOR
		&& preprocessing_token_1->get_terminal()->get_form() 
		   == PreprocessingTokenForm::HASHTAG) {
		stack[si++] = preprocessing_token_1;

		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) 
			== PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()
			                        ->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			stack[si++] = preprocessing_token_2;

			const PreprocessingToken* const terminal
				= preprocessing_token_2->get_terminal();

			const char* const lexeme
				= terminal->get_lexeme();

			if (strcmp(lexeme, "elif") == 0) {

				PreprocessingAstNode* constant_expression;
				if (pp_parse_constant_expression(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl, 
					constant_expression)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = constant_expression;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input, 
						produced_lexema,
						file_location_descriptor,
						bkl, 
						new_line) == PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input, 
							produced_lexema,
							file_location_descriptor,
							bkl, 
							group)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = group;
						}
						alt = PreprocessingAstNodeAlt::ELIF_GROUP_1;
						should_generate = true;
					}
				}
			}
		}
	}
	if (should_generate) {
		elif_group = construct_node_from_children(
			PreprocessingAstNodeName::ELIF_GROUP,
			PreprocessingAstNodeAlt::ELIF_GROUP_1,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = backtrack_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_else_group(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & else_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	const char* backtrack_ptr 
		= input;

	PreprocessingTokenForm alt;

	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate 
		= false;

	PreprocessingAstNode* preprocessing_token_1;
	if (pp_parse_preprocessing_token(
		input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		preprocessing_token_1) 
		== PreprocessorExitCode::SUCCESS
		&& (preprocessing_token_1->get_terminal()->get_name()
		    == PreprocessingTokenName::PUNCTUATOR)
		&& (preprocessing_token_1->get_terminal()->get_form()
		    == PreprocessingTokenForm::HASHTAG)) {
		stack[si++] = preprocessing_token_1;

		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) 
			== PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			stack[si++] = preprocessing_token_2;


			const PreprocessingToken* const terminal
				= preprocessing_token_2->get_terminal();
			const char* lexeme 
				= terminal->get_lexeme();

			if (strcmp(lexeme, "else") == 0) {

				PreprocessingAstNode* new_line;
				if (pp_parse_new_line(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl, 
					new_line) == PreprocessorExitCode::SUCCESS) {
					stack[si++] = new_line;

					PreprocessingAstNode* group;
					if (pp_parse_group(
						input, produced_lexema,
						file_location_descriptor,
						bkl, 
						group)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = group;
					}
					should_generate = true;
				}
			}
		}
	}
	if (should_generate) {
		else_group = construct_node_from_children(
			PreprocessingAstNodeName::ELSE_GROUP,
			PreprocessingAstNodeAlt::ELSE_GROUP_1,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = backtrack_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_endif_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & endif_line)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	bool should_generate 
		= false;

	PreprocessingAstNode* stack[16];
	int si = 0;

	PreprocessingAstNode* preprocessing_token_1;
	if (pp_parse_preprocessing_token(
		input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		preprocessing_token_1) 
		== PreprocessorExitCode::SUCCESS
		&& (preprocessing_token_1->get_terminal()->get_name()
		    == PreprocessingTokenName::PUNCTUATOR)
		&& (preprocessing_token_1->get_terminal()->get_form()
		    == PreprocessingTokenForm::HASHTAG)) {
		stack[si++] = preprocessing_token_1;

		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) 
			== PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()
			                        ->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			stack[si++] = preprocessing_token_2;

			const PreprocessingToken* const terminal
				= preprocessing_token_2->get_terminal();
			const char* const lexeme 
				= terminal->get_lexeme();

			if (strcmp(lexeme, "endif") == 0) {

				PreprocessingAstNode* new_line;
				if (pp_parse_new_line(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl, new_line) == PreprocessorExitCode::SUCCESS) {

					endif_line
						= new PreprocessingAstNode(
							PreprocessingAstNodeName::ENDIF_LINE,
							PreprocessingAstNodeAlt::ENDIF_LINE_1,
							NULL);
					endif_line->add_child(new_line);
					exitcode = PreprocessorExitCode::SUCCESS;
				}
			}
		}
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_control_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & control_line)
{	
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* stack[16];
	const char* backtrack_ptr 
		= input;

	int si = 0;

	bool should_generate = false;

	PreprocessingAstNodeAlt alt;

	PreprocessingAstNode* preprocessing_token;
	if (pp_parse_preprocessing_token(
		input, 
		produced_lexema, 
		file_location_descriptor, 
		bkl, 
		preprocessing_token) 
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = preprocessing_token;

		Directives dir;
		PreprocessingAstNode* new_line;
		PreprocessingAstNode* preprocessing_token_1;
		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) 
			== PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			stack[si++] = preprocessing_token_2;

			const PreprocessingToken* const terminal
				= preprocessing_token_2->get_terminal();
			const char* const lexeme 
				= terminal->get_lexeme();

			if (strcmp(lexeme, "include") == 0) {

				PreprocessingAstNode* pp_tokens;
				if (pp_parse_pp_tokens(
					input,
					produced_lexema,
					file_location_descriptor,
					pp_tokens,
					bkl,
					true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl,
						new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						should_generate = true;
						alt = PreprocessingAstNodeAlt::CONTROL_LINE_1;
					}
				}
			
			} else if (strcmp(lexeme, "define") == 0) {

				PreprocessingAstNode* identifier;
				if (pp_parse_preprocessing_token(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl,
					identifier)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = identifier;

					PreprocessingAstNode* replacement_list;
					PreprocessingAstNode* lparen;
					if (pp_parse_replacement_list(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl,
						replacement_list)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = replacement_list;

						PreprocessingAstNode* new_line;
						if (pp_parse_new_line(
							input,
							produced_lexema,
							file_location_descriptor,
							bkl, 
							new_line)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = new_line;

							should_generate = true;
							alt = PreprocessingAstNodeAlt::CONTROL_LINE_2;
						}

					} else if (pp_parse_lparen(
						input,
						produced_lexema,
						file_location_descriptor,
						bkl,
						lparen)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = lparen;

						PreprocessingAstNode* identifier_list;
						if (pp_parse_identifier_list(
							input,
							produced_lexema,
							file_location_descriptor,
							bkl, 
							identifier_list)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = identifier_list;

							if (*input == ','
								&& *(input + 1) == '.'
								&& *(input + 2) == '.'
								&& *(input + 3) == '.' 
								&& *(input + 4) == ')') {
								input += 5;

								if (pp_parse_replacement_list(
									input,
									produced_lexema,
									file_location_descriptor,
									bkl, 
									replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(input,
										produced_lexema,
										file_location_descriptor,
										bkl,
										new_line) 
										== PreprocessorExitCode::SUCCESS) {
										stack[si++] = new_line;

										should_generate = true;
										alt = PreprocessingAstNodeAlt::CONTROL_LINE_4;
									}
								}

							} else if (*input == ')') {
								input++;

								if (pp_parse_replacement_list(
									input,
									produced_lexema,
									file_location_descriptor,
									bkl, 
									replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
										input,
										produced_lexema,
										file_location_descriptor,
										bkl, 
										new_line) 
										== PreprocessorExitCode::SUCCESS) {
										stack[si++] = new_line;

										should_generate = true;
										alt = PreprocessingAstNodeAlt::CONTROL_LINE_3;
									}
								}
							}

						} else {

							if (*input == '.'
								&& *(input + 1) == '.'
								&& *(input + 2) == '.'
								&& *(input + 3) == ')') {
								input += 4;

								PreprocessingAstNode* replacement_list;
								if (pp_parse_replacement_list(
									input,
									produced_lexema,
									file_location_descriptor,
									bkl, 
									replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
										input,
										produced_lexema,
										file_location_descriptor,
										bkl,
										new_line) 
										== PreprocessorExitCode::SUCCESS) {
										stack[si++] = new_line;

										should_generate = true;
										alt = PreprocessingAstNodeAlt::CONTROL_LINE_4;
									}
								}
							}

							if (*input == ')') {
								input++;

								if (pp_parse_replacement_list(
									input,
									produced_lexema, 
									file_location_descriptor,
									bkl,
									replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
											input,
											produced_lexema,
											file_location_descriptor,
											bkl,
											new_line)
										== PreprocessorExitCode::FAILURE) {
										stack[si++] = new_line;

										should_generate = true;
										alt = PreprocessingAstNodeAlt::CONTROL_LINE_3;
									}
								}
							}
						}
						PreprocessingAstNode* replacement_list;
						if (pp_parse_replacement_list(input,
							produced_lexema,
							file_location_descriptor,
							bkl,
							replacement_list)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = replacement_list;

							PreprocessingAstNode* new_line;
							if (pp_parse_new_line(
								input,
								produced_lexema,
								file_location_descriptor,
								bkl,
								new_line)
								== PreprocessorExitCode::SUCCESS) {
								stack[si++] = new_line;

							}
						}

					} else if (*input == '.'
						       && *(input + 1) == '.'
						       && *(input + 2) == '.') {
					}
				}

			} else if (strcmp(lexeme, "undef") == 0) {
				
				PreprocessingAstNode* preprocessing_token;
				if (pp_parse_preprocessing_token(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl, 
					preprocessing_token)
					== PreprocessorExitCode::SUCCESS
					&& preprocessing_token->get_terminal()->get_name() 
						== PreprocessingTokenName::IDENTIFIER) {
					stack[si++] = preprocessing_token;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input, 
						produced_lexema,
						file_location_descriptor,
						bkl,
						new_line)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						should_generate = true;
						alt = PreprocessingAstNodeAlt::CONTROL_LINE_6;
					}
				}

			} else if (strcmp(lexeme, "line") == 0) {

				PreprocessingAstNode* pp_tokens;
				if (pp_parse_pp_tokens(
					input, 
					produced_lexema,
					file_location_descriptor,
					pp_tokens,
					bkl,
					true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input, 
						produced_lexema,
						file_location_descriptor,
						bkl, new_line)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						should_generate = true;
						alt = PreprocessingAstNodeAlt::CONTROL_LINE_7;
					}
				}
			
			} else if (strcmp(lexeme, "error") == 0) {

				PreprocessingAstNode* pp_tokens;
				if (pp_parse_pp_tokens(
					input, 
					produced_lexema,
					file_location_descriptor,
					pp_tokens,
					bkl,
					true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;
				}
				PreprocessingAstNode* new_line;
				if (pp_parse_new_line(
					input,
					produced_lexema,
					file_location_descriptor,
					bkl, 
					new_line)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = new_line;

					should_generate = true;
					alt = PreprocessingAstNodeAlt::CONTROL_LINE_8;
				}

			} else if (strcmp(lexeme, "pragma") == 0) {

				PreprocessingAstNode* pp_tokens;
				if (pp_parse_pp_tokens(
					input,
					produced_lexema,
					file_location_descriptor,
					pp_tokens,
					bkl,
					true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;
				}
				PreprocessingAstNode* new_line;
				if (pp_parse_new_line(
					input, 
					produced_lexema,
					file_location_descriptor,
					bkl, new_line)
					== PreprocessorExitCode::SUCCESS) {
					should_generate = true;
					alt = PreprocessingAstNodeAlt::CONTROL_LINE_9;
				}
			}

		} else if (pp_parse_new_line(
			           input,
			           produced_lexema,
			           file_location_descriptor,
			           bkl, 
			           new_line) 
			       == PreprocessorExitCode::SUCCESS) {

			PreprocessingAstNode* new_line;
			if (pp_parse_new_line(
				input,
				produced_lexema,
				file_location_descriptor,
				bkl, 
				new_line)
				== PreprocessorExitCode::SUCCESS) {
				stack[si++] = new_line;

				should_generate = true;
				alt = PreprocessingAstNodeAlt::CONTROL_LINE_10;
			}
		}
	}
	if (should_generate) {
		control_line = construct_node_from_children(
			PreprocessingAstNodeName::CONTROL_LINE,
			alt,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = backtrack_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_text_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & text_line)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* stack[16];
	int si = 0;

	PreprocessingAstNode* pp_tokens;
	if (pp_parse_pp_tokens(
		input,
		produced_lexema,
		file_location_descriptor,
		pp_tokens,
		bkl,
		false)
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = pp_tokens;
	}
	PreprocessingAstNode* new_line;
	if (pp_parse_new_line(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			new_line)
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = new_line;

		text_line
			= construct_node_from_children(
			      PreprocessingAstNodeName::TEXT_LINE,
				  PreprocessingAstNodeAlt::TEXT_LINE_1,
				  stack,
				  si);
		exitcode = PreprocessorExitCode::SUCCESS;

	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_new_line(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & new_line)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	PreprocessingAstNode* preprocessing_token;
	if (*input == '\n') {
		new_line = new PreprocessingAstNode(
			PreprocessingAstNodeName::NEW_LINE,
			PreprocessingAstNodeAlt::NEW_LINE_1,
			NULL);
		input++;
		exitcode = PreprocessorExitCode::SUCCESS;
	}
	return exitcode;
}

static inline bool is_directive(
	const char* input)
{
	bool retval = false;
	if (*input == 'i') {

		if (*(input + 1) == 'f') {

			if (*(input + 2) == ' '
				|| *(input + 2) == '\t'
				|| *(input + 3) == '\n') {
				retval = true;

			} else if (
				*(input + 2) == 'd'
				&& *(input + 3) == 'e'
				&& *(input + 4) == 'f'
				&& (*(input + 5) == ' ' 
					|| *(input + 5) == '\t')
				    || *(input + 5) == '\n') {
				retval = true;

			} else if (
				*(input + 2) == 'n'
				&& *(input + 3) == 'd'
				&& *(input + 4) == 'e'
				&& *(input + 5) == 'f'
				&& (*(input + 6) == ' '
					|| *(input + 6) == '\t')
				    || *(input + 3) == '\n') {
				retval = true;
			
			} else {
				
			}

		} else if (
			*(input + 1) == 'n' 
			&& *(input + 2) == 'c' 
			&& *(input + 3) == 'l' 
			&& *(input + 4) == 'u' 
			&& *(input + 5) == 'd' 
			&& *(input + 6) == 'e' 
			&& (*(input + 7) == ' ' 
				|| (*input + 7) == '\t')
			    || *(input + 7) == '\n') {
			retval = true;

		} else {

		}

	} else if (*input == 'e') {

		if (*(input + 1) == 'l') {

			if (*(input + 2) == 'i'
				&& *(input + 3) == 'f'
				&& (*(input + 4) == ' '
					|| *(input + 4) == '\t')
				    || *(input + 4) == '\n') {
				retval = true;

			} else if (*(input + 2) == 's'
				    && *(input + 3) == 'e'
				    && (*(input + 4) == ' '
					    || *(input + 4) == '\t')
				        || *(input + 4) == '\n') {
				retval = true;

			} else {

			}

		} else if (
			*(input + 1) == 'n'
			&& *(input + 2) == 'd'
			&& *(input + 3) == 'i'
			&& *(input + 4) == 'f'
			&& (*(input + 5) == ' '
				|| *(input + 5) == '\t')
			    || *(input + 5) == '\n') {
			retval = true;
		}

	} else if (
		*input == 'd'
		&& *(input + 1) == 'e'
		&& *(input + 2) == 'f'
		&& *(input + 3) == 'i'
		&& *(input + 4) == 'n'
		&& *(input + 5) == 'e'
		&& (*(input + 6) == ' '
		    || *(input + 6) == '\t')
		    || *(input + 6) == '\n') {
			retval = true;

	} else if (
		*input == 'u'
		&& *(input + 1) == 'd'
		&& *(input + 2) == 'e'
		&& *(input + 3) == 'f'
		&& (*(input + 4) == ' '
		    || *(input + 4) == '\t')
		    || *(input + 4) == '\n') {
		retval = true;

	} else if (
		*input == 'l'
		&& *(input + 1) == 'i'
		&& *(input + 2) == 'n'
		&& *(input + 3) == 'e'
		&& (*(input + 4) == ' '
		    || *(input + 4) == '\t')
		    || *(input + 4) == '\n') {
		retval = true;

	} else if (
		*input == 'p'
		&& *(input + 1) == 'r'
		&& *(input + 2) == 'a'
		&& *(input + 3) == 'g'
		&& *(input + 4) == 'm'
		&& *(input + 5) == 'a'
		&& (*(input + 6) == ' '
		    || *(input + 6) == '\t')
		    || *(input + 6) == '\n') {
		retval = true;

	} else {

	}
	return retval;
}

static inline PreprocessorExitCode pp_parse_non_directive(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & non_directive)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	const char* backtrack_ptr = input;

	bool should_generate 
		= false;

	PreprocessingAstNode* stack[16];
	int si = 0;

	PreprocessingAstNode* pp_tokens;
	if (!is_directive(input) 
		&& pp_parse_pp_tokens(
		       input,
		       produced_lexema,
		       file_location_descriptor,
		       pp_tokens,
		       bkl,
		       false)
		   == PreprocessorExitCode::SUCCESS) {
		stack[si++] = pp_tokens;

		PreprocessingAstNode* new_line;
		if (pp_parse_new_line(
			input,
			produced_lexema,
			file_location_descriptor,
			bkl,
			new_line)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = new_line;
			should_generate = true;
		}
	}
	if (should_generate) {
		non_directive = construct_node_from_children(
			PreprocessingAstNodeName::NON_DIRECTIVE,
			PreprocessingAstNodeAlt::NON_DIRECTIVE_1,
			stack,
			si);
		exitcode = PreprocessorExitCode::SUCCESS;
	} else {
		/* Free unused ast nodes generated. */
		pp_free_stack(stack, si);
		input = backtrack_ptr;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_lparen(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & lparen)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* preprocessing_token;
	if (pp_parse_preprocessing_token(input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		preprocessing_token)
		== PreprocessorExitCode::SUCCESS) {
		lparen = new PreprocessingAstNode(
			PreprocessingAstNodeName::LPAREN,
			PreprocessingAstNodeAlt::LPAREN_1,
			NULL);
		lparen->add_child(
			preprocessing_token);
		exitcode = PreprocessorExitCode::SUCCESS;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_replacement_list(
	const char*            & input,
	const char**           & produced_lexema,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & replacement_list)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	replacement_list = new PreprocessingAstNode(
		PreprocessingAstNodeName::PP_TOKENS,
		PreprocessingAstNodeAlt::PP_TOKENS_1,
		NULL);
	PreprocessingAstNode* pp_tokens;
	if (pp_parse_pp_tokens(
		input,
		produced_lexema,
		file_location_descriptor,
		pp_tokens,		
		bkl,
		false)
		== PreprocessorExitCode::SUCCESS) {
		replacement_list->add_child(
			pp_tokens);
	}
	exitcode = PreprocessorExitCode::SUCCESS;

	return exitcode;
}

static inline PreprocessorExitCode pp_execute_preprocessing_file(
	PreprocessingAstNode* & preprocessing_file,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_group(
	PreprocessingAstNode* & group,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_group_part(
	PreprocessingAstNode* & group_part,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_if_section(
	PreprocessingAstNode* & if_section,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_if_group(
	PreprocessingAstNode* & if_group,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_elif_groups(
	PreprocessingAstNode* & elif_groups,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_identifier_list(
	PreprocessingAstNode* & identifier_list,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_constant_expression(
	PreprocessingAstNode* & constant_expression,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	return exitcode;
}

static inline PreprocessorExitCode pp_execute_elif_group(
	PreprocessingAstNode* & elif_group,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_else_group(
	PreprocessingAstNode* & else_group,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_endif_line(
	PreprocessingAstNode* & endif_line,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_control_line(
	PreprocessingAstNode* & control_line,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

		case PreprocessingAstNodeAlt::CONTROL_LINE_1:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_2:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_3:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_4:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_5:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_6:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_7:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_8:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_9:
			break;

		case PreprocessingAstNodeAlt::CONTROL_LINE_10:
			break;
	
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_text_line(
	PreprocessingAstNode* & text_line,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_new_line(
	PreprocessingAstNode* & new_line,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_non_directive(
	PreprocessingAstNode* & non_directive,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_lparen(
	PreprocessingAstNode* & lparen,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_execute_replacement_list(
	PreprocessingAstNode* & replacement_list,
	const char**          & produced_lexema,
	AlertList             & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_preprocessing_file(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	
	PreprocessingAstNode* group 
		= preprocessing_file->get_child();
	if (group) {
		 pp_gen_group(
			 group, 
			 output, 
			 bkl);
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_group(
	PreprocessingAstNode* const& group,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	switch (group->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_1:
		{
			PreprocessingAstNode* group_part
				= group->get_child();
			pp_gen_group_part(
				group_part,
				output,
				bkl);
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_2:
		{
			PreprocessingAstNode* lesser_group
				= group->get_child();
			PreprocessingAstNode* group_part
				= lesser_group->get_sibling();
			pp_gen_group(
				lesser_group,
				output,
				bkl);
			pp_gen_group_part(
				group_part,
				output,
				bkl);
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_group_part(
	PreprocessingAstNode* const& group_part,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (group_part->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_PART_1:
		{
			PreprocessingAstNode* if_section
				= group_part->get_child();
			pp_gen_if_section(
				if_section,
				output,
				bkl);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_2:
		{
			PreprocessingAstNode* control_line
				= group_part->get_child();
			pp_gen_control_line(
				control_line,
				output,
				bkl);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_3:
		{
			PreprocessingAstNode* text_line
				= group_part->get_child();
			pp_gen_text_line(
				text_line,
				output,
				bkl);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_4:
		{
			PreprocessingAstNode* non_directive
				= group_part->get_child();
			pp_gen_non_directive(
				non_directive,
				output,
				bkl);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_if_section(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_elif_groups(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_elif_group(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_else_group(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_endif(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_control_line(
	PreprocessingAstNode* const& control_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

		case PreprocessingAstNodeAlt::CONTROL_LINE_1:
		{
			/* Inclusion Logic. TODO; */
			PreprocessingAstNode* pp_tokens
				= control_line->get_child();
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_2:
		{
			/* Define Logic. TODO; */
			break;
		}
		
		case PreprocessingAstNodeAlt::CONTROL_LINE_3:
		{
			/* Define Logic. TODO;*/
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_4:
		{
			/* Define Logic. TODO;*/
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_5:
		{
			/* Define logic. TODO. */
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_6:
		{	
			/* Undef Logic. TODO; */
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_7:
		{
			/* Line Logic. TODO; */
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_8:
		{
			/* Error Logic. TODO; */
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_9:
		{
			/* Pragma Logic. TODO; */
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_10:
		{
			exitcode = PreprocessorExitCode::SUCCESS;
			break; 
		}

		default:
			break;

	}
	//TODO;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_text_line(
	PreprocessingAstNode* const& text_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* pp_tokens
		= text_line->get_child();
	if (pp_tokens) {
		pp_gen_pp_tokens(
			pp_tokens,
			output,
			bkl);
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_non_directive(
	PreprocessingAstNode* const& non_directive,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* pp_tokens 
		= non_directive->get_child();
	pp_gen_pp_tokens(
		pp_tokens,
		output,
		bkl);

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_lparen(
	PreprocessingAstNode* const& lparen,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* preprocessing_token
		= lparen->get_child();
	if (preprocessing_token) {
		pp_gen_preprocessing_token(
			preprocessing_token,
			output,
			bkl);
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_replacement_list(
	PreprocessingAstNode* const& replacement_list,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* pp_tokens
		= replacement_list->get_child();
	if (pp_tokens) {
		pp_gen_pp_tokens(
			pp_tokens, 
			output, 
			bkl);
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_pp_tokens(
	PreprocessingAstNode* const& pp_tokens,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (pp_tokens->get_alt()) {

		case PreprocessingAstNodeAlt::PP_TOKENS_1:
		{
			PreprocessingAstNode* preprocessing_token
				= pp_tokens->get_child();
			pp_gen_preprocessing_token(
				preprocessing_token,
				output,
				bkl);
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::PP_TOKENS_2:
		{
			PreprocessingAstNode* lesser_pp_tokens
				= pp_tokens->get_child();
			PreprocessingAstNode* preprocessing_token
				= lesser_pp_tokens->get_sibling();
			pp_gen_pp_tokens(
				lesser_pp_tokens,
				output,
				bkl);
			pp_gen_preprocessing_token(
				preprocessing_token,
				output,
				bkl);
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_gen_new_line(
	PreprocessingAstNode* const& new_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline PreprocessorExitCode pp_gen_preprocessing_token(
	PreprocessingAstNode* const& preprocessing_token,
	PreprocessingToken*        & output,
	AlertList                  & bkl) 
{
	*output++ = *(preprocessing_token->get_terminal());
	return PreprocessorExitCode::SUCCESS;
}

static inline PreprocessorExitCode preprocess(
	const char*              & input,
	const char**             & produced_lexema, 
	const char*         const& filename,
	AlertList                & bkl,
	PreprocessingToken*      & pp_tokens)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	FileLocationDescriptor file_location_descriptor
		= FileLocationDescriptor( 
			  { filename, 0, 0, 0 } );
	PreprocessingAstNode* preprocessing_file;
	pp_parse_preprocessing_file(
		input,
		produced_lexema,
		file_location_descriptor,
		bkl,
		preprocessing_file);
	pp_execute_preprocessing_file(
		preprocessing_file,
		produced_lexema,
		bkl);
	pp_gen_preprocessing_file(
		preprocessing_file,
		pp_tokens,
		bkl);
	return exitcode;
}

#endif