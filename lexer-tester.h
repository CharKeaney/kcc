
#ifndef LEXER_TESTER_H
#define LEXER_TESTER_H 1

#include "tester-tools.h"
#include "lexer.h"

//////////////////////////////////////////////////////////////////
//        Testing for the recognition of keyword tokens         //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_KEYWORD_TESTS 74

struct keyword_test_case {
	const char* lexeme;
	TokenName name;
	TokenForm form;
};

static const keyword_test_case test_keyword_table[NUM_LEX_KEYWORD_TESTS] = {
	{"auto", TokenName::KEYWORD, TokenForm::AUTO},
	{"break", TokenName::KEYWORD, TokenForm::BREAK},
	{"case", TokenName::KEYWORD, TokenForm::CASE},
	{"char", TokenName::KEYWORD, TokenForm::CHAR},
	{"const", TokenName::KEYWORD, TokenForm::CONST},
	{"continue", TokenName::KEYWORD, TokenForm::CONTINUE},
	{"default", TokenName::KEYWORD, TokenForm::DEFAULT},
	{"do", TokenName::KEYWORD, TokenForm::DO},
	{"double", TokenName::KEYWORD, TokenForm::DOUBLE},
	{"else", TokenName::KEYWORD, TokenForm::ELSE},
	{"enum", TokenName::KEYWORD, TokenForm::ENUM},
	{"extern", TokenName::KEYWORD, TokenForm::EXTERN},
	{"float", TokenName::KEYWORD, TokenForm::FLOAT},
	{"for", TokenName::KEYWORD, TokenForm::FOR},
	{"goto", TokenName::KEYWORD, TokenForm::GOTO},
	{"if", TokenName::KEYWORD, TokenForm::IF},
	{"inline", TokenName::KEYWORD, TokenForm::INLINE},
	{"int", TokenName::KEYWORD, TokenForm::INT},
	{"long", TokenName::KEYWORD, TokenForm::LONG},
	{"register", TokenName::KEYWORD, TokenForm::REGISTER},
	{"restrict", TokenName::KEYWORD, TokenForm::RESTRICT},
	{"return", TokenName::KEYWORD, TokenForm::RETURN},
	{"short", TokenName::KEYWORD, TokenForm::SHORT},
	{"signed", TokenName::KEYWORD, TokenForm::SIGNED},
	{"sizeof", TokenName::KEYWORD, TokenForm::SIZEOF},
	{"static", TokenName::KEYWORD, TokenForm::STATIC},
	{"struct", TokenName::KEYWORD, TokenForm::STRUCT},
	{"switch", TokenName::KEYWORD, TokenForm::SWITCH},
	{"typedef", TokenName::KEYWORD, TokenForm::TYPEDEF},
	{"union", TokenName::KEYWORD, TokenForm::UNION},
	{"unsigned", TokenName::KEYWORD, TokenForm::UNSIGNED},
	{"void", TokenName::KEYWORD, TokenForm::VOID},
	{"volatile", TokenName::KEYWORD, TokenForm::VOLATILE},
	{"while", TokenName::KEYWORD, TokenForm::WHILE},
	{"_Bool", TokenName::KEYWORD, TokenForm::_BOOL},
	{"_Complex", TokenName::KEYWORD, TokenForm::_COMPLEX},
	{"_Imaginary", TokenName::KEYWORD, TokenForm::_IMAGINARY},
	{"autoadditional", TokenName::ERROR, TokenForm::AUTO},
	{"breakadditional", TokenName::ERROR, TokenForm::BREAK},
	{"caseadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"charadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"constadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"continueadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"defaultadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"doadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"doubleadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"elseadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"enumadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"externadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"floatadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"foradditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"gotoadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"ifadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"inlineadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"intadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"longadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"registeradditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"restrictadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"returnadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"shortadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"signedadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"sizeofadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"staticadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"structadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"switchadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"typedefadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"unionadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"unsignedadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"voidadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"volatileadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"whileadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"_Booladditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"_Complexadditional", TokenName::ERROR, TokenForm::SIMPLE},
	{"_Imaginaryadditional", TokenName::ERROR, TokenForm::SIMPLE}
};

inline TestResult test_lex_keyword(
	TestResult results[NUM_LEX_KEYWORD_TESTS])
{
	bool all_tests_passed = true;
	for (const keyword_test_case* ltc = test_keyword_table;
		ltc < test_keyword_table + NUM_LEX_KEYWORD_TESTS;
		ltc++) {
		Token o = Token();
		Token* out = &o;
		PreprocessingToken ppt = PreprocessingToken(
			ltc->lexeme, 			
			PreprocessingTokenName::IDENTIFIER,
			FileLocationDescriptor(NULL, 0, 0),
			PreprocessingTokenForm::SIMPLE
		);
		LexerExitCode exitcode = lex_keyword(ppt, out);
		bool success_criteria
			= o.get_name() == ltc->name
			  && o.get_form() == ltc->form;
		results[ltc - test_keyword_table]
			= success_criteria ? TestResult::SUCCESS : TestResult::FAIL;
		if (o.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//       Testing for the recognition of identifier tokens       //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_IDENTIFIER_TESTS 10

struct identifier_test_case {
	const char* lexeme;
	TokenName name;
};

static const identifier_test_case test_identifier_table[NUM_LEX_IDENTIFIER_TESTS] = {
	{ "lexer_test_case", TokenName::IDENTIFIER },
	{ "test_token_name", TokenName::IDENTIFIER },
	{ "TokenName", TokenName::IDENTIFIER },
	{ "IDENTIFIER", TokenName::IDENTIFIER },
	{ "_systemmethod", TokenName::IDENTIFIER },
	{ "_1systemvariable", TokenName::IDENTIFIER },
	{ "__systemvariable", TokenName::IDENTIFIER },
	{ "identifier", TokenName::IDENTIFIER },
	{ "1startswithnumber", TokenName::ERROR },
	{ "invalidbecauseof space", TokenName::ERROR }
};

inline TestResult test_lex_identifier(
	TestResult results[NUM_LEX_IDENTIFIER_TESTS])
{
	bool all_tests_passed = true;
	for (const identifier_test_case* ltc = test_identifier_table;
		ltc < test_identifier_table + NUM_LEX_IDENTIFIER_TESTS;
		ltc++) {
		Token o = Token();
		Token* out = &o;
		PreprocessingToken ppt = PreprocessingToken(
			ltc->lexeme,
			PreprocessingTokenName::IDENTIFIER,
			FileLocationDescriptor(NULL, 0, 0),
			PreprocessingTokenForm::SIMPLE
		);
		LexerExitCode exitcode = lex_identifier(ppt, out);
		bool success_criteria = o.get_name() == ltc->name;
		results[ltc - test_identifier_table] 
			= success_criteria ? TestResult::SUCCESS : TestResult::FAIL;
		if (o.get_name() != ltc->name) {
			all_tests_passed = false;
		}
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//        Testing for the recognition of constant tokens        //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_CONSTANT_TESTS 50

struct constant_test_case {
	const char* lexeme;
	TokenName name;
	TokenValue val;
};

static const constant_test_case test_constant_table[NUM_LEX_CONSTANT_TESTS] = {
	{ "1", TokenName::CONSTANT },
	{ "1234567890123456789", TokenName::CONSTANT },
	{ "123456l", TokenName::CONSTANT },
	{ "123456ll", TokenName::CONSTANT },
	{ "123456llu", TokenName::CONSTANT },
	{ "123456ull", TokenName::CONSTANT },
	{ "0", TokenName::CONSTANT },
	{ "0001234", TokenName::CONSTANT },
	{ "0xDEADBEEF", TokenName::CONSTANT },
	{ "0x0", TokenName::CONSTANT },
	{ "1.0", TokenName::CONSTANT },
	{ "1.5f", TokenName::CONSTANT },
	{ "1.5ff", TokenName::ERROR },
	{ "1.5F", TokenName::CONSTANT },
	{ "1.5FF", TokenName::ERROR },
	{ "3.141592653589", TokenName::CONSTANT },
	{ "1.", TokenName::CONSTANT },
	{ "1.54334E-34", TokenName::CONSTANT },
	{ "1.54334e+34", TokenName::CONSTANT },
	{ "1e50", TokenName::CONSTANT },
	{ ".1e50", TokenName::CONSTANT },
	{ "3.02530e+01", TokenName::CONSTANT },
	{ "3.02530e+00", TokenName::CONSTANT },
	{ "0x1p-1074", TokenName::CONSTANT },
	{ "0x3.3333333333334p-5", TokenName::CONSTANT },
	{ "0xcc.ccccccccccdp-11", TokenName::CONSTANT },
	{ "0x1.999999999999ap-4", TokenName::CONSTANT },
	{ "0129e+0129", TokenName::CONSTANT },
	{ "3.02530e+00", TokenName::CONSTANT },
	{ "\'a\'", TokenName::CONSTANT },
	{ "\'z\'", TokenName::CONSTANT },
	{ "\'\\a\'", TokenName::CONSTANT },
	{ "\'\\xDEADBEEF\'", TokenName::CONSTANT },
	{ "L\'\\xDEADBEEF\'", TokenName::CONSTANT },
	{ "\'\\167\'", TokenName::CONSTANT },
	{ "\'\\x1679\'", TokenName::CONSTANT },
	{ "\'\\1679\'", TokenName::CONSTANT },
	{ "\"a\"", TokenName::ERROR },
	{ "\"z\"", TokenName::ERROR },
	{ "\"\\a\"", TokenName::ERROR },
	{ "\"\\xDEADBEEF\"", TokenName::ERROR },
	{ "L\"\\xDEADBEEF\"", TokenName::ERROR },
	{ "\"\\167\"", TokenName::ERROR },
	{ "\"\\x1679\"", TokenName::ERROR },
	{ "\"\\1679\"", TokenName::ERROR },
	{ "0XDEADBEEFe+0xB33F", TokenName::ERROR },
	{ "0xDEADBEES", TokenName::ERROR },
	{ "0x", TokenName::ERROR },
	{ "09", TokenName::ERROR },
	{ "00012349", TokenName::ERROR },
};

inline TestResult test_lex_constant(
	TestResult results[NUM_LEX_CONSTANT_TESTS])
{
	bool all_tests_passed = true;
	
	for (const constant_test_case* ltc = test_constant_table;
		ltc < test_constant_table + NUM_LEX_CONSTANT_TESTS;
		ltc++) {

		Token o = Token();
		Token* out = &o;

		PreprocessingToken ppt = PreprocessingToken(
			ltc->lexeme,
			PreprocessingTokenName::CHARACTER_CONSTANT,
			FileLocationDescriptor(NULL, 0, 0),
			PreprocessingTokenForm::SIMPLE
		);
		LexerExitCode exitcode = lex_constant(ppt, out);
		bool success_criteria = o.get_name() == ltc->name;
		results[ltc - test_constant_table]
			= success_criteria ? TestResult::SUCCESS : TestResult::FAIL;
		if (!success_criteria) {
			all_tests_passed = false;
		};
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}
                      
//////////////////////////////////////////////////////////////////
//     Testing for the recognition of string literal tokens     //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_STRING_LITERAL_TESTS 8

struct string_literal_test_case {
	const char* lexeme;
	TokenName name;
	TokenValue val;
};

static const string_literal_test_case test_string_literal_table[
	NUM_LEX_STRING_LITERAL_TESTS] = {
	{ "\"a\"", TokenName::STRING_LITERAL },
	{ "\"z\"", TokenName::STRING_LITERAL },
	{ "\"\\a\"", TokenName::STRING_LITERAL },
	{ "\"\\xDEADBEEF\"", TokenName::STRING_LITERAL },
	{ "L\"\\xDEADBEEF\"", TokenName::STRING_LITERAL },
	{ "\"\\167\"", TokenName::STRING_LITERAL },
	{ "\"\\x1679\"", TokenName::STRING_LITERAL },
	{ "\"\\1679\"", TokenName::STRING_LITERAL },
};

inline TestResult test_lex_string_literal(
	TestResult results[NUM_LEX_STRING_LITERAL_TESTS])
{
	bool all_tests_passed = true;

	for (const string_literal_test_case* ltc = test_string_literal_table;
		ltc < test_string_literal_table + NUM_LEX_STRING_LITERAL_TESTS;
		ltc++) {

		Token o = Token();
		Token* out = &o;

		PreprocessingToken ppt = PreprocessingToken(
			ltc->lexeme,
			PreprocessingTokenName::STRING_LITERAL,
			FileLocationDescriptor(NULL, 0, 0),
			PreprocessingTokenForm::SIMPLE
		);
		LexerExitCode exitcode = lex_string_literal(
			ppt, out);
		bool success_criteria = o.get_name() == ltc->name;
		results[ltc - test_string_literal_table]
			= success_criteria ? TestResult::SUCCESS : TestResult::FAIL;
		if (!success_criteria) all_tests_passed = false;
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//      Testing for the recognition of punctuator tokens        //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_PUNCTUATOR_TESTS 53

struct punctuator_test_case {
	const char* lexeme;
	TokenName name;
	TokenForm form;
};

static const punctuator_test_case test_punctuator_table[NUM_LEX_PUNCTUATOR_TESTS] = {
	{"[", TokenName::PUNCTUATOR, TokenForm::OPEN_SQUARE_BRACKET},
	{"]", TokenName::PUNCTUATOR, TokenForm::CLOSE_SQUARE_BRACKET},
	{"(", TokenName::PUNCTUATOR, TokenForm::OPEN_PAREN},
	{")", TokenName::PUNCTUATOR, TokenForm::CLOSE_PAREN}, 
	{"{", TokenName::PUNCTUATOR, TokenForm::OPEN_CURLY_BRACKET},
	{"}", TokenName::PUNCTUATOR, TokenForm::CLOSE_CURLY_BRACKET},
	{".", TokenName::PUNCTUATOR, TokenForm::DOT},
	{"++", TokenName::PUNCTUATOR, TokenForm::INCREMENT},
	{"--", TokenName::PUNCTUATOR, TokenForm::DECREMENT},
	{"&", TokenName::PUNCTUATOR, TokenForm::AMPERSAND},
	{"*", TokenName::PUNCTUATOR, TokenForm::ASTERIX},
	{"+", TokenName::PUNCTUATOR, TokenForm::PLUS},
	{"-", TokenName::PUNCTUATOR, TokenForm::MINUS},
	{"~", TokenName::PUNCTUATOR, TokenForm::TILDE},
	{"!", TokenName::PUNCTUATOR, TokenForm::EXCLAMATION_MARK},
	{"/", TokenName::PUNCTUATOR, TokenForm::FORWARD_SLASH},
	{"%", TokenName::PUNCTUATOR, TokenForm::MODULO},
	{"<<", TokenName::PUNCTUATOR, TokenForm::LEFT_SHIFT},
	{">>", TokenName::PUNCTUATOR, TokenForm::RIGHT_SHIFT},
	{"<", TokenName::PUNCTUATOR, TokenForm::LESS_THAN},
	{">", TokenName::PUNCTUATOR, TokenForm::GREATER_THAN},
	{"<=", TokenName::PUNCTUATOR, TokenForm::LESS_THAN_EQUAL},
	{">=", TokenName::PUNCTUATOR, TokenForm::GREATER_THAN_EQUAL},
	{"==", TokenName::PUNCTUATOR, TokenForm::EQUAL},
	{"!=", TokenName::PUNCTUATOR, TokenForm::NOT_EQUAL},
	{"^", TokenName::PUNCTUATOR, TokenForm::XOR},
	{"|", TokenName::PUNCTUATOR, TokenForm::OR},
	{"&&", TokenName::PUNCTUATOR, TokenForm::DOUBLE_AMPERSAND},
	{"||", TokenName::PUNCTUATOR, TokenForm::DOUBLE_OR},
	{"?", TokenName::PUNCTUATOR, TokenForm::QUESTION_MARK},
	{":", TokenName::PUNCTUATOR, TokenForm::COLON},
	{";", TokenName::PUNCTUATOR, TokenForm::SEMI_COLON},
	{"...", TokenName::PUNCTUATOR, TokenForm::TRIPLE_DOT},
	{"=", TokenName::PUNCTUATOR, TokenForm::ASSIGN},
	{"*=", TokenName::PUNCTUATOR, TokenForm::MULTIPLY_EQUAL},
	{"/=", TokenName::PUNCTUATOR, TokenForm::DIVIDE_EQUALS},
	{"%=", TokenName::PUNCTUATOR, TokenForm::MODULO_EQUALS},
	{"+=", TokenName::PUNCTUATOR, TokenForm::PLUS_EQUALS},
	{"-=", TokenName::PUNCTUATOR, TokenForm::MINUS_EQUALS},
	{"<<=", TokenName::PUNCTUATOR, TokenForm::LEFT_SHIFT_EQUALS},
	{">>=", TokenName::PUNCTUATOR, TokenForm::RIGHT_SHIFT_EQUALS},
	{"&=", TokenName::PUNCTUATOR, TokenForm::AMPERSAND_EQUAL},
	{"^=", TokenName::PUNCTUATOR, TokenForm::XOR_EQUAL},
	{"|=", TokenName::PUNCTUATOR, TokenForm::OR_EQUAL},
	{",", TokenName::PUNCTUATOR, TokenForm::COMMA},
	{"#", TokenName::PUNCTUATOR, TokenForm::HASHTAG},
	{"##", TokenName::PUNCTUATOR, TokenForm::DOUBLE_HASHTAG},
	{"<:", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_OPEN_SQUARE_BRACKET},
	{":>", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_CLOSE_SQUARE_BRACKET},
	{"<%", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_OPEN_CURLY_BRACKET},
	{"%>", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_CLOSE_CURLY_BRACKET},
	{"%:", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_HASHTAG},
	{"%:%:", TokenName::PUNCTUATOR, TokenForm::ANTIQUATED_DOUBLE_HASHTAG},
};

inline TestResult test_lex_punctuator(
	TestResult results[NUM_LEX_PUNCTUATOR_TESTS]) 
{
	bool all_tests_passed = true;

	for (const punctuator_test_case* ltc = test_punctuator_table;
		ltc < test_punctuator_table + NUM_LEX_PUNCTUATOR_TESTS;
		ltc++) {

		Token o = Token();
		Token* out = &o;

		PreprocessingToken ppt = PreprocessingToken(
			ltc->lexeme,
			PreprocessingTokenName::PUNCTUATOR,
			FileLocationDescriptor(NULL, 0, 0),
			PreprocessingTokenForm::SIMPLE);

		LexerExitCode exitcode = lex_punctuator(ppt, out);
		bool success_criteria = o.get_name() == ltc->name
			&& o.get_form() == ltc->form;
		results[ltc - test_punctuator_table]
			= success_criteria ? TestResult:: SUCCESS : TestResult::FAIL;
		if (!success_criteria) all_tests_passed = false;
	}
	return all_tests_passed ? TestResult::SUCCESS : TestResult::FAIL;
}

//////////////////////////////////////////////////////////////////
//     Code for running and presenting the results of tests     //
//////////////////////////////////////////////////////////////////

#define NUM_LEX_TESTS NUM_LEX_KEYWORD_TESTS \
					  + NUM_LEX_IDENTIFIER_TESTS \
					  + NUM_LEX_CONSTANT_TESTS \
					  + NUM_LEX_STRING_LITERAL_TESTS \
					  + NUM_LEX_PUNCTUATOR_TESTS

inline TestResult test_lex(
	TestResult results[NUM_LEX_TESTS],
	char* &output,
	int indent = 0) 
{
	TestResult lex_keyword_results[NUM_LEX_KEYWORD_TESTS];
	TestResult lex_keyword_result
		= test_lex_keyword(lex_keyword_results);
	results[0] = lex_keyword_result;

	TestResult lex_identifier_results[NUM_LEX_IDENTIFIER_TESTS];
	TestResult lex_identifier_result
		= test_lex_identifier(lex_identifier_results);
	results[1] = lex_identifier_result;

	TestResult lex_constant_results[NUM_LEX_CONSTANT_TESTS];
	TestResult lex_constant_result
		= test_lex_constant(lex_constant_results);
	results[2] = lex_constant_result;

	TestResult lex_string_literal_results[NUM_LEX_STRING_LITERAL_TESTS];
	TestResult lex_string_literal_result
		= test_lex_string_literal(lex_string_literal_results);
	results[3] = lex_string_literal_result;

	TestResult lex_punctuator_results[NUM_LEX_PUNCTUATOR_TESTS];
	TestResult lex_punctuator_result
		= test_lex_punctuator(lex_punctuator_results);
	results[4] = lex_punctuator_result;

	for (int i = 0; i < indent; i++) print_to_output("\t", output);
	print_to_output("<-> LexerNonterminalTests", output);
	print_to_output("\n", output);

	const char* keyword_title = "LexerKeywordTests";
	present_test_set_synopsis(
		keyword_title,
		lex_keyword_result,
		lex_keyword_results,
		NUM_LEX_KEYWORD_TESTS,
		output,
		indent + 1
	);

	const char* id_title = "LexerIdentifierTests";
	present_test_set_synopsis(
		id_title,
		lex_identifier_result,
		lex_identifier_results,
		NUM_LEX_IDENTIFIER_TESTS,
		output,
		indent + 1
	);

	const char* const_title = "LexerConstantTests";
	present_test_set_synopsis(
		const_title,
		lex_constant_result,
		lex_constant_results,
		NUM_LEX_CONSTANT_TESTS,
		output,
		indent + 1
	);

	const char* string_literal_title = "LexerStringLiteralTests";
	print_to_output("\n", output);

	present_test_set_synopsis(
		string_literal_title,
		lex_string_literal_result,
		lex_string_literal_results,
		NUM_LEX_STRING_LITERAL_TESTS,
		output,
		indent + 1

	);

	const char* punctuator_title = "LexerPunctuatorTests";
	print_to_output("\n", output);

	present_test_set_synopsis(
		punctuator_title,
		lex_punctuator_result,
		lex_punctuator_results,
		NUM_LEX_PUNCTUATOR_TESTS,
		output,
		indent + 1
	);

	for (int i = 0; i < indent + 1; i++) print_to_output("\t", output);
	print_to_output("<-> LexerIntegrationTests", output);
	print_to_output("\n", output);
	
	//const char* misra_title = "MISRA tests";
	//print_to_output(misra_title, output);

	return ((lex_keyword_result == TestResult::SUCCESS)
		    && (lex_identifier_result == TestResult::SUCCESS)
		    && (lex_constant_result == TestResult::SUCCESS)
		    && (lex_string_literal_result == TestResult::SUCCESS)
		    && (lex_punctuator_result == TestResult::SUCCESS)) 
		   ? TestResult::SUCCESS
		   : TestResult::FAIL;
}

#endif