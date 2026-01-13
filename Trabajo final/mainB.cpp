/*
#------------------------------------------------------------------------------
# File:   mainB
# Author: Martín González, Rubén   841886
#	      López Torralba, Alejandro   845154
# Date:   mayo 2022
# Coms:   Main para el trabajo de Programación II
#------------------------------------------------------------------------------
*/

#include <iostream>
#include <stdlib.h>
#include<time.h>
#include "betris.hpp"

using namespace std;


int main(int numD,char* datos[]){
    srand(time(NULL));
    int comp=0;
    int num, aux;
    tpTablero tabla;
    int objetivo,retardo;
    int entrada[MAXENTRADA],salida[MAXENTRADA];
    tabla.nfils=atoi(datos[1]);                     //convertimos los elementos char en int
    tabla.ncols=atoi(datos[2]);
    objetivo=atoi(datos[3]);
    retardo=atoi(datos[4]);
    if(retardo<=0){
        retardo=0;
    }
    for (int i=5; i < numD; i++){
        entrada[i-5]=atoi(datos[i]);
        salida[i-5]=0;
        comp++;
    }
    if(entrada[0]<0){                               //caso en que se introduzca solo un numero negativo.
        num=entrada[0]*(-1);
        for(int p=0;p<num;p++){
            entrada[p]=rand()%5;                    //generamos numeros aleatorios modulo 5 {0,1,2,3,4}.
        }
        comp=num;
        entrada[comp]=-1;
    }
    else{
        comp--;
    }
    inicializarTablero(tabla);
    int y=buscaSolucion(tabla,entrada,salida,objetivo,0,retardo);
    cout<<"Entrada(número de piezas): ";
    for(int z=0;z<comp;z++){
    cout<<entrada[z]<<" ";
    } 
    cout<<endl;
    cout<<"Número de piezas colocadas: "<<y<<endl;
    cout<<"Salida (número de columnas): ";
        for(int t=0;t<y;t++){
        cout<<salida[t]<<" ";
    }
    cout<<endl;
}