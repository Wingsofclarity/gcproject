#include "heap.h"
#include <stdio.h>
#include <assert.h>
#include <CUnit/Basic.h>

int main(){
  heap *h = new_heap(32);
  heap_alloc_format(h,"isdfj");

  
  puts("Test completed.");
  return 0;
}

void test_maxi(void)
{
  //CU_ASSERT(false);
}
