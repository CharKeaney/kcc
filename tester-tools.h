
#ifndef TESTER_TOOLS_H
#define TESTER_TOOLS_H 1

#include <cstddef>

enum class TestResult {
	SUCCESS,
	FAIL
};

inline void print_to_output(
	const char* const& val_to_print, 
	char*            & output) 
{
	for (const char* c = val_to_print; *c != NULL; ) {
		*output++ = *c++;
	}
}

static inline void present_test_set_synopsis(
	const char*       & title,
	TestResult   const& test_set_result,
	TestResult*  const& subtest_results,
	const size_t      & size,
	char*             &output,
	int                indent = 0) 
{
	for (int i = 0; i < indent; i++) print_to_output("\t", output);

	print_to_output("<-> ", output);
	print_to_output(title, output);
	print_to_output("\n", output);

	for (int i = 0; i < indent + 1; i++) print_to_output("\t", output);

	print_to_output("<", output);
	print_to_output(
		(test_set_result == TestResult::SUCCESS ? "+" : "-"), 
		output);
	print_to_output("> ", output);
	print_to_output(
		(test_set_result == TestResult::SUCCESS ? "All Passed" : "Some Failed"), 
		output);
	print_to_output("\n", output);

	if (!(test_set_result == TestResult::SUCCESS)) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < indent + 2; j++) print_to_output("\t", output);
				print_to_output("<+> Test ", output);
				// cout << i + 1
				print_to_output(
					(subtest_results[i] == TestResult::SUCCESS ? "Passed" : "Failed"),
					output);
				print_to_output("\n", output);
		}
	}
}

#endif