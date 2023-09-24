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

void testBlock(void)
{
	const char* input =
		"{var a = \"123a\";"
		" print a; }";

	const char* output = "123a\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testScope(void)
{
	const char* input =
		"var a = \"123\"; print a;"
		"{var a = \"456\"; print a;}"
		"print a;";

	const char* output = "123\n456\n123\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testLookUpOuterScope(void)
{
  const char* input = 
	  "var a = \"123\";"
	  "{var b = a + \"456\"; print b;}";
  const char* output = "123456\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(ret.output, output);
	free(ret.output);
}

void testSelfAssign(void)
{
	const char* input = "var a = \"outer\"; {var a = a;}";

	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_COMPILE_ERROR);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testBlock);
RUN_TEST(testScope);
RUN_TEST(testLookUpOuterScope);
RUN_TEST(testSelfAssign);

return UNITY_END();
}
