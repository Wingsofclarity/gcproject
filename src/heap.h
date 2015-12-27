#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> //for uintptr_t
#include <stdio.h>

typedef struct heap_t heap;
typedef struct heap_side_t heap_side;

heap *new_heap();

void *heap_alloc_format(heap*, char *);

bool has_space(heap_side*, int);

heap_side *heap_active_side(heap *);

void heap_switch(heap *);

void traverse_heap(heap*, uintptr_t);

void printHeap(uintptr_t);

uintptr_t heap_get_start(heap*);

uintptr_t heap_get_free(heap*);

#endif
