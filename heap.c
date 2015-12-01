#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct heap_side {
  int size;
  void* start;
  void* first_free;
};

typedef struct heap_side heap_side;

struct heap {
  heap_side* left_side;
  heap_side* right_side;
  int size;
  bool active_side; //true for left, false for right.
};


typedef struct heap heap;

heap* new_heap(int sizet){
  heap* temp_heap = (heap*)malloc(sizeof(heap));;
  temp_heap->size = sizet;
  temp_heap->active_side = true;

  temp_heap->left_side = (heap_side*)malloc(sizeof(heap_side));
  temp_heap->right_side = (heap_side*)malloc(sizeof(heap_side));

  temp_heap->left_side->size = sizet;
  temp_heap->right_side->size = sizet;

  temp_heap->left_side->start = (int*)malloc(sizeof(int)*sizet);
  temp_heap->right_side->start = (int*)malloc(sizeof(int)*sizet);

  temp_heap->left_side->first_free = temp_heap->left_side->start;
  temp_heap->right_side->first_free = temp_heap->right_side->start;
  
  return temp_heap;
}

int get_size(heap* heap){
  return heap->size;
}

int main (int argc, char* argv[]){
  heap* heap_test = new_heap(20);
  printf("Size: %d", get_size(heap_test));
}
