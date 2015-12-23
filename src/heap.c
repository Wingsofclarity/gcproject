#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "heap.h"
#include "header.h"

struct heap_side_t{
  uintptr_t start;
  uintptr_t free;
  uintptr_t end;
 
};

struct heap_t{
  heap_side* a;
  heap_side* b;
  bool active;
};

heap *new_heap(int size){
  heap *h = (heap*) malloc(sizeof(heap));
  h->a=new_heap_side(size/2);
  h->b=new_heap_side(size/2);
  h->active =true;
  return h;
}

heap_side *new_heap_side(int size){
  heap_side* hs = malloc(sizeof(heap_side)+size);
  hs->start = (uintptr_t) (hs+sizeof(heap_side));
  hs->free = hs->start;
  hs->end = (uintptr_t) (hs+sizeof(heap_side)+size);

  return hs;
}

/*OBS: Changed return type from unitptr_t to void* */
void* heap_alloc_format(heap* h, char *formatstring){
  uintptr_t a = set_header_size(formatstring);
  size_t size = size_of_object(a);
  heap_side* hs = heap_active_side(h);

  // TODO: Detta ger fel nÃ¤r man vill traversera heapen /Peter
  // Vad för fel, får gärna beskriva mer än bara "fel"...
  /* 
    if (!has_space(hs,size)){
    heap_switch(h);
    hs = heap_active_side(h);
  
    if(!has_space(hs,size)){
    // Error
    }
    }
    
  */
  
  uintptr_t r = hs->free;
  hs->free = hs->free+size;
  printf("ALLOCATED: %lu\n",r);  // OBS: TemporÃ¤r printsats,tas bort sen! 
  void *p = &r;
  return p;
}

/*Beginning to traverse heap*/
void traverse_heap(heap *h, uintptr_t pointer){
  /*
    Du ska inte gå igenom hela heapen. Den här funktionen ska ta emot
    en void pekare till ett objekt på heapen och sen kolla igenom det
    objektet för att lista ut om det finns en pekare eller inte i det.

    Detta borde dessutom vara en egen modul om möjligt, det blir mycket
    kod i heap annars.

    Jag ser hellre att vi har getter funktioner för att be om gränserna
    för heapen, t.ex:

    uintptr_t get_start (heap* h){
    return h->start;
    }
    
    Funktionen ska förmodligen byggas ungefär såhär:
    1. Ta emot pekare till ett objekt.
    2. Plocka ut headern genom att backa sizeof(uintptr_t).
    3. Om heapen är "osäker" (fråga Gustav), kolla headern om det 
       nuvarande objektet innehåller pekare.
    4. Kolla om de pekarna pekar på nuvarande heap.
    5. Om ja, skicka pekarna till funktionen som anropar denna i gc.h 
       (den är ej byggd ännu).
  */
    
  heap_side* hs = heap_active_side(h);
  uintptr_t start = hs->start;
  uintptr_t end = hs->free;

  printf("\n-----Traverse------\n");
  while(start < end) 
      {
	
        //f(start);
	start = start + 8;   // TODO: Ã¤ndra 8an till sizen av actuellt objekt! /Peter
      }
}

/*Testfunction: Print out the allocated addresses */
void printHeap(uintptr_t n)
{
  printf("Pointer: %lu ", n);
  printf("\tsize:%lu \n",sizeof(n));
  
}


void heap_switch(heap *h){
  h->active = !h->active;
}

heap_side *heap_active_side(heap *h){
  if (h->active) return h->a;
  else return h->b;
}

bool has_space(heap_side* hs, int size){
  return (hs->free+size>=hs->end);
}
