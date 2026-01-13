#include <iostream>
#include <iomanip>
#include "ordenar.hpp"
#include <ctime>
using namespace std;

int generador ( const int a , const int b){
    return a + rand()%(b-a+1);
}

int main(int numArg, char* args[]) {
    int num = atoi (args[1]);
    int a = atoi (args[2]);
    int b = atoi (args[3]);
    int v[num];
    time_t semilla = time ( nullptr );
    srand ( semilla );
    for(int i=0; i<num;i++){
        v[i]=generador(a,b);
    }
    cout<< "Datos a ordenar:"<<endl;
    for(int i=0; i<20;i++){
        cout<<setw(8)<<v[i];
        if((i+1)%10==0){
            cout<<endl;
        }
    }
    cout<<endl;
    for(int i=(num-20); i<num;i++){
        cout<<setw(8)<<v[i];
        if((i+1)%10==0){
            cout<<endl;
        }
    }
    cout<< "ordenando "<<num<< " datos enteros...."<<endl;
    cout<<endl;
    time_t t1 = time ( nullptr );
    ordenar(v,num);
    cout<< "Datos a ordenados:"<<endl;
    for(int i=0; i<20;i++){
        cout<<setw(8)<<v[i];
        if((i+1)%10==0){
            cout<<endl;
        }
    }
    cout<<endl;
    for(int i=(num-20); i<num;i++){
        cout<<setw(8)<<v[i];
        if((i+1)%10==0){
            cout<<endl;
        }
    }
    time_t t2 = time ( nullptr );
    int segundos = int (t2 - t1 );
    cout<<"Tiempo de CPU para ordenar "<< num <<" enteros : "<< segundos <<" segundos"<<endl;

}