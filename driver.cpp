
#ifndef DRIVER_CPP
#define DRIVER_CPP 1

#include "driver.h"

int main() {
	//kcc_run_tests();
	const char* input = new char[NUM_INPUT_CHARACTERS] {
		"#if 1\n"
		"#endif\n"
		"float Q_rsqrt( float number )\n"
		"{\n"
		"long i;\n"
		"float x2, y;\n"
		"const float threehalfs = 1.5F;\n"
		"x2 = number * 0.5F;\n"
		"y  = number;\n"
		"// evil floating point bit level hacking\n"
		"i  = 0x5f3759df - ( i >> 1 ); // what the\n"
		"y  = * ( float * ) &i;\n"
		"y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration\n"
		"//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed\n"
		"return y;\n"
		"}\n",
	};
	//cout << input;
	CompilerFlags flags = { 0 };
	//flags.display_annotree = true;
	flags.display_pptokens = false;
	flags.display_tokens   = false;
	flags.display_annotree = false;
	flags.display_x86      = true;
	flags.help             = false;

	drive("test.c", input, flags);
}



#endif