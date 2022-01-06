
#ifndef DRIVER_CPP
#define DRIVER_CPP 1

#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "kcc-tester.h"
#include "semantic-annotator.h"

#define NUM_INPUT_CHARACTERS	 1028
#define NUM_PREPROCESSING_TOKENS 1028
#define NUM_ASSEMBLY_TOKENS		 1028

inline void drive(
	FileLocationDescriptor const& fld,
   const char*& input) {

	PreprocessingToken* ppts 
		= new PreprocessingToken[NUM_PREPROCESSING_TOKENS];

	PreprocessingToken* ppts_ptr = ppts;
		preprocess(input, fld, ppts_ptr);

	int count_pptokens = ppts_ptr - ppts;
	
	for (PreprocessingToken* p = ppts;
		p < ppts + count_pptokens;
		p++) {
		p->print();
		cout << endl;
	}

	Token* tokens = new Token[count_pptokens + 1];
	Token* tokens_ptr = tokens;
	lex(ppts, tokens_ptr, count_pptokens);
	int count_tokens = tokens_ptr - tokens;

	for (Token* t = tokens;
		t < tokens + count_tokens;
		t++) {
		t->print();
		cout << endl;
	}

	AstNode* ast_root = NULL;
 	parse(tokens, ast_root);
	if (ast_root != NULL) {
		ast_root->print();
	}

	AnnotatedAstNode* anno_ast_root = NULL;
	annotate(ast_root, anno_ast_root);
	if (anno_ast_root != NULL) {
		anno_ast_root->print();
	}
	x86_AssemblyInstruction* instrs 
		= new x86_AssemblyInstruction[NUM_ASSEMBLY_TOKENS];
	StackDescriptor stack = {
		{ 0 },
		0,
		0
	};
	gen(stack, anno_ast_root, instrs);

	cout << "----- Stack -----" << endl;
	print_stack(stack);
	
	delete ppts;
	delete tokens;
	delete ast_root;
	/*delete instrs;*/
}

void main() {
	//kcc_run_tests();
	//return;*/
	FileLocationDescriptor fld = FileLocationDescriptor("test.c", 0, 0);
	////const char *input = new char[NUM_INPUT_CHARACTERS] {
	////	"float Q_rsqrt( float number )\n"
	////	"{\n"
	////	"long i;\n"
	////	"float x2, y;\n"
	////	"const float threehalfs = 1.5F;\n"
	////	"x2 = number * 0.5F;\n"
	////	"y  = number;\n"
	////	"i  = * ( long * ) &y; // evil floating point bit level hacking\n"
	////	"i  = 0x5f3759df - ( i >> 1 ); // what the\n"
	////	"y  = * ( float * ) &i;\n"
	////	"y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration\n"
	////	"//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed\n"
	////	"return y;\n"
	////	"}\n",
	////};
	const char* input = new char[NUM_INPUT_CHARACTERS] {
		"float Q_rsqrt( float number )\n"
			"{\n"
			"long i;\n"
			"float x2, y;\n"
			"const float threehalfs = 1.5F;\n"
			"x2 = number * 0.5F;\n"
			"y  = number;\n"
			"return y;\n"
			"}\n",
	};
	drive(fld, input);
}

#endif