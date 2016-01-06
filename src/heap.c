#include "heap.h"
#include "header.h"
#include <stdio.h> //for debugging
#include <string.h>
#define SIDE_SIZE 2048

struct heap_side_t{
  uintptr_t start;
  uintptr_t free;
  uintptr_t end;
  bool active;
  bool safe;
};

struct heap_t{
  heap_side* sides;
  int num_sides;

};

bool has_space(heap_side*, size_t);
heap_side *new_heap_side();
heap_side *heap_active_free_side(heap *, size_t);
void heap_switch(heap *);
void heap_side_free(heap_side*);

heap *new_heap(size_t size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->num_sides = size/SIDE_SIZE;
  h->sides = malloc(h->num_sides*(sizeof(heap_side)+SIDE_SIZE));
  //h->sides=heap_side[h->num_sides];
  for (int i = 0; i<h->num_sides; i++){
    h->sides[i]=*new_heap_side();
  }
  return h;
}

heap_side *new_heap_side(){
  heap_side* hs = malloc(sizeof(heap_side)+SIDE_SIZE);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs->start+SIDE_SIZE);
  hs->active = false;
  hs->safe=false;
  return hs;
}

uintptr_t *heap_alloc_format(heap* h, char *formatstring){
  if (strcmp(formatstring,"")==0){
    return NULL;
  }
  
  uintptr_t a = set_header_size(formatstring);
  size_t size = size_of_object(a);
  //size_t size=2; //CHEAT!
  return heap_alloc(h, size);
}

uintptr_t *heap_alloc(heap* h, size_t size){
  if (size>SIDE_SIZE){
    return NULL;
  }
  
  heap_side* hs = heap_active_free_side(h, size);
  
  if (hs==NULL){
    return NULL;
  }
  
  uintptr_t r = hs->free;
  hs->free = hs->free+size;
  void *p = &r;
  return p;
}

heap_side *heap_active_free_side(heap *h, size_t size){
  for (int i = 0; i<h->num_sides; i++){
    if (has_space(&h->sides[i],size) &&
	h->sides[i].active){
      return &h->sides[i];
    }
  }
  return NULL;
}

bool has_space(heap_side* hs, size_t size){
  return (hs->free+size<=hs->end);
}

uintptr_t heap_get_start(heap* h){
  return 0;
}

uintptr_t heap_get_free(heap* h){
  return 0;
}

void heap_free(heap *h){
  free(h);  
}

void heap_side_free(heap_side *hs){
  //TODO: Is nessary?
}
