/**************** zrównoleglanie programu ********** 

metoda: dekompozycja danych
  
   cwiczenie: wykorzystując dyrektywy parallel i for
   zapisać równoległą wersję programu. Porównać czas
   wykonywania wersji sekwencyjnej i równoległej.

****************************************************/

#include <iostream>
#include <cstdlib>
#include <omp.h>

#define ILE 100000000
#define LW 1

using namespace std;

int a[ILE];

int main () {

int i;


srand(0);

for (i=0; i<ILE;i++) a[i] = i+1;//rand()%10;

/* 
cout <<"wartosci w tablicy:"<<endl;
for (i=0; i<ILE;i++) cout <<a[i]<<" ";
cout <<endl;
*/

double t0=omp_get_wtime(),t1=t0;
 
double suma=0;

#pragma omp parallel num_threads(LW)
{
double s=0;
int i;

#pragma omp for 
for (i=0;i<ILE;i++) s = s + a[i];

#pragma omp atomic
suma=suma+s;


}


t1 = omp_get_wtime();          

cout << "suma = " << suma << " czas obliczen "<<t1-t0<<endl;
return 0;
}





