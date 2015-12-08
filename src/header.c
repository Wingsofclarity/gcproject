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

  for (int i = 0; i < length; i++) {
    char temp_char = *( formatstring + ( sizeof(char) * i ) );

    switch (temp_char) {
    case 'L':
    case 'l':
      final_header += sizeof(long);
      break;
    case 'I':
    case 'i':
      final_header += sizeof(int);
      break;
    case 'D':
    case 'd':
      final_header += sizeof(double);
      break;
    case 'F':
    case 'f':
      final_header += sizeof(float);
      break;
    case 'C':
    case 'c':
      final_header += sizeof(char);
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

char* translate_formatstring(char* formatstring){
  size_t length = strlen( formatstring );
  int final_size = 0;
  
  for (int i = 0; i < length; i++) {
    char* temp_char = formatstring + ( sizeof(char) * i );
    
    if ( isdigit( *temp_char ) ) {
      int int_size = 1;
      
      do {
	
      } while (false);
    }
  }
}
