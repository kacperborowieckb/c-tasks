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

int x;

#define iter 100

sem_t odczytane,zapisane;


void* p (void* l) { // funkcja watku (watek)
      int i,j=0;

      for (i=0;i< iter;i++) {
      
      sem_wait(&odczytane);
      x=rand()%100+1;
      sem_post(&zapisane);
      }
          
      sem_wait(&odczytane);     //czeka na zapisanie znaku konca danych
      x=-1;
      sem_post(&zapisane);      //sygnalizuje zapisanie konca danych

      

return 0;     
}



void* q (void* l) { // funkcja watku (watek)
      int n=(long)l;
      int i=0,y=0;

      while(y!=-1) {
      
      sem_wait(&zapisane);
      y=x;
      
      if (y==-1) {          // reakcja na odczyt końca danych
       sem_post(&zapisane);
       continue;
      }
   
       
      if ( (y%2==1)) {
        printf("watek %d  wypisal %d\n",n,x);i++;
        sem_post(&odczytane);
      }
      else sem_post(&zapisane);
      

      }

      printf("watek %d  wypisal liczb %d \n",n,i);

return 0;     
}




void* r (void* l) { // funkcja watku (watek)
      int n=(long)l;
      int i=0,y=0;

      while(y!=-1) {
      
      sem_wait(&zapisane);
      y=x;

      if (y==-1) {          // reakcja na odczyt końca danych
       sem_post(&zapisane);
       continue;
      }


      if (y%2==0) {
        printf("watek %d  wypisal %d\n",n,x); i++;
        sem_post(&odczytane);
      }
  
      else sem_post(&zapisane);
      

      }

      printf("watek %d  wypisal liczb %d \n",n,i);

return 0;     
}




int main () {
	pthread_t w1,w2,w3;
    srand(time(0));
	
  sem_init(&zapisane,0,0);
  sem_init(&odczytane,0,1);
		
  pthread_create(&w1, 0, p,0); // tworzy nowy watek 		
  pthread_create(&w2, 0, q,(void*)1); // tworzy nowy watek 				
  pthread_create(&w3, 0, r,(void*)2); // tworzy nowy watek
	








  pthread_join(w1,0); 	// czeka na zakonczenie watku 1
  pthread_join(w2,0);     
  pthread_join(w3,0);

  
  
return 0;
}
