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

void testStringConcatenate(void)
{
	const char* input = "print \"a\" + \"b\" + \"cd\";";
	const char* output = "abcd\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testInvalidStringConcatenate(void)
{
	const char* input = "print 3 + \"abc\";";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_RUNTIME_ERROR);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testStringConcatenate);
RUN_TEST(testInvalidStringConcatenate);

return UNITY_END();
}
