#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vm.h"
#include "scriptRunHelper.h"

ScriptResult scriptRun(const char* source) {
  // tmp file for script outstream
	FILE* tmp_out = tmpfile();
	if(tmp_out == NULL) {
		fprintf(stderr, "Could not create temp file.");
 		exit(74);
	}
	// run interpreter
	InterpretResult ir = interpret(source, tmp_out);
	
	ScriptResult ret;
	ret.result = ir;

	if (ir == INTERPRET_OK) {
		//only dump output stream to string when run successfully
		fseek(tmp_out, 0L, SEEK_END);
		size_t fileSize = ftell(tmp_out);
  	rewind(tmp_out);
 
  	char* outString = (char*) malloc(fileSize + 1);
  	size_t bytesRead = fread(outString, sizeof(char), fileSize, tmp_out);
  	if(bytesRead < fileSize) {
    	fprintf(stderr, "Could not read temp file");
    	exit(74);
  	}
	  outString[bytesRead] = '\0';
		ret.output = outString;
	} else {
		ret.output = NULL; 
	}
	//close file
	fclose(tmp_out);
	
	return ret;	
}

