/*
#------------------------------------------------------------------------------
# File:   betris.cpp
# Author: Martín González, Rubén   841886
#	      López Torralba, Alejandro   845154
# Date:   mayo 2022
# Coms:   betris para el trabajo de Programación II
#------------------------------------------------------------------------------
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "betris.hpp"

using namespace std;

// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero){
    for(int i=0;i<tablero.nfils;i++){
        for(int j=0;j<tablero.ncols;j++){
            tablero.matriz[i][j]=-1;            //todos los elementos a -1 para vaciarlo
        }
    }
}

// Pre: vEntrada contiene los números de las piezas que entran y tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero &tablero, const int vEntrada[MAXENTRADA]){
    string aux;
    for(int m=0;m<=tablero.nfils;m++){
        cout<<"#";
    }
    cout<<endl;
    for(int i=0;i<tablero.nfils;i++){
        cout<<"|";
        for(int j=0;j<tablero.ncols;j++){
            if(tablero.matriz[i][j]!=-1){
                aux="\033[";
                aux+=to_string(vPiezas[vEntrada[tablero.matriz[i][j]]].color);    //convertimos el numero de color de la  pieza de vEntrada a string
                aux+="m";
                cout<<aux<<" "<<"\033[0m";
            }
            else{
                cout<<"\033[47m"<<" "<<"\033[0m";           //coloreamos el fonde de blanco si ese hueco esta vacio(-1)
            }
        }
    cout<<"|"<<endl;
    }
    for(int m=0;m<=tablero.nfils;m++){
        cout<<"#";
    }
    cout<<endl;
}



//Pre: tablero tiene escritas las posiciones de algunas piezas y otras pueden estar vacias.
//Post: devuelve true si la pieza correspondiente puede encajar en el tablero sin solaparse con ninguna otra
//      si no cabe devuelve false. 
bool cabe(tpTablero t,const int vEntrada[MAXENTRADA],int n,int fila,int col){
    switch (vEntrada[n]){
    case 0:
        if(t.matriz[fila][col]==-1 && t.matriz[fila][col+1]==-1 && t.matriz[fila][col+2]==-1 && t.matriz[fila][col+3]==-1 ){
            return true;
        }
        else{
            return false;
        }
        break;
    
    case 1:
        if(t.matriz[fila][col]==-1 && t.matriz[fila+1][col]==-1 && t.matriz[fila+2][col]==-1 && t.matriz[fila+3][col]==-1 ){
            return true;
        }
        else{
            return false;
        }
        break;
    
    case 2:
        if(t.matriz[fila][col]==-1 && t.matriz[fila][col+1]==-1 && t.matriz[fila+1][col]==-1 && t.matriz[fila+2][col]==-1 ){
            return true;
        }
        else{
            return false;
        }
        break;
    
    case 3:
        if(t.matriz[fila][col]==-1 && t.matriz[fila][col+1]==-1 && t.matriz[fila][col+2]==-1 && t.matriz[fila+1][col+2]==-1 ){
            return true;
        }
        else{
            return false;
        }
        break;

    case 4:
        if(t.matriz[fila][col]==-1 && t.matriz[fila][col+1]==-1 && t.matriz[fila+1][col]==-1 && t.matriz[fila+1][col+1]==-1 ){
            return true;
        }
        else{
            return false;
        }
        break;    
    }
}

//Pre:true
//Post:construye la pieza correspondiente en el tablero asignando su posicion en vEntrada.
void construir(tpTablero &t,const int vEntrada[MAXENTRADA],int numD,int fila,int col){
    switch (vEntrada[numD]){
    case 0:
        t.matriz[fila][col]=numD;
        t.matriz[fila][col+1]=numD;
        t.matriz[fila][col+2]=numD;
        t.matriz[fila][col+3]=numD;
        break;
    
    case 1:
        t.matriz[fila][col]=numD;
        t.matriz[fila+1][col]=numD;
        t.matriz[fila+2][col]=numD;
        t.matriz[fila+3][col]=numD;
        break;
    
    case 2:
        t.matriz[fila][col]=numD;
        t.matriz[fila][col+1]=numD;
        t.matriz[fila+1][col]=numD;
        t.matriz[fila+2][col]=numD;
        break;

    case 3:
        t.matriz[fila][col]=numD;
        t.matriz[fila][col+1]=numD;
        t.matriz[fila][col+2]=numD;
        t.matriz[fila+1][col+2]=numD;
        break;

    case 4:
        t.matriz[fila][col]=numD;
        t.matriz[fila][col+1]=numD;
        t.matriz[fila+1][col]=numD;
        t.matriz[fila+1][col+1]=numD;
        break;   
    }   
}

//Pre:tablero contiene piezas o no.
//Post: devuelve true si la pieza n cabe en la columna c y false en caso contrario.
bool verCol(tpTablero t,const int vEntrada[MAXENTRADA],int col,int n){
    int f=0;
    while(cabe(t,vEntrada,n,f,col)){            
        f++;                                //comprobamos la siguiente fila de esa columna
    }
    if(f==0){                               //si devuelve 0 es que no ha entrado en el bucle por lo que no cabe en esa columna
        return false;
    }
    else{
        return true;
    }
}

//Pre: la columna c tiene sitio para la pieza n.
//Post: devuelve la fila en la que podemos colocar la pieza n en la columna c.
int verFil(tpTablero tablero,const int vEntrada[MAXENTRADA],int c,int n){
    int f=0;
    while(cabe(tablero,vEntrada,n,f,c)){
        f++;                                //comprueba si cabe en la siguiente fila
    }
    return f-1;                             //devuelve f-1 ya que en la fila f es la primera fila en la que no cabe
}

//Pre:tablero tiene contenida la pieza n.
//Post: borra la pieza n del tablero.
void borrarPieza(tpTablero &t, const int vEntrada[MAXENTRADA],int fila,int col,int n){
    switch (vEntrada[n]){
    case 0:
        t.matriz[fila][col]=-1;
        t.matriz[fila][col+1]=-1;
        t.matriz[fila][col+2]=-1;
        t.matriz[fila][col+3]=-1;
        break;
    
    case 1:
        t.matriz[fila][col]=-1;
        t.matriz[fila+1][col]=-1;
        t.matriz[fila+2][col]=-1;
        t.matriz[fila+3][col]=-1;
        break;
    
    case 2:
        t.matriz[fila][col]=-1;
        t.matriz[fila][col+1]=-1;
        t.matriz[fila+1][col]=-1;
        t.matriz[fila+2][col]=-1;
        break;

    case 3:
        t.matriz[fila][col]=-1;
        t.matriz[fila][col+1]=-1;
        t.matriz[fila][col+2]=-1;
        t.matriz[fila+1][col+2]=-1;
        break;

    case 4:
        t.matriz[fila][col]=-1;
        t.matriz[fila][col+1]=-1;
        t.matriz[fila+1][col]=-1;
        t.matriz[fila+1][col+1]=-1;
        break;   
    }   
}

//Pre:tablero tiene la pieza n colocada en la columna c. 
//Post:devuelve la fila en la que esta colocada en la columna c.
int buscaPieza(tpTablero t,const int vEntrada[MAXENTRADA],int c,int n){
    for(int f=0;f<t.nfils;f++){
        if(t.matriz[f][c]==n)       //busca la fila en la que se encuentra la pieza de vEntrada
        return f;
    }
}


//Pre: tablero tiene algunas piezas contenidas.
//Post: devuelve true si se han completado objetivo filas y false en el caso contrario.
bool objetivoConseguido(tpTablero tablero,int objetivo){
    for(int f=0;f<tablero.nfils;f++){
        int vacia=0;
        for(int c=0;c<tablero.ncols;c++){
            if (tablero.matriz[f][c]==-1){
                vacia++;                        //aumenta vacia si hay un hueco de la fila f vacio
            } 
        }
        if (vacia==0){                         // si comprueba una fila y no aumenta vacio es que esta llena
            objetivo=objetivo-1;
        }
        if(objetivo==0){
            return true;
        }
    }
    return false;
}

//Pre:tablero tiene n piezas colocadas.
//Post: construye la pieza en la primera columna disponible.
bool construirPieza(tpTablero &t,const int vEntrada[MAXENTRADA],int &y,int n){
    while(!verCol(t,vEntrada,y,n) && y<t.ncols){            
        y++;                                        //comprueba si cabe en la columna y, si no cabe pasa a la siguiente columna
    }
    if(y==t.ncols){                                 //no cabe en el tablero
        return false;
    }
    else{                                                   
        construir(t,vEntrada,n,verFil(t,vEntrada,y,n),y);       //construye la pieza en la columna y, y en la primera fila que pueda ponerse.
        return true;
    }
}


// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo){

    mostrarTablero(tablero,vEntrada);                            //mostramos el tablero durante retardo milisegundos
    this_thread::sleep_for(chrono::milliseconds(retardo));
    system("clear");                                             //limpiamos la terminal

    if(construirPieza(tablero,vEntrada,vSalida[n],n)){           //si puede construir la pieza comprobaremos el objetivo
        if(objetivoConseguido(tablero,objetivo)){
            mostrarTablero(tablero,vEntrada);
            return n+1;
        }
        else{                                                     //si no se cumple el objetivo pasamos a la siguiente pieza
            if(vEntrada[n+1]!=-1){                                
                vSalida[n+1]=0;
                buscaSolucion(tablero,vEntrada,vSalida,objetivo,n+1,retardo);       //construimos la siguiente pieza
            }
            else{                                                   //si es la ultima pieza la borramos y buscamos otra solucion 
                mostrarTablero(tablero,vEntrada);
                this_thread::sleep_for(chrono::milliseconds(retardo));
                system("clear");
    
                borrarPieza(tablero,vEntrada,buscaPieza(tablero,vEntrada,vSalida[n],n),vSalida[n],n);
                vSalida[n]++;
                buscaSolucion(tablero,vEntrada,vSalida,objetivo,n,retardo);
            }
        }
    }
    else{                                           //si no se puede construir la pieza
        if(n==0){                                   //si no se puede contruir la primera pieza no se puede construir el objetivo
            return -1;
        }
        else{                                       //borramos la ultima pieza colocada y le buscamos otra solucion en la siguiente columna
            borrarPieza(tablero,vEntrada,buscaPieza(tablero,vEntrada,vSalida[n-1],n-1),vSalida[n-1],n-1);
            vSalida[n-1]++;
            buscaSolucion(tablero,vEntrada,vSalida,objetivo,n-1,retardo);
        }
    }
}

   

