#include <stdlib.h>
#include <stdbool.h>
#ifndef HEAP_H
#define HEAP_H


typedef struct heap_t heap;
typedef struct heap_side_t heap_side;

heap *new_heap();

void *heap_alloc_format(heap*, char *);
bool has_space(heap_side*, int);
heap_side *new_heap_side(int);
heap_side *heap_active_side(heap *);
void heap_switch(heap *);
void traverse_heap(heap *h, void(*f)(uintptr_t));
void printHeap(uintptr_t);
#endif
