#include "heap.h"
#include "heap_traversal.h"


/*Beginning to traverse heap*/
void traverse_heap(heap *h, uintptr_t pointer){
  /*
    Du ska inte gå igenom hela heapen. Den här funktionen ska ta emot
    en void pekare till ett objekt på heapen och sen kolla igenom det
    objektet för att lista ut om det finns en pekare eller inte i det.

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
    
  uintptr_t start = heap_get_start(h);
  uintptr_t end = heap_get_free(h);

  printf("\n-----Traverse------\n");
  while(start < end) 
      {
	
        //f(start);
	start = start + 8;   // TODO: Ändra 8:an till sizen av actuellt objekt! /Peter
      }
}
