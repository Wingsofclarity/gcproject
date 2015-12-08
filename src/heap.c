#include <stdbool.h> //For returns of functions.
#include <stdlib.h> 
#include <stdio.h> //For error checking
#include <string.h>
#include <stdint.h>
#include <math.h> //For squareing in bit operations

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

uintptr_t set_header_size(char formatstring[]){
  return 0;
}

int int_pow (int base, int exponent){
  if (exponent == 0) return 1;

  int result = base;
  for (int i = 1; i < exponent; i++){
    result = result * base;
  }
  return result;
}

uintptr_t read_formatstring(char formatstring[]){
  size_t len = strlen( formatstring );
  uintptr_t formatbinary = 0;
  if ( len > ( (PTRSIZE * 8) - 3)  ){
    set_header_size( formatstring );
  }
  else {
    printf("\n");
    for (int i = (len - 1); i >= 0; i--) {
      printf("Character %d: %c\n", i, formatstring[i]);
      if ( formatstring[i] == '*' ){ //If pointer, set bit to 1.
	formatbinary = ( formatbinary | int_pow(2, i) ); //
      }
      // Else keep as 0 because databit should be 0;
    }
  }
  printf("formatbinary: %d\n", formatbinary);
  formatbinary = formatbinary << 2; /* Shift two steps left so we have room
				       for the instruction bits */
  return formatbinary;
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

int main (int argc, char* argv[]){
  heap* heap_test = new_heap(20);
  //printf("Size: %d\n", get_size(heap_test));
  char test[] = "**i*i**iiii*";
  for (int i = 0; i < 25; i++) {
    if (!write_to_heap(heap_test, (99)-i, test) ) {
      //printf("%d: Heap is full!\n", i);
    }
  }
  print_heap(heap_test);

  printf("Size1: %d", heap_test->left_side->size);
  return 1;
  
  //int* test_int = (int*)malloc(sizeof(int));
  //*test_int = 99;
  //void* first_free = (void*)get_first(heap_test);
  //memcpy(first_free, test_int, sizeof(int));
  //printf("\nInt is: %d", *((int*)first_free));
}
