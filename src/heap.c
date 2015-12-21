#include <stdlib.h>
#include <stdint.h>
#include "heap.h"
#include <stdbool.h>
#include "header.h"

typedef struct heap_side_t heap_side;
typedef struct heap_t heap;

struct heap_side_t{
  uintptr_t start;
  uintptr_t free;
  uintptr_t end;
};

struct heap_t{
  heap_side* a;
  heap_side* b;
  bool active;
};

bool has_space(heap_side*, int);
heap_side *new_heap_side(int);
heap_side *heap_active_side(heap *);
void heap_switch(heap *);

heap *new_heap(int size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->a=new_heap_side(size/2);
  h->b=new_heap_side(size/2);
  return h;
}

heap_side *new_heap_side(int size){
  heap_side* hs = malloc(sizeof(heap_side)+size);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs+sizeof(heap_side)+size);
  return hs;
}

uintptr_t heap_alloc_format(heap* h, char *formatstring){
  uintptr_t a = read_formatstring(formatstring);
  size_t size = size_of_object(a);
  heap_side* hs = heap_active_side(h);
  if (!has_space(hs,size)){
    heap_switch(h);
    hs = heap_active_side(h);
    
    if(!has_space(hs,size)){
      //Error
    }
  }
  uintptr_t r = hs->free;
  hs->free = hs->free+size;
  return r;
}

void heap_switch(heap *h){
  h->active = !h->active;
}

heap_side *heap_active_side(heap *h){
  if (h->active) return h->a;
  else return h->b;
}

bool has_space(heap_side* hs, int size){
  return (hs->free+size>=hs->end);
}
