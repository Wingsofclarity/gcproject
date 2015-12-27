#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>

uintptr_t set_header_size(char*);

uintptr_t read_formatstring(char*);

char* translate_formatstring(char*);

uintptr_t new_header(char*);

size_t size_of_object(uintptr_t);

size_t size_of_formatstring(char*);

int int_pow(int, int);

#endif //HEADER_H_
