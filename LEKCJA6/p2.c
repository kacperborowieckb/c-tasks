/****************************** Monitory *********************



**************************************************************/



#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fstream>
#include <iostream>


using namespace std;


/************************ cwiczenie *******************************

Przy  pomocy monitora rozwiazac problem bezpiecznego 
przejazdu przez waski most. Przejazd uważamy za bezpieczny
jeżeli na moście nie będzie dwóch samochodów jadących w 
kierunku przeciwnym. Oczywiście liczba samochodów jadących 
w tym samym kerunku może być dowolna (zał. most jest bardzo długi)
Zakładamy że wątki samochod_W (numery parzyste) i 
samochod_Z (numery nieparzyste) jadą w przeciwnym 
kierunku. W programie symulacyjnym poniżej wątki wielokrotnie
mogą przejezdzać przez ten sam most.
Monitor powinie mieć metody:
wjazd_odwschodu()
wjazd_odzachodu()
które wywołuje odpowiednio samochd_W i samochod_Z.
opuszcza
które wywołuje samochod zjeździe z mostu.

Własność bezpieczeństwa: na moście nie mogą się znaleźć 
jednocześnie samochody z numerami parzystymi i nieparzystymi


*******************************************************************/




#define ilosc 100
#define maxw 10       

pthread_mutex_t z;


void wypisz(long n, const char *s) {
pthread_mutex_lock(&z);


cout << n<<" "<<s<<endl;


pthread_mutex_unlock(&z);

usleep(rand()%1000);

}


MOST most;

int sig=0,sigl=0,sigp=0;



void* samochod_W (void* k) { // funkcja watku (watek)
	 
	 long n=(long)k;
	 int ile=ilosc;
	 n=2*n;
	 
         while (ile--) {
         usleep(rand()%10000);

         most.wjazd_zprawej();

          sigp=1;

         wypisz(n,"wjezdza na most");
         
         wypisz(n,"\tjedzie po moscie");
         
         wypisz(n,"\t\tzjezdza z mostu");
         sigc=0;
         most.opuszcza();
         
         }          
                sig=sig+1;          
return 0;     
}





void* samochod_Z (void* k) { // funkcja watku (watek)
	 
	 long n=(long)k;
	 int ile=ilosc;
	 
	 n=2*n-1;
	 
         while (ile--) {

         usleep(rand()%10000);

         most.wjazd_zlewej();

         sigl=1;
         wypisz(n,"wjezdza na most");
                 
         wypisz(n,"\tjedzie po moscie");
         
         wypisz(n,"\t\tzjezdza z mostu");

         sigp=0;
         most.opuszcza();
         }          
            
         sig=sig+1;              
return 0;     
}





int main(int arg, char **argv) {

pthread_t w1[maxw],w2[maxw];


for(long i=1;i<=maxw;i++) { pthread_create(&w1[i-1],0,samochod_W,(void*)i);
                           pthread_create(&w2[i-1],0,samochod_Z,(void*)i);}



while (sig<(2*maxw)){
     
   if ((sigp+sigl)>1) {printf ("\t:kolizja\n");_exit(0);}
  }
                           
for(long i=1;i<=maxw;i++) {                         
pthread_join(w1[i-1],0);  
pthread_join(w2[i-1],0);                          
}
return 0;

}




