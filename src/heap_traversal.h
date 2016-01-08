#ifndef HEAP_TRAV_H
#define HEAP_TRAV_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> //for uintptr_t
#include "heap.h"

void heap_trav(heap *h, void (*f) (uintptr_t));

#endif
