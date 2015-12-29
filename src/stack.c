#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include "stack.h"
#include <inttypes.h>

#define DumpRegisters() jmp_buf env; if (setjmp(env)) abort();

// Bottom of the stack
extern char **environ;

// Gets a pointer to just above the stack
uintptr_t getStartPoint() {
	return (uintptr_t)(__builtin_frame_address(0));
}

// What we're here for
void stackTrace(void* stackFunc(void*)){
// If you have problem compiling this, don't do it on a windows computer
	DumpRegisters();
	void *current;
	uintptr_t end; 
	const size_t iterator = (sizeof(uintptr_t));
	const uintptr_t stackBot = (uintptr_t)environ;
	uintptr_t tracker = getStartPoint();
	if (stackBot < tracker) {end = tracker; tracker = stackBot;}
	else {end = stackBot;}
	while (tracker < end){
		current = (void*)(tracker);
		current = stackFunc(current);
		tracker = tracker + iterator;
	}
}

