/* 
Zrównoleglanie programu:

Przykładowy program wykonuje sortowanie tablicy metodą zliczania.
Korzystając z dyrektyw OpenMP napisać równoległą wersję
tego programu.
Uwaga: zrównoleglić należy tylko sam algorytm sortowania

Wskazówka:
1) zastanowić się gdzie utworzyć blok równoległy
2) skorzystać z dyrektywy rozbićia pętli
3) zastanowić się które zmienne powinny byc lokalne
   dla wątków
4) postarać sie uzyskać najkrótszy czas wykonania    

 */

#include<stdio.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<omp.h>

 using namespace std;

#define N 30000
#define LW 3


double a[N],czas;

int main()
{
int i,j,k,x;
srand(time(0));
for (i=0;i<N;i++) a[i]=rand()%100;


czas=omp_get_wtime();


// algorytm sortowania tablicy



for (i=1;i<N;i++) {


    k=i;

    for (j=k+1;j<N;j++)
        if (a[k]>a[j]) k=j;
    
    
    x=a[i];
    if (x > a[k]){
    a[i]=a[k];
    a[k]=x;
    }

}

czas=omp_get_wtime()-czas;


printf("\n________________________\n"); 


for (i=1;i<N;i++)  {
//cout <<a[i]<<" ";
}

printf ("\nczas=%lf\n",czas);


printf("\n________________________\n");

return 0;
}


