#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, ObjectType) \
		(type*)allocateObject(sizeof(type), ObjectType)

static Obj* allocateObject(size_t size, ObjType type) {
	Obj* object = (Obj*)reallocate(NULL, 0, size);
	object->type = type;
	object->isMarked = false;

	object->next = vm.objects;
	vm.objects = object;

#ifdef DEBUG_LOG_GC
	printf("%p allocate %ld for %d\n", (void*)object, size, type);
#endif
	return object;
}

ObjBoundMethod* newBoundMethod(Value receiver, ObjClosure* method) {
	ObjBoundMethod* bound = ALLOCATE_OBJ(ObjBoundMethod, OBJ_BOUND_METHOD);
	bound->receiver = receiver;
	bound->method = method;
	return bound;
}

ObjClass* newClass(ObjString* name) {
	ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
	klass->name = name;
	initTable(&klass->methods);
	return klass;
}

ObjInstance* newInstance(ObjClass* klass) {
	ObjInstance* instance = ALLOCATE_OBJ(ObjInstance, OBJ_INSTANCE);
	instance->klass = klass;
	initTable(&instance->fields);
	return instance;
}

ObjClosure* newClosure(ObjFunction* function) {
	ObjUpvalue** upvalues = ALLOCATE(ObjUpvalue*, function->upvalueCount);
	for (int i = 0; i < function->upvalueCount; i++) {
		upvalues[i] = NULL;
	}
	ObjClosure* closure = ALLOCATE_OBJ(ObjClosure, OBJ_CLOSURE);
	closure->function = function;
	closure->upvalues = upvalues;
	closure->upvalueCount = function->upvalueCount;
	return closure;
}

ObjFunction* newFunction() {
	ObjFunction* function = ALLOCATE_OBJ(ObjFunction, OBJ_FUNCTION);

	function->arity = 0;
	function->upvalueCount = 0;
	function->name = NULL;
	initChunk(&function->chunk);
	return function;
}

ObjNative* newNative(NativeFn function) {
	ObjNative* native = ALLOCATE_OBJ(ObjNative, OBJ_NATIVE);
	native->function = function;
	return native;
}

static ObjString* allocateString(char* chars, int length, uint32_t hash) {
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->length = length;
	string->chars = chars;
	string->hash = hash;

	push(OBJ_VAL(string));
	tableSet(&vm.strings, string, NIL_VAL);
	pop();
	return string;
}

static uint32_t hashString(const char* key, int length) {
	uint32_t hash = 2166136261u;

	for(int i = 0; i < length; i++) {
		hash ^= key[i];
		hash *= 16777619;
	}
	return hash;
}

ObjString* takeString(char* chars, int length) {
	uint32_t hash = hashString(chars, length);
	ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
	if (interned != NULL) {
		FREE_ARRAY(char, chars, length + 1);
		return interned;
	}

	return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
	uint32_t hash = hashString(chars, length);
	ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
	if (interned != NULL) return interned;

	char* heapChars = ALLOCATE(char, length + 1);
	memcpy(heapChars, chars, length);
	heapChars[length] = '\0';

	return allocateString(heapChars, length, hash);
}

ObjUpvalue* newUpvalue(Value* slot) {
	ObjUpvalue* upvalue = ALLOCATE_OBJ(ObjUpvalue, OBJ_UPVALUE);
	upvalue->location = slot;
	upvalue->next = NULL;
	upvalue->closed = NIL_VAL;

	return upvalue;
}

static void printFunction(ObjFunction* function, FILE* outstream) {
	if(function->name == NULL) {
		fprintf(outstream, "<script>");
		return;
	}
	fprintf(outstream, "<fn %s>", function->name->chars);
}

void printObject(Value value, FILE* outstream) {
	switch (OBJ_TYPE(value)) {
		case OBJ_CLASS:
			fprintf(outstream, "%s", AS_CLASS(value)->name->chars);
			break;
		case OBJ_INSTANCE:
			fprintf(outstream, "%s instance",
						  AS_INSTANCE(value)->klass->name->chars);
			break;
		case OBJ_STRING:
			fprintf(outstream, "%s", AS_CSTRING(value));
			break;
		case OBJ_FUNCTION:
			printFunction(AS_FUNCTION(value), outstream);
			break;
		case OBJ_NATIVE:
			fprintf(outstream, "<native fn>");
			break;
		case OBJ_BOUND_METHOD:
			printFunction(AS_BOUND_METHOD(value)->method->function, outstream);
			break;
		case OBJ_CLOSURE:
			printFunction(AS_CLOSURE(value)->function, outstream);
			break;
		case OBJ_UPVALUE:
			fprintf(outstream, "upvalue");
			break;
	}
}
