#include "gc.h"
#include "testing_objects.h"
#include "heap_traversal.h"
#include "header.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>

heap *h;

void function(uintptr_t a){
  ++(*(int *) a);
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
  h = h_init(20000, false, 0.75);
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
  h_delete(h);
  return 0;
}

void test_alloc(void){
  int *a = h_alloc_data(h,sizeof(int));
  puts("Trace!5");
  *a = 3;
  CU_ASSERT(*a==3);
}


void test_alloc_mod(void){
  int *a = h_alloc_data(h,sizeof(int));
  *a = 3;
  ++(*a);
  CU_ASSERT(*a==4);
}

void test_header(void){
  int *a = h_alloc_data(h,sizeof(int));
  a = a - sizeof(uintptr_t);
  size_t b = header_size_of_header((uintptr_t) *a);
  CU_ASSERT(b==sizeof(int));
}

void test_trav(void){
  int *a = h_alloc_data(h,sizeof(int));
  *a = 3;
  //heap_trav(h,&function);
  CU_ASSERT(*a==4);
}

void test_gc1(void){
  size_t memory_before = h_avail(h);
  int *a = h_alloc_data(h,sizeof(int));
  *a = 3;
  h_gc(h);
  size_t memory_after = h_avail(h);
  CU_ASSERT(*a ==3);
  CU_ASSERT(memory_before < memory_after);
}

void test_alloc_struct(void){
  struct pair_int a;
  a.a=2;
  a.b=3;
  struct pair_int *b = h_alloc_struct(h, "ii");
  *b=a;
  CU_ASSERT(false);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
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
   if (
       (NULL == CU_add_test(pSuite, "test of alloc", test_alloc)) ||
       (NULL == CU_add_test(pSuite, "test of alloc mod", test_alloc_mod)) ||
       (NULL == CU_add_test(pSuite, "test of header", test_header)) ||
       (NULL == CU_add_test(pSuite, "test of trav", test_trav)) ||
       (NULL == CU_add_test(pSuite, "test of gc1", test_gc1)) ||
       (NULL == CU_add_test(pSuite, "test of alloc struct", test_alloc_struct)) ||
       false)
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
