#include <stdbool.h>

struct heap {
  heap_side* left_side;
  heap_side* right_side;
  int size;
  bool active_side; //true for left, false for right.
};

struct heap_side {
  int size;
  void* start;
  void* first_free;
};

typedef struct heap heap;

heap* new_heap(int size){
  heap* temp_heap = (heap*)malloc(sizeof(heap));;
  temp_heap->size = size;
  temp_heap->active_side = true;

  temp_heap->left_side = (heap_side*)malloc(sizeof(heap_side));
  temp_heap->right_side = (heap_side*)malloc(sizeof(heap_side));

  temp_heap->left_side->size = size;
  temp_heap->right_side->size = size;


}
