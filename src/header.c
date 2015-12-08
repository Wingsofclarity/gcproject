#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "header.h"

/*#define INTSIZE sizeof(int)*/
  #define PTRSIZE sizeof(uintptr_t)

int int_pow (int base, int exponent){
  if (exponent == 0) return 1;

  int result = base;
  for (int i = 1; i < exponent; i++){
    result = result * base;
  }
  return result;
}

uintptr_t set_header_size(char formatstring[]){
  return 0;
}

uintptr_t read_formatstring(char formatstring[]){
  size_t len = strlen( formatstring );
  uintptr_t formatbinary = 0;
  if ( len > ( (PTRSIZE * 8) - 3)  ){
    set_header_size( formatstring );
  }
  else {
    printf("\n");
    for (int i = (len - 1); i >= 0; i--) {
      //printf("Character %d: %c\n", i, formatstring[i]);
      if ( formatstring[i] == '*' ){ //If pointer, set bit to 1.
	formatbinary = ( formatbinary | int_pow(2, i) ); 
      }
      // Else keep as 0 because databit should be 0;
    }
  }
  printf("formatbinary: %"PRIuPTR"\n", formatbinary);
  formatbinary = formatbinary << 2; /* Shift two steps left so we have room
				       for the instruction bits */
  return formatbinary;
}
