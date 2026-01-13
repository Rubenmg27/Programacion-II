#include "pilaEnt.hpp"


// Pre: ---
// Post: p = []
void vaciar(PilaEnt &p) {
    p.numDatos = 0;
}


// Pre: p = [d_1, d_2, ..., d_K] ∧ K >= 0 ∧ K < DIM
// Post: p = [d_1, d_2, ..., d_K, nuevo]
void apilar(PilaEnt &p, const int nuevo) {
    p.datos[p.numDatos] = nuevo;
    p.numDatos++;
}


// Pre: p = [d_1, d_2, ...,d_(K-1), d_K] ∧ K > 0
 // Post: p = [d_1, d_2, ..., d_(K-1)]
void desapilar(PilaEnt &p) {
    p.numDatos--;
}


// Pre: p = [d_1, d_2, ...,d_(K-1),d_K] ∧ K > 0
 // Post: cima(p) = d_K
int cima(const PilaEnt &p) {
    return p.datos[p.numDatos-1];
}


// Pre: ---
// Post: estaVacia(p) = (p = [])
bool estaVacia(const PilaEnt &p) {
    return p.numDatos == 0;
}
// Pre: p = [d_1, d_2, ..., d_K]
// Post: estaLlena(p) = (K = DIM])
bool estaLlena(const PilaEnt &p) {
    return p.numDatos == DIM;
}