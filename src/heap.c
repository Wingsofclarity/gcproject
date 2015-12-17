#include <stdlib.h>
#include "heap_2.h"

typedef struct heap_side_t heap_side;
typedef struct heap_t heap;

struct heap_side_t{
  int a;
  int b;
};

struct heap_t{
  heap_side* a;
  heap_side* b;

};



heap *new_heap(){
  return (heap*) malloc(sizeof(heap));
}
