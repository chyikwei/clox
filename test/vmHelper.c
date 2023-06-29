#include "object.h"
#include "vm.h"
#include "vmHelper.h"

int objectCount() {
	int cnt = 0;
	Obj* object = vm.objects;
	while (object != NULL) {
		object = object->next;
		cnt += 1;
	}
	return cnt;
}
