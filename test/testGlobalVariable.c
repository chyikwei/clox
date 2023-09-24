#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "vm.h"
#include "scriptRunHelper.h"

void setUp(void) {
	initVM();
}

void tearDown(void) {
  freeVM();
}

void testDeclareVariable(void)
{
	const char* input =
		"var a = \"123a\";"
		"var b = \"456b\";"
		"print a + b;";

	const char* output = "123a456b\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testAssignVariable(void)
{
	const char* input =
		"var a = \"123\";"
		"var b = \"456\";"
		"a = b + \"789\";"
		"print a;";

	const char* output = "456789\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testNotInitializedVariable(void)
{
	const char* input = "var a; print a;";
	const char* output = "nil\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testInvalidAssigment(void)
{
	const char* input = 
		"var a;"
		"var b;"
		"a * b = 4;";

	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_COMPILE_ERROR);
}

void testInvalidAssigment2(void)
{
	const char* input = 
		"var a;"
		"b = 4;";

	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_RUNTIME_ERROR);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testDeclareVariable);
RUN_TEST(testAssignVariable);
RUN_TEST(testNotInitializedVariable);
RUN_TEST(testInvalidAssigment);
RUN_TEST(testInvalidAssigment2);

return UNITY_END();
}
