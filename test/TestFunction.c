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
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testFnDeclaration);

return UNITY_END();
}
