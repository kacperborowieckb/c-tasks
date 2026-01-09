
/*************************************************************    
skompilować program poleceniem: g++ -fopenmp p1.cpp

    Tworzenie bloków równoległych  
    dyrektywa parallel - tworzy blok równoległy
    dyrektywa critical - tworzy blok w bloku równoległym w którym może przebywać tylko jeden wątek.
                         Dyrektywa ta działa jak mutex w programach wielowątkowych i służy do 
                         zabezpieczenia sekcji krytycznej.  

    ćwiczenie:
    1) wykonać program: objaśnić wynik
    2) zakomentować dyrektywę critical i wykonać program: objaśnić wynik
    
    zwócić uwagę:
    1) gdzie w kodzie programu znajdują się bloki równoległe
    2) ile wątków wykonuje bloki równoległe, jak wpływa na to klauzula < num_threads >
    3) jakimi wartościami są numerowane wątki
    4) dowód współbieżności wykonywania się bloku równoległego (co się dzieje po zakomentowaniu
        dyrektywy critical)


**************************************************************/


#include <iostream>
#include <omp.h>

using namespace std;

int main () {

int proc =omp_get_num_procs();

cout << "liczba procesorów "<<proc <<endl;

cout << "\t\twykonuje watek : " << omp_get_thread_num() << endl;

cout <<"tworze blok równolegly \n";

#pragma omp parallel num_threads(5)
{                               // początek bloku równoległego

#pragma omp critical 
cout << "\t\twykonuje watek : " << omp_get_thread_num() << endl;



}                              // koniec bloku równoległego       

cout <<"koniec bloku równoleglego \n";

cout << "\t\twykonuje watek : " << omp_get_thread_num() << endl;

cout <<"tworze blok równolegly \n";


#pragma omp parallel 
{                             // początek bloku równoległego


#pragma omp critical 
cout << "\t\twykonuje watek : " << omp_get_thread_num() << endl;
                

}                             // koniec bloku równoległego       


cout <<"koniec bloku równoleglego \n";

cout << "\t\twykonuje watek : " << omp_get_thread_num() << endl;


return 0;
}
