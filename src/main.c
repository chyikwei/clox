#include <stdio.h>
#include "common.h"
#include "chunk.h"

#ifndef TEST
int main(int argc, const char* argv[]) {
  Chunk chunk;
	initChunk(&chunk);
	writeChunk(&chunk, OP_RETURN);
	freeChunk(&chunk);
	printf("test\n");
	return 0;
}
#endif

