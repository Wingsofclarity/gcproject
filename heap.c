#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct heap_side {
  int size;
  uintptr_t start;
  uintptr_t first_free;
};

typedef struct heap_side heap_side;

struct heap {
  heap_side* left_side;
  heap_side* right_side;
  int size;
  bool active_side; //true for left, false for right.
};


typedef struct heap heap;

heap* new_heap(int size){
  heap* temp_heap = (heap*)malloc(sizeof(heap));;
  temp_heap->size = size;
  temp_heap->active_side = true;

  temp_heap->left_side = (heap_side*)malloc(sizeof(heap_side));
  //temp_heap->right_side = (heap_side*)malloc(sizeof(heap_side));

  temp_heap->left_side->size = size;
  temp_heap->right_side->size = size;

  temp_heap->left_side->start = (uintptr_t)malloc(sizeof(int)*size);
  temp_heap->right_side->start = (uintptr_t)malloc(sizeof(int)*size);

  temp_heap->left_side->first_free = temp_heap->left_side->start;
  temp_heap->right_side->first_free = temp_heap->right_side->start;
  
  return temp_heap;
}

int get_size(heap* heap){
  return heap->size;
}

uint32_t get_first(heap* heap){
  if (heap->active_side){
    return (heap->left_side->first_free);
  }
  return 0;
}

bool write_to_left(heap* heap, int value){
  int* first_free = (int*)heap->left_side->first_free;
  *first_free = value;
  heap->left_side->first_free = (heap->left_side->first_free) + sizeof(int);
  return true;
}

bool write_to_heap(heap* heap, int value){
  if (heap->active_side){
    return write_to_left(heap, value);
  }
  else {
    return false;
  }
}

void print_heap(heap* heap){ /*Mainly a test function, will never be used in
			       testing*/
  if (heap->active_side){
    uintptr_t start = heap->left_side->start;
    uintptr_t end = heap->left_side->first_free;

    
    
    int i = 0;
    for (; start < end; start = start + sizeof(int)) {
      printf("\n%d: %d", i++, *((int*)start));
    }
    printf("\n");
  }
}

int main (int argc, char* argv[]){
  heap* heap_test = new_heap(20);
  printf("Size: %d", get_size(heap_test));

  for (int i = 0; i < 22; i++) {
      write_to_heap(heap_test, 99-i);
  }
  print_heap(heap_test);

  printf("Size: %d", heap_test->left_side->size);
  //int* test_int = (int*)malloc(sizeof(int));
  //*test_int = 99;
  //void* first_free = (void*)get_first(heap_test);
  //memcpy(first_free, test_int, sizeof(int));
  //printf("\nInt is: %d", *((int*)first_free));
}
