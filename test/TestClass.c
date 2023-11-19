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

void testPrintClass(void)
{
	const char* input = 
		"class Brioche {} \
		 print Brioche;";
	const char* output = "Brioche\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testPrintInstance(void)
{
	const char* input = 
		"class Brioche {} \
		 print Brioche();";
	const char* output = "Brioche instance\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testProperty(void)
{
	const char* input =
		"class Pair {}\
		 var pair = Pair();\
		 pair.first = 1;\
		 print pair.first;";
	const char* output = "1\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testMethod(void)
{
	const char* input =
		"class Brunch {\
		 bacon() { print 123; }\
		}\
		Brunch().bacon();";

	const char* output = "123\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testThis(void)
{
	const char* input =
		"class Person {\
		 	sayName() { print this.name; }\
		}\
		var jane = Person();\
		jane.name = \"Jane\";\
		jane.sayName();";

	const char* output = "Jane\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
	free(ret.output);
}

void testThisInFunction(void)
{
	const char* input =
		"class Nested {\
		 	method() {\
			 	fun function() {print this;}\
			 	function();\
			}\
		}\
		Nested().method();";

	const char* output = "Nested Instance\n";
	ScriptResult ret = scriptRun(input);
	TEST_ASSERT(ret.result == INTERPRET_OK);
	TEST_ASSERT_EQUAL_STRING(output, ret.output);
}


int main(void)
{
UNITY_BEGIN();

RUN_TEST(testPrintClass);
RUN_TEST(testPrintInstance);
RUN_TEST(testProperty);
RUN_TEST(testMethod);
RUN_TEST(testThis);
RUN_TEST(testThisInFunction);

return UNITY_END();
}
