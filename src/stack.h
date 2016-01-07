#ifndef STACK_H
#define STACK_H

/// Takes the function pointer stackFunc and applies it to everything that may be a pointer on the stack
/// stackFunc must either return the new address to the pointer, or if that is not possible, its argument
void stackTrace(void* stackFunc(void*));

#endif
