#include <stdbool.h> //For true .
#include <stdlib.h> 
#include <stdio.h> //For error checking
#include <string.h>
#include <stdint.h>

#include <math.h> //For squareing in bit operations

#include "heap.h"

#define INTSIZE sizeof(int)
#define PTRSIZE sizeof(uintptr_t)

struct heap_side {
  int size;
  
  uintptr_t start;
  uintptr_t first_free;
  uintptr_t last_block;
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
  //The heap currently only works with ints, as the implemenation details
  //will mean the allocation is done differently.
  heap* temp_heap = (heap*)malloc(sizeof(heap));;
  temp_heap->size = size;
  temp_heap->active_side = true;

  heap_side* leftside = (heap_side*)malloc(sizeof(heap_side));
  heap_side* rightside = (heap_side*)malloc(sizeof(heap_side));
  
  leftside->size = size;
  rightside->size = size;

  leftside->start = (uintptr_t)malloc( (INTSIZE + PTRSIZE) * size );
  rightside->start = (uintptr_t)malloc( (INTSIZE + PTRSIZE) * size);

  leftside->last_block = (leftside->start + ((INTSIZE + PTRSIZE) * size) );
  rightside->last_block = (rightside->start + ((INTSIZE + PTRSIZE) *size));

  leftside->first_free = leftside->start;
  rightside->first_free = rightside->start;

  temp_heap->left_side = leftside;
  temp_heap->right_side = rightside;
  
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

bool write_to_side(heap_side* heapside, int value, char formatstring[]){
  uintptr_t header = read_formatstring(formatstring);
  if ( header != 0 ) printf("Header: %d\n", header);
  int* first_free = (int*)heapside->first_free;
  if (heapside->first_free >= heapside->last_block ||
      heapside->first_free < heapside->start) {
    return false;
  }
  *first_free = value;
  heapside->first_free = (heapside->first_free) + INTSIZE + PTRSIZE;
  return true;
}

bool write_to_heap(heap* heap, int value, char formatstring[]){
  if (heap->active_side){
    return write_to_side(heap->left_side, value, formatstring);
  }
  else {
    return write_to_side(heap->right_side, value, formatstring);
  }
  return false;
} 

bool change_to_right(heap* head){
  return false;
}

bool change_to_left(heap* head){
  return false;
}

bool change_side(heap* heap){
  if (heap->active_side){ //left is active
    return change_to_right(heap);
  }
  else return change_to_left(heap);
}

void print_heap(heap* heap){ /*Mainly a test function, 
			       will never be used outside tests*/
  if (heap->active_side){
    uintptr_t start = heap->left_side->start;
    uintptr_t end = heap->left_side->first_free;

    
    
    int i = 0;
    printf("\n%d sizeof(int). %d sizeof(uintptr_t)\n", INTSIZE,
	   PTRSIZE);
    for (; start < end; start = start + INTSIZE + PTRSIZE) {
      printf("\n%d: %d", i++, *((int*)start));
    }
    printf("\nPrinted %d objects\n\n", i);
  }
}

