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

void testIfStmt(void)
{
	const char* input = "var x = 1; if (x > 0) print \"a\";";
	const char* output = "a\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testIfElseStmt(void)
{
	const char* input = "var x = 0; if (x > 0) print \"a\"; else print \"b\";";
	const char* output = "b\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testAndLogic(void)
{
	const char* input = "var x = (2 > 1) and (3 > 2); print x;";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testOrLogic(void)
{
	const char* input = "var x = (1 > 2) or (3 > 2); print x;";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testWhileLoop(void)
{
	const char* input = 
		"var x = 0;"
		"while (x < 3) {"
		"	print x;"
		" x = x + 1;"
		"}";
	const char* output = "0\n1\n2\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testForLoop(void)
{
	const char* input = "for (var x = 0; x < 3; x = x + 1) { print x;}";
	const char* output = "0\n1\n2\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}


int main(void)
{
UNITY_BEGIN();

RUN_TEST(testIfStmt);
RUN_TEST(testIfElseStmt);
RUN_TEST(testAndLogic);
RUN_TEST(testOrLogic);
RUN_TEST(testWhileLoop);
RUN_TEST(testForLoop);

return UNITY_END();
}
