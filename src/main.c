#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"

#ifndef TEST
int main(int argc, const char* argv[]) {
  Chunk chunk;
	initChunk(&chunk);
	int constant = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constant, 123);
	int constant2 = addConstant(&chunk, 1.4);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constant2, 123);

	writeChunk(&chunk, OP_RETURN, 123);

	disassembleChunk(&chunk, "test chunk");
	freeChunk(&chunk);
	return 0;
}
#endif

