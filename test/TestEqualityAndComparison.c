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

void testEquality(void)
{
	const char* input = "3 == 3";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(output);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testNilEQuality(void)
{
	const char* input = "nil == nil";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(output);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testNotQuality(void)
{
	const char* input = "3 != 3";
	const char* output = "false\n";
	ScriptResult ret = scriptRun(output);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testGreater(void)
{
	const char* input = "3 > 4";
	const char* output = "false\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testLess(void)
{
	const char* input = "3 < 4";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testEquality);
RUN_TEST(testNilEQuality);
RUN_TEST(testNotQuality);
RUN_TEST(testGreater);
RUN_TEST(testLess);

return UNITY_END();
}
