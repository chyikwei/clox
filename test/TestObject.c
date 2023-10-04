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
	// total should be 8 objects: "aa", "bb", "cc", "aabb", "aabbcc"
	// native: "clock", clock fn(), "<script>", <script> closure
	TEST_ASSERT_EQUAL_INT(9, objectCount());
	free(ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testObjectCount);

return UNITY_END();
}
