#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include "stack.h"
#include <inttypes.h>

#define DumpRegisters() jmp_buf env; if (setjmp(env)) abort();

// Bottom of the stack
extern char **environ;

// For testing stuff
uintptr_t runs = 0;
uintptr_t comb = 0;

// Gets a pointer to just above the stack
uintptr_t getStartPoint() {
	return (uintptr_t)(__builtin_frame_address(0));
}

// What we're here for
void stackTrace(void stackFunc(void*)){
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
		stackFunc(current);
		tracker = tracker + iterator;
	}
}

// Testing stuff
void stackTester(void* maybePointer){
	runs++;
	comb = comb + *(uintptr_t*)(maybePointer);
}

// Testing stuff
int main (int argc, char *argv[]){
	stackTrace(stackTester);
	printf("%"PRIuPTR"\n", comb);
	printf("%"PRIuPTR"\n", runs);
}
