#ifndef STACK_H
#define STACK_H

/// Takes the function pointer stackFunc and applies it to everything that may be a pointer on the stack
void stackTrace(void stackFunc(void*));

#endif
