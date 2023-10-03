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

void testNativeFn(void)
{
	const char* input = 
		"var a = clock();"
		"print a < 100;"
		"var b = clock();"
		"print b >= a;";
	const char* output = "true\ntrue\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
}

void testRecursiveFn(void)
{
	const char* input = 
		"fun fib(n) {"
		"  if (n < 2) return n;"
		"  return fib(n-2) + fib(n-1);"
		"}"
		"print fib(10);";
	const char* output = "55\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testFnDeclaration);
RUN_TEST(testFnCall);
RUN_TEST(testFnNilReturn);
RUN_TEST(testFnReturn);
RUN_TEST(testNativeFn);
RUN_TEST(testRecursiveFn);

return UNITY_END();
}
