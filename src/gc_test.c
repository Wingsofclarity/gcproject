#include "gc.h"
#include "testing_objects.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>

heap *h;

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

void test1(void){
  void *a = h_alloc_data(h,sizeof(int));
  *(int *) a = 3;
  CU_ASSERT(*(int *) a ==3);
}


void test2(void){
  void *a = h_alloc_data(h,sizeof(int));
  *(int *) a = 3;
  ++(*(int *) a);
  CU_ASSERT(*(int *) a ==4);
}

void test3(void){
  struct pair_int a;
  a.a=2;
  a.b=3;
  void *b = h_alloc_struct(h, "ii");
  *(struct pair_int *) b=a;
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
   if ((NULL == CU_add_test(pSuite, "test of 1", test1)) ||
       (NULL == CU_add_test(pSuite, "test of 2", test2)) ||
       (NULL == CU_add_test(pSuite, "test of 3", test3)))
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
