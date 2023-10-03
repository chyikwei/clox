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

void testFnDeclaration(void)
{
	const char* input = 
		"fun test(a, b) { print \"test function\";}"
		"print test;";
	const char* output = "<fn test>\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testFnCall(void)
{
	const char* input = 
		"fun add(a, b) { print a + b;}"
		"add(3,4);";
	const char* output = "7\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testFnNilReturn(void)
{
	const char* input = 
		"fun empty() {return;}"
		"var c = empty();"
		"print c;";
	const char* output = "nil\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testFnReturn(void)
{
	const char* input = 
		"fun add(a, b) { return a + b;}"
		"var c = add(3,4);"
		"print c;";
	const char* output = "7\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testFnDeclaration);
RUN_TEST(testFnCall);
RUN_TEST(testFnNilReturn);
RUN_TEST(testFnReturn);

return UNITY_END();
}