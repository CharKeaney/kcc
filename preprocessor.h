/* Authored By Charlie Keaney                        */
/* preprocessor.h - Responsible for preprocessing a 
					provided character string into 
					an array of preprocessing tokens.

					Implementation Notes: 
					The preprocessor has an internal
					ast tree to represent directives
					etc.                             */

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H 1

#include <iostream>

#include "lexema-pool.h"
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

/*****************************************************//**
*                      Declarations                      *
/********************************************************/

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
	PREPROCESSING_TOKEN_2,
	PREPROCESSING_TOKEN_3,
	PREPROCESSING_TOKEN_4,
	PREPROCESSING_TOKEN_5,
	PREPROCESSING_TOKEN_6,
	PREPROCESSING_TOKEN_7,
	NEW_LINE_1,
	IDENTIFIER_LIST_1,
	IDENTIFIER_LIST_2,
	CONSTANT_EXPRESSION_1
};

static 
const char* preprocessing_ast_form_string_reprs[] {
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
	"PREPROCESSING_TOKEN_2",
	"PREPROCESSING_TOKEN_3",
	"PREPROCESSING_TOKEN_4",
	"PREPROCESSING_TOKEN_5",
	"PREPROCESSING_TOKEN_6",
	"PREPROCESSING_TOKEN_7",
	"NEW_LINE_1",
	"IDENTIFIER_LIST_1",
	"IDENTIFIER_LIST_2",
	"CONSTANT_EXPRESSION_1"
};

/**
* Represents an ast node used for preprocessing.
* Describes a preprocessing-file in terms of groups
* which can include directives, text lines, etc.
* This ast node can be executed to execute directives
* and invocate macros.
* Exists completely independent of C ast nodes.
**/
class PreprocessingAstNode {
private:
	PreprocessingAstNodeName name;
	PreprocessingAstNodeAlt  alt;
	PreprocessingToken*      terminal;
	PreprocessingAstNode*    child;
	PreprocessingAstNode*    sibling;
	uint64_t                 val;
public:
	inline 
	PreprocessingAstNode(
		PreprocessingAstNodeName const& n,
		PreprocessingAstNodeAlt  const& a,
		PreprocessingToken*      const& t) :
		name(n),
		alt(a),
		terminal(t),
		child(NULL),
		sibling(NULL) {
	}

	inline 
	void set_val(
		uint64_t const& v) 
	{
		val = v;
	};

	inline 
	PreprocessingAstNode() :
		name(PreprocessingAstNodeName::ERROR),
		alt(PreprocessingAstNodeAlt::ERROR),
		terminal(NULL),
		child(NULL),
		sibling(NULL) {
	}

	inline
	PreprocessingAstNodeName get_name() const
	{
		return name;
	};

	inline 
	PreprocessingAstNodeAlt get_alt() const
	{
		return alt;
	};

	inline 
	PreprocessingToken* get_terminal() const
	{
		return terminal;
	};

	inline 
	uint64_t get_val() const
	{
		return val;
	};

	inline 
	PreprocessingAstNode* get_child() const
	{
		return child;
	};

	inline 
	PreprocessingAstNode* get_sibling() const
	{
		return sibling;
	};

	inline 
	void add_child(PreprocessingAstNode* node)
	{
		if (child == NULL) {
			child = node;
		} else {
			PreprocessingAstNode* current = child;
			while (current->sibling) {
				current = current->sibling;
			}
			current->sibling = node;
		}
	}

	inline
	void add_children(
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

	inline 
	void print(
		string const& parent_prefix = "",
		string const& child_prefix  = "")
	{
		const int name_i 
			= (int) name;
		const char* const name_s
			= preprocessing_ast_name_string_reprs[name_i];
		const int alt_i
			= (int) alt;
		const char* const alt_s
			= preprocessing_ast_form_string_reprs[alt_i];
		
		cout << parent_prefix
			 << "name="
			 << name_s
			 << ",alt="
			 << alt_s;
		if (terminal) terminal->print();
		cout << endl;

		PreprocessingAstNode* node = child;
		for (; 
			node; 
			node = node->sibling) {

			if (node->sibling) {
				string appended_p 
					= child_prefix 
					  + "|____";
				string appended_c 
					= child_prefix 
					  + "|    ";
				node->print(
					appended_p, 
					appended_c);
			} else {
				string appended_p 
					= child_prefix 
					  + "|____";
				string appended_c 
					= child_prefix 
					  + "     ";
				node->print(
					appended_p, 
					appended_c);
			}
		}
	}
};

/**
* Constructs a preprocessing ast node with given 
* name and alt containing the given children whose 
* number is described in count.
* 
* @param name The given name.
* @param alt The given alt.
* @param children Pointer to array of children.
* @param count The number of children.
* @return The node constructed and heap allocated.
**/
static inline
PreprocessingAstNode* construct_node_from_children(
	PreprocessingAstNodeName const& name,
	PreprocessingAstNodeAlt  const& alt,
	PreprocessingAstNode**   const& children,
	int                      const& count);

/**
* Constructs a lexeme from a section of a string.
* i.e. Creates a new string from a given substring.
* 
* @param lexeme_start Pointer to the start of the data.
* @param lexeme_end Pointer to the end of the data.
* @return The lexema constructed.
**/
static inline
const char* construct_lexeme(
	const char* const& lexeme_start,
	const char* const& lexeme_end);

struct LexemaPool;

/**
* Takes a given lexeme substring and, if that substring
* is not already present in the pool, inserts it into
* the pool
* 
* @param lexeme_start Pointer to the start of the data.
* @param lexeme_end Pointer to 
**/
static inline void ensure_lexeme_substring_in_pool(
	LexemaPool       & lexema_pool,
	const char* const& lexeme_start,
	const char* const& lexeme_end);

/**
* Used to lexically preprocess a header name.
* 
* @param input The input from which to preprocess.
* @param fld The input's file location descriptor.
* @param header_name The produced pp-number header_name.
* @return Returns an exitcode for success or failure.
**/
static inline
PreprocessorExitCode pp_lex_header_name(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & header_name);

/**
* Used to lexically preprocess an identifier.
* 
* @param input The input from which to preprocess.
* @param fld The input's file location descriptor.
* @param pp_number The produced pp-number pptoken.
* @return Returns an exitcode for success or failure.
**/
static inline
PreprocessorExitCode pp_lex_identifier_name(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_name,
	AlertList              & bkl);

/**
* Used to lexically preprocess a pp-number.
* 
* @param input The input from which to preprocess.
* @param fld The input's file location descriptor.
* @param pp_number The produced pp-number pptoken.
* @return Returns an exit code describing how the parse went.
**/
static inline
 PreprocessorExitCode pp_lex_pp_number(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & pp_number,
	AlertList              & bkl);

/**
* Used to lexically preprocess a character-constant.
* 
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param character_constant The reference to where to place
*        the produced character_constant pptoken.
* @param bkl The location to send error alerts to.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_lex_character_constant(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & identifier_output,
	AlertList              & bkl);

/**
* Used to lexically preprocess a string-literal.
* 
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param string_literal The reference to where to place
*        the produced string-literal pptoken.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_lex_string_literal(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & string_literal,
	AlertList              & bkl);

/**
* Used to lexically preprocess a punctuator.
* 
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param punctuator The reference to where to place
*        the produced punctuator pptoken.
* @param bkl The location to send alerts to.
* @return Returns an exit code describing how the parse went.
**/
static inline
 PreprocessorExitCode pp_lex_punctuator(
	const char*            & input,
	LexemaPool             & lexema_pool,
    FileLocationDescriptor & fld,
	PreprocessingToken*    & punctuator,
	AlertList              & bkl);

/**
* Used to preprocess a character string (char*) input.
* 
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param punctuator The reference to where to place
*					the produced pptokens.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_pp_tokens(
	const char*                 & input,
	LexemaPool                  & lexema_pool,
	FileLocationDescriptor      & file_location_descriptor,
	PreprocessingAstNode*       & pp_tokens,
	AlertList                   & bkl,
	bool			       const& in_directive);

/**
* Used to performing a preprocessing parse on a 
* preprocessing-file.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param preprocessing_file Reference to where to store
*                           the produced preprocessing-file
* 							preprocessing ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_preprocessing_file(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & preprocessing_file);

/**
* Used to performing a preprocessing parse on a
* group.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param group Reference to where to store the
*              produced group preprocessing ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group);

/**
* Used to performing a preprocessing parse on a
* group-part.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param group_part Reference to where to store the
*                   produced group-part preprocessing
*                   ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_group_part(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & group_part);

/**
* Used to performing a preprocessing parse on an
* if-section.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param if_section Reference to where to store the
*                   produced if-section preprocessing
*                    ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_if_section(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_section);

/**
* Used to performing a preprocessing parse on an
* if-group.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param if_group Reference to where to store the
*                 produced if-group preprocessing
*                    ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_if_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & if_group);

/**
* Used to performing a preprocessing parse on an
* elif-groups.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param elif_groups Reference to where to store the
*                    produced elif-groups preprocessing
*                    ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_elif_groups(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_groups);

/**
* Used to performing a preprocessing parse on an
* constant-expression.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param constant_expression Reference to where to store the
*                            produced constant-expression 
*                            preprocessing ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_constant_expression(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & constant_expression);

/**
* Used to performing a preprocessing parse on an
* elif-group.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param elif_group Reference to where to store the
*                   produced elif-group preprocessing 
*                   ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_elif_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & elif_group);

/**
* Used to performing a preprocessing parse on an
* else-group.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param else_group Reference to where to store the
*                   produced else-group preprocessing
*                   ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_else_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & else_group);

/**
* Used to performing a preprocessing parse on an
* endif-line.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param endif_line Reference to where to store the
*                   produced endif-line preprocessing
*                   ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_endif_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & endif_line);

/**
* Used to performing a preprocessing parse on an
* control-line.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param control_line Reference to where to store the
*                     produced control-line preprocessing
*                     ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_control_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & control_line);

/**
* Used to performing a preprocessing parse on a
* text-line.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param text_line Reference to where to store the
*                  produced control-line preprocessing
*                  ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_text_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & text_line);

/**
* Used to performing a preprocessing parse on a
* new-line.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param new_line Reference to where to store the
*                 produced control-line preprocessing
*                 ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_new_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & new_line);

/**
* Used to performing a preprocessing parse on a
* non-directive.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param non_directive Reference to where to store the
*                      produced non-directive preprocessing
*                      ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_non_directive(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & non_directive);

/**
* Used to performing a preprocessing parse on an
* lparen.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param lparen Reference to where to store the
*               produced lparenpreprocessing ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_lparen(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & lparen);

/**
* Used to performing a preprocessing parse on a
* replacement-list.
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema are allocated.
* @param fld The file location descriptor for the input.
* @param bkl The location to send alerts to.
* @param replacement_list Reference to where to store the
*                         produced replacement-list 
*                         preprocessing ast node.
* @return Returns an exit code describing how the parse went.
**/
static inline
PreprocessorExitCode pp_parse_replacement_list(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & replacement_list);

/**
* Used to execute directives and invocate macros within
* a preprocessing-file preprocessing ast node.
* This will change the contents of this preprocessing-ast
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* @param preprocessing_file The preprocessing-file 
*							preprocessing ast node to 
*                           execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_preprocessing_file(
	PreprocessingAstNode* & preprocessing_file,
	AlertList             & bkl,
	PreprocessingAstNode* & executed_preprocessing_file);

/**
* Used to execute directives and invocate macros within
* a group preprocessing ast node.
* This will change the contents of this group so that when 
* preprocessing-tokens are generated from it, the relevant 
* directives etc will have been performed.
* @param group The group preprocessing ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_group(
	PreprocessingAstNode* & group,
	AlertList             & bkl,
	SymbolTable           & symtab,
	PreprocessingAstNode* & executed_group);

/**
* Used to execute directives and invocate macros within
* a group-part preprocessing ast node.
* This will change the contents of this group-part so that 
* when preprocessing-tokens are generated from it, the 
* relevant directives etc will have been performed.
* 
* @param group The group preprocessing ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_group_part(
	PreprocessingAstNode* & group_part,
	AlertList             & bkl,
	SymbolTable           & symtab,
	PreprocessingAstNode* & executed_group_part);

/**
* Used to execute directives and invocate macros within
* a group-part preprocessing ast node.
* This will change the contents of this group-part so that
* when preprocessing-tokens are generated from it, the
* relevant directives etc will have been performed.
* 
* @param group The group preprocessing ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_if_section(
	PreprocessingAstNode* & if_section,
	AlertList             & bkl,
	SymbolTable           & symtab,
	PreprocessingAstNode* & executed_group_part);

/**
* Used to execute directives and invocate macros within
* an if-group preprocessing ast node.
* This will change the contents of this if-group so that
* when preprocessing-tokens are generated from it, the
* relevant directives etc will have been performed.
* 
* @param if_group The if-group preprocessing ast node 
*                 to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_if_group(
	PreprocessingAstNode* & if_group,
	AlertList             & bkl,
	SymbolTable           & symtab,
	PreprocessingAstNode* & executed_group_part);

/**
* Used to execute directives and invocate macros within
* an elif-groups preprocessing ast node.
* This will change the contents of this elif-groups so that
* when preprocessing-tokens are generated from it, the
* relevant directives etc will have been performed.
* 
* @param elif_groups The elif-groups preprocessing ast node
*                    to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_elif_groups(
	PreprocessingAstNode* & elif_groups,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an identifier-list preprocessing ast node.
* This will change the contents of this identifier-list 
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param identifier_list The identifier-list preprocessing 
*                        ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_identifier_list(
	PreprocessingAstNode* & identifier_list,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an constant-expression preprocessing ast node.
* This will change the contents of this identifier-list
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param constant_expression The constant-expression 
*                            preprocessing ast node 
*							 to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_constant_expression(
	PreprocessingAstNode* & constant_expression,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an elif-group preprocessing ast node.
* This will change the contents of this elif-group
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param elif_group The elif-group preprocessing ast node
*				    to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_elif_group(
	PreprocessingAstNode* & elif_group,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an else-group preprocessing ast node.
* This will change the contents of this else-group
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param else_group The else-group preprocessing ast node
*				    to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_else_group(
	PreprocessingAstNode* & else_group,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an endif-line preprocessing ast node.
* This will change the contents of this endif-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param endif_line The endif-line preprocessing ast node
*				    to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_endif_line(
	PreprocessingAstNode* & endif_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 1 (CONTROL_LINE_1).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing 
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_1(
	PreprocessingAstNode* & control_line,
	PreprocessingAstNode* & preprocessing_file,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 2 (CONTROL_LINE_2).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_2(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 3 (CONTROL_LINE_3).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_3(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 4 (CONTROL_LINE_4).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_4(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 5 (CONTROL_LINE_5).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_5(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 6 (CONTROL_LINE_6).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_6(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable			  & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 7 (CONTROL_LINE_7).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_7(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a control-line with alternative 8 (CONTROL_LINE_8).
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing
*                     ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line_8(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an control-line preprocessing ast node.
* This will change the contents of this control-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param control_line The control-line preprocessing ast 
*                     node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_control_line(
	PreprocessingAstNode* & control_line,
	PreprocessingAstNode* & group_part,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros 
* within a text-line preprocessing ast node.
* This will change the contents of this text-line
* so that when preprocessing-tokens are generated 
* from it, the relevant directives etc will have 
* been performed.
* 
* @param text_line The text-line preprocessing 
*                  ast node to execute.
* @param lexema_pool The pool in which lexema 
                     are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the 
*         execution went.
**/
static inline
PreprocessorExitCode pp_execute_text_line(
	PreprocessingAstNode* & text_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a new-line preprocessing ast node.
* This will change the contents of this new-line
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param new_line The new-line preprocessing ast
*                 node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_new_line(
	PreprocessingAstNode* & new_line,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a non-directive preprocessing ast node.
* This will change the contents of this non-directive
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param non_directive The non-directive preprocessing ast
*                      node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_non_directive(
	PreprocessingAstNode* & non_directive,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* an lparen preprocessing ast node.
* This will change the contents of this lparen
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param lparen The lparen preprocessing ast
*               node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_lparen(
	PreprocessingAstNode* & lparen,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a replacement-list preprocessing ast node.
* This will change the contents of this replacement-list
* so that when preprocessing-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param replacement_list The replacement-list 
*                         preprocessing ast node to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_replacement_list(
	PreprocessingAstNode* & replacement_list,
	AlertList             & bkl,
	SymbolTable           & symtab);

static inline
PreprocessorExitCode pp_insert_macro_replacement_list(
	PreprocessingAstNode* & replacement_list,
	PreprocessingAstNode* & pp_tokens,
	SymbolTable           & symtab);

/**
* Used to execute directives and invocate macros within
* a pp-tokens preprocessing ast node.
* This will change the contents of this replacement-list
* so that when pp-tokens are generated from it,
* the relevant directives etc will have been performed.
* 
* @param pp_tokens The pp-tokens preprocessing ast node 
*                  to execute.
* @param lexema_pool The pool in which lexema are allocated.
* @param bkl The location to send alerts to.
* @return Returns an exit code for how the execution went.
**/
static inline
PreprocessorExitCode pp_execute_pp_tokens(
	PreprocessingAstNode* & pp_tokens,
	AlertList             & bkl,
	SymbolTable           & symtab);

/**
* Generates a list of preprocessing tokens from
* a given preprocessing-file.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to 
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param preprocessing_file The preprocessing-file
*						    from which to generate
*							preprocessing-tokens.
* @param output The location to place the preprocessing
*               tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect macros etc.
* @return Returns an exit code for how the generation went.
**/
static inline
PreprocessorExitCode pp_gen_preprocessing_file(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given group.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param group The group from which to generate
*			   preprocessing-tokens.
* @param output The location to place the preprocessing
*               tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect macros etc.
* @return Returns an exit code for how the generation went.
**/
static inline
PreprocessorExitCode pp_gen_group(
	PreprocessingAstNode* const& group,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given group-part.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param group_part The group-part from which to generate
*			   preprocessing-tokens.
* @param output The location to place the preprocessing
*               tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect macros etc.
* @return Returns an exit code for how the generation went.
**/
static inline
PreprocessorExitCode pp_gen_group_part(
	PreprocessingAstNode* const& group_part,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given text-line preprocessing ast node.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param text_line The text-line from which to 
*                  generate preprocessing-tokens.
* @param output The location to place the 
*               preprocessing tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect
*               macros etc.
* @return Returns an exit code for how the 
*         generation went.
**/
static inline
PreprocessorExitCode pp_gen_text_line(
	PreprocessingAstNode* const& text_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given non-directive ast node.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param non_directive The non-directive from 
*                      which to generate 
*                      preprocessing-tokens.
* @param output The location to place the 
*               preprocessing tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to 
*               detect macros etc.
* @return Returns an exit code for how the 
*         generation went.
**/
static inline
PreprocessorExitCode pp_gen_non_directive(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given pp-tokens ast node.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param pp_tokens The pp-tokens from which to generate
*                  preprocessing-tokens.
* @param output The location to place the preprocessing
*               tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect macros etc.
* @return Returns an exit code for how the generation went.
**/
static inline
PreprocessorExitCode pp_gen_pp_tokens(
	PreprocessingAstNode* const& pp_tokens,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Generates a list of preprocessing tokens from
* a given preprocessing-token ast node.
* Essentially 'flattens' the tree.
* Useful as it allows you to convert back to
* preprocessing-tokens after performing directive
* executions and macro invocations.
* 
* @param preprocessing_token The preprocessing-token from 
*                            which to generate 
*							 preprocessing-tokens.
* @param output The location to place the preprocessing
*               tokens into.
* @param bkl The location to send alerts to.
* @param symtab The symbol table to use to detect macros etc.
* @return Returns an exit code for how the generation went.
**/
static inline
PreprocessorExitCode pp_gen_preprocessing_token(
	PreprocessingAstNode* const& preprocessing_token,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab);

/**
* Used to preprocess input.
* 
* @param input The input from which to preprocess.
* @param lexema_pool The pool where lexema will be allocated. 
* @param filename The input file name.
* @param bkl The location to send alerts to.
* @return An exitcode describing how preprocessing went.
**/
static inline
PreprocessorExitCode preprocess(
	const char*              & input,
	LexemaPool               & lexema_pool,
	const char*         const& filename,
	AlertList                & bkl,
	PreprocessingToken*      & output);

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

static inline
PreprocessingAstNode* construct_node_from_children(
	PreprocessingAstNodeName const& name,
	PreprocessingAstNodeAlt  const& alt,
	PreprocessingAstNode**   const& children,
	int                      const& count)
{
	PreprocessingAstNode* node
		= new PreprocessingAstNode(
			name,
			alt,
			NULL);
	node->add_children(
		children,
		count);
	return node;
}

static inline
const char* construct_lexeme(
	const char* const& lexeme_start,
	const char* const& lexeme_end)
{
	char* lexeme = new char[lexeme_end - lexeme_start + 1];
	for (int i = 0; 
		 i < lexeme_end - lexeme_start + 1; 
		 i++) {
		*(lexeme + i) = *(lexeme_start + i);
	}
	*(lexeme + (lexeme_end - lexeme_start)) = NULL;
	return lexeme;
}

static inline void ensure_lexeme_substring_in_pool(
	LexemaPool       & lexema_pool,
	const char* const& lexeme_start,
	const char* const& lexeme_end)
{
	const char* lexeme
		= construct_lexeme(lexeme_start, lexeme_end);
	if (lookup_lexeme_in_pool(lexema_pool, lexeme)) {
		delete lexeme;
	} else {
		insert_lexeme_into_pool(lexema_pool, lexeme);
	}
}

static inline
PreprocessorExitCode pp_lex_header_name(
	const char*            & input, 
	LexemaPool             & lexema_pool,
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
				const char* lexeme
					= construct_lexeme(
						  input, 
						  chr);

				LexemaEntry* e
					= lookup_lexeme_in_pool(
						lexema_pool,
						lexeme);
					if (e) {
						delete lexeme;
						lexeme = e->lexeme;
					} else {
						insert_lexeme_into_pool(lexema_pool, lexeme);
					}

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
				const char* const err_msg 
					= "This header name could not be recognised. "
					  "Did you mispell it?";
				Error* error
					= construct_error_book(
						ErrorCode::ERR_PP_INVALID_HEADER,
						err_msg,
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

static inline
PreprocessorExitCode pp_lex_identifier_name(
	const char*            & input, 
	LexemaPool             & lexema_pool,
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
						form = PreprocessingTokenForm::IDENTIFIER_1;
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
						form = PreprocessingTokenForm::IDENTIFIER_2;
						input++;
						continue;

					case '1': case '2': case '3':
					case '4': case '5': case '6':
					case '7': case '8': case '9':
					case '0':
						// TODO: UNIVERSAL-CHARACTER-NAME
						form = PreprocessingTokenForm::IDENTIFIER_3;
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
			= construct_lexeme(
				lexeme_start,
				input);

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

		preprocessor_report_success(
			"preprocess_identifier_name",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;

		*identifier_name 
			= PreprocessingToken(
			      lexeme,
				  PreprocessingTokenName::IDENTIFIER,
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

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

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
		const char* const err_msg
			= "This identifier could not be recognised. "
			  "Did you mispell it?";
		Error* error
			= construct_error_book(
				ErrorCode::ERR_PP_INVALID_IDENTIFIER,
				err_msg,
				fld);
		fld.character_number += (input - lexeme_start);

		exitcode = PreprocessorExitCode::FAILURE;
	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_lex_pp_number(
	const char*            & input, 
	LexemaPool             & lexema_pool,
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
					form = PreprocessingTokenForm::PP_NUMBER_1;
					state = PP_NUMBER;
					continue;

				} else if (*input == '.') {
					input++;
					if (*input >= '0' 
						&& *input <= '9') {
						input++;
						form = PreprocessingTokenForm::PP_NUMBER_2;
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
						form = PreprocessingTokenForm::PP_NUMBER_3;
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
						form = PreprocessingTokenForm::PP_NUMBER_4;
						continue;

					case 'e': 
						form = PreprocessingTokenForm::PP_NUMBER_5;
						input++;
						if (*input == '+'
							|| *input == '-') {
							input++;
						}
						continue;

					case 'E':
						form = PreprocessingTokenForm::PP_NUMBER_6;
						input++;
						if (*input == '+'
							|| *input == '-') {
							input++;
						}
						continue;

					case 'p': 
						form = PreprocessingTokenForm::PP_NUMBER_7;
						input++;
						if (*input == '+'
							|| *input == '-') {
							input++;
						}
						continue;

					case 'P':
						form = PreprocessingTokenForm::PP_NUMBER_8;
						input++;
						if (*input == '+'
							|| *input == '-') {
							input++;
						}
						continue;

					case '.':
						form = PreprocessingTokenForm::PP_NUMBER_9;
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

				LexemaEntry* e
					= lookup_lexeme_in_pool(
						lexema_pool,
						lexeme);
				if (e) {
					delete lexeme;
					lexeme = e->lexeme;
				} else {
					insert_lexeme_into_pool(lexema_pool, lexeme);
				}

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

				LexemaEntry* e
					= lookup_lexeme_in_pool(
						lexema_pool,
						lexeme);
				if (e) {
					delete lexeme;
					lexeme = e->lexeme;
				} else {
					insert_lexeme_into_pool(lexema_pool, lexeme);
				}

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

static inline
PreprocessorExitCode pp_lex_character_constant(
	const char*            & input, 
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & fld,
	PreprocessingToken*    & character_constant,
	AlertList              & bkl)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	const char* lexeme_start 
		= input;
	bool found_preprocess 
		= false;

	bool encountered_l = false;
	if (*input == 'L') {
		input++;
		encountered_l = true;
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

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

		PreprocessingTokenForm form
			= encountered_l
			  ? PreprocessingTokenForm::CHARACTER_CONSTANT_2
			  : PreprocessingTokenForm::CHARACTER_CONSTANT_1;

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*character_constant
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

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}
		 
		preprocessor_report_failure(
			"preprocess_pp_number",
			PreprocessingTokenForm::UNDEFINED,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*character_constant
			= PreprocessingToken(
			      lexeme,
			      PreprocessingTokenName::ERROR,
			      fld,
			      PreprocessingTokenForm::UNDEFINED);
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

static inline
PreprocessorExitCode pp_lex_string_literal(
	const char*            & input, 
	LexemaPool             & lexema_pool,
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

	bool encountered_l = false;
	if (*input == 'L') {
		encountered_l = true;
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
			= construct_lexeme(
				lexeme_start,
				input);

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

		PreprocessingTokenForm form
			= encountered_l
			  ? PreprocessingTokenForm::STRING_LITERAL_2
			  : PreprocessingTokenForm::STRING_LITERAL_1; 

		preprocessor_report_success(
			"preprocess_header_name",
			form,
			lexeme);

		fld.lexeme_length 
			= input 
			  - lexeme_start;
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
			= construct_lexeme(
				lexeme_start,
				input);

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

		preprocessor_report_failure(
			"preprocess_pp_number",
			PreprocessingTokenForm::UNDEFINED,
			lexeme);

		fld.lexeme_length 
			= input - lexeme_start;
		*string_literal = PreprocessingToken(
			lexeme,
			PreprocessingTokenName::ERROR,
			fld,
			PreprocessingTokenForm::UNDEFINED);
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

static inline
PreprocessorExitCode pp_lex_punctuator(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			= construct_lexeme(
				lexeme_start,
				input);

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

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

		LexemaEntry* e
			= lookup_lexeme_in_pool(
				lexema_pool,
				lexeme);
		if (e) {
			delete lexeme;
			lexeme = e->lexeme;
		} else {
			insert_lexeme_into_pool(lexema_pool, lexeme);
		}

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
* Used to perform a preprocessing parse on a token.
* @param input The input from which to preprocess.
* @param fld The file location descriptor for the input.
* @param punctuator The reference to where to place
*					the produced pptokens.
* @param bkl The location to send alerts to.
* @param preprocessing_token The output preprocessing token.
**/
static inline
PreprocessorExitCode pp_parse_preprocessing_token(
	const char*            & input,
	LexemaPool             & lexema_pool,
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

	PreprocessingAstNodeAlt form
		= PreprocessingAstNodeAlt::ERROR;

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
					lexema_pool,
					file_location_descriptor,
					token,
					bkl)
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_2;
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case 'L':
				if (*(input + 1) != '\"') {
					if (pp_lex_identifier_name(
						input,
						lexema_pool,
						file_location_descriptor,
						token,
						bkl) 
						== PreprocessorExitCode::SUCCESS) {
						form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_2;
						finished_preprocessed_word = true;
						should_generate = true;
					}
				} else {
					if (pp_lex_string_literal(
						input,
						lexema_pool,
						file_location_descriptor,
						token,
						bkl) 
						== PreprocessorExitCode::SUCCESS) {
						form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_5;
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
					lexema_pool,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_3;
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '\'':
				if (pp_lex_character_constant(
					input,
					lexema_pool,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_4;
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '\"':
				if (pp_lex_string_literal(
					input,
					lexema_pool,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_5;
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '/':
				if (pp_lex_punctuator(
					input,
					lexema_pool,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_6;
					finished_preprocessed_word = true;
					should_generate = true;
				}
				break;

			case '[': case ']':
			case '(': case ')':
			case '{': case '}': case ':':
			case '.':
			case '&': case '+': case '-':
			case '~': case '!': case '#':
			case '%': case '<': case '>':
			case '^': case '|': case '?':
			case ';': case '=': case ',':
			case '*':
				if (pp_lex_punctuator(
					input,
					lexema_pool,
					file_location_descriptor,
					token,
					bkl) 
					== PreprocessorExitCode::SUCCESS) {
					form = PreprocessingAstNodeAlt::PREPROCESSING_TOKEN_6;
					finished_preprocessed_word = true;
					should_generate = true;
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

static inline
PreprocessorExitCode pp_parse_pp_tokens(
	const char*                 & input,
	LexemaPool                  & lexema_pool,
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
							terminated = true;
							break;

						case ' ':
							file_location_descriptor.character_number++;
							input++;
							break;

						case '\t':
							file_location_descriptor.character_number 
								+= file_location_descriptor.character_number
								   % 4;
							input++;
							break;

						case '\r':
							file_location_descriptor.character_number = 0;
							input++;
							break;

						case '/':
							if (*(input + 1) == '*') {
								input += 2;
								file_location_descriptor.character_number += 2;

								while ((*input != '*')
									|| (*(input + 1) != '/')) {
									input++;
									file_location_descriptor.character_number++;

								}
								input += 2;								
								file_location_descriptor.character_number += 2;

							} else if (*(input + 1) == '/') {
								input += 2;
								file_location_descriptor.character_number += 2;

								while (*input != '\n') {
									input++;
									file_location_descriptor.character_number++;

								}
								continue;
							
							}
							break;

						default:
							PreprocessingAstNode* preprocessing_token;
							if (pp_parse_preprocessing_token(
								input,
								lexema_pool,
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
				switch (*input) {

					case '\n':
						break;

					case ' ':
						file_location_descriptor.character_number++;
						input++;
						continue;

					case '\t':
						file_location_descriptor.character_number += 4;
						input++;
						continue;

					case '\r':
						file_location_descriptor.character_number = 0;
						input++;
						continue;

					case '/':
						if (*(input + 1) == '*') {
							input += 2;
							file_location_descriptor.character_number += 2;

							while ((*input != '*')
								|| (*(input + 1) != '/')) {
								input++;
								file_location_descriptor.character_number++;

							}
							input += 2;
							file_location_descriptor.character_number += 2;

						}
						else if (*(input + 1) == '/') {
							input += 2;
							file_location_descriptor.character_number += 2;

							while (*input != '\n') {
								input++;
								file_location_descriptor.character_number++;

							}
							continue;

						}
						break;

					default:
						PreprocessingAstNode* preprocessing_token;
						if (pp_parse_preprocessing_token(
							input,
							lexema_pool,
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
							continue;

						} else {
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

static inline
PreprocessorExitCode pp_parse_preprocessing_file(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
					lexema_pool,
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
					lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_group_part(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
				lexema_pool,
				file_location_descriptor,
				bkl,
				if_section)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = if_section;

			alt = PreprocessingAstNodeAlt::GROUP_PART_1;
			should_generate = true;

		} else if (pp_parse_control_line(
			           input,
			           lexema_pool,
			           file_location_descriptor,
			           bkl, 
			           control_line)
			       == PreprocessorExitCode::SUCCESS) {
			stack[si++] = control_line;

			alt = PreprocessingAstNodeAlt::GROUP_PART_2;
			should_generate = true;

		} else if (pp_parse_preprocessing_token(
			           input,
			           lexema_pool,
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
					lexema_pool,
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
				lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_if_section(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		lexema_pool,
		file_location_descriptor,
		bkl, 
		if_group)
		== PreprocessorExitCode::SUCCESS) {
		stack[si++] = if_group;

		PreprocessingAstNode* elif_groups;
		if (pp_parse_elif_groups(
			input,
			lexema_pool,
			file_location_descriptor,
			bkl, 
			elif_groups)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = elif_groups;
		}

		PreprocessingAstNode* else_group;
		if (pp_parse_else_group(
			input,
			lexema_pool,
			file_location_descriptor,
			bkl, 
			else_group)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = else_group;
		}

		PreprocessingAstNode* endif_line;
		if (pp_parse_endif_line(
			input,
			lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_if_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			lexema_pool, 
			file_location_descriptor, 
			bkl, 
			preprocessing_token_1) 
		== PreprocessorExitCode::SUCCESS
		&& preprocessing_token_1->get_terminal()->get_name() 
		   == PreprocessingTokenName::PUNCTUATOR
		&& preprocessing_token_1->get_terminal()->get_form() 
		   == PreprocessingTokenForm::HASHTAG) {

		PreprocessingAstNode* preprocessing_token_2;
		if (pp_parse_preprocessing_token(
			input,
			lexema_pool,
			file_location_descriptor,
			bkl,
			preprocessing_token_2) == PreprocessorExitCode::SUCCESS
			&& preprocessing_token_2->get_terminal()
			                        ->get_name() 
			   == PreprocessingTokenName::IDENTIFIER) {
			const char* lexeme 
				= preprocessing_token_2->get_terminal()
				                       ->get_lexeme();
			if (strcmp(lexeme, "if") == 0) {

				PreprocessingAstNode* constant_expression;
				if (pp_parse_constant_expression(
						input, 
						lexema_pool,
						file_location_descriptor,
						bkl,
						constant_expression)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = constant_expression;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
							input,
							lexema_pool,
							file_location_descriptor,
							bkl, 
							new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
								input,
								lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl,
						preprocessing_token) 
					== PreprocessorExitCode::SUCCESS) {
					stack[si++];

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
							input,
							lexema_pool,
							file_location_descriptor,
							bkl, 
							new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input,
							lexema_pool,
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
						lexema_pool,
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
							lexema_pool,
							file_location_descriptor,
							bkl, 
							new_line) 
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
								input,
								lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_elif_groups(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
						lexema_pool,
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
						lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_identifier_list(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
						lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl,
						preprocessing_token)
					== PreprocessorExitCode::SUCCESS) {

					PreprocessingAstNode* preprocessing_token;
					if (pp_parse_preprocessing_token(
							input,
							lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_constant_expression(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_elif_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		lexema_pool,
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
				lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl, 
						constant_expression)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = constant_expression;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
						input, 
						lexema_pool,
						file_location_descriptor,
						bkl, 
						new_line) == PreprocessorExitCode::SUCCESS) {
						stack[si++] = new_line;

						PreprocessingAstNode* group;
						if (pp_parse_group(
							input, 
							lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_else_group(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			lexema_pool,
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
				lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl, 
						new_line) 
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = new_line;

					PreprocessingAstNode* group;
					if (pp_parse_group(
							input, 
							lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_endif_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		lexema_pool,
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
			lexema_pool,
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
					lexema_pool,
					file_location_descriptor,
					bkl, 
					new_line) 
					== PreprocessorExitCode::SUCCESS) {

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

static inline
PreprocessorExitCode pp_parse_control_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			lexema_pool, 
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
				lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						pp_tokens,
						bkl,
						true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
							input,
							lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl,
						identifier)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = identifier;

					PreprocessingAstNode* replacement_list;
					PreprocessingAstNode* lparen;
					if (pp_parse_replacement_list(
							input,
							lexema_pool,
							file_location_descriptor,
							bkl,
							replacement_list)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = replacement_list;

						PreprocessingAstNode* new_line;
						if (pp_parse_new_line(
								input,
								lexema_pool,
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
								   lexema_pool,
								   file_location_descriptor,
								   bkl,
								   lparen)
						== PreprocessorExitCode::SUCCESS) {
						stack[si++] = lparen;

						PreprocessingAstNode* identifier_list;
						if (pp_parse_identifier_list(
								input,
								lexema_pool,
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
										lexema_pool,
										file_location_descriptor,
										bkl, 
										replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(input,
											lexema_pool,
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
										lexema_pool,
										file_location_descriptor,
										bkl, 
										replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
											input,
											lexema_pool,
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
										lexema_pool,
										file_location_descriptor,
										bkl, 
										replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
											input,
											lexema_pool,
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
										lexema_pool, 
										file_location_descriptor,
										bkl,
										replacement_list)
									== PreprocessorExitCode::SUCCESS) {
									stack[si++] = replacement_list;

									PreprocessingAstNode* new_line;
									if (pp_parse_new_line(
											input,
											lexema_pool,
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
								lexema_pool,
								file_location_descriptor,
								bkl,
								replacement_list)
							== PreprocessorExitCode::SUCCESS) {
							stack[si++] = replacement_list;

							PreprocessingAstNode* new_line;
							if (pp_parse_new_line(
									input,
									lexema_pool,
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
						lexema_pool,
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
							lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						pp_tokens,
						bkl,
						true)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = pp_tokens;

					PreprocessingAstNode* new_line;
					if (pp_parse_new_line(
							input, 
							lexema_pool,
							file_location_descriptor,
							bkl, 
							new_line)
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
						lexema_pool,
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
						lexema_pool,
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
						lexema_pool,
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
						lexema_pool,
						file_location_descriptor,
						bkl, 
						new_line)
					== PreprocessorExitCode::SUCCESS) {
					should_generate = true;
					alt = PreprocessingAstNodeAlt::CONTROL_LINE_9;
				}
			}

		} else if (pp_parse_new_line(
				       input,
					   lexema_pool,
					   file_location_descriptor,
					   bkl,
					   new_line)
				   == PreprocessorExitCode::SUCCESS) { 
			stack[si++] = new_line;

			should_generate = true;
			alt = PreprocessingAstNodeAlt::CONTROL_LINE_10;
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

static inline
PreprocessorExitCode pp_parse_text_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
			lexema_pool,
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
			lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_new_line(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		file_location_descriptor.line_number++;
		file_location_descriptor.character_number = 0;
		input++;
		exitcode = PreprocessorExitCode::SUCCESS;
	}
	return exitcode;
}

static inline
bool is_directive(
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
		    || *(input + 6) == '\t'
		    || *(input + 6) == '\n')) {
		retval = true;

	} else {

	}
	return retval;
}

static inline
PreprocessorExitCode pp_parse_non_directive(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		       lexema_pool,
		       file_location_descriptor,
		       pp_tokens,
		       bkl,
		       false)
		   == PreprocessorExitCode::SUCCESS) {
		stack[si++] = pp_tokens;

		PreprocessingAstNode* new_line;
		if (pp_parse_new_line(
			input,
			lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_lparen(
	const char*            & input,
	LexemaPool             & lexema_pool,
	FileLocationDescriptor & file_location_descriptor,
	AlertList              & bkl,
	PreprocessingAstNode*  & lparen)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* preprocessing_token;
	if (pp_parse_preprocessing_token(input,
		lexema_pool,
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

static inline
PreprocessorExitCode pp_parse_replacement_list(
	const char*            & input,
	LexemaPool             & lexema_pool,
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
		lexema_pool,
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

static inline
PreprocessorExitCode pp_execute_preprocessing_file(
	PreprocessingAstNode* & preprocessing_file,
	AlertList             & bkl,
	PreprocessingAstNode* & executed_preprocessing_file)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* group
		= preprocessing_file->get_child();
	SymbolTable symtab
		= SymbolTable();

	executed_preprocessing_file = new PreprocessingAstNode(
		PreprocessingAstNodeName::PREPROCESSING_FILE,
		PreprocessingAstNodeAlt::PREPROCESSING_FILE_1,
		NULL);

	if (group) {
		PreprocessingAstNode* executed_group;
		pp_execute_group(
			group,
			bkl,
			symtab,
			executed_group);
		executed_preprocessing_file->add_child(executed_group);

	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_insert_group_into_group(
	PreprocessingAstNode* & former_group,
	PreprocessingAstNode* & latter_group,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	switch (latter_group->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_1:
		{
			PreprocessingAstNode* latter_group_group_part
				= latter_group->get_child();
			PreprocessingAstNode* higher_group
				= new PreprocessingAstNode(
					PreprocessingAstNodeName::GROUP,
					PreprocessingAstNodeAlt::GROUP_2,
					NULL);
			higher_group->add_child(
				former_group);
			higher_group->add_child(
				latter_group_group_part);
			former_group
				= higher_group;
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::PP_TOKENS_2:
		{
			PreprocessingAstNode* latter_group_group
				= latter_group->get_child();
			PreprocessingAstNode* latter_group_group_part
				= latter_group_group->get_sibling();

			pp_insert_group_into_group(
				former_group,
				latter_group_group,
				symtab);
			PreprocessingAstNode* higher_group
				= new PreprocessingAstNode(
					PreprocessingAstNodeName::GROUP,
					PreprocessingAstNodeAlt::GROUP_2,
					NULL);
			higher_group->add_child(
				former_group);
			higher_group->add_child(
				latter_group_group_part);
			former_group
				= higher_group;
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_group(
	PreprocessingAstNode* & group,
	AlertList             & bkl,
	SymbolTable           & symtab,
	PreprocessingAstNode* & executed_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (group->get_alt()) {
	
		case PreprocessingAstNodeAlt::GROUP_1:
		{	
			PreprocessingAstNode* group_part			
				= group->get_child();			
			PreprocessingAstNode* executed_group_part
				= NULL;

			if (pp_execute_group_part(
					group_part,
					bkl,
					symtab,
					executed_group_part)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			if (executed_group_part) {
				executed_group
					= new PreprocessingAstNode(
						PreprocessingAstNodeName::GROUP,
						PreprocessingAstNodeAlt::GROUP_1,
						NULL);
				executed_group->add_child(executed_group_part);
			
			} else {
				executed_group = NULL;
			}

			exitcode 
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_2:
		{
			PreprocessingAstNode* lower_group
				= group->get_child();
			PreprocessingAstNode* group_part
				= lower_group->get_sibling();

			PreprocessingAstNode* executed_former_group;
			if (pp_execute_group(
					lower_group,
					bkl,
					symtab,
					executed_former_group)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			PreprocessingAstNode* executed_latter_group;
			if (pp_execute_group_part(
					group_part,
					bkl,
				 	symtab,
					executed_latter_group)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}

			if (executed_former_group) {

				if (executed_latter_group) {
					pp_insert_group_into_group(
						executed_former_group,
						executed_latter_group,
						symtab);
				} 

				executed_group 
					= executed_former_group;

			} else if (executed_latter_group) {
				executed_group
					= executed_latter_group;

			} else {
				executed_group 
					= NULL;
			}

			exitcode 
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_group_part(
	PreprocessingAstNode*       & group_part,
	AlertList                   & bkl,
	SymbolTable                 & symtab,
	PreprocessingAstNode*       & executed_group_part)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (group_part->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_PART_1:
		{
			PreprocessingAstNode* if_section
				= group_part->get_child();
			if (pp_execute_if_section(
					if_section,
					bkl,
					symtab,
					executed_group_part
				)
				== PreprocessorExitCode::FAILURE) {
				break;
			}
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_2:
		{
			PreprocessingAstNode* control_line
				= group_part->get_child();
			if (pp_execute_control_line(
					control_line, 
					group_part,
					bkl, 
					symtab)
				== PreprocessorExitCode::FAILURE) {
				break;
			}
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_3:
		{
			PreprocessingAstNode* text_line
				= group_part->get_child();
			if (pp_execute_text_line(
					text_line,
					bkl,
					symtab) 
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			executed_group_part = group_part;
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_4:
		{
			PreprocessingAstNode* non_directive
				= group_part->get_child();
			if (pp_execute_non_directive(
					non_directive,
					bkl,
					symtab)
				== PreprocessorExitCode::SUCCESS) {
				break;
			}
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_if_section(
	PreprocessingAstNode*       & if_section,
	AlertList                   & bkl,
	SymbolTable                 & symtab,	
	PreprocessingAstNode*       & executed_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* if_group
		= if_section->get_child();
	PreprocessingAstNode* if_group_sibling
		= if_group->get_sibling();
	PreprocessingAstNode* elif_groups
		= (if_group_sibling->get_name()
		   == PreprocessingAstNodeName::ELIF_GROUPS)
		  ? if_group_sibling
		  : NULL;
	PreprocessingAstNode* else_group
		= elif_groups
		  ? ((elif_groups->get_sibling()->get_name()
		      == PreprocessingAstNodeName::ELIF_GROUPS)
		     ? elif_groups->get_sibling()
		     : NULL)
		  : ((if_group_sibling->get_name()
		      == PreprocessingAstNodeName::ELSE_GROUP)
		     ? if_group_sibling
			 : NULL);
	PreprocessingAstNode* endif_line
		= else_group
		  ? else_group->get_sibling()
		  : (elif_groups 
		     ? elif_groups->get_sibling()
		     : if_group->get_sibling());

	pp_execute_if_group(
		if_group,
		bkl,
		symtab,
		executed_group);
	if (elif_groups) {
		pp_execute_elif_groups(
			elif_groups,
			bkl,
			symtab);
	}
	if (else_group) {
		pp_execute_else_group(
			else_group,
			bkl,
			symtab);
	}
	pp_execute_endif_line(
		endif_line,
		bkl,
		symtab);

	exitcode = PreprocessorExitCode::SUCCESS;

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_if_group(
	PreprocessingAstNode*       & if_group,
	AlertList                   & bkl,
	SymbolTable                 & symtab,
	PreprocessingAstNode*       & executed_group)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (if_group->get_alt()) {

		case PreprocessingAstNodeAlt::IF_GROUP_1:
		{
			PreprocessingAstNode* constant_expression
				= if_group->get_child();
			PreprocessingAstNode* new_line
				= constant_expression->get_sibling();
			PreprocessingAstNode* lower_group
				= new_line->get_sibling();

			PreprocessingToken preprocessing_tokens[16]
				= { };
			PreprocessingToken* preprocessing_tokens_ptr
				= preprocessing_tokens;

			/* Get the Tokens within the conditional expression. */
			pp_gen_pp_tokens(
				constant_expression->get_child(),
				preprocessing_tokens_ptr,
				bkl,
				symtab);
			int num_preprocessing_tokens
				= preprocessing_tokens_ptr 
				  - preprocessing_tokens;

			preprocessing_tokens_ptr
				= preprocessing_tokens;
			Token tokens[16]
				= { };
			Token* tokens_ptr
				= tokens;

			lex(
				preprocessing_tokens_ptr,
				tokens_ptr,
				num_preprocessing_tokens,
				bkl);

			/* Get the Abstract Syntax Tree associated
				with the conditional expression. */
			const Token* new_tokens_ptr
				= tokens;
			AstNode* ast_constant_expression;
			parse_constant_expression(
				NULL,
				new_tokens_ptr,
				ast_constant_expression);

			/* Annotate the abstract syntax tree associated
				with the conditional expression. */
			AnnotatedAstNode* anno_ast_constant_expression;
			construct_unatrributed_annotated_ast(
				ast_constant_expression,
				anno_ast_constant_expression);
			SymbolTable* symtab = new SymbolTable();
			visit_constant_expression(
				anno_ast_constant_expression,
				symtab);

			uint64_t constant_expression_val
				= 0;

			constant_expression_val
				= anno_ast_constant_expression->get_constant_val()
				  != 0;

			if (constant_expression_val) {
				executed_group = lower_group;
			}
			exitcode = PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::IF_GROUP_2:
		{	
			PreprocessingAstNode* identifier
				= if_group->get_child();
			PreprocessingAstNode* new_line
				= identifier->get_sibling();
			PreprocessingAstNode* group
				= new_line->get_sibling();
			break;
		}
		
		case PreprocessingAstNodeAlt::IF_GROUP_3:
		{
			PreprocessingAstNode* identifier
				= if_group->get_child();
			PreprocessingAstNode* new_line
				= identifier->get_sibling();
			PreprocessingAstNode* group
				= new_line->get_sibling();

			break;
		}

		default:
			break;

	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_elif_groups(
	PreprocessingAstNode* & elif_groups,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (elif_groups->get_alt()) {

		case PreprocessingAstNodeAlt::ELIF_GROUPS_1:
		{
			PreprocessingAstNode* elif_group
				= elif_groups->get_child();
			if (pp_execute_elif_group(
					elif_group,
					bkl,
					symtab)
				== PreprocessorExitCode::FAILURE) {
				break;
			}
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::ELIF_GROUPS_2:
		{
			PreprocessingAstNode* lesser_elif_groups
				= elif_groups->get_child();
			PreprocessingAstNode* elif_group
				= lesser_elif_groups->get_sibling();
			if (pp_execute_elif_groups(
					lesser_elif_groups,
					bkl,
					symtab)
				== PreprocessorExitCode::FAILURE) {
				break;
			}
			if (pp_execute_elif_group(
					elif_group,
					bkl,
					symtab)
				== PreprocessorExitCode::FAILURE) {
				break;
			}
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_identifier_list(
	PreprocessingAstNode* & identifier_list,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_constant_expression(
	PreprocessingAstNode* & constant_expression,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_elif_group(
	PreprocessingAstNode* & elif_group,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_else_group(
	PreprocessingAstNode* & else_group,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_endif_line(
	PreprocessingAstNode* & endif_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_1(
	PreprocessingAstNode* & control_line,
	PreprocessingAstNode* & group_part,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	/* TODO; */
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_2(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	PreprocessingAstNode* identifier
		= control_line->get_child();
	PreprocessingAstNode* replacement_list
		= identifier->get_sibling();

	PreprocessingToken* terminal
		= identifier->get_terminal();
	const char* lexeme 
		= terminal->get_lexeme();

	symtab.add_entry(
		lexeme);
	SymbolTableEntry* entry 
		= symtab.get_entry(lexeme);
	entry->identifier_type  
		= IdentifierClassifier::MACRO_NAME;
	entry->replacement_list 
		= replacement_list;

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_3(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_4(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_5(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_6(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable			  & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_7(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_8(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line_9(
	PreprocessingAstNode* & control_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_control_line(
	PreprocessingAstNode* & control_line,
	PreprocessingAstNode* & group_part,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	switch (control_line->get_alt()) {

		case PreprocessingAstNodeAlt::CONTROL_LINE_1:
		{
			pp_execute_control_line_1(
				control_line,
				group_part,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_2:
		{
			pp_execute_control_line_2(
				control_line,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_3:
		{
			pp_execute_control_line_3(
				control_line,
				bkl,
				symtab);
			break;
		}
		
		case PreprocessingAstNodeAlt::CONTROL_LINE_4:
		{
			pp_execute_control_line_4(
				control_line,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_5:
		{
			pp_execute_control_line_5(
				control_line,
				bkl,
				symtab);
			break;
		}
		
		case PreprocessingAstNodeAlt::CONTROL_LINE_6:
		{	pp_execute_control_line_6(
				control_line,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_7:
		{
			pp_execute_control_line_7(
				control_line,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_8:
		{
			pp_execute_control_line_8(
				control_line,
				bkl,
				symtab);
			break;
		}

		case PreprocessingAstNodeAlt::CONTROL_LINE_9:
		{
			pp_execute_control_line_9(
				control_line,
				bkl,
				symtab);
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
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_text_line(
	PreprocessingAstNode* & text_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_new_line(
	PreprocessingAstNode* & new_line,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_non_directive(
	PreprocessingAstNode* & non_directive,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_lparen(
	PreprocessingAstNode* & lparen,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_replacement_list(
	PreprocessingAstNode* & replacement_list,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	
	return exitcode;
}

static inline
PreprocessorExitCode pp_insert_macro_replacement_list(
	PreprocessingAstNode* & replacement_list,
	PreprocessingAstNode* & pp_tokens,
	SymbolTable           & symtab)
{ 
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::FAILURE;

	switch (pp_tokens->get_alt()) {

		case PreprocessingAstNodeAlt::PP_TOKENS_1:
		{
			PreprocessingAstNode* preprocessing_token
				= pp_tokens->get_child();
			PreprocessingAstNode* lower_pp_tokens
				= replacement_list->get_child();
			PreprocessingAstNode* higher_pp_tokens
				= new PreprocessingAstNode(
					PreprocessingAstNodeName::PP_TOKENS,
					PreprocessingAstNodeAlt::PP_TOKENS_2,
					NULL);
			higher_pp_tokens->add_child(
				lower_pp_tokens);
			higher_pp_tokens->add_child(
				preprocessing_token);
			pp_tokens
				= higher_pp_tokens;
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::PP_TOKENS_2:
		{
			PreprocessingAstNode* lower_pp_tokens
				= replacement_list->get_child();
			pp_insert_macro_replacement_list(
				replacement_list,
				lower_pp_tokens,
				symtab);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_execute_pp_tokens(
	PreprocessingAstNode* & pp_tokens,
	AlertList             & bkl,
	SymbolTable           & symtab)
{
	PreprocessorExitCode exitcode
		= PreprocessorExitCode::SUCCESS;

	/* Macro Invocation. */
	switch (pp_tokens->get_alt()) {

		case PreprocessingAstNodeAlt::PP_TOKENS_1:
		{
			PreprocessingAstNode* preprocessing_token
				= pp_tokens->get_child();

			PreprocessingToken* const terminal
				= preprocessing_token->get_terminal();
			if (terminal->get_name()
				== PreprocessingTokenName::IDENTIFIER) {

				const char* lexeme
					= terminal->get_lexeme();
				SymbolTableEntry* entry
					= symtab.get_entry(lexeme);
				if (entry != NULL
					&& (entry->identifier_type 
					    == IdentifierClassifier::MACRO_NAME)) {

					/* Insert the tokens within the macro here. */
					PreprocessingAstNode* replacement_list
						= entry->replacement_list;
					pp_insert_macro_replacement_list(
						replacement_list,
						pp_tokens,
						symtab);
				}
			}
			break;
		}
		
		case PreprocessingAstNodeAlt::PP_TOKENS_2:
		{
			PreprocessingAstNode* lower_pp_tokens
				= pp_tokens->get_child();
			PreprocessingAstNode* preprocessing_token
				= lower_pp_tokens->get_sibling();

			PreprocessingToken* const terminal
				= preprocessing_token->get_terminal();
			if (terminal->get_name()
				== PreprocessingTokenName::IDENTIFIER) {

				const char* lexeme
					= terminal->get_lexeme();
				SymbolTableEntry* entry
					= symtab.get_entry(lexeme);
				if (entry != NULL
					&& (entry->identifier_type
						== IdentifierClassifier::MACRO_NAME)) {

					/* Insert the tokens within the macro here. */
					PreprocessingAstNode* replacement_list
						= entry->replacement_list;
					pp_insert_macro_replacement_list(
						replacement_list,
						pp_tokens,
						symtab);
				}
			}
			break;
		}
		
		default:
			break;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_preprocessing_file(
	PreprocessingAstNode* const& preprocessing_file,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	
	symtab = SymbolTable();

	PreprocessingAstNode* group 
		= preprocessing_file->get_child();
	if (group) {

		if (pp_gen_group(
				group,
				output,
				bkl, 
				symtab)
			== PreprocessorExitCode::SUCCESS) {
			exitcode 
				= PreprocessorExitCode::SUCCESS;
		}

	} else {
		exitcode 
			= PreprocessorExitCode::SUCCESS;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_group(
	PreprocessingAstNode* const& group,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	switch (group->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_1:
		{
			PreprocessingAstNode* group_part
				= group->get_child();
			if (pp_gen_group_part(
					group_part,
					output,
					bkl,
					symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_2:
		{
			PreprocessingAstNode* lesser_group
				= group->get_child();
			PreprocessingAstNode* group_part
				= lesser_group->get_sibling();
			if (pp_gen_group(
					lesser_group,
					output,
					bkl,
					symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			if (pp_gen_group_part(
					group_part,
					output,
					bkl,
					symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_group_part(
	PreprocessingAstNode* const& group_part,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (group_part->get_alt()) {

		case PreprocessingAstNodeAlt::GROUP_PART_1:
		{
			/* Cannot generate tokens from
			   an if-section, it is a directive 
			   not text. */
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_2:
		{
			/* Cannot generate tokens from
			   a control-line, it is a directive
			   not text. */
			break;
		}

		case PreprocessingAstNodeAlt::GROUP_PART_3:
		{
			PreprocessingAstNode* text_line
				= group_part->get_child();
			if (pp_gen_text_line(
				text_line,
				output,
				bkl,
				symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
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
				bkl,
				symtab);
			exitcode
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_text_line(
	PreprocessingAstNode* const& text_line,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;

	PreprocessingAstNode* pp_tokens
		= text_line->get_child();
	if (pp_tokens
		&& pp_gen_pp_tokens(
		       pp_tokens,
			   output,
			   bkl,
			   symtab)
			== PreprocessorExitCode::SUCCESS) {
		exitcode 
			= PreprocessorExitCode::SUCCESS;
	} else {
		exitcode
			= PreprocessorExitCode::SUCCESS;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_non_directive(
	PreprocessingAstNode* const& non_directive,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	/* Do not need to do anything in this case, 
	   much like a comment it is ignored. */
	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_pp_tokens(
	PreprocessingAstNode* const& pp_tokens,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::FAILURE;

	switch (pp_tokens->get_alt()) {

		case PreprocessingAstNodeAlt::PP_TOKENS_1:
		{
			PreprocessingAstNode* preprocessing_token
				= pp_tokens->get_child();
			if (pp_gen_preprocessing_token(
					preprocessing_token,
					output,
					bkl,
					symtab) 
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			exitcode 
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		case PreprocessingAstNodeAlt::PP_TOKENS_2:
		{
			PreprocessingAstNode* lesser_pp_tokens
				= pp_tokens->get_child();
			PreprocessingAstNode* preprocessing_token
				= lesser_pp_tokens->get_sibling();
			if (pp_gen_pp_tokens(
					lesser_pp_tokens,
					output,
					bkl,
					symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			if (pp_gen_preprocessing_token(
					preprocessing_token,
					output,
					bkl,
					symtab)
				!= PreprocessorExitCode::SUCCESS) {
				break;
			}
			exitcode 
				= PreprocessorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline
PreprocessorExitCode pp_gen_preprocessing_token(
	PreprocessingAstNode* const& preprocessing_token,
	PreprocessingToken*        & output,
	AlertList                  & bkl,
	SymbolTable                & symtab)
{
	*output++ = *(preprocessing_token->get_terminal());
	return PreprocessorExitCode::SUCCESS;
}

static inline
PreprocessorExitCode preprocess(
	const char*              & input,
	LexemaPool               & lexema_pool,
	const char*         const& filename,
	AlertList                & bkl,
	PreprocessingToken*      & pp_tokens)
{
	PreprocessorExitCode exitcode 
		= PreprocessorExitCode::SUCCESS;
	FileLocationDescriptor file_location_descriptor
		= FileLocationDescriptor( 
			  { filename, 0, 0, 0 } );
	/* Parse the Preprocessing File */
	PreprocessingAstNode* preprocessing_file;
	SymbolTable symtab;
	pp_parse_preprocessing_file(
		input,
		lexema_pool,
		file_location_descriptor,
		bkl,
		preprocessing_file);
	/* Execute the preprocessing file, 
	   acting on given directives. */
	PreprocessingAstNode* executed_preprocessing_file;
	pp_execute_preprocessing_file(
		preprocessing_file,
		bkl,
		executed_preprocessing_file);
	/* Convert the directed preprocessing ast node 
	   tree back into a series of preprocessing 
	   tokens suitable for input into the lexer.   */
	pp_gen_preprocessing_file(
		executed_preprocessing_file,
		pp_tokens,
		bkl,
		symtab);

	return exitcode;
}

#endif