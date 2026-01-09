/**************** zrównoleglanie programu ********** 

metoda: dekompozycja funkcjonalna
   
   cwiczenie: wykorzystując dyrektywy parallel i sections
   zapisać równoległą wersję programu. Porównać czas
   wykonywania wersji sekwencyjnej i równoległej.

****************************************************/

#include <iostream>
#include<cstdlib>
#include <omp.h>

#define ILE 100000000
#define LW 1



using namespace std;


int a[ILE];



int  zlicza (int n) {
  int licznik=0;
  
  for (int i=0;i<ILE;i++) 
           if (a[i]%n==0) licznik+=1;
                   
  return licznik;
  }


int main () {

int y1,y2,y3;
srand(0);

for (int i=0;i<ILE;i++) a[i]=rand()%1000000;  
  
double t0=omp_get_wtime(),t1=t0;  


#pragma omp parallel num_threads(LW)
{

#pragma omp sections 
{
#pragma omp section
y1=zlicza(2);
#pragma omp section
y2=zlicza(3);
#pragma omp section
y3=zlicza(5);
}

}

t1=omp_get_wtime();

cout << "ilosc podzielnych przez 2 = " << y1 <<endl;
cout << "ilosc podzielnych przez 3 = " << y2 <<endl;
cout << "ilosc podzielnych przez 5 = " << y3 <<endl;
cout << "czas obliczen " << t1-t0<<endl;

return 0;
}



