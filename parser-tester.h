
#ifndef PARSER_TESTER_H
#define PARSER_TESTER_H 1

#include "tester-tools.h"
#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>
#include "preprocessor.h"

//////////////////////////////////////////////////////////////////
//      Testing for the recognition of punctuator tokens        //
//////////////////////////////////////////////////////////////////

#define NUM_MISRA_TESTS 133

static const char* misra_test_case_filenames[NUM_MISRA_TESTS] = {
	"misra.h",
};

inline TestResult test_misra_tests(
	TestResult results[NUM_MISRA_TESTS])
{
	bool all_tests_passed = true;

	for (const char** testcase = misra_test_case_filenames;
		testcase < misra_test_case_filenames + NUM_MISRA_TESTS;
		testcase++) {

		/* Get characters in the file. */
		const char* filename = *testcase;
		string filename_str = "./test-cases/misrul10/" + string(filename);
		std::ifstream f(filename_str);
		std::stringstream buffer;
		buffer << f.rdbuf();
		string buffer_str = buffer.str();
		const char* file = buffer_str.c_str();
		FileLocationDescriptor fld(*testcase, 0, 0);

		/* Get the preprocessing tokens from the characters */
		PreprocessingToken* ppts
			= new PreprocessingToken[buffer.str().size()];
		PreprocessingToken* ppts_ptr = ppts;
		preprocess(file, fld, ppts_ptr);
		int count_pptokens = ppts_ptr - ppts;
		for (PreprocessingToken* p = ppts;
			p < ppts + count_pptokens;
			p++) {
			p->print();
			cout << endl;
		}

		/* Get the tokens from the preprocessing tokens. */
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
		const char* err_lexeme = "";
		*(tokens + count_pptokens) = Token(TokenName::ERROR, TokenForm::SIMPLE, { 0 }, err_lexeme);
		AstNode* ast_root = NULL;
		parse(tokens, ast_root);
		if (ast_root != NULL) {
			ast_root->print();
		}

		/* Return results */
		bool success_criteria = ast_root != NULL;
		results[testcase - misra_test_case_filenames]
			= success_criteria 
			  ? TestResult::SUCCESS 
			  : TestResult::FAIL;
		
		if (!success_criteria) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//     Code for running and presenting the results of tests     //
//////////////////////////////////////////////////////////////////

#define NUM_PARSER_TESTS NUM_MISRA_TESTS
 
inline TestResult test_parser(
	TestResult results[NUM_PARSER_TESTS],
	char*& output,
	int indent = 0)
{
	for (int i = 0; i < indent; i++) {
		print_to_output("\t", output);
	}
	print_to_output("<-> ParserIntegrationTests", output);
	print_to_output("\n", output);

	TestResult misra_test_results[NUM_MISRA_TESTS];
	TestResult misra_test_result = test_misra_tests(misra_test_results);

	const char* misra_title = "MisraTests";
	present_test_set_synopsis(
		misra_title,
		misra_test_result,
		misra_test_results,
		NUM_MISRA_TESTS,
		output,
		indent + 1
	);

	return (misra_test_result == TestResult::SUCCESS)
		   ? TestResult::SUCCESS
		   : TestResult::FAIL;
}

#endif