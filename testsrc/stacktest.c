#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include "../src/stack.h"
#include <inttypes.h>



// For testing stuff
uintptr_t runs = 0;
uintptr_t comb = 0;

// Stupid implementation test function
void* stackTester(void* point)
{
	uintptr_t* maybePointer = point;
	runs++;
	comb = comb + *(uintptr_t*)point;
	if (100 > *(uintptr_t*)point) {(*maybePointer)++; printf("%"PRIuPTR"\n", *maybePointer); return point;}
	printf("%"PRIuPTR"\n", *maybePointer);
	return point;
}

int main(int argc, char* argv[])
{
	stackTrace(stackTester);
	printf("%"PRIuPTR"\n", comb);
	printf("%"PRIuPTR"\n", runs);
	return 0;
}
