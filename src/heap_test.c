#include "heap.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdint.h>
#define HUGE_FORMAT_STRING "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"


heap* h;
heap_page* p;

void test_new_page(void){
  size_t memory = heap_page_free_memory(p);
  CU_ASSERT(memory==2048);
  CU_ASSERT(p->free==p->start);
}

void test_new_heap(void){
  size_t memory = heap_free_memory(h);
  CU_ASSERT(memory==2048*h->num_pages);
  CU_ASSERT(h->num_pages==(int)(10000/2048));
}


void test_alloc_empty(void){
  uintptr_t *object = heap_alloc_format(h, "", true);
  CU_ASSERT(object==NULL);
  size_t memory = heap_free_memory(h);
  CU_ASSERT(memory==2048*h->num_pages);
}

void test_alloc_fitting(void){
  size_t memory_before = heap_free_memory(h);
  uintptr_t *object = heap_alloc(h,100, true);
  CU_ASSERT(object!=NULL);
  size_t memory_after = heap_free_memory(h);
  CU_ASSERT(memory_after==memory_before-100);
}

void test_alloc_large(void){
  int pages_to_fill = heap_num_active_pages(h);
  for (int i = 0; i<pages_to_fill; ++i){
    uintptr_t *object = heap_alloc(h,1200,true);
    CU_ASSERT(object!=NULL);
  }
  uintptr_t *object = heap_alloc(h,2000,true);
  CU_ASSERT(object==NULL);
}

void test_alloc_huge(void)
{
  uintptr_t a = heap_get_free(h);
  uintptr_t *object = heap_alloc(h,3000, true);
  uintptr_t b = heap_get_free(h);
  CU_ASSERT(object==NULL);
  CU_ASSERT(a==b);
}

int init_suite1()
{
  h = new_heap(10000);
  p = new_heap_page();
  return 0;
}

int clean_suite1()
{
  heap_free(h);
  return 0;
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main(void)
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "test of new page", test_new_page)) ||
       (NULL == CU_add_test(pSuite, "test of new heap", test_new_heap)) ||
       (NULL == CU_add_test(pSuite, "test of empty", test_alloc_empty)) ||
       (NULL == CU_add_test(pSuite, "test of fitting", test_alloc_fitting)) ||
       (NULL == CU_add_test(pSuite, "test of large", test_alloc_large)) ||
       (NULL == CU_add_test(pSuite, "test of huge", test_alloc_huge)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
