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

#define LP 1
#define LQ 1
#define SIZE 2
#define ILOSC 100

int bufor[SIZE];

int creator_index = 0;
int consumer_index = 0;

sem_t sem_creator;
sem_t sem_consumer;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;

void *p(void *l)
{ // funkcja watku (watek)
      int i, x;

      for (i = 0; i < ILOSC; i++)
      {
            x = rand() % 100;

            sem_wait(&sem_creator);
            pthread_mutex_lock(&mu);

            bufor[creator_index] = x;
            creator_index = (creator_index + 1) % SIZE;

            pthread_mutex_unlock(&mu);
            sem_post(&sem_consumer);
      }

      return 0;
}

void *q(void *l)
{ // funkcja watku (watek)

      int i, x;

      for (i = 0; i < ILOSC; i++)
      {
            sem_wait(&sem_consumer);
            pthread_mutex_lock(&mu);

            x = bufor[consumer_index];
            consumer_index = (consumer_index + 1) % SIZE;
            printf("x=%d\n", x);

            pthread_mutex_unlock(&mu);
            sem_post(&sem_creator);
      }

      return 0;
}

int main()
{
      pthread_t wp[LP], wq[LQ];

      sem_init(&sem_creator, 0, SIZE);
      sem_init(&sem_consumer, 0, 0);

      int i;

      for (i = 0; i < LP; i++)
            pthread_create(&wp[i], 0, p, 0); // tworzy nowy watek
      for (i = 0; i < LQ; i++)
            pthread_create(&wq[i], 0, q, 0); // tworzy nowy watek

      for (i = 0; i < LP; i++)
            pthread_join(wp[i], 0); // czeka na zakonczenie watku 1
      for (i = 0; i < LQ; i++)
            pthread_join(wq[i], 0);

      return 0;
}
