#include <stdbool.h> //For true .
#include <stdlib.h> 
#include <stdio.h> //For error checking
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h> //For squareing in bit operations
#include "header.h"
#include "heap_old.h"

#define INTSIZE sizeof(int)
#define PTRSIZE sizeof(uintptr_t)

struct heap_side {
  int bytes;
  
  uintptr_t start;
  uintptr_t first_free;
  uintptr_t last_block;
};

typedef struct heap_side heap_side;

struct heap {
  heap_side* left_side;
  heap_side* right_side;
  int bytes;
  bool active_side; //true for left, false for right.
};

heap* new_heap_old(size_t bytes){
  heap* temp_heap = (heap*)malloc(sizeof(heap));
  // Is this neccesary?
  temp_heap->bytes = bytes;
  // Can't imagine where we'd use this information.

  temp_heap->active_side = true;

  heap_side* leftside = (heap_side*)malloc( bytes );
  heap_side* rightside = (heap_side*)malloc ( bytes );

  leftside->start = (uintptr_t)leftside;
  rightside->start = (uintptr_t)rightside;

  leftside->first_free = (uintptr_t)leftside->start;
  rightside->first_free = (uintptr_t)rightside->start;
  printf("leftside->start: %d\n", leftside->start);
  printf("leftside->first_free: %d\n", leftside->first_free);
  
  leftside->last_block = leftside->first_free + bytes;
  rightside->last_block = rightside->first_free + bytes;
  printf("Leftside->last_block: %d\n", leftside->last_block);
  
  temp_heap->left_side = leftside;
  temp_heap->right_side = rightside;
  printf("Temp-heap firstfree: %d\n", temp_heap->left_side->first_free);
  return temp_heap;
}

int get_size(heap* heap){
  return heap->bytes;
}

uint32_t get_first(heap* heap){
  if (heap->active_side){
    return (heap->left_side->first_free);
  }
  else return heap->right_side->first_free;
  return 0;
}

bool write_to_side(heap_side* heapside, int value, char* formatstring){
  uintptr_t header = read_formatstring(formatstring);
  if ( header != 0 ) printf("Header: %"PRIuPTR"\n", header);
  
  printf("%d\n", heapside->first_free);
  if (heapside->first_free >= heapside->last_block ||
      heapside->first_free < heapside->start) { 
    printf("heapsize: %d, %d, %d\n", heapside->first_free,
	   heapside->start, heapside->last_block);
    return false;
  }
  *( (int*)heapside->first_free ) = value;
  //This is the line that creates the bug.
  
  printf("%d written in to %d\n", value, heapside->first_free);
  heapside->first_free =(uintptr_t) (heapside->first_free) + 8;
  return true;
}

bool write_to_heap(heap* heap, int value, char* formatstring){
  if (heap->active_side){
    return write_to_side(heap->left_side, value, formatstring);
  }
  else {
    return write_to_side(heap->right_side, value, formatstring);
  }
  return false;
} 

bool change_to_right(heap* head){
  head->active_side = false;
  head->left_side->first_free = head->left_side->start;
  return true;
}

bool change_to_left(heap* head){
  head->active_side = true;
  head->right_side->first_free = head->right_side->start;
  return true;
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
    printf("\n%"PRIuPTR" sizeof(int). %"PRIuPTR" sizeof(uintptr_t)\n", INTSIZE,
	   PTRSIZE);
    for (; start < end; start = start + INTSIZE + PTRSIZE) {
      printf("\n%d: %d", i++, *((int*)start));
    }
    printf("\nPrinted %d objects\n\n", i);
  }
}

