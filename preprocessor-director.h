
#ifdef PREPROCESSOR_DIRECTOR_H
#define PREPROCESSOR_DIRECTOR_H 1

#include "preprocessor.h"

#define pp_free_stack(s, si) while (si > 0) { delete stack[--si]; } 

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
	NEW_LINE
};

static const char* preprocessing_ast_form_string_reprs[] {
	/* Error */
	"ERROR",
	/* Terminals */
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
	"NEW_LINE"
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
	NEW_LINE_1
};

static const char* preprocessing_ast_node_alt_string_reprs[]{
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
	"NEW_LINE_1"
};


class PreprocessingAstNode {
private:
	PreprocessingAstNodeName name;
	PreprocessingAstNodeAlt alt;
	PreprocessingToken* terminal;
	PreprocessingAstNode* child;
	PreprocessingAstNode* sibling;
public:
	inline PreprocessingAstNode(
		PreprocessingAstNodeName const& n,
		PreprocessingAstNodeAlt  const& a,
		PreprocessingToken* const& t) :
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
		int const& count)
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
		string child_prefix = "")
	{
		cout << parent_prefix
			<< "name="
			<< preprocessing_ast_form_string_reprs[(int)name]
			<< ",alt="
			<< preprocessing_ast_node_alt_string_reprs[(int)alt];
		if (terminal) terminal->print();
		cout << endl;
		PreprocessingAstNode* node = child;
		for (; node; node = node->sibling) {
			if (node->sibling) {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "|    ";
				node->print(appended_p, appended_c);
			}
			else {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "     ";
				node->print(appended_p, appended_c);
			}
		}
	}
};

PreprocessingAstNode* construct_node_from_children(
	PreprocessingAstNodeName const& name,
	PreprocessingAstNodeAlt const& alt,
	PreprocessingAstNode** const& children,
	int const& count);

PreprocessorExitCode pp_parse_preprocessing_file(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& preprocessing_file);

PreprocessorExitCode pp_parse_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& group);

PreprocessorExitCode pp_parse_group_part(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& group_part);

PreprocessorExitCode pp_parse_if_section(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& if_section);

PreprocessorExitCode pp_parse_if_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& if_group);

PreprocessorExitCode pp_parse_elif_groups(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& elif_groups);

PreprocessorExitCode pp_parse_elif_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& elif_group);

PreprocessorExitCode pp_parse_else_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& else_group);

PreprocessorExitCode pp_parse_endif_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& endif_line);

PreprocessorExitCode pp_parse_control_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& control_line);

PreprocessorExitCode pp_parse_text_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& text_line);

PreprocessorExitCode pp_parse_non_directive(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& non_directive);

PreprocessorExitCode pp_parse_lparen(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& lparen);

PreprocessorExitCode pp_parse_replacement_list(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& replacement_list);

PreprocessorExitCode preprocessor_parse_pp_tokens(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& pp_tokens);

static inline PreprocessingAstNode* construct_node_from_children(
	PreprocessingAstNodeName const& name,
	PreprocessingAstNodeAlt const& alt,
	PreprocessingAstNode** const& children,
	int const& count)
{
	PreprocessingAstNode* node = new PreprocessingAstNode(
		name,
		alt,
		NULL
	);
	node->add_children(children, count);
	return node;
}

static inline PreprocessorExitCode pp_parse_preprocessing_file(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& preprocessing_file)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	
	PreprocessingAstNode* group;
	if (pp_parse_group(tokens, group)
		== PreprocessorExitCode::SUCCESS) {
		
		preprocessing_file = new PreprocessingAstNode(
			PreprocessingAstNodeName::PREPROCESSING_FILE,
			PreprocessingAstNodeAlt::PREPROCESSING_FILE_1,
			tokens++);
		exitcode = PreprocessorExitCode::SUCCESS;
	}
	
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& group)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	
	PreprocessingAstNode* stack[16];
	int si = 0;

	bool should_generate = false;
	switch (Directives::IF) {
		case IF:
			if (pp_parse)
			break;
		case IFDEF:
			if (pp_parse_group()) {

			}
			break;
		case IFNDEF:
		{
			if (tokens->get_name()
				== PreprocessingTokenName::IDENTIFIER) {
				stack[si++] = construct_terminal(tokens++);
				//if new line {
				if (pp_parse_group(tokens, group)
					== PreprocessorExitCode::SUCCESS) {
					stack[si++] = group;
				}
				alt = PreprocessingAstNodeAlt::IF_GROUP_1;
				//}
			}
			if (pp_parse_group()) {

			}
		}

		default:
			break;
	}
	if (should_generate) {
		construct_node_from_children(
			group, 
			alt,
			stack,
			si);
	}
	else {
		free_stack(stack, si);
	}

	return exitcode;
}

static inline PreprocessorExitCode pp_parse_group_part(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& group_part)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	
	switch () {

	}

	return exitcode;
}

static inline PreprocessorExitCode pp_parse_if_section(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& if_section)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	
	PreprocessingAstNode* stack[16];
	int si = 0;
	bool should_generate = false;

	PreprocessingAstNode* if_group;
	if (pp_parse_if_group(tokens, if_group)
		== PreprocessorExitCode::SUCCESS) {		
		stack[si++] = if_group;

		PreprocessingAstNode* elif_groups;
		if (pp_parse_elif_groups(tokens, elif_groups)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = elif_groups;
		}

		PreprocessingAstNode* else_group;
		if (pp_parse_else_group(tokens, else_group)
			== PreprocessorExitCode::SUCCESS) {
			stack[si++] = else_group;
		}

		PreprocessingAstNode* endif_line;
		if (pp_parse_endif_line(tokens, endif_line)
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
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& if_group)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_elif_groups(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& elif_groups)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_elif_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& elif_group)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_else_group(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& else_group)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_endif_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& endif_line)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_control_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& control_line)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_text_line(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& text_line)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_non_directive(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& non_directive)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_lparen(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& lparen)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode pp_parse_replacement_list(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& replacement_list)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

static inline PreprocessorExitCode preprocessor_parse_pp_tokens(
	PreprocessingToken*& tokens,
	PreprocessingAstNode*& pp_tokens)
{
	PreprocessorExitCode exitcode = PreprocessorExitCode::FAILURE;
	return exitcode;
}

#endif