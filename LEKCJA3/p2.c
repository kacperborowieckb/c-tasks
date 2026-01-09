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

#define iter 5

sem_t sem_create;
sem_t sem_consume;

void *p(void *l)
{ // funkcja watku (watek)
      int i, j = 0;

      for (i = 0; i < iter; i++)
      {

            sem_wait(&sem_create);
            j = j + 2;
            x = j;
            sem_post(&sem_consume);
      }

      return 0;
}

void *q(void *l)
{ // funkcja watku (watek)
      int i, j = -1;

      for (i = 0; i < iter; i++)
      {

            sem_wait(&sem_create);
            j = j + 2;
            x = j;
            sem_post(&sem_consume);
      }

      return 0;
}

void *r(void *l)
{ // funkcja watku (watek)

      int i;

      for (i = 0; i < 2 * iter; i++)
      {
            sem_wait(&sem_consume);
            printf("x=%d\n", x);
            sem_post(&sem_create);
      }

      return 0;
}

int main()
{
      pthread_t w1, w2, w3;

      sem_init(&sem_create, 0, 1);
      sem_init(&sem_consume, 0, 0);

      pthread_create(&w1, 0, p, 0); // tworzy nowy watek
      pthread_create(&w2, 0, q, 0); // tworzy nowy watek
      pthread_create(&w3, 0, r, 0); // tworzy nowy watek

      pthread_join(w1, 0); // czeka na zakonczenie watku 1
      pthread_join(w2, 0);
      pthread_join(w3, 0);

      return 0;
}
