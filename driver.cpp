/* Authored by Charlie Keaney                   */
/* driver.cpp - Responsible for driving the kcc
                compiler, taking in arguments.  */

#ifndef DRIVER_CPP
#define DRIVER_CPP 1

#include "driver.h"

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

int main() {
	//kcc_run_tests();
	const char* input = new char[NUM_INPUT_CHARACTERS] {
		"#if (6 > (3 + 1 << 1))\n"
		"c allows literally anything here, so long as the ifdef is not true.\n"
		"#endif\n"
		"#if ((2 << 3) > (2 << 2))\n"
		"float Q_rsqrt( float number )\n"
		"{\n"
		"\tlong i;\n"
		"\tfloat x2, y;\n"
		"\tconst float threehalfs = 1.5F;\n"
		"\tx2 = number * 0.5F;\n"
		"\ty  = number;\n"
		"\t// evil floating point bit level hacking\n"
		"\ti  = 0x5f3759df - ( i >> 1 ); // what the\n"
		"\ty  = * ( float * ) &i;\n"
		"\ty  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration\n"
		"\t//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed\n"
		"\treturn y;\n"
		"}\n"
		"#endif\n",
	};
	//cout << input;
	CompilerFlags flags = { 0 };	
	flags.display_pptokens = false;
	flags.display_tokens   = false;
	flags.display_annotree = false;
	flags.display_x86      = true;
	flags.help             = true;

	//cout << input;
	//cout << endl;
	
	drive("test.c", input, flags);
}

#endif