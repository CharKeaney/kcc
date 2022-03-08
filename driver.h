
#ifndef DRIVER_H
#define DRIVER_H 1

#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "semantic-annotator.h"
#include "annotated-ast-node.h" 

#include "kcc-tester.h"

#define NUM_INPUT_CHARACTERS	 1028
#define NUM_PREPROCESSING_TOKENS 1028
#define NUM_ASSEMBLY_TOKENS		 1028

enum class CompilerFlag {
	DISPLAY_PPTOKENS,
	DISPLAY_TOKENS,
	DISPLAY_TREE,
	DISPLAY_ANNO_TREE,
	DISPLAY_X86,
	DISPLAY_NOTHING
};

struct CompilerFlags {
	bool help             : 1;
	bool display_pptokens : 1;
	bool display_tokens   : 1;
	bool display_tree     : 1;
	bool display_annotree : 1;
	bool display_x86      : 1;
	bool display_nothing  : 1;
};

struct CompilerArgs {
	CompilerFlags flags;
	const char* dest;
};

enum class KccExitCode {
	SUCCESS,
	FAIL
};

const char* help_msg 
	= "Keaney's C Compiler (c) 2022\n"
	  "Designed by Charlie Keaney of Queen's " 
	  "University Belfast during his MEng "
	  "Computer Science Program.\n"
	  "This compiler is designed for the "
	  "output of x86-64 Bit.\n"
	  "Run it with the command :\n"
	  "\tkcc -<options> <args>\n"
	  "\n"
	  "\t\t\tOptions\n"
	  "\t-h : Display help menu.\n"
	  "\t-p : Display produced preprocessing tokens.\n"
	  "\t-l : Display produced lexer tokens.\n"
	  "\t-t : Display produced abstract syntax tree.\n"
	  "\t-s : Display produced abstract syntax tree"
	  " with semantic annotations.\n"
	  "\t-p : Display produced x86 code.\n"
	  "\t-m : Mute (display nothing) (default).\n";

static inline void print_help() {
	cout << help_msg;
}

struct CompilationEnvironment {
	PreprocessingToken*      ppts;
	const char**             lexema;
	Token*                   tokens;
	AstNode*                 ast_root;
	AnnotatedAstNode*        anno_ast_root;
	x86_Asm_IR* instrs;
	AlertList                bkl;
};

static inline void free_compilation_environment(
	CompilationEnvironment& environment) 
{
	if (environment.ppts) {
		delete[] environment.ppts;
		environment.ppts = NULL;
	}
	if (environment.lexema) {
		for (const char** l = environment.lexema;
			*l != NULL;
			l++) {
			delete* l;
			*l = NULL;
		}
		delete[] environment.lexema;
		environment.lexema = NULL;
	}
	if (environment.tokens) {
		delete[] environment.tokens;
		environment.tokens = NULL;
	}
	if (environment.ast_root) {
		delete environment.ast_root;
		environment.ast_root = NULL;
	}
	if (environment.anno_ast_root) {
		delete environment.anno_ast_root;
		environment.anno_ast_root = NULL;
	}
	if (environment.instrs) {
		delete[] environment.instrs;
		environment.instrs = NULL;
	}
}

static inline KccExitCode drive(
	const char*         const& filename,
	const char*         const& input,
	const CompilerFlags const& flags)
{
	if (flags.help) {
		print_help();
	}

	KccExitCode exitcode = KccExitCode::FAIL;

	CompilationEnvironment environment = CompilationEnvironment({ 0 });
	environment.bkl = AlertList();

	/* Preprocessing. */
	environment.ppts 
		= new PreprocessingToken[NUM_PREPROCESSING_TOKENS] { };
	environment.lexema 
		= new const char* [NUM_PREPROCESSING_TOKENS] { };
	const char** lexema_produced_ptr 
		= environment.lexema;
	PreprocessingToken* ppts_ptr 
		= environment.ppts;

	const char* input_ptr = input;
	if (preprocess(
		input_ptr,
		lexema_produced_ptr,
		filename,
		environment.bkl,
		ppts_ptr
		)
		== PreprocessorExitCode::SUCCESS) {

		int count_pptokens 
			= ppts_ptr - environment.ppts;

		if (flags.display_pptokens) {
			print_preprocessing_token_table(
				environment.ppts, 
				count_pptokens);
		}

		/* Lexing. */
		environment.tokens 
			= new Token[count_pptokens + 1] { };
		Token* tokens_lex_ptr 
			= environment.tokens;
		if (lex(
			environment.ppts, 
			tokens_lex_ptr, 
			count_pptokens,
			environment.bkl) 
			== LexerExitCode::SUCCESS) { 
			int count_tokens 
				= tokens_lex_ptr - environment.tokens;

			if (flags.display_tokens) {

				for (Token* t = environment.tokens;
					t < environment.tokens + count_tokens;
					t++) {
					t->print();
					cout << endl;
				}
			}

			/* Parsing. */
			const Token* tokens_parse_ptr 
				= environment.tokens;
			if (parse(
				tokens_parse_ptr,
				environment.ast_root) 
				== ParserExitCode::SUCCESS) {

				if (flags.display_tree) {
					environment.ast_root->print();
				}

				/* Semantic Analysis. */
				if (annotate(
					environment.ast_root,
					environment.anno_ast_root) 
					== SemanticAnnotatorExitCode::SUCCESS) { 

					if (flags.display_annotree) {
						environment.anno_ast_root->print();
					}

					/* Code Generation. */
					environment.instrs
						= new x86_Asm_IR[NUM_ASSEMBLY_TOKENS]{ };
					x86_Asm_IR* instrs_ptr
						= environment.instrs;
										
					int num_labels = 0;
					gen(num_labels,
						environment.anno_ast_root,
						instrs_ptr);

					if (flags.display_x86) {
						
						for (x86_Asm_IR* i = environment.instrs;
							 i != instrs_ptr;
							 i++) {
							i->print();
						}
					}
				}
			}
		}
	}
	environment.bkl.print(input);
	/* Memory Management. */
	free_compilation_environment(environment);
	/* Returning*/
	return exitcode;
}

/*
	kcc-directive:
		kcc <flags> <filepath>

	flags:
		<flags> <flag>
	    | <flag> 

	flag:
		-<flag-mnemonics>

	flag-mnemonic:
		h
		| p
		| l
		| t
		| s
		| x
		| m

	-<arg>
*/

static inline void interpret_args(
	const char** const& argv, 
	int          const& argc) 
{
	CompilerArgs  args  = CompilerArgs({ 0 });
	CompilerFlags flags = CompilerFlags({ 0 });
	/* Fill args.flags */
	const char* chr = argv[1];
	if (*chr == '-') {
		while (*chr) {
			switch (*chr++) {
				case 'h': flags.help             = true; break;
				case 'p': flags.display_pptokens = true; break;
				case 'l': flags.display_tokens   = true; break;
				case 't': flags.display_tree     = true; break;
				case 's': flags.display_annotree = true; break;
				case 'x': flags.display_x86      = true; break;
				case 'm': flags.display_nothing  = true; break;
				default: break;
			}
		}
	} 
	args.flags = flags;
	/* Fill args.dest */
	args.dest = argv[2];

}

#endif