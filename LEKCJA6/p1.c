/*************************************************************

      Monitor dla problemu czytelnicy i pisarze
                 
                 
**************************************************************/



#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <fstream>
#include <iostream>



using namespace std;


class MONITOR_CP {
    pthread_mutex_t blokada;
    pthread_cond_t mozna_czytac,mozna_pisac;    

    int czeka_czytelnik,czeka_pisarz,czyta,pisze;
    
    public:
    
    MONITOR_CP(){
    czeka_czytelnik=czeka_pisarz=czyta=pisze=0; 
    pthread_cond_init(&mozna_pisac,NULL);
    pthread_cond_init(&mozna_czytac,NULL);    
    pthread_mutex_init(&blokada,0);                
    }
    
    
    ~MONITOR_CP () { 
    pthread_mutex_destroy(&blokada);
    pthread_cond_destroy(&mozna_pisac);
    pthread_cond_destroy(&mozna_czytac);    
    }
    
    
    
    void poczatek_czytania(); 
    void poczatek_pisania();  

    void koniec_czytania(); 
    void koniec_pisania();  

};



 void MONITOR_CP::poczatek_czytania() {
    pthread_mutex_lock(&blokada);
           
    
    if  (czeka_pisarz || pisze > 0 )  {
          czeka_czytelnik++;
          pthread_cond_wait(&mozna_czytac,&blokada);
          pthread_cond_signal(&mozna_czytac);
          czeka_czytelnik--; 
          printf("<------ czytelnik");
          }
    
   else {
        printf("<--- czytelnik");
        }
      
         czyta++;
             
         
         fflush(stdout);
   pthread_mutex_unlock(&blokada);    

    }


    void MONITOR_CP::koniec_czytania() {
    pthread_mutex_lock(&blokada);
    czyta--;
    
    if (czyta == 0 )
          pthread_cond_signal(&mozna_pisac);           
          
          printf("\nczytelnik -------------->\n");
          fflush(stdout);

    pthread_mutex_unlock(&blokada);    

    }




    void MONITOR_CP::poczatek_pisania() {
    pthread_mutex_lock(&blokada);
    
    
    if (czyta>0 || pisze >0 ) {
       czeka_pisarz++;
       pthread_cond_wait(&mozna_pisac,&blokada);
       czeka_pisarz--;
       printf("<------ pisarz"); 
       }
                   
    else {
       printf("<--- pisarz"); 
   }
    pisze=1;
           
    
    fflush(stdout);
         
    pthread_mutex_unlock(&blokada);    

    }


    void MONITOR_CP::koniec_pisania() {
    pthread_mutex_lock(&blokada);
    pisze=0;
    
    if (czeka_czytelnik > 0 )
          pthread_cond_signal(&mozna_czytac);           
    else
          pthread_cond_signal(&mozna_pisac);           
          
          printf("\npisarz -------------->\n"); 
          fflush(stdout);
    pthread_mutex_unlock(&blokada);    

    }





#define ile 1000
#define maxc 50       // liczba czytelnikow
#define maxp 20       // liczba pisarzy

int sigp=0,sigc=0,sig=0;



MONITOR_CP cp;   

pthread_mutex_t z;


void* pisarz (void* k) { // funkcja watku (watek)
         long nr=(long)k;
         int n=ile;
	 
         while (n--) {
	    cp.poczatek_pisania();

        pthread_mutex_lock(&z);
        sigp++;  
        pthread_mutex_unlock(&z);	 



         usleep(rand()%100);        //czytelnia
	

         sigp=0;
         cp.koniec_pisania();
                        
         }   
         pthread_mutex_lock(&z);  
         sig=sig+1; 
         pthread_mutex_unlock(&z);    
                 
 //        printf("pisarz konczy\n");      
return 0;     
}



void* czytelnik (void* k) { // funkcja watku (watek)
         long nr=(long)k;
         int n=ile*3;
         
        
         while (n--) {
       //  usleep(rand()%10000);
	    cp.poczatek_czytania();
         
         pthread_mutex_lock(&z);
         sigc++;
         pthread_mutex_unlock(&z);


	     usleep(rand()%300);        //czytelnia


         pthread_mutex_lock(&z);
         sigc--;
         pthread_mutex_unlock(&z);
	
        cp.koniec_czytania();  
         }          

        pthread_mutex_lock(&z);
        sig=sig+1;
        pthread_mutex_unlock(&z);
        printf("czytelnik konczy\n");  

return 0;     
}




int main(int arg, char **argv) {

pthread_t pi[maxp],cz[maxc];



for (long i=0;i<maxc;i++)
pthread_create (&cz[i],0,czytelnik,(void*)i);

for (long i=0;i<maxp;i++)
pthread_create (&pi[i],0,pisarz,(void*)i);


  while (sig<(maxp+maxc)){
     
   if (sigp>1) {printf ("\tblad:pisarz-pisarz\n"); _exit(0);}
   if (sigp*sigc>0) {printf ("\tblad:pisarz-czytelnik\n");_exit(0);}
  }


for (int i=0;i<maxc;i++)
pthread_join (cz[i],0);

for (int i=0;i<maxp;i++)
pthread_join (pi[i],0);




return 0;

}




