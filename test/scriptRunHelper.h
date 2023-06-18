#include "vm.h"

typedef struct {
	const char* output;
	InterpretResult result;
} ScriptResult;

ScriptResult scriptRun(const char* source);

