#include "vm.h"

typedef struct {
	char* output;
	InterpretResult result;
} ScriptResult;

ScriptResult scriptRun(const char* source);

