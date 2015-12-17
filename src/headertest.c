#include <stdint.h> // for uintptr_t
#include <stdbool.h> // for booleans.
#include <stdio.h> //for error output.

#include "header.h"

#define TESTLENGTH 10

bool testFormatstring (int argc, char* argv[]){
  char test[] = "i*";
  test[0] = '0';
  char* testPointer = test;
  printf("after test: %s\n", test);
  for (int i = 0; i < TESTLENGTH; i++) {
    test[0] = (i + '0');
    printf("%d: %d\n", i, read_formatstring(translate_formatstring(testPointer)));
    if ( i == 0 ) {
      //CASSERT( i == read_formatstring(translate_formatstring(testPointer)));
      if ( i == read_formatstring(translate_formatstring(testPointer))) {
	return true;
      }
      else return false;
    }
    else {
      return ( int_pow(2, i) == read_formatstring(translate_formatstring(testPointer)));
	
    }
  }
  return false;
}
