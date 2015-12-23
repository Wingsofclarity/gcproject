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

size_t char_to_size(char temp_char){

  switch (temp_char) {
    case 'L':
    case 'l':
      return sizeof(long);
      break;
    case 'I':
    case 'i':
      return sizeof(int);
      break;
    case 'D':
    case 'd':
      return sizeof(double);
      break;
    case 'F':
    case 'f':
      return sizeof(float);
      break;
    case 'C':
    case 'c':
      return sizeof(char);
      break;
    default:
      printf("Header contains invalid information: %c\n", temp_char);
      return 0;
  }
  return 0;
}

uintptr_t set_header_size(char* formatstring){
  uintptr_t final_header = 0;

  size_t length = strlen(formatstring);
  
  for (int i = 0; i < length; i++) {
    char temp_char = *( formatstring + ( sizeof(char) * i ) );

    final_header += char_to_size(temp_char);
  }

  final_header = final_header << 2;
  
  return final_header;
}

uintptr_t read_formatstring(char* formatstring){
  size_t length = strlen( formatstring );
  uintptr_t formatbinary = 0;

  if ( length > ( (PTRSIZE * 8) - 3)  ){ /*Formatstring is longer than 
					   allowed in the bitvector */
    formatbinary = set_header_size( formatstring ); 
  }
  else {
    for (int i = (length - 1); i >= 0; i--) {
      if ( formatstring[i] == '*' ){ //If pointer, set bit to 1.
	formatbinary = ( formatbinary | int_pow(2, i) ); 
      }
    }
  }
  //printf("formatbinary: %"PRIuPTR"\n", formatbinary);
  /*
    Formatbinary flips the formatstring, so that the first character
    is the least significant bit in the formatstring. 
   */
  
  formatbinary = formatbinary << 2; /* Shift two steps left so we have 
				       room for the instruction bits */
  return formatbinary;
}

size_t size_of_object(uintptr_t header) {
  if ((header % 4) == 3) {
    
  }
  else if ((header % 4) == 2){
    
  }
  else if ((header % 4) == 1) {
    return (size_t)0;
    // Not sure how to represent "This has been moved"
  }
  else {
    char* formatstring = (char*)header;
    size_t final_size = size_of_formatstring(formatstring);
    return final_size;
  }
  return (size_t)2;
}

size_t size_of_formatstring(char* formatstring){
  size_t length = strlen( formatstring );
  char tempchar = '\0';
  size_t result = 0;
  
  for (int i = 0; i < length; i++){
    tempchar = formatstring[i];
    if (tempchar != '\0') {
      size_t tempsize = char_to_size(tempchar);
      if (tempsize != 0) {
	result += tempsize;
      }
      else {
	printf("CRITICAL ERROR, invalid formatstring");
	return 0;
      }
    }
  }
  
  return result;
}

char* translate_formatstring (char* formatstring) {
  size_t length = strlen( formatstring );
  char* temp_char = formatstring;
  int first_digit = -1;
  int final_size = 0;

  for ( int i = 1; i < (length + 1); i++ ){
    if ( isdigit( *temp_char ) ) {
	if ( first_digit < 0 ){
	  first_digit = i;
	}
    }
    else {
      if ( first_digit >= 0 ) {
	int int_size = ( i - first_digit );
	char* digit = calloc(1,  sizeof(char) * ( int_size) );
	/*I think we have a memory leak here. digit is also not being 
	  null terminated*/
	
	for ( int x = 0; x < int_size; x++ ) {
	  *(digit + ( sizeof(char) * x ) ) = *(formatstring +
					       (sizeof(char) *
						(i - (int_size - x) )
						-1 ) );
	  //Please don't read this code, it works.
	}
	
	final_size += atoi(digit);
	free(digit);
	first_digit = -1;
      }
      else {
	final_size += 1;
      }
    }
    temp_char = formatstring + ( i * sizeof(char) );
  }
  //free(temp_char);
  
  char* final_format = calloc(1, final_size + 1);
  int pos_in_final = 0;
  
  for (int i = 0; i < length; i++) {
    if ( isdigit( *( formatstring + (sizeof(char) * i) ) ) ){
	if ( first_digit < 0 ){
	  first_digit = i;
	}
    }
    else {
       if ( first_digit >= 0 ) {
	int int_size = ( i - first_digit );
	char* digit = calloc(1,  sizeof(char) * ( int_size ) );
	/*I think we have a memory leak due to digit not being null
	 terminated, but I'm not 100%.*/

	for (int x = 0; x < int_size; x++ ) {
	  
	  *(digit + ( sizeof(char) * x ) ) = *(formatstring +
					       (sizeof(char) *
						(i - (int_size - x) )
						-0 ) );
	  //Please don't read this code, it works.
	}
	int final_size = atoi(digit);
	char next_char = *(formatstring + (sizeof(char) * i)  );
	
	for (int y = 0; y < final_size; y++){
	  *(final_format + (sizeof(char) * pos_in_final++) ) = next_char;
	}
	free(digit);
	first_digit = -1;
	
       }
       else {
	 *(final_format +
	   (sizeof(char) * pos_in_final++) ) = *(formatstring +
						 (sizeof(char) * i ) );
       }
    }
  }

  //This leaks memory.
  return final_format;
}
