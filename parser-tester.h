
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
	"misra.h",	"misra1.c",	"misra10.c",	"misra100.c",	"misra101.c",	"misra102.c",	"misra103.c",	"misra104.c",	"misra105.c",	"misra106.c",	"misra107.c",	"misra108.c",	"misra109.c",	"misra11.c",	"misra110.c",	"misra111.c",	"misra112.c",	"misra113.c",	"misra114.c",	"misra115.c",	"misra117.c",	"misra118.c",	"misra119.c",	"misra12.c",	"misra120.c",	"misra121.c",	"misra122.c",	"misra123.c",	"misra124.c",	"misra125.h",	"misra126.c",	"misra127.c",	"misra13.c",	"misra14.c",	"misra15.c",	"misra16.c",	"misra17.c",	"misra18.c",	"misra19.c",	"misra1a.c",	"misra1b.c",	"misra1c",	"misra20.c",	"misra21.c",	"misra22.c",	"misra23.c",	"misra24.c",	"misra25a.c",	"misra25b.c",	"misra26a.c",	"misra26b.c",	"misra27.c",	"misra27.h",	"misra28.c",	"misra29.c",	"misra3.c",	"misra30.c",	"misra31.c",	"misra32.c",	"misra33.c",	"misra34.c",	"misra35.c",	"misra36.c",	"misra37.c",	"misra38.c",	"misra39.c",	"misra4.c",	"misra40.c",	"misra41.c",	"misra42.c",	"misra43.c",	"misra44.c",	"misra45.c",	"misra46.c",	"misra47.c",	"misra48.c",	"misra49.c",	"misra5.c",	"misra50.c",	"misra51.c",	"misra52.c",	"misra53.c",	"misra54.c",	"misra55.c",	"misra56.c",	"misra57.c",	"misra58.c",	"misra59.c",	"misra6.c",	"misra60.c",	"misra61.c",	"misra62.c",	"misra63.c",	"misra64.c",	"misra65.c",	"misra66.c",	"misra67.c",	"misra68.c",	"misra69.c",	"misra7.c",	"misra70.c",	"misra70a.c",	"misra71.c",	"misra72.c",	"misra73.c",	"misra74.c",	"misra75.c",	"misra76.c",	"misra77.c",	"misra78.c",	"misra79.c",	"misra8.c",	"misra80.c",	"misra81.c",	"misra82.c",	"misra83.c",	"misra84.c",	"misra85.c",	"misra86.c",	"misra87.c",	"misra88.c",	"misra89.c",	"misra9.c",	"misra90.c",	"misra91.c",	"misra92.c",	"misra93.c",	"misra94.c",	"misra95.c",	"misra96.c",	"misra97.c",	"misra98.c",	"misra99.c",
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