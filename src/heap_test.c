#include "heap.h"
#include <stdio.h>
#include <assert.h>
//#include "Basic.h"

void test_heap(){
  heap *h = new_heap(32);
  heap_alloc_format(h,"isdfj");

  
  puts("Test completed.");
}

void test_maxi(void)
{
  //CU_ASSERT(false);
}
