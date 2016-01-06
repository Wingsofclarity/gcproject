#ifndef HEAP_C
#define HEAP_C


#include "heap.h"
#include "header.h"
#include <stdio.h> //for debugging
#include <string.h>
#define PAGE_SIZE 2048

/*
struct heap_page_t{
  uintptr_t start;
  uintptr_t free;
  uintptr_t end;
  bool active;
  bool safe;
};

struct heap_t{
  heap_page* pages;
  int num_pages;
};
*/

bool has_space(heap_page*, size_t);
heap_page * new_heap_page();
heap_page *heap_active_free_page(heap *, size_t);
heap_page *heap_passive_page(heap*);
void heap_switch(heap *);
void heap_page_free(heap_page*);
int heap_num_active_pages(heap*);
size_t heap_free_memory(heap *h);
size_t heap_page_free_memory(heap_page *p);

heap *new_heap(size_t size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->num_pages = size/PAGE_SIZE;
  h->pages = malloc(h->num_pages*(sizeof(heap_page)+PAGE_SIZE));
  //h->pages=heap_page[h->num_pages];
  for (int i = 0; i<h->num_pages; i++){
    h->pages[i]=*new_heap_page();
  }
  h->pages[0].active=false;
  return h;
}

heap_page *new_heap_page(){
  heap_page* p = malloc(sizeof(heap_page)+PAGE_SIZE);
  p->start = (uintptr_t) (p+sizeof(heap_page));
  p->free = p->start;
  p->end = (uintptr_t) (p->start+PAGE_SIZE);
  p->active = true;
  p->safe=true;
  return p;
}

uintptr_t *heap_alloc_format(heap* h, char *formatstring, bool safe){
  if (strcmp(formatstring,"")==0){
    return NULL;
  }
  
  uintptr_t a = set_header_size(formatstring);
  size_t size = size_of_object(a);
  //size_t size=2; //CHEAT!
  return heap_alloc(h, size, safe);
}

uintptr_t *heap_alloc(heap* h, size_t size, bool safe){
  if (size>PAGE_SIZE){
    return NULL;
  }
  
  heap_page* p = heap_active_free_page(h, size);
  
  if (p==NULL){
    return NULL;
  }
  
  uintptr_t r = p->free;
  p->free = p->free+size;

  if (!safe){
    p->active=false;
  }
  return &r;
}

heap_page *heap_active_free_page(heap *h, size_t size){
  for (int i = 0; i<h->num_pages; i++){
    /*printf("%d && %d \n", has_space(&h->pages[i],size),
	   h->pages[i].active);*/
    if (has_space(&h->pages[i],size) &&
	h->pages[i].active){
      return &h->pages[i];
    }
  }
  return NULL;
}

heap_page *heap_passive_page(heap *h){
  for (int i = 0; i<h->num_pages; i++){
      if (!(h->pages[i].active)){
      return &h->pages[i];
    }
  }
  return NULL;
}

bool has_space(heap_page* p, size_t size){
  return (p->free+size<=p->end);
}

uintptr_t heap_get_start(heap* h){
  return 0;
}

uintptr_t heap_get_free(heap* h){
  return 0;
}

void heap_free(heap *h){
  free(h);  
}

void heap_page_free(heap_page *p){
  //TODO: Is nessary?
}

int heap_num_active_pages(heap* h){
  int num = 0;
  for (int i = 0; i<h->num_pages; ++i){
    if (h->pages[i].active){
      ++num;
    }
  }
  return num;
}

size_t heap_free_memory(heap *h){
  size_t a = 0;
  for (int i = 0; i<h->num_pages; ++i){
    a=a+heap_page_free_memory(&h->pages[i]);
  }
  return a;
}

size_t heap_page_free_memory(heap_page *p){
  return (size_t) p->end-p->free;
}

#endif //HEAP_C
