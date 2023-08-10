#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "value.h"
#include "object.h"
#include "objHelper.h"
#include "table.h"

Table table;
ObjString* str1;
ObjString* str2;
ObjString* str3;
Value retVal;


void setUp(void) {
	initTable(&table);
	str1 = createString("test1", 5, 10);
	str2 = createString("test2", 5, 10);
	str3 = createString("test3", 5, 5);
	retVal = NIL_VAL;
}

void tearDown(void) {
  freeTable(&table);
}

void testSetGet(void) {
	tableSet(&table, str1, NUMBER_VAL(3));
	TEST_ASSERT_EQUAL_INT(table.count, 1);

	bool ret = tableGet(&table, str1, &retVal);
	TEST_ASSERT_TRUE(ret);
	TEST_ASSERT_EQUAL_INT(AS_NUMBER(retVal), 3);
}

void testSameHashValue(void) {
	tableSet(&table, str1, NUMBER_VAL(3));
	tableSet(&table, str2, NUMBER_VAL(4));
	TEST_ASSERT_EQUAL_INT(table.count, 2);

	bool ret = tableGet(&table, str1, &retVal);
	TEST_ASSERT_TRUE(ret);
	TEST_ASSERT_EQUAL_INT(AS_NUMBER(retVal), 3);

	bool ret2 = tableGet(&table, str2, &retVal);
	TEST_ASSERT_TRUE(ret2);
	TEST_ASSERT_EQUAL_INT(AS_NUMBER(retVal), 4);
}

void testDeletion(void) {
	tableSet(&table, str1, NUMBER_VAL(3));
	tableDelete(&table, str1);
	bool ret = tableGet(&table, str1, &retVal);
	TEST_ASSERT_FALSE(ret);
}

void testAddAll(void) {
	Table toTable;
	tableSet(&table, str1, NUMBER_VAL(3));
	tableSet(&table, str2, NUMBER_VAL(4));
	tableAddAll(&table, &toTable);

	bool ret = tableGet(&toTable, str1, &retVal);
	TEST_ASSERT_TRUE(ret);
	TEST_ASSERT_EQUAL_INT(AS_NUMBER(retVal), 3);

	bool ret2 = tableGet(&toTable, str2, &retVal);
	TEST_ASSERT_TRUE(ret2);
	TEST_ASSERT_EQUAL_INT(AS_NUMBER(retVal), 4);
}

void testFindString() {
	tableSet(&table, str1, NUMBER_VAL(3));
	//find
	ObjString* ret1 = tableFindString(&table, "test1", 5, 10);
	TEST_ASSERT_NOT_NULL(ret1);
	// not find
	ObjString* ret2 = tableFindString(&table, "test2", 5, 10);
	TEST_ASSERT_NULL(ret2);

}

int main(void) {
UNITY_BEGIN();

RUN_TEST(testSetGet);
RUN_TEST(testSameHashValue);
RUN_TEST(testDeletion);
RUN_TEST(testAddAll);
RUN_TEST(testFindString);

return UNITY_END();
}
