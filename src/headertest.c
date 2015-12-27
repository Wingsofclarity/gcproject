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

  char* testR = "ffiicdddddfififififfffffffffffffffffffffffffff";
  uintptr_t resultR = set_header_size(testR);
  uintptr_t desiredResultR = (34*sizeof(float) + 6*sizeof(int) +
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

void test_size_of_formatstring(void) {
  char* testC = "ccc";
  size_t resultC = size_of_formatstring(testC);
  size_t desiredResultC = 3*sizeof(char);
  CU_ASSERT_EQUAL(resultC, desiredResultC);

  char* testI = "ii";
  size_t resultI = size_of_formatstring(testI);
  size_t desiredResultI = 2*sizeof(int);
  CU_ASSERT_EQUAL(resultI, desiredResultI);
}

void test_translate_formatstring(void) {
  char* test1 = "3*2i2d";
  char* result1 = translate_formatstring(test1);
  char* desiredResult1 = "***iidd";
  CU_ASSERT_EQUAL(*result1, *desiredResult1);

  char* test2 = "32c";
  char* result2 = translate_formatstring(test2);
  char* desiredResult2 = "cccccccccccccccccccccccccccccccc";
  CU_ASSERT_EQUAL(*result2, *desiredResult2);

  char* test3 = "32";
  char* result3 = translate_formatstring(test3);
  char* desiredResult3 = "";
  CU_ASSERT_EQUAL(*result3, *desiredResult3);
}

void test_size_of_object(void){
  //test for ( (header % 4) == 0 )
  //pointer to formatstring
  char* formatstring4 = "dddd";
  uintptr_t header4 = (uintptr_t)malloc(sizeof(uintptr_t));
  header4 = new_header(formatstring4);
  //printf("\n&formatstring4: %p\n", &formatstring4);
  //printf("header4: %d\n", header4);
  size_t result4 = size_of_object(header4);
  size_t expectedResult4 = 4*sizeof(double);
  printf("Result4: %d, expectedResult4: %d", result4, expectedResult4);
  CU_ASSERT_EQUAL(result4, expectedResult4);
  //printf("\n\n test 2\n\n");

  /*I don't know how to force them in to word allignment, therefore
    these functions will fail until I figure it out.
  */
  
  //test for ( (header % 4) == 1 )
  //Object has been moved.
  char* formatstring3 = "ddd";
  uintptr_t header3 = new_header(formatstring3);
  //printf("%d\n", header3);
  header3 += 0;
  size_t result3 = size_of_object(header3);
  size_t expectedResult3 = 0;
  CU_ASSERT_EQUAL(result3, expectedResult3);
  free(formatstring3);

  //test for ( (header % 4) == 2 )

  //test for ( (header % 4) == 3 )
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
        (NULL == CU_add_test(pSuite, "test_set_header_size",
			     test_set_header_size) ) ||
        (NULL == CU_add_test(pSuite, "test_read_formatstring",
			     test_read_formatstring) ) ||
	(NULL == CU_add_test(pSuite, "test_size_of_formatstring",
			     test_size_of_formatstring)) ||
	(NULL == CU_add_test(pSuite, "test_translate_formatstring",
			     test_translate_formatstring)) ||
	(NULL == CU_add_test(pSuite, "test_size_of_object",
			     test_size_of_object))
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
