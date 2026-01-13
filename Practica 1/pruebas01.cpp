//*****************************************************************
// File:   pruebas01.cpp
// Author: Programación II. Universidad de Zaragoza
// Date:   febrero 2022
// Coms:   Programa de pruebas del comportamiento de las funciones
//         definidas en el módulo calculos
//         Para la práctica 1
//*****************************************************************

#include <iostream>
#include "calculos.hpp"

using namespace std;


// Pre:  <cifra> es el número de cifras de <n> cuando se escribe en base <b>
//       y <b> está comprendido entre 2 y 10
// Post: Informa si el valor devuelto al ejecutar numCifras(n, b) es igual
//       a <cifras> o no lo es
void probarNumCifras(const int n, const int b, const int cifras) {
    int r = numCifras(n, b);
    if (r == cifras) {
        cout << "Ok. numCifras(" << n << "," << b << ") = " << r << endl;
    } else {
        cout << "Mal. numCifras(" << n << "," << b << ") = " << r << "  pero debiera ser "
             << cifras << endl;
    }
}


// Prueba el comportamiento de numCifras(n,10) para los siguientes valores de n:
// 0, 1, 9, 10, 99, 100, 999, 1000, ... , 99999, 100000, 99999 y 1000000
// y prueba el comportamiento de numCifras(n,2) para los siguientes valores de n:
// 0, 1, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, ..., 4095, 4096, 8191 y 8192
void probarNumCifras() {
    // Prueba el comportamiento de numCifras(n) para los siguientes valores de n:
    // 0, 1, 9, 10, 99, 100, 999, 1000, ..., 99999, 100000, 99999 y 1000000
    probarNumCifras(0, 10, 1);
    probarNumCifras(1, 10, 1);
    int n = 10;
    int cifras = 2;
    while (n <= 1000000) {
        probarNumCifras(n - 1, 10, cifras-1);
        probarNumCifras(n, 10, cifras);
        n = 10 * n;
        cifras = cifras + 1;
    }
    cout << endl;
    // Prueba el comportamiento de numCifras(n,2) para los siguientes valores de n:
    // 0, 1, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, ..., 4095, 4096, 8191 y 8192
    probarNumCifras(0, 2, 1);
    probarNumCifras(1, 2, 1);
    n = 2;
    cifras = 2;
    while (n <= 10000) {
        probarNumCifras(n - 1, 2, cifras-1);
        probarNumCifras(n, 2, cifras);
        n = 2 * n;
        cifras = cifras + 1;
    }
    cout << endl;
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10
// Post: Informa si los valores devueltos al ejecutar cifra(n, i, b) corresponden
//       o no a la i-ésima cifra de <n>, cuando este número se escribe en base <b>
void probarCifra(const int n,const int b) {
    int mal=0;
    int aux=n;
    for(int i=1;i<=numCifras(n,b);i++){
        if (!cifra(n,i,b)==(aux%b)) {
            cout << "Mal. cifra(" << n << ","<<i<<"," << b << ") = " << cifra(n,i,b) << "  pero debiera ser "
            <<(aux%b)<< endl;
            mal++;
        } 
        aux=aux/b;
    }
    if(mal==0){
        cout << "Ok. cifra(" << n << "," << b << ")" << endl;
    }
}


// Prueba el comportamiento de cifra(n,i,b) para diferentes números naturales
// en las bases de numeración 2 y 10
void probarCifra() {
   probarCifra(7,10);
   probarCifra(356,10);
   probarCifra(567894,10);

   probarCifra(7,2);
   probarCifra(356,2);
   probarCifra(567894,2);

   probarCifra(7,8);
   probarCifra(356,8);
   probarCifra(567894,8);
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laMayor> es
//       el valor de la mayor de las cifras de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar cifraMayor(n, b) coincide con el
//       de <laMyor>, cuando <n> se escribe en base <b>
void probarCifraMayor(const int n, const int laMayor, const int b) {
    int r = cifraMayor(n, b);
    if (r == laMayor) {
        cout << "Ok. cifraMayor(" << n << "," << b << ") = " << r << endl;
    } else {
        cout << "Mal. cifraMayor(" << n << "," << b << ") = " << r << "  pero debiera ser "
             << laMayor << endl;
    }
}


// Prueba el comportamiento de cifraMayor(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarCifraMayor() {
   probarCifraMayor(7,7,10);
   probarCifraMayor(356,6,10);
   probarCifraMayor(1234567894,9,10);

   probarCifraMayor(7,1,2);
   probarCifraMayor(356,1,2);
   probarCifraMayor(1234567894,1,2);

   probarCifraMayor(7,7,8);
   probarCifraMayor(356,5,8);
   probarCifraMayor(1234567894,6,8);
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laMasSignificativa>
//       es el valor de cifra más significativa de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar cifraMasSignificativa(n, b) coincide
//       con el de <laMasSignificativa>, cuando <n> se escribe en base <b>
void probarCifraMasSignificativa(const int n, const int laMasSignificativa, const int b) {
    int r = cifraMasSignificativa(n, b);
    if (r == laMasSignificativa) {
        cout << "Ok. cifraMasSignificativa(" << n << "," << b << ") = " << r << endl;
    } else {
        cout << "Mal. cifraMasSignificativa(" << n << "," << b << ") = " << r << "  pero debiera ser "
             << laMasSignificativa << endl;
    }
}


// Prueba el comportamiento de cifraMasSignificativa(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarCifraMasSignificativa() {
   probarCifraMasSignificativa(7,7,10);
   probarCifraMasSignificativa(356,3,10);
   probarCifraMasSignificativa(1234567894,1,10);

   probarCifraMasSignificativa(7,1,2);
   probarCifraMasSignificativa(356,1,2);
   probarCifraMasSignificativa(1234567894,1,2);

   probarCifraMasSignificativa(7,7,8);
   probarCifraMasSignificativa(356,5,8);
   probarCifraMasSignificativa(1234567894,1,8);
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laSuma> es
//       el valor de las cifras de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar sumaCifras(n, b) coincide
//       con el de <laSuma>, cuando <n> se escribe en base <b>
void probarSumaCifras(const int n, const int laSuma, const int b) {
    int r = sumaCifras(n, b);
    if (r == laSuma) {
        cout << "Ok. numCifras(" << n << "," << b << ") = " << r << endl;
    } else {
        cout << "Mal. numCifras(" << n << "," << b << ") = " << r << "  pero debiera ser "
             << laSuma<< endl;
    }
}


// Prueba el comportamiento de probarSumaCifras(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarSumaCifras() {
   probarSumaCifras(7,7,10);
   probarSumaCifras(356,14,10);
   probarSumaCifras(1234567894,49,10);

   probarSumaCifras(7,3,2);
   probarSumaCifras(356,4,2);
   probarSumaCifras(1234567894,13,2);

   probarSumaCifras(7,7,8);
   probarSumaCifras(356,13,8);
   probarSumaCifras(1234567894,28,8);   
}


// Ejecuta una secuencia de pruebas de las funciones definidas
// en el módulo cálculos
int main() {
    // Pruebas del comportamiento de numCifras(n,b)
    probarNumCifras ();
    // Pruebas del comportamiento de cifra(n,i,)
    probarCifra();
    // Pruebas del comportamiento de cifraMayor(n,b)
    probarCifraMayor();
    // Pruebas del comportamiento de cifraMasSignificativa(n,b)
    probarCifraMasSignificativa();
    // Pruebas del comportamiento de sumaCifras(n,b)
    probarSumaCifras();
    // Fin del programa de pruebas
    return 0;
}
