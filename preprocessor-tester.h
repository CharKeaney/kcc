/* Authored By Charlie Keaney                   */
/* preprocessor.h - Responsible for testing the
					preprocessor.
					Note: Temporarily defunct.  */

#ifdef PREPROCESSOR_TESTER_CPP
#define PREPROCESSOR_TESTER_CPP 1

#include "preprocessor.h"
#include "tester-tools.h"

#define NUM_PREPROCESSOR_TESTS NUM_PP_IDENTIFIER_TESTS

//////////////////////////////////////////////////////////////////
//      Testing for the recognition of identifier tokens        //
//////////////////////////////////////////////////////////////////

#define NUM_PP_IDENTIFIER_TESTS 82

struct pp_identifier_test_case {
	const char* lexeme;
	PreprocessingTokenName name;
};

static const 
pp_identifier_test_case test_pp_identifier_table[NUM_PP_IDENTIFIER_TESTS] = {
	{"auto", PreprocessingTokenName::IDENTIFIER},
	{"break", PreprocessingTokenName::IDENTIFIER},
	{"case", PreprocessingTokenName::IDENTIFIER},
	{"char", PreprocessingTokenName::IDENTIFIER},
	{"const", PreprocessingTokenName::IDENTIFIER},
	{"continue", PreprocessingTokenName::IDENTIFIER},
	{"default", PreprocessingTokenName::IDENTIFIER},
	{"do", PreprocessingTokenName::IDENTIFIER},
	{"double", PreprocessingTokenName::IDENTIFIER},
	{"else", PreprocessingTokenName::IDENTIFIER},
	{"enum", PreprocessingTokenName::IDENTIFIER},
	{"extern", PreprocessingTokenName::IDENTIFIER},
	{"float", PreprocessingTokenName::IDENTIFIER},
	{"for", PreprocessingTokenName::IDENTIFIER},
	{"goto", PreprocessingTokenName::IDENTIFIER},
	{"if", PreprocessingTokenName::IDENTIFIER},
	{"inline", PreprocessingTokenName::IDENTIFIER},
	{"int", PreprocessingTokenName::IDENTIFIER},
	{"long", PreprocessingTokenName::IDENTIFIER},
	{"register", PreprocessingTokenName::IDENTIFIER},
	{"restrict", PreprocessingTokenName::IDENTIFIER},
	{"return", PreprocessingTokenName::IDENTIFIER},
	{"short", PreprocessingTokenName::IDENTIFIER},
	{"signed", PreprocessingTokenName::IDENTIFIER},
	{"sizeof", PreprocessingTokenName::IDENTIFIER},
	{"static", PreprocessingTokenName::IDENTIFIER},
	{"struct", PreprocessingTokenName::IDENTIFIER},
	{"switch", PreprocessingTokenName::IDENTIFIER},
	{"typedef", PreprocessingTokenName::IDENTIFIER},
	{"union", PreprocessingTokenName::IDENTIFIER},
	{"unsigned", PreprocessingTokenName::IDENTIFIER},
	{"void", PreprocessingTokenName::IDENTIFIER},
	{"volatile", PreprocessingTokenName::IDENTIFIER},
	{"while", PreprocessingTokenName::IDENTIFIER},
	{"_Bool", PreprocessingTokenName::IDENTIFIER},
	{"_Complex", PreprocessingTokenName::IDENTIFIER},
	{"_Imaginary", PreprocessingTokenName::IDENTIFIER},
	{"autoadditional", PreprocessingTokenName::IDENTIFIER},
	{"breakadditional", PreprocessingTokenName::IDENTIFIER},
	{"caseadditional", PreprocessingTokenName::IDENTIFIER},
	{"charadditional", PreprocessingTokenName::IDENTIFIER},
	{"constadditional", PreprocessingTokenName::IDENTIFIER},
	{"continueadditional", PreprocessingTokenName::IDENTIFIER},
	{"defaultadditional", PreprocessingTokenName::IDENTIFIER},
	{"doadditional", PreprocessingTokenName::IDENTIFIER},
	{"doubleadditional", PreprocessingTokenName::IDENTIFIER},
	{"elseadditional", PreprocessingTokenName::IDENTIFIER},
	{"enumadditional", PreprocessingTokenName::IDENTIFIER},
	{"externadditional", PreprocessingTokenName::IDENTIFIER},
	{"floatadditional", PreprocessingTokenName::IDENTIFIER},
	{"foradditional", PreprocessingTokenName::IDENTIFIER},
	{"gotoadditional", PreprocessingTokenName::IDENTIFIER},
	{"ifadditional", PreprocessingTokenName::IDENTIFIER},
	{"inlineadditional", PreprocessingTokenName::IDENTIFIER},
	{"intadditional", PreprocessingTokenName::IDENTIFIER},
	{"longadditional", PreprocessingTokenName::IDENTIFIER},
	{"registeradditional", PreprocessingTokenName::IDENTIFIER},
	{"restrictadditional", PreprocessingTokenName::IDENTIFIER},
	{"returnadditional", PreprocessingTokenName::IDENTIFIER},
	{"shortadditional", PreprocessingTokenName::IDENTIFIER},
	{"signedadditional", PreprocessingTokenName::IDENTIFIER},
	{"sizeofadditional", PreprocessingTokenName::IDENTIFIER},
	{"staticadditional", PreprocessingTokenName::IDENTIFIER},
	{"structadditional", PreprocessingTokenName::IDENTIFIER},
	{"switchadditional", PreprocessingTokenName::IDENTIFIER},
	{"typedefadditional", PreprocessingTokenName::IDENTIFIER},
	{"unionadditional", PreprocessingTokenName::IDENTIFIER},
	{"unsignedadditional", PreprocessingTokenName::IDENTIFIER},
	{"voidadditional", PreprocessingTokenName::IDENTIFIER},
	{"volatileadditional", PreprocessingTokenName::IDENTIFIER},
	{"whileadditional", PreprocessingTokenName::IDENTIFIER},
	{"_Booladditional", PreprocessingTokenName::IDENTIFIER},
	{"_Complexadditional", PreprocessingTokenName::IDENTIFIER},
	{"_Imaginaryadditional", PreprocessingTokenName::IDENTIFIER},
	{ "lexer_test_case", PreprocessingTokenName::IDENTIFIER},
	{ "test_token_name", PreprocessingTokenName::IDENTIFIER},
	{ "TokenName", PreprocessingTokenName::IDENTIFIER},
	{ "IDENTIFIER", PreprocessingTokenName::IDENTIFIER},
	{ "_systemmethod", PreprocessingTokenName::IDENTIFIER},
	{ "_1systemvariable", PreprocessingTokenName::IDENTIFIER},
	{ "__systemvariable", PreprocessingTokenName::IDENTIFIER},
	{ "identifier", PreprocessingTokenName::IDENTIFIER},
};

static inline TestResult test_pp_identifier(
	TestResult results[NUM_PP_IDENTIFIER_TESTS]) 
{
	bool all_tests_passed = true;
	for (const pp_identifier_test_case* ltc = test_pp_identifier_table;
		ltc < test_pp_identifier_table + NUM_PP_IDENTIFIER_TESTS;
		ltc++) {

		PreprocessingToken ppt;
		PreprocessingToken* ppt_ptr = &ppt;

		const char* lexeme = ltc->lexeme;
		const char** lexeme_produced = NULL;
		const char* lptr = lexeme;

		preprocess_identifier_name(
			lptr,
			lexeme_produced,
			FileLocationDescriptor(), 
			ppt_ptr);

		bool success_criteria = ppt.get_name() == ltc->name
			&& (strcmp(ppt.get_lexeme(), lexeme) == 0);


		results[ltc - test_pp_identifier_table]
			= success_criteria 
			  ? TestResult::SUCCESS 
			  : TestResult::FAIL;

		if (ppt.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//       Testing for the recognition of pp_number tokens        //
//////////////////////////////////////////////////////////////////

#define NUM_PP_NUMBER_TESTS 25

struct pp_pp_number_test_case {
	const char* lexeme;
	PreprocessingTokenName name;
};

static const
pp_pp_number_test_case test_pp_number_table[NUM_PP_NUMBER_TESTS] = {
	{ "1", PreprocessingTokenName::PP_NUMBER },
	{ "1234567890123456789", PreprocessingTokenName::PP_NUMBER },
	{ "123456l", PreprocessingTokenName::PP_NUMBER },
	{ "123456ll", PreprocessingTokenName::PP_NUMBER },
	{ "123456llu", PreprocessingTokenName::PP_NUMBER },
	{ "123456ull", PreprocessingTokenName::PP_NUMBER },
	{ "0", PreprocessingTokenName::PP_NUMBER },
	{ "0001234", PreprocessingTokenName::PP_NUMBER },
	{ "0xDEADBEEF", PreprocessingTokenName::PP_NUMBER },
	{ "0x0", PreprocessingTokenName::PP_NUMBER },
	{ "1.0", PreprocessingTokenName::PP_NUMBER },
	{ "3.141592653589", PreprocessingTokenName::PP_NUMBER },
	{ "1.", PreprocessingTokenName::PP_NUMBER },
	{ "1.54334E-34", PreprocessingTokenName::PP_NUMBER },
	{ "1.54334e+34", PreprocessingTokenName::PP_NUMBER },
	{ "1e50", PreprocessingTokenName::PP_NUMBER },
	{ ".1e50", PreprocessingTokenName::PP_NUMBER },
	{ "3.02530e+01", PreprocessingTokenName::PP_NUMBER },
	{ "3.02530e+00", PreprocessingTokenName::PP_NUMBER },
	{ "0x1p-1074", PreprocessingTokenName::PP_NUMBER },
	{ "0x3.3333333333334p-5", PreprocessingTokenName::PP_NUMBER },
	{ "0xcc.ccccccccccdp-11", PreprocessingTokenName::PP_NUMBER },
	{ "0x1.999999999999ap-4", PreprocessingTokenName::PP_NUMBER },
	{ "0129e+0129", PreprocessingTokenName::PP_NUMBER },
	{ "3.02530e+00", PreprocessingTokenName::PP_NUMBER },
};

static inline TestResult test_pp_number(
	TestResult results[NUM_PP_NUMBER_TESTS]) 
{
	bool all_tests_passed = true;
	for (const pp_pp_number_test_case* ltc = test_pp_number_table;
		ltc < test_pp_number_table + NUM_PP_NUMBER_TESTS;
		ltc++) {

		PreprocessingToken ppt;
		PreprocessingToken* ppt_ptr = &ppt;

		const char* lexeme = ltc->lexeme;		
		const char** lexeme_produced = NULL;
		const char* lptr = lexeme;

		preprocess_pp_number(
			lptr,
			lexeme_produced,
			FileLocationDescriptor(),
			ppt_ptr);

		bool success_criteria = ppt.get_name() == ltc->name
			&& (strcmp(ppt.get_lexeme(), lexeme) == 0);

		results[ltc - test_pp_number_table]
			= success_criteria
			? TestResult::SUCCESS
			: TestResult::FAIL;

		if (ppt.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}


//////////////////////////////////////////////////////////////////
//   Testing for the recognition of character constant tokens   //
//////////////////////////////////////////////////////////////////

#define NUM_PP_CHARACTER_CONSTANT_TESTS 8

struct pp_character_constant_test_case {
	const char* lexeme;
	PreprocessingTokenName name;
};

static const
pp_character_constant_test_case test_character_constant_table[] = {
	{ "\'a\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'z\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'\\a\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'\\xDEADBEEF\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "L\'\\xDEADBEEF\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'\\167\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'\\x1679\'", PreprocessingTokenName::CHARACTER_CONSTANT },
	{ "\'\\1679\'", PreprocessingTokenName::CHARACTER_CONSTANT },
};

static inline TestResult test_character_constant(
	TestResult results[NUM_PP_CHARACTER_CONSTANT_TESTS]) 
{
	bool all_tests_passed = true;
	for (const pp_character_constant_test_case* ltc = test_character_constant_table;
		ltc < test_character_constant_table + NUM_PP_CHARACTER_CONSTANT_TESTS;
		ltc++) {

		PreprocessingToken ppt;
		PreprocessingToken* ppt_ptr = &ppt;

		const char* lexeme = ltc->lexeme;
		const char** lexeme_produced = NULL;
		const char* lptr = lexeme;

		preprocess_character_constant(
			lptr,
			lexeme_produced,
			FileLocationDescriptor(),
			ppt_ptr);

		bool success_criteria = ppt.get_name() == ltc->name
			&& (strcmp(ppt.get_lexeme(), lexeme) == 0);

		results[ltc - test_character_constant_table]
			= success_criteria
			? TestResult::SUCCESS
			: TestResult::FAIL;

		if (ppt.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//     Testing for the recognition of string literal tokens     //
//////////////////////////////////////////////////////////////////

#define NUM_PP_STRING_LITERAL_TESTS 8

struct pp_string_literal_test_case {
	const char* lexeme;
	PreprocessingTokenName name;
};

static const
pp_string_literal_test_case test_pp_string_literal_table[NUM_PP_STRING_LITERAL_TESTS] = {
	{ "\"a\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"z\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"\\a\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"\\xDEADBEEF\"", PreprocessingTokenName::STRING_LITERAL },
	{ "L\"\\xDEADBEEF\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"\\167\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"\\x1679\"", PreprocessingTokenName::STRING_LITERAL },
	{ "\"\\1679\"", PreprocessingTokenName::STRING_LITERAL },
};

static inline TestResult test_string_literal(
	TestResult results[NUM_PP_STRING_LITERAL_TESTS]) 
{
	bool all_tests_passed = true;
	for (const pp_string_literal_test_case* ltc = test_pp_string_literal_table;
		ltc < test_pp_string_literal_table + NUM_PP_STRING_LITERAL_TESTS;
		ltc++) {

		PreprocessingToken ppt;
		PreprocessingToken* ppt_ptr = &ppt;

		const char* lexeme = ltc->lexeme;
		const char** lexeme_produced = NULL;
		const char* lptr = lexeme;

		preprocess_string_literal(
			lptr,
			lexeme_produced,
			FileLocationDescriptor(),
			ppt_ptr);

		bool success_criteria = ppt.get_name() == ltc->name
			&& (strcmp(ppt.get_lexeme(), lexeme) == 0);

		results[ltc - test_pp_string_literal_table]
			= success_criteria
			? TestResult::SUCCESS
			: TestResult::FAIL;

		if (ppt.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}


//////////////////////////////////////////////////////////////////
//       Testing for the recognition of punctuator tokens       //
//////////////////////////////////////////////////////////////////

#define NUM_PP_PUNCTUATOR_TESTS 53

struct pp_punctuator_test_case {
	const char* lexeme;
	PreprocessingTokenName name;
};

static const
pp_punctuator_test_case test_pp_punctuator_table[NUM_PP_PUNCTUATOR_TESTS] = {
	{"[", PreprocessingTokenName::PUNCTUATOR},
	{"]", PreprocessingTokenName::PUNCTUATOR},
	{"(", PreprocessingTokenName::PUNCTUATOR},
	{")", PreprocessingTokenName::PUNCTUATOR},
	{"{", PreprocessingTokenName::PUNCTUATOR},
	{"}", PreprocessingTokenName::PUNCTUATOR},
	{".", PreprocessingTokenName::PUNCTUATOR},
	{"++", PreprocessingTokenName::PUNCTUATOR},
	{"--", PreprocessingTokenName::PUNCTUATOR},
	{"&", PreprocessingTokenName::PUNCTUATOR},
	{"*", PreprocessingTokenName::PUNCTUATOR},
	{"+", PreprocessingTokenName::PUNCTUATOR},
	{"-", PreprocessingTokenName::PUNCTUATOR},
	{"~", PreprocessingTokenName::PUNCTUATOR},
	{"!", PreprocessingTokenName::PUNCTUATOR},
	{"/", PreprocessingTokenName::PUNCTUATOR},
	{"%", PreprocessingTokenName::PUNCTUATOR},
	{"<<", PreprocessingTokenName::PUNCTUATOR},
	{">>", PreprocessingTokenName::PUNCTUATOR},
	{"<", PreprocessingTokenName::PUNCTUATOR},
	{">", PreprocessingTokenName::PUNCTUATOR},
	{"<=", PreprocessingTokenName::PUNCTUATOR},
	{">=", PreprocessingTokenName::PUNCTUATOR},
	{"==", PreprocessingTokenName::PUNCTUATOR},
	{"!=", PreprocessingTokenName::PUNCTUATOR},
	{"^", PreprocessingTokenName::PUNCTUATOR},
	{"|", PreprocessingTokenName::PUNCTUATOR},
	{"&&", PreprocessingTokenName::PUNCTUATOR},
	{"||", PreprocessingTokenName::PUNCTUATOR},
	{"?", PreprocessingTokenName::PUNCTUATOR},
	{":", PreprocessingTokenName::PUNCTUATOR},
	{";", PreprocessingTokenName::PUNCTUATOR},
	{"...", PreprocessingTokenName::PUNCTUATOR},
	{"=", PreprocessingTokenName::PUNCTUATOR},
	{"*=", PreprocessingTokenName::PUNCTUATOR},
	{"/=", PreprocessingTokenName::PUNCTUATOR},
	{"%=", PreprocessingTokenName::PUNCTUATOR},
	{"+=", PreprocessingTokenName::PUNCTUATOR},
	{"-=", PreprocessingTokenName::PUNCTUATOR},
	{"<<=", PreprocessingTokenName::PUNCTUATOR},
	{">>=", PreprocessingTokenName::PUNCTUATOR},
	{"&=", PreprocessingTokenName::PUNCTUATOR},
	{"^=", PreprocessingTokenName::PUNCTUATOR},
	{"|=", PreprocessingTokenName::PUNCTUATOR},
	{",", PreprocessingTokenName::PUNCTUATOR},
	{"#",PreprocessingTokenName::PUNCTUATOR},
	{"##", PreprocessingTokenName::PUNCTUATOR},
	{"<:", PreprocessingTokenName::PUNCTUATOR},
	{":>", PreprocessingTokenName::PUNCTUATOR},
	{"<%", PreprocessingTokenName::PUNCTUATOR},
	{"%>", PreprocessingTokenName::PUNCTUATOR},
	{"%:", PreprocessingTokenName::PUNCTUATOR},
	{"%:%:", PreprocessingTokenName::PUNCTUATOR},
};

static inline TestResult test_punctuator(
	TestResult results[NUM_PP_PUNCTUATOR_TESTS]) 
{
	bool all_tests_passed = true;
	for (const pp_punctuator_test_case* ltc = test_pp_punctuator_table;
		ltc < test_pp_punctuator_table + NUM_PP_PUNCTUATOR_TESTS;
		ltc++) {

		PreprocessingToken ppt;
		PreprocessingToken* ppt_ptr = &ppt;

		const char* lexeme = ltc->lexeme;
		const char** lexeme_produced = NULL;
		const char* lptr = lexeme;

		preprocess_punctuator(
			lptr,
			lexeme_produced,
			FileLocationDescriptor(),
			ppt_ptr);

		bool success_criteria = ppt.get_name() == ltc->name
			&& (strcmp(ppt.get_lexeme(), lexeme) == 0);

		results[ltc - test_pp_punctuator_table]
			= success_criteria
			? TestResult::SUCCESS
			: TestResult::FAIL;

		if (ppt.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

static inline TestResult test_preprocessor(
	TestResult results[NUM_PREPROCESSOR_TESTS],
	char* &output,
	int indent = 0) 
{
	TestResult pp_identifier_results[NUM_PP_IDENTIFIER_TESTS];
	TestResult pp_identifier_result
		= test_pp_identifier(pp_identifier_results);
	results[0] = pp_identifier_result;

	TestResult pp_pp_number_results[NUM_PP_NUMBER_TESTS];
	TestResult pp_pp_number_result
		= test_pp_number(pp_pp_number_results);
	results[1] = pp_pp_number_result;

	TestResult pp_character_constant_results[NUM_PP_CHARACTER_CONSTANT_TESTS];
	TestResult pp_character_constant_result
		= test_character_constant(pp_character_constant_results);
	results[2] = pp_character_constant_result;

	TestResult pp_string_literal_results[NUM_PP_STRING_LITERAL_TESTS];
	TestResult pp_string_literal_result
		= test_string_literal(pp_string_literal_results);
	results[3] = pp_string_literal_result;

	TestResult pp_punctuator_results[NUM_PP_PUNCTUATOR_TESTS];
	TestResult pp_punctuator_result
		= test_punctuator(pp_punctuator_results);
	results[4] = pp_punctuator_result;

	for (int i = 0; i < indent; i++) print_to_output("\t", output);
	print_to_output("<-> PreprocessorNonterminalTests", output);
	print_to_output("\n", output);

	const char* identifier_title = "PreprocessorIdentifierTests";
	present_test_set_synopsis(
		identifier_title,
		pp_identifier_result,
		pp_identifier_results,
		NUM_PP_IDENTIFIER_TESTS,
		output,
		indent + 1
	);

	const char* pp_number_title = "PreprocessorPPNumberTests";
	present_test_set_synopsis(
		pp_number_title,
		pp_pp_number_result,
		pp_pp_number_results,
		NUM_PP_NUMBER_TESTS,
		output,
		indent + 1
	);

	const char* character_constant_title = "PreprocessorCharacterConstantTests";
	present_test_set_synopsis(
		character_constant_title,
		pp_character_constant_result,
		pp_character_constant_results,
		NUM_PP_CHARACTER_CONSTANT_TESTS,
		output,
		indent + 1
	);

	const char* string_literal_title = "PreprocessorStringLiteralTests";
	present_test_set_synopsis(
		string_literal_title,
		pp_string_literal_result,
		pp_string_literal_results,
		NUM_PP_STRING_LITERAL_TESTS,
		output,
		indent + 1
	);

	const char* punctuator_title = "PreprocessorPunctuatorTests";
	present_test_set_synopsis(
		punctuator_title,
		pp_punctuator_result,
		pp_punctuator_results,
		NUM_PP_PUNCTUATOR_TESTS,
		output,
		indent + 1
	);

	return (pp_identifier_result == TestResult::SUCCESS) 
		   ? TestResult::SUCCESS 
		   : TestResult::FAIL;
}

#endif