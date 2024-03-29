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

void testCompileSuccess(void)
{
	const char* input = "print 3 + 3 + 3;";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	if (ret.output != NULL) {
		free(ret.output);
	}
}

void testCompileFailure(void)
{
	const char* input = "print 3 + ;";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_COMPILE_ERROR);
}

void testRunTimeError(void)
{
	const char* input = "print 3 + true;";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_RUNTIME_ERROR);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testCompileSuccess);
RUN_TEST(testCompileFailure);
RUN_TEST(testRunTimeError);

return UNITY_END();
}
