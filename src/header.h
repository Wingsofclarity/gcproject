#ifndef HEADER_H_
#define HEADER_H_

uintptr_t set_header_size(char[]);

uintptr_t read_formatstring(char[]);

char* translate_formatstring(char*);

size_t size_of_object(uintptr_t);

#endif //HEADER_H_
