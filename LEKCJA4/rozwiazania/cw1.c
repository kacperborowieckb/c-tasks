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

#define LP   34
#define LQ   51
#define SIZE  20
#define ILOSC 1000000
int bufor[SIZE];
int ilosc=0,iz=0,io=0;

sem_t pelny,pusty;
pthread_mutex_t zamekp,zamekq;

void* p (void* l) { // funkcja watku (watek)
      int x;

      while (ilosc <= ILOSC) {

      x=rand()%100+1;
      sem_wait(&pusty);
      
        pthread_mutex_lock(&zamekp);
        
        if (ilosc< ILOSC) {  //zapis danych do bufora
        bufor[iz]=x;
        iz=(iz+1)%SIZE; 
        }

        if (ilosc==ILOSC) bufor[iz]=-1;  // zapis znak konca danych do bufora

        ilosc=ilosc+1;         
        pthread_mutex_unlock(&zamekp);

        sem_post(&pelny);
     
      }

      sem_post(&pusty); // po zapisie wszystkich danych sygnalizuje że bufor w końcu będzie pusty
      

return 0;     
}


void* q (void* l) { // funkcja watku (watek)
     
      int x,i=0;

      while (x!=-1) {

      sem_wait(&pelny);
      
        pthread_mutex_lock(&zamekq);
            x=bufor[io];                    // odczyt danych
            if (x!=-1) io=(io+1)%SIZE;     //  jeżeli nie jest to znak końca to ustaw pozycje do kolejnego odczytu
            i++;        
        pthread_mutex_unlock(&zamekq);

       sem_post(&pusty);
       printf("%d \n",x);
      }
      
      printf("odczytal %d\n",i-1);
       
      sem_post(&pelny);                 // sygnalizuje znak końca danych w buforze

      

return 0;     
}



int main () {
	pthread_t wp[LP],wq[LQ];
	
   int i;

  sem_init(&pelny,0,0);
  sem_init(&pusty,0,SIZE);

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
