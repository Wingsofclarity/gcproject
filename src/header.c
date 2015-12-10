#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> //isdigit() in translate_formatstring.
#include <stdbool.h> //temp in isdigit, remove.
#include <inttypes.h>

#include "header.h"

#define PTRSIZE sizeof(uintptr_t)

int int_pow (int base, int exponent){ //Used for bitwise manipulations.
  if (exponent == 0) return 1;

  int result = base;
  for (int i = 1; i < exponent; i++){
    result = result * base;
  }
  return result;
}

uintptr_t set_header_size(char* formatstring){
  uintptr_t final_header = 0;

  size_t length = strlen(formatstring);

  size_t long_size = sizeof(long);
  size_t int_size = sizeof(int);
  size_t double_size = sizeof(double);
  size_t float_size = sizeof(float);
  size_t char_size = sizeof(char);
  
  for (int i = 0; i < length; i++) {
    char temp_char = *( formatstring + ( sizeof(char) * i ) );

    switch (temp_char) {
    case 'L':
    case 'l':
      final_header += long_size;
      break;
    case 'I':
    case 'i':
      final_header += int_size;
      break;
    case 'D':
    case 'd':
      final_header += double_size;
      break;
    case 'F':
    case 'f':
      final_header += float_size;
      break;
    case 'C':
    case 'c':
      final_header += char_size;
      break;
    default:
      printf("Header contains invalid information: %c\n", temp_char);
    }
  }

  printf("final_header: %lu\n", final_header);
  
  
  return final_header;
}

uintptr_t read_formatstring(char* formatstring){
  size_t length = strlen( formatstring );
  uintptr_t formatbinary = 0;
  if ( length > ( (PTRSIZE * 8) - 3)  ){ /*Formatstring is longer than allowed
					in the bitvector */
    set_header_size( formatstring ); 
  }
  else {
    for (int i = (length - 1); i >= 0; i--) {
      if ( formatstring[i] == '*' ){ //If pointer, set bit to 1.
	formatbinary = ( formatbinary | int_pow(2, i) ); 
      }
    }
  }
  //printf("formatbinary: %"PRIuPTR"\n", formatbinary);

  formatbinary = formatbinary << 2; /* Shift two steps left so we have room
				       for the instruction bits */
  return formatbinary;
}

char* translate_formatstring (char* formatstring) {
  size_t length = strlen( formatstring );
  char* temp_char = formatstring;
  int first_digit = -1;
  int final_size = 0;

  for ( int i = 0; i < (length + 1); i++ ){
    if ( isdigit( *temp_char ) ) {
	if ( first_digit < 0 ){
	  first_digit = i;
	}
    }
    else {
      if ( first_digit > 0 ) {
	int int_size = ( i - first_digit );
	char* digit = calloc(1,  sizeof(char) * ( int_size ) );
	printf("Found number, size: %d\n", ( int_size ) );
	
	for ( int x = 0; x < int_size; x++ ) {
	  printf("Loop %d in x for-loop\n", x);
	  *(digit + ( sizeof(char) * x ) ) = *(formatstring +
					       (sizeof(char) *
						(i - (int_size - x) )
						-1 ) );
	  //Please don't read this code, it works.
	}
	final_size += atoi(digit);
	printf("Digits: %s\n", digit);
      }
      else {
	final_size += 1;
      }
    }
    printf("%c\n", *temp_char);
    temp_char = formatstring + ( i * sizeof(char) );
  }

  printf("Final_size: %d\n", final_size);

  /*Create new char* with calloc (1, final_size). And transform above to
   the acceptable format.*/

  char* final_format = calloc(1, final_size);
  
  for (int i = 0; i < ( length + 1 ); i++){
    *( final_format + (sizeof(char) * i) ) = *( formatstring +
						(sizeof(char) * i) );
  }

  

  return final_format;
}
