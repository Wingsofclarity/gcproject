#include <stdlib.h>
#include "heap.h"
#include "header.h"
#include <stdio.h>

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

heap *new_heap(int size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->a=new_heap_side(size/2);
  h->b=new_heap_side(size/2);
  h->active =true;
  return h;
}

heap_side *new_heap_side(int size){
  heap_side* hs = malloc(sizeof(heap_side)+size);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs+sizeof(heap_side)+size);

  return hs;
}

/*OBS: Changed return type from unitptr_t to void* */
void* heap_alloc_format(heap* h, char *formatstring){
  uintptr_t a = set_header_size(formatstring);
  size_t size = size_of_object(a);
  heap_side* hs = heap_active_side(h);

  // TODO: Detta ger fel när man vill traversera heapen /Peter
  /* 
    if (!has_space(hs,size)){
    heap_switch(h);
    hs = heap_active_side(h);
  
    if(!has_space(hs,size)){
    // Error
    }
    }
    
  */
  
  uintptr_t r = hs->free;
  hs->free = hs->free+size;
  printf("ALLOCATED: %lu\n",r);  // OBS: Temporär printsats,tas bort sen! 
  void *p = &r;
  return p;
}

/*Beginning to traverse heap*/
void traverse_heap(heap *h, void(*f)(uintptr_t)){
 
  heap_side* hs = heap_active_side(h);
  uintptr_t start = hs->start;
  uintptr_t end = hs->free;

  printf("\n-----Traverse------\n");
  while(start < end) 
      {
	
        f(start);
	start = start + 8;   // TODO: ändra 8an till sizen av actuellt objekt! /Peter
      }
}

/*Testfunction: Print out the allocated addresses */
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
