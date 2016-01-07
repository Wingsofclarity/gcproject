#include "gc.h"
#include "heap.h"

heap *h_init(size_t bytes, bool unsafe_stack, float gc_threshold){
  return new_heap(bytes);
}

void h_delete(heap *h){
  heap_free(h);
}

void *h_alloc_struct(heap *h, char *layout){
  return (void *) heap_alloc_format(h,layout, true);
}

void *h_alloc_union(heap *h, size_t bytes, s_trace_f f){
  return NULL;
}

void *h_alloc_data(heap *h, size_t bytes){
  return (void *) heap_alloc(h,bytes, true);
}

size_t h_gc(heap *h){
  return 0;
}

size_t h_avail(heap *h){
  return heap_free_memory(h);
}

size_t h_used(heap *h){
  return 0;
}
