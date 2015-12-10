#include <stdint.h> //for uintptr_t
#include <stdbool.h> //for boolean returns on write functions to confirm.
#include <stdio.h>  //For error checking while coding.

#include "header.h"
#include "heap.h"

int main (int argc, char* argv[]){
  /*heap* heap_test = new_heap(20);
  printf("sizeof(uintptr_t): %d\n", sizeof(uintptr_t));
  //printf("Size: %d\n", get_size(heap_test));
  char test[] = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiicclliififd";
  for (int i = 0; i < 25; i++) {
    if (!write_to_heap(heap_test, (59)-i, test) ) {
      //printf("%d: Heap is full!\n", i);
    }
  }
  print_heap(heap_test);

  //printf("Size1: %d", heap_test->left_side->size);
  return 1;
*/

  char* teststring = "iii23*";
  printf("%s\n", teststring);
  teststring = translate_formatstring( teststring );
  printf("HEJSAN %s\n", teststring);
  
  //int* test_int = (int*)malloc(sizeof(int));
  //*test_int = 99;
  //void* first_free = (void*)get_first(heap_test);
  //memcpy(first_free, test_int, sizeof(int));
  //printf("\nInt is: %d", *((int*)first_free));
}
