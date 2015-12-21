#include <stdlib.h>
#include <stdint.h>

#ifndef HEAP_H
#define HEAP_H


typedef struct heap_t heap;
heap *new_heap();

uintptr_t heap_alloc_format(heap*, char *);

#endif
