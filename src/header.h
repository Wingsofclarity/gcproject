#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>
#include <stdlib.h>

uintptr_t set_header_size(char*);

uintptr_t read_formatstring(char*);

char* translate_formatstring(char*);

uintptr_t new_header(char*);

uintptr_t new_header_format(char *);

uintptr_t new_header_bitlayout(size_t);

size_t header_size_of_header(const uintptr_t);

size_t header_size_of_object(const uintptr_t);

size_t size_of_formatstring(char*);

uintptr_t new_header_bitlayout(size_t);

int int_pow(int, int);

#endif //HEADER_H_
