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
	const char* input = "3 + 3 + 3";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
}

void testCompileFailure(void)
{
	const char* input = "3 + ";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_COMPILE_ERROR);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testCompileSuccess);
RUN_TEST(testCompileFailure);

return UNITY_END();
}
