#include <iostream>
#include <algorithm>    // std::max y std::min
#include <ctime>
#include "maxsolape.hpp"

using namespace std;

// Pre: iniA <= finA AND iniB <= finB 
// Post: solape(iniA, finA, iniB, finB) = S AND 
//	 min{finA, finB} - max{iniA, iniB} > 0 -->
//	 S = min{finA, finB} - max{iniA, iniB} AND
//       min{finA, finB} - max{iniA, iniB} <= 0 -->
//	 S = 0
double solape(const double iniA, const double finA, const double iniB, const double finB){
	return min(finA, finB) - max(iniA, iniB);
}
// sobrecarga función solape (uso con intervalos)
// Pre: a.ini <= a.fin AND a.ini <= a.fin 
// Post: solape(a, b) = S AND 
//	 min{a.fin, b.fin} - max{a.ini, b.ini} > 0 -->
//	 S = min{a.fin, b.fin} - max{a.ini, b.ini} AND
//       min{a.fin, b.fin} - max{a.ini, b.ini} <= 0 -->
//	 S = 0
double solape(const tpInter a, const tpInter b){
	return min(a.fin, b.fin) - max(a.ini, b.ini);
}

// Cada fila de inters representa un intervalo. La primera columna
// es el inicio del intervalo, y la segunda el final. Por ejemplo:
//    double inters[N][2] = {
//        {1.5, 8.0},
//        {0.0, 4.5},
//        {2.0, 4.0},
//        {1.0, 6.0},
//        {3.5, 7.0}
//    };
// tiene cinco intervalos, el primero empieza en 8.0 y termina en 9.0.
// maxSolFBruta devuelve un registro tpSolape en el que el campo solape
// es el maximo solape entre parejas de los n primeros intervalos de inters,
// y los campos interA e interB son los indices de dichos intervalos.
// Para la matriz inters de ejemplo, el resultado es solape=4.5, interA=0,
// interB=3
// (los valores de interA e interB pueden estar intercambiados, es decir,
// el resultado para el ejemplo anterior también puede ser solape=4.5,
// interA=3, interB=0).
tpSolape maxSolFBruta(double inters[N][2], int n){
	int indMaxA = 0;
	int indMaxB = 0;
	double solapeMax = 0;
	for (int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++) {	
			double solapeAB = solape(inters[i][0], inters[i][1], inters[j][0], inters[j][1]);
			if(solapeAB > solapeMax){
				solapeMax = solapeAB;
				indMaxA = i;
				indMaxB = j;
			}
		}
	}
	tpSolape maxSolapeFB = {indMaxA, indMaxB, solapeMax};
	return maxSolapeFB;
}

// Crea un vector de tpInter con los n primeros intervalos de inters.
// Por ejemplo para la matrix inters de la funcion anterior y n=5, los
// valores de indinters seran:
// [{ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void crearvind(double inters[N][2], tpInter indinters[N], int n){
	for(int i = 0; i < n; i++){
		indinters[i].ind = i;
		indinters[i].ini = inters[i][0];
		indinters[i].fin = inters[i][1];
	}
}

//Pre: a = X AND b = Y
//Post: a = Y AND b = X
void intercambiar(tpInter &a, tpInter &b) {
	tpInter aux = a;
	a = b;
	b = aux;	
}

//Pre: p >= 0 AND f < #indinters 
//		AND FA alpha [p, medio - 1]. indinters[alpha].ini <= indinters[alpha + 1].ini
//		AND FA alpha [medio + 1, f - 1]. indinters[alpha].ini <= indinters[alpha + 1].ini
//Post: FA alpha [0, n-2]. indinters[alpha].ini <= indinters[alpha + 1].ini
void mergeIndInters(tpInter indinters[N], int p, int med, int f){
	int i = p;			//primera parte subvector
	int j = med + 1;	//segunda parte subvector
	int k = p;			//recorre vector auxiliar
	tpInter aux[N];
	while(i <= med && j <= f){
		//guardar datos ordenados
		if(indinters[i].ini < indinters[j].ini){
			aux[k] = indinters[i];
			i++;
		}
		else {	//indinters[i] >= indinters[j]
			aux[k] = indinters[j];
			j++;
		}
		k++;
	}
	//i > med -> guardar resto subvector 2
	if (i > med){
		for(int jp = j; jp <= f; jp++){
			aux[k] = indinters[jp];
			k++;
		}
	}
	else { // i >= med -> j > f -> guardar resto subvector 1
		for(int ip = i; ip <= med; ip++){
			aux[k] = indinters[ip];
			k++;
		}
	}
	for (int t = p; t <= f; t++){
		indinters[t] = aux[t];
	}
}

// Ordena con el algoritmo mergesort los intervalos de indinters
// comprendidos entre p y f de acuerdo al valor de inicio de los intervalos.
// Por ejemplo, para el vector de la funcion anterior, p=0 y f=4, el vector
// ordenado sera:
// [{ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void mergesortIndInters(tpInter indinters[N], int p, int f){
	if(p < f) {
		int medio = (p + f) / 2;
		mergesortIndInters(indinters, p, medio);	//ordena la primera mitad del subvector
		mergesortIndInters(indinters, medio + 1, f);	//ordena la segunda mitad del subvector
		mergeIndInters(indinters, p, medio, f);
	}
	
}
//busca el intervalo de mayor solape con i en v en el intervalo [p, f]
//i < p
tpSolape buscarMaxSolInt(tpInter v[N], int d, int p, int f){
	double maxSol = 0;
	int iMax = p;
	for(int i = p; i <= f; i++) {
		double s = solape(v[d], v[i]);
		if(s > maxSol){
			iMax = v[i].ind;
			maxSol = s;
		}
	}
	return {v[d].ind, iMax, maxSol};
}

//devuelve el solape I tal que I.solape = MAX{a.solape, b.solape}
tpSolape maxSol(tpSolape a, tpSolape b,tpSolape c){
	if(a.solape>b.solape){
		if(a.solape>c.solape){
			return a;
		}
		else{
			return c;
		}
	}
	else if(b.solape>c.solape){
		return b;
	}
	else{
		return c;
	}
}

// Dado un vector indinters, utiliza la tecnica de Divide y Venceras para
// devolver el maximo solape entre parejas de intervalos comprendidos
// entre p y f. Por ejemplo, para el vector del procedimiento anterior,
// el resultado es solape=4.5, interA=0, interB=3
tpSolape maxSolDyV(tpInter indinters[N], int p, int f){
	if(p == f - 1) {
		tpSolape sol;
		sol.interA=p;
		sol.interB=f;
		sol.solape= solape(indinters[p], indinters[f]);
		return sol;
	}
	else if (p < f) { //p < f - 1
		int m = (p + f) / 2;
		int d = p;
		double maxF = 0;
		for(int i = p; i <= m; i++) {
			if(indinters[i].fin > maxF){
				d = i;
				maxF = indinters[i].fin;
			}
		}
		tpSolape s1 = maxSolDyV(indinters, p, m);
		tpSolape s2 = maxSolDyV(indinters, m + 1, f);
		tpSolape s3 = buscarMaxSolInt(indinters, d, m + 1, f);
		return maxSol(s1,s2,s3);
	} 
	else {

		return {0, 0, 0.0};
	}

}


