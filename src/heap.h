#ifndef HEAP_H
#define HEAP_H

typedef struct heap_t heap;
heap *new_heap();
void heap_alloc_int(heap*, int);
void heap_alloc_format(heap*, char *);

#endif
