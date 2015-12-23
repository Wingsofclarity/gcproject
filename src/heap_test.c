#include "heap.h"
#include <stdio.h>
#include <assert.h>
//#include "Basic.h"

struct testStruct{
  int i;
  int j;
};

typedef struct testStruct TS;
void test(TS *a,int c);


int main(){
  heap *h = new_heap(1024);
  
  TS *a=heap_alloc_format(h,"ii");
  TS *b=heap_alloc_format(h,"ii");
  
  test(a,2);
  
  printf("\nPrint value: %i\n",a->i);

  test(b,6);
  printf("Print value: %i\n",b->i);
  
  traverse_heap(h,printHeap);

  puts("Test completed.");
  return 0;
}

void test(TS *a,int c){
  a->i=c;
}

void test_maxi(void)
{
  //CU_ASSERT(false);
}
