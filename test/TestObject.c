#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "vm.h"
#include "scriptRunHelper.h"
#include "vmHelper.h"

void setUp(void) {
	initVM();
}

void tearDown(void) {
  freeVM();
}

void testObjectCount(void)
{
	const char* input = "print \"aa\" + \"bb\" + \"cc\";";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_INT(objectCount(), 5);
	free(ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testObjectCount);

return UNITY_END();
}
