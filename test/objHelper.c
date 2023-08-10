#include "memory.h"
#include "object.h"
#include "objHelper.h"


ObjString* createString(char* chars, int length, uint32_t hash) {
	size_t size = sizeof(ObjString);
	ObjString* string = (ObjString*)reallocate(NULL, 0, size);
	((Obj*)string)->type = OBJ_STRING;
	((Obj*)string)->next = NULL;
	string->length = length;
	string->chars = chars;
	string->hash = hash;
	return string;
}

