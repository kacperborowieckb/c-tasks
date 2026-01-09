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

// definicja monitora

class SEMAFOR {

    pthread_mutex_t blokada;
    pthread_cond_t niezero;
    
    int wartosc;	             // aktualna wartosc semafora
    public:
    SEMAFOR (int l=1) { 
    
    pthread_cond_init ( &niezero,NULL);
    pthread_mutex_init(&blokada,0);    
    wartosc=l;
    }
    
    friend void Wait(SEMAFOR &s) {  // zamyka semafor
     pthread_mutex_lock(&s.blokada);

         while (s.wartosc == 0) pthread_cond_wait(&s.niezero,&s.blokada);
                    
         s.wartosc=s.wartosc-1;

     pthread_mutex_unlock(&s.blokada);    
    }


    friend void Signal(SEMAFOR &s) {  //otwiera semafor
     pthread_mutex_lock(&s.blokada);

        s.wartosc=s.wartosc+1;    
        pthread_cond_signal(&s.niezero); 

     pthread_mutex_unlock(&s.blokada);                
    }
};



class SEMAFOR_SILNY {

    pthread_mutex_t blokada;
    pthread_cond_t niezero;
    
    int wartosc;	             // aktualna wartosc semafora
    int czekajace;
    public:
    SEMAFOR_SILNY (int l=1) { 
    
    pthread_cond_init ( &niezero,NULL);
    pthread_mutex_init(&blokada,0);    
    wartosc=l;
    czekajace=0;
    }
    
    friend void Wait(SEMAFOR_SILNY &s) {  // zamyka semafor
     pthread_mutex_lock(&s.blokada);

         if (s.wartosc == 0) {
               s.czekajace++;
               pthread_cond_wait(&s.niezero,&s.blokada);
               s.czekajace--;
               }
                    
         else s.wartosc=s.wartosc-1;

     pthread_mutex_unlock(&s.blokada);    
    }


    friend void Signal(SEMAFOR_SILNY &s) {  //otwiera semafor
     pthread_mutex_lock(&s.blokada);

        
        if (s.czekajace>0) pthread_cond_signal(&s.niezero); 
        else s.wartosc=s.wartosc+1;    

     pthread_mutex_unlock(&s.blokada);                
    }
};









SEMAFOR s(1);


double liczba=0;

#define maks 1000000
#define wartosc_semafora 1


void* p (void* l) { // funkcja watku (watek)
      int i=0;

     
      for (i=0;i<maks;i++) { 
    
      Wait(s);
      liczba=liczba+1;	// sekcja krytyczna
      Signal(s);
     
      }

      

return 0;     
}


void* q (void* l) { // funkcja watku (watek)
     
      int i=0;

     
      for (i=0;i<maks;i++) {
     
     Wait(s);
       liczba=liczba+1;	// sekcja krytyczna
     Signal(s);
     
      
      }

return 0;     
}



int main () {
	pthread_t w1,w2,w3;
	

	
		
  pthread_create(&w1, 0, p,0); // tworzy nowy watek 		
  pthread_create(&w2, 0, q,0); // tworzy nowy watek
  pthread_create(&w3, 0, p,0); // tworzy nowy watek 				
	

  pthread_join(w1,0); 	// czeka na zakonczenie watku 1
  pthread_join(w2,0);     
  pthread_join(w3,0);

  printf("liczba=%.0lf",liczba);  
  
  printf("\nkoniec procesu\n");

  
  
return 0;
}
