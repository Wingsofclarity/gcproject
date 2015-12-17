#include <stdint.h> // for uintptr_t
#include <stdbool.h> // for booleans.
#include <stdio.h> //for error output.

#include "header.h"

#define TESTLENGTH 10

int main (int argc, char* argv[]){
  char* test = "i*";
  
  for (int i = 0; i < TESTLENGTH; i++) {
    *(test) = i + '0';
    printf("%d\n", read_formatstring(test));
  }
}
