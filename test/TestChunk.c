#include <stdlib.h>
#include "unity.h"
#include "chunk.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void testChunk(void)
{
Chunk chunk;
initChunk(&chunk);
writeChunk(&chunk, OP_RETURN);
freeChunk(&chunk);
}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(testChunk);
return UNITY_END();
}
