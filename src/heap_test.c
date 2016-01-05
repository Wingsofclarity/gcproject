#include "heap.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdint.h>

heap* h;

void test_new(void){
  uintptr_t a = heap_get_start(h);
  uintptr_t b = heap_get_start(h);
  CU_ASSERT(a==b);
}

void test_alloc_empty(void){
  heap_alloc_format(h, "");
  uintptr_t a = heap_get_start(h);
  uintptr_t b = heap_get_start(h);
  CU_ASSERT(a!=b);
}

void test_alloc_fitting(void){
  heap_alloc_format(h,"ii");
  CU_ASSERT(false);
}

void test_alloc_large(void){
    CU_ASSERT(false);
}

void test_alloc_huge(void)
{
  heap_alloc_format(h,"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");
  CU_ASSERT(false);
}

int init_suite1()
{
  h = new_heap(1000);
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
   if ((NULL == CU_add_test(pSuite, "test of ...1", test_new)) ||
       (NULL == CU_add_test(pSuite, "test of ...1", test_alloc_empty)) ||
       (NULL == CU_add_test(pSuite, "test of ...1", test_alloc_fitting)) ||
       (NULL == CU_add_test(pSuite, "test of ...1", test_alloc_large)) ||
       (NULL == CU_add_test(pSuite, "test of ...2", test_alloc_huge)))
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
