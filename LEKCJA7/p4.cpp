/****************************************************   
   cwiczenie: wykorzystując dyrektywy parallel i for
   oraz klauzulę reduction zapisać równoległą wersję programu. 
   Porównać czas wykonywania wersji sekwencyjnej i równoległej.

****************************************************/

#include <iostream>
#include <cstdlib>
#include <omp.h>

#define ILE 100000000
#define LW 2

using namespace std;

int a[ILE];

int main () {

int i;


srand(0);

for (i=0; i<ILE;i++) a[i] = rand()%10;

/* 
cout <<"wartosci w tablicy:"<<endl;
for (i=0; i<ILE;i++) cout <<a[i]<<" ";
cout <<endl;
*/

double t0=omp_get_wtime(),t1=t0;
 
double suma=0;

#pragma omp parallel for num_threads(LW) reduction(+:suma)
for (i=0;i<ILE;i++) suma = suma + a[i];


t1 = omp_get_wtime();          

cout << "suma = " << suma << " czas obliczen "<<t1-t0<<endl;
return 0;
}





