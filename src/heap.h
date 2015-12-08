#ifndef HEAP_H_
#define HEAP_H_

typedef struct heap_side heap_side;

typedef struct heap heap;

heap* new_heap(int);

bool write_to_heap(heap*, int, char[]);

void print_heap(heap*);

#endif //HEAP_H_
