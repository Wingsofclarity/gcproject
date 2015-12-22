#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include <stdio.h>  // for printf
#include <stdint.h> // for uintptr_t
#include <stdlib.h> // for free()

#include "header.h"
/* Test Suite setup and cleanup functions: */

#define TESTLOOPS 10

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

void test_int_pow(void)
{ for(int i = 0; i < TESTLOOPS; i++){
    int x = 1;
    for (int a = i; a > 0; a--){
      x = x * 2;
    }
    CU_ASSERT_EQUAL(int_pow(2,i), x);
  }
}

void test_set_header_size(void) {
  char* testD = "ddd";
  uintptr_t result = set_header_size(testD);
  uintptr_t desiredResult = (3 * sizeof(double)) << 2;
  CU_ASSERT_EQUAL(result, desiredResult);
  free(testD);
  
  char* testI = "iiii";
  uintptr_t resultI = set_header_size(testI);
  uintptr_t desiredResultI = (4 * sizeof(int)) << 2;
  CU_ASSERT_EQUAL(resultI, desiredResultI);
  free(testI);
  
  char* testF = "fffff";
  uintptr_t resultF = set_header_size(testF);
  uintptr_t desiredResultF = (5 * sizeof(float)) << 2;
  CU_ASSERT_EQUAL(resultF, desiredResultF);
  free(testF);
  
  char* testC = "ccccccc";
  uintptr_t resultC = set_header_size(testC);
  uintptr_t desiredResultC = (7 * sizeof(char)) << 2;
  CU_ASSERT_EQUAL(resultC, desiredResultC);
  free(testC);

  char* testR = "ffiicdddddfififififfffffffffff";
  uintptr_t resultR = set_header_size(testR);
  uintptr_t desiredResultR = (18*sizeof(float) + 6*sizeof(int) +
			      1*sizeof(char) + 5*sizeof(double)) << 2;
  CU_ASSERT_EQUAL(resultR, desiredResultR);
  free(testR);

}

void test_read_formatstring(void) {
  char* test1 = "***ddd";
  uintptr_t result1 = read_formatstring(test1);
  uintptr_t desiredResult1 = (7) << 2;
  CU_ASSERT_EQUAL(result1, desiredResult1);
}

void max_test_3(void) {

}

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "test_int_pow", test_int_pow) ) ||
        (NULL == CU_add_test(pSuite, "test_set_header_size"
			     , test_set_header_size) ) ||
        (NULL == CU_add_test(pSuite, "test_read_formatstring",
			     test_read_formatstring) )
      ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
   /*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
   */
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
#include "header.h"
