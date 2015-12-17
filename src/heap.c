#include <stdlib.h>
#include "heap.h"
#include <stdbool.h>

typedef struct heap_side_t heap_side;
typedef struct heap_t heap;

struct heap_side_t{
  
};

struct heap_t{
  heap_side* a;
  heap_side* b;
  bool active;
};

int heap_char_to_size(char);

heap *new_heap(){
  return (heap*) malloc(sizeof(heap));
}

void heap_alloc(char *s){
  int i = heap_char_to_size(s[0]);
  malloc(i);
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
