
#ifndef DRIVER_CPP
#define DRIVER_CPP 1

#include "driver.h"

int main() {
	//kcc_run_tests();
	//return;*/
	FileLocationDescriptor fld 
		= FileLocationDescriptor("test.c", 0, 0);
	//const char *input = new char[NUM_INPUT_CHARACTERS] {
	//	"float Q_rsqrt( float number )\n"
	//	"{\n"
	//	"long i;\n"
	//	"float x2, y;\n"
	//	"const float threehalfs = 1.5F;\n"
	//	"x2 = number * 0.5F;\n"
	//	"y  = number;\n"
	//	"i  = * ( long * ) &y; // evil floating point bit level hacking\n"
	//	"i  = 0x5f3759df - ( i >> 1 ); // what the\n"
	//	"y  = * ( float * ) &i;\n"
	//	"y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration\n"
	//	"//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed\n"
	//	"return y;\n"
	//	"}\n",
	//};
	const char* input = new char[NUM_INPUT_CHARACTERS] {
		"float Q_rsqrt( float number )\n"
			"{\n"
			"long i;\n"
			"float x2, y;\n"
			"const float threehalfs = 1.5F;\n"
			"x2 = number * 0.5F;\n"
			"y  = number;\n"
			"i  = 0x5f3759df - ( i >> 1 );\n"
			"y = y * (threehalfs - (x2 * y * y));\n"
		"return y;\n"
		"}\n",
	};
	drive(fld, input);
}

#endif