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

void testBooleanValue(void)
{
	const char* bool_val = "true";
	const char* output = "true\n";
	ScriptResult ret = scriptRun(bool_val);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testNilValue(void)
{
	const char* nil_val = "nil";
	const char* output = "nil\n";
	ScriptResult ret = scriptRun(nil_val);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testNumberValue(void)
{
	const char* number_val = "10";
	const char* output = "10\n";
	ScriptResult ret = scriptRun(number_val);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);

	if (ret.output != NULL) {
		free(ret.output);
	}
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testBooleanValue);
RUN_TEST(testNilValue);
RUN_TEST(testNumberValue);

return UNITY_END();
}
