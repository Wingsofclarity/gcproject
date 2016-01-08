#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> //for uintptr_t
#include <stdio.h>

typedef struct heap_t heap;
typedef struct heap_page_t heap_page;

heap *new_heap(size_t);

uintptr_t heap_alloc_raw(heap*, size_t, bool);

uintptr_t heap_alloc_format(heap*, char *, bool);

void heap_switch(heap *);

void traverse_heap(heap*, uintptr_t);

void printHeap(uintptr_t);

size_t heap_free_memory(heap *);

uintptr_t heap_page_get_start(heap_page*);

uintptr_t heap_page_get_free(heap_page*);

heap_page *heap_active_pages(heap*);

void heap_free(heap*);

int heap_num_active_pages(heap*);

#endif
