/*************  kontrola liczby watkow - semafory **************
Funkcja tworzenia watku:
  pthread_create(&w, &atw, watek,(void*)par);
  w   	- obiekt watku
  atw 	- obiekt atrybutu watku ( do ustawienia atrybutow tworzonego watku) 
  watek - funkcja ktora wykonuje sie jako nowy watek
  par   - parametr funkcji watek

Funkcja watku:
 void *fw( void *) - prototyp funkcji watku
 Funkcje watku dzialaja wspolbieznie (rownolegle) po utworzeniu 
 watku (wywolanie  pthread_create ) w ramach tego samego procesu.
 Zmienne globalne programu sa wspolne dla wszystkich watkow

**************************************************************/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define max_watkow  5

pthread_mutex_t blokada;

sem_t nowy_watek;



long utworzone=0, zakonczone=0;




void* p (void* l) { // funkcja watku (watek)
      
     long n=(long)l;

     
     usleep(rand()%100000);
   

     pthread_mutex_lock(&blokada);

     zakonczone++;  //sekcja krytyczna

     pthread_mutex_unlock(&blokada);

     sem_post(&nowy_watek);

     return 0;     
}







int main () {
	pthread_t w;
	pthread_attr_t atrybut;
	pthread_attr_init(&atrybut); //tworzy domyslny obiekt atrybutu dla watku

        pthread_attr_setdetachstate(&atrybut,PTHREAD_CREATE_DETACHED); //ustawia atrybut wątek ulotny
					

   sem_init(&nowy_watek,0,max_watkow);

	

 	while (1) {

     sem_wait(&nowy_watek); // czeka na mozliwość utworzenia nowego watku
      
	if (pthread_create(&w, &atrybut, p,0)==0)
         ++utworzone; 
         printf("liczba watkow aktywnych %ld\n", utworzone-zakonczone);
        }  
  
  
        printf("\nkoniec procesu\n");

  
  
return 0;
}
