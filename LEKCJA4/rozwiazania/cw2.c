/*************  korzystanie z semaforów  ******************************

deklaracje w pliku semaphore.h


sem_t 		- typ semaforowy
sem_init(sem_t* s,0,wartość_semafora) - inicjowanie wartością początkową semafora
sem_post(sem_t* s) 	- operacja signal
sem_wait(sem_t* s)	- operacja wait



**************************************************************/


/*************  korzystanie z mutexu  ******************************


ptheread_mutex_t 		- typ mutexowy

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER - inicjowanie (mutex otwarty) (domyślna inicjalizacja)
pthread_mutex_lock(pthread_mutex* m) 	- zamknięcie mutexu
pthread_mutex_unlock(pthread_mutex* m) 	- otwarcie mutexu

uwaga: 
- operacja pthread_mutex_lock blokuje wątek gdy mutex jest zamkniety
- operacja pthread_mutex_unlock jest niezdefiniowana gdy mutex jest otwarty


**************************************************************/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define SIZE  10
#define ILOSC 100000

sem_t sr,sq,pusty;

int bufor[SIZE];


void* p (void* l) { // funkcja watku (watek)
      int i,x;

      for (i=0;i< ILOSC;i++) {
      
      x=rand();

      sem_wait(&pusty);       // czeka na możliwość zapisu danych do bufora
      bufor[i%SIZE]=x;       // zapis danych do bufora
      sem_post(&sq);        // sygnalizuje dostepnośc danych dla watku q 
 
      }

      

return 0;     
}



void* q (void* l) { // funkcja watku (watek)
      int i,x;

      for (i=0;i<ILOSC ;i++) {
      sem_wait(&sq);          // czeka na możliwość odczytu danych z bufora   
      x=bufor[i%SIZE];       // odczyt danych z bufora
      sem_post(&sr);        // sygnalizuje dostepnośc danych dla watku r 
      if (x%2==0) printf("watek q wypisal %d\n",x);
      
 
      }

      

return 0;     
}




void* r (void* l) { // funkcja watku (watek)
      int i,x;

      for (i=0;i<ILOSC ;i++) {
      sem_wait(&sr);          // czeka na możliwość odczytu danych z bufora
      x=bufor[i%SIZE];       // odczyt danych z bufora
      sem_post(&pusty);     // sygnalizuje możliwość zapisu dla watku p 
      if (x%2==1) printf("watek r  wypisal %d\n",x);
      
 
      }

      

return 0;     
}





int main () {
	pthread_t w1,w2,w3;
	
  sem_init(&sr,0,0);
  sem_init(&sq,0,0);
  sem_init(&pusty,0,SIZE);

  pthread_create(&w1, 0, p,0); // tworzy nowy watek 		
  pthread_create(&w2, 0, q,(void*)1); // tworzy nowy watek 				
  pthread_create(&w3, 0, r,(void*)2); // tworzy nowy watek
	








  pthread_join(w1,0); 	// czeka na zakonczenie watku 1
  pthread_join(w2,0);     
  pthread_join(w3,0);

  
  
return 0;
}
