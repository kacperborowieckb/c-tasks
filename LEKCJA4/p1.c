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

#define LP   1
#define LQ   1
#define SIZE  2
#define ILOSC 100
int bufor[SIZE];



void* p (void* l) { // funkcja watku (watek)
      int i,x;

      for (i=0;i<ILOSC;i++) {

      x=i+1;
     
      }

      

return 0;     
}


void* q (void* l) { // funkcja watku (watek)
     
      int i,x;

      for (i=0;i<ILOSC;i++) {
    

      printf("x=%d\n",x);
      }


return 0;     
}



int main () {
	pthread_t wp[LP],wq[LQ];
	
   int i;

  for (i=0;i<LP;i++)		
  pthread_create(&wp[i], 0, p,0); // tworzy nowy watek 		
  for (i=0;i<LQ;i++)
  pthread_create(&wq[i], 0, q,0); // tworzy nowy watek 				
	







  for (i=0;i<LP;i++)
  pthread_join(wp[i],0); 	// czeka na zakonczenie watku 1
  for (i=0;i<LQ;i++)
  pthread_join(wq[i],0);     
  

  
  
return 0;
}
