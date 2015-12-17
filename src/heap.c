#include <stdlib.h>
#include "heap.h"
#include <stdbool.h>

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

int heap_char_to_size(char);
heap_side *new_heap_side();

heap *new_heap(int size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->a=new_heap_side(size);
  h->b=new_heap_side(size);
  return h;
}

heap_side *new_heap_side(int size){
  heap_side* hs = malloc(sizeof(heap_side)+size);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs+sizeof(heap_side)+size);
  return hs;
}

void heap_alloc_format(heap* h, char *formatstring){
  int size = 0;
  
  for (int i = 0; formatstring[i]!='\0'; i++){
    size += heap_char_to_size(formatstring[i]);
  }
  
  heap_alloc_int(h, size);
}

void heap_alloc_int(heap* h, int a){

}

int heap_char_to_size(char a){
  switch (a){
    
  case '*':
    return 3;
    break;

  case 'i':
    return sizeof(int);
    break;
    
  default:
    return 2;
	  
  }
}

bool isSpace(int a){
  return true;
}
