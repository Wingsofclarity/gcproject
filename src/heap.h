#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> //for uintptr_t
#include <stdio.h>

typedef struct heap_t heap;
typedef struct heap_page_t heap_page;

heap *new_heap(size_t);

uintptr_t heap_alloc(heap*, size_t, bool);

uintptr_t heap_alloc_format(heap*, char *, bool);

void heap_switch(heap *);

void traverse_heap(heap*, uintptr_t);

void printHeap(uintptr_t);

size_t heap_free_memory(heap *);

uintptr_t heap_get_start(heap*);

uintptr_t heap_get_free(heap*);

void heap_free(heap*);


//-------

struct heap_page_t{
  uintptr_t start;
  uintptr_t free;
  uintptr_t end;
  bool active;
  bool safe;
};

struct heap_t{
  heap_page* pages;
  int num_pages;
};

bool has_space(heap_page*, size_t);
heap_page * new_heap_page();
heap_page *heap_active_free_page(heap *, size_t);
heap_page *heap_passive_page(heap*);
void heap_switch(heap *);
void heap_page_free(heap_page*);
int heap_num_active_pages(heap*);
size_t heap_free_memory(heap *h);
size_t heap_page_free_memory(heap_page *p);
//-------


#endif
