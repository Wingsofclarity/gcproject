#include "heap.h"
#include "header.h"
#include <stdio.h> //for debugging

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
heap_side *new_heap_side(size_t);
heap_side *heap_active_side(heap *);
void heap_switch(heap *);
void heap_side_free(heap_side*);

heap *new_heap(size_t size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->a=new_heap_side(size/2);
  h->b=new_heap_side(size/2);
  h->active = true;
  return h;
}

heap_side *new_heap_side(size_t size){
  heap_side* hs = malloc(sizeof(heap_side)+size);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs->start+size);
  return hs;
}

uintptr_t *heap_alloc_format(heap* h, char *formatstring){
  puts("Trace!");
  uintptr_t a = set_header_size(formatstring);
  puts("Trace!");
  size_t size = size_of_object(a);
  puts("Trace!");
  heap_side* hs = heap_active_side(h);
  puts("Trace!");
  
  if (!has_space(hs,size)){
    heap_switch(h);
    hs = heap_active_side(h);
    //Switch side everywhere
    
    if(!has_space(hs,size)){
      //If there is no space at this point, then the heap is simply too small.
      perror("Heap too small too allocate.");
      exit(0);
    }
  }
  
  uintptr_t r = hs->free;
  hs->free = hs->free+size;
  void *p = &r;
  return p;
}

/*Testfunction: Print out the allocated addresses */
//This name seams off. /Gustav
void printHeap(uintptr_t n)
{
  printf("Pointer: %lu ", n);
  printf("\tsize:%lu \n",sizeof(n));
  
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

uintptr_t heap_get_start(heap* h){
  return heap_active_side(h)->start;
}

uintptr_t heap_get_free(heap* h){
  return heap_active_side(h)->free;
}

void heap_free(heap *h){
  heap_side_free(h->a);
  heap_side_free(h->b);
  free(h);  
}

void heap_side_free(heap_side *hs){
  //TODO: Is nessary?
}
