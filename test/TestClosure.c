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

void testScopeVar(void)
{
	const char* input = 
		"var x = \"global\";\
		 fun outer() {\
			 var x = \"outer\";\
	     fun inner() { print x; }\
		   inner();\
		}\
		outer();";
	const char* output = "outer\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testClosedVar(void)
{
	const char* input = 
		"fun outer() {\
		   var x = \"outer\";\
			 fun mid() {\
			   fun inner() { print x;}\
				 return inner;\
			 }\
	     return mid;\
     }\
		 var mid = outer();\
		 var in = mid();\
     in();";
	
			 
	const char* output = "outer\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testAssignment(void)
{
	const char* input = 
		"fun outer() {\
		   var x = \"before\";\
			 fun inner() {x = \"after\";}\
			 inner();\
			 print x;\
		}\
		outer();";
	const char* output = "after\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

int main(void)
{
UNITY_BEGIN();

RUN_TEST(testScopeVar);
RUN_TEST(testClosedVar);
RUN_TEST(testAssignment);

return UNITY_END();
}
