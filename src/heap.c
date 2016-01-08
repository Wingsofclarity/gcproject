#ifndef HEAP_C
#define HEAP_C


#include "heap.h"
#include "header.h"
#include <stdio.h> //for debugging
#include <string.h>
#define PAGE_SIZE 2048


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


uintptr_t heap_alloc(heap*, uintptr_t, bool);
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

uintptr_t heap_alloc_format(heap* h, char *formatstring, bool safe){
  if (strcmp(formatstring,"")==0){
    return 0;
  }
  return heap_alloc(h, new_header_format(formatstring), safe);
}

uintptr_t heap_alloc_raw(heap* h, size_t size, bool safe){
  return heap_alloc(h, new_header_bitlayout(size),safe);
}

uintptr_t heap_alloc(heap* h, uintptr_t header, bool safe){


  size_t size_object = header_size_of_header(header); //header.c will manage this..

  size_t size_header = sizeof(void*);
  size_t size_joint = size_header + size_object;

  if (size_joint>PAGE_SIZE){ //Guard. If the object+header is larger than a single page.
    return 0;
  }
  
  heap_page* p = heap_active_free_page(h, size_joint);
  if (p==NULL){ //Guard. p=NULL if there are no page with enough free memory.
    return 0;
  }

  /*
    I need a line here to insert the header.
    p->free = header; //Doesn't actually insert the header...just changes the free-pointer
                        to point somehwere random

    *p->free =  header; //Doesn't work due to dereferncing a void * (or rahter a uintptr)

    */
  uintptr_t *a = (void*) p->free;
  *a = header;

  uintptr_t object_ptr = p->free+size_header; //Remembering where the object is so we can return it.
  p->free = p->free+size_joint; 


  if (!safe){ 
    p->active=false;
  }

  return object_ptr;
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

uintptr_t heap_page_get_start(heap_page* p){
  return p->start;
}

uintptr_t heap_page_get_free(heap_page* p){
  return p->free;
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

heap_page *heap_active_pages(heap *h){
  heap_page *pages = malloc(sizeof(heap_page)*heap_num_active_pages(h));
  int j = 0;
  for (int i=0; i<h->num_pages; ++i){
    if (h->pages[i].active){
      pages[j]=h->pages[i];
      ++j;
    }
  }
  return pages;
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
