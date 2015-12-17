#include "heap.h"
#include <stdio.h>
#include <assert.h>
//#include "Basic.h"

int main(){
  heap *h = new_heap(32);
  heap_alloc_int(h,321);

  
  puts("Test completed.");
  return 0;
}

void test_maxi(void)
{
  //CU_ASSERT(false);
}
