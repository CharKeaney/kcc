
#ifndef KCC_TESTER_H
#define KCC_TESTER_H 1

#include "lexer-tester.h"
#include "preprocessor-tester.h"
#include "parser-tester.h"

 inline void kcc_run_tests() 
{
	char output[1 << 16];
	char* o = output;

	print_to_output("<-> KCC-Tests\n", o);
	
	TestResult pp_results[NUM_PREPROCESSOR_TESTS];
	TestResult pp_result = test_preprocessor(pp_results, o, 1);

	TestResult lex_results[NUM_LEX_TESTS];
	TestResult lex_result = test_lex(lex_results, o, 1);

	TestResult parser_results[NUM_PARSER_TESTS];
	TestResult parser_result = test_parser(parser_results, o, 1);
	
	*o++ = NULL;
	cout << output;
}

#endif