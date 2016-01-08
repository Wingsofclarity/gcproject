#include "heap_traversal.h"
#include "header.h"
#include <stdio.h>

void page_trav(heap_page *p, void (*f) (uintptr_t));

/*
    Funktionen ska förmodligen byggas ungefär såhär:
    1. Ta emot pekare till ett objekt.
    2. Plocka ut headern genom att backa sizeof(uintptr_t).
    3. Om heapen är "osäker" (fråga Gustav), kolla headern om det 
       nuvarande objektet innehåller pekare.
    4. Kolla om de pekarna pekar på nuvarande heap.
    5. Om ja, skicka pekarna till funktionen som anropar denna i gc.h 
       (den är ej byggd ännu).
*/

/*
void heap_trav(heap *h, void (*f) (uintptr_t)){
  heap_page *pages = heap_active_pages(h);
  int num_pages = heap_num_active_pages(h);
  for (int i = 0; i<num_pages; ++i){
    puts("New page");
    page_trav(&pages[i],f);
  }
}

void page_trav(heap_page *p, void (*f) (uintptr_t)){
  uintptr_t current = heap_page_get_start(p);
  while (current<heap_page_get_free(p)){
    //printf("%i \n", current);
    f(current);
    current = current + header_size_of_object(current);
  }
}
*/
