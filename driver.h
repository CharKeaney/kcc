
#ifndef DRIVER_H
#define DRIVER_H 1

#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "semantic-annotator.h"

#include "kcc-tester.h"

#define NUM_INPUT_CHARACTERS	 1028
#define NUM_PREPROCESSING_TOKENS 1028
#define NUM_ASSEMBLY_TOKENS		 1028

#define DEBUG_OUTPUT_PPTOKENS	 0
#define DEBUG_OUTPUT_TOKENS		 0
#define DEBUG_OUTPUT_TREE		 0
#define DEBUG_OUTPUT_ANNO_TREE	 1
#define DEBUG_OUTPUT_X86		 0
#define DEBUG_OUTPUT_NOTHING	 0

enum class CompilerFlags {
	OUTPUT_PPTOKENS,
	OUTPUT_TOKENS,
	OUTPUT_TREE,
	OUTPUT_ANNO_TREE,
	OUTPUT_X86,
	OUTPUT_NOTHING
};

enum class KccExitCode {
	SUCCESS,
	FAIL
};

static inline KccExitCode drive(
	FileLocationDescriptor const& fld,
	const char*& input,
	CompilerFlags flag = CompilerFlags::OUTPUT_X86)
{
	KccExitCode exitcode = KccExitCode::FAIL;

	PreprocessingToken* ppts = NULL;
	const char** lexema_produced = NULL;
	Token* tokens = NULL;
	AstNode* ast_root = NULL;
	AnnotatedAstNode* anno_ast_root = NULL;
	x86_AssemblyInstruction* instrs = NULL;

	if (input != NULL) {

		/* Preprocessing. */
		ppts = new PreprocessingToken[NUM_PREPROCESSING_TOKENS] { };
		lexema_produced = new const char* [NUM_PREPROCESSING_TOKENS] { };
		const char** lexema_produced_ptr = lexema_produced;
		PreprocessingToken* ppts_ptr = ppts;
		preprocess(input, lexema_produced_ptr, fld, ppts_ptr);
		int count_pptokens = ppts_ptr - ppts;

		if (flag == CompilerFlags::OUTPUT_PPTOKENS
			|| DEBUG_OUTPUT_PPTOKENS) {
			for (PreprocessingToken* p = ppts;
				p < ppts + count_pptokens;
				p++) {
				p->print();
				cout << endl;
			}
		}

		/* Lexing. */
		tokens = new Token[count_pptokens + 1] { };
		Token* tokens_lex_ptr = tokens;
		lex(ppts, tokens_lex_ptr, count_pptokens);
		int count_tokens = tokens_lex_ptr - tokens;

		if (flag == CompilerFlags::OUTPUT_TOKENS
			|| DEBUG_OUTPUT_TOKENS) {
			for (Token* base_type = tokens;
				base_type < tokens + count_tokens;
				base_type++) {
				base_type->print();
				cout << endl;
			}
		}

		/* Parsing. */
		Token* tokens_parse_ptr = tokens;
		parse(tokens_parse_ptr, ast_root);
		if (flag == CompilerFlags::OUTPUT_TREE) {
			ast_root->print();
		}

		/* Semantic Analysis. */
		annotate(ast_root, anno_ast_root);
		if (flag == CompilerFlags::OUTPUT_ANNO_TREE
			|| DEBUG_OUTPUT_ANNO_TREE) {
			anno_ast_root->print();
		}

		/* Code Generation. */
		instrs = new x86_AssemblyInstruction[NUM_ASSEMBLY_TOKENS] { };
		x86_AssemblyInstruction* instrs_ptr
			= instrs;

		if (flag == CompilerFlags::OUTPUT_X86
			|| DEBUG_OUTPUT_X86) {
			int num_labels = 0;
			gen(num_labels, anno_ast_root, instrs_ptr);
			for (x86_AssemblyInstruction* base_type = instrs;
				base_type != instrs_ptr;
				base_type++) {
				base_type->print();
			}
		}
	}
	/* Memory Management. */
	if (ppts) {
		delete[] ppts;
	}
	if (lexema_produced) {
		for (const char** l = lexema_produced;
			*l != NULL;
			l++) {
			delete *l;
		}
		delete[] lexema_produced;
	}
	if (tokens) {
		delete[] tokens;
	}
	if (ast_root) {
		delete ast_root;
	}
	if (anno_ast_root) {
		delete anno_ast_root;
	}
	if (instrs) {
		delete[] instrs;
	}
	/* Returning*/
	return exitcode;
}


#endif