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





int pierwsza (long n){

int i,s;
s=1;
while (s*s <= n) s++;

for (i=2;i<s;i++)
    if (n%i==0) return 0;
return 1;
}


#define LWAT 1
#define SIZE 100000

int ile=0,ind=-1;

long A[SIZE];


void* p (void* l) { // funkcja watku (watek)

while (ind < SIZE-1){

ind =ind+1;


if (pierwsza(A[ind])) {
ile++;
}

}
return 0;     
}






int main () {
	pthread_t w[LWAT];

  int i;
  srandom(1);

  for (i=0;i<SIZE;i++) A[i]=random();
  
  for (i=0;i<LWAT;i++)		
     pthread_create(&w[i], 0, p,0); // tworzy nowy watek 		
  
  
  for (i=0;i<LWAT;i++)
      pthread_join(w[i],0); 	// czeka na zakonczenie watku 1
      
  
  printf ("liczb pierwszych %d\n",ile);
  
  
return 0;
}
