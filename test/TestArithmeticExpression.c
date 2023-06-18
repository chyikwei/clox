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

void testAddition(void)
{
	const char* input = "3 + 3 + 3";
	const char* output = "9\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
}

void testSubtraction(void)
{
	const char* input = "3 - 2";
	const char* output = "1\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
}

void testMultiplication(void)
{
	const char* input = "3 * 4";
	const char* output = "12\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
}

void testDivision(void)
{
	const char* input = "6 / 2";
	const char* output = "3\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testAddition);
RUN_TEST(testSubtraction);
RUN_TEST(testMultiplication);
RUN_TEST(testDivision);

return UNITY_END();
}
