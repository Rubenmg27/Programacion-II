#ifndef CALCULOS_HPP
#define CALCULOS_HPP

// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: (n = 0 -> numCifras(n,b) = 1) ∧
//       (n > 0 -> numCifras(n,b) = NC ∧  n >= b^(NC-1) ∧ n < b^NC)
int numCifras(const int n, const int b = 10){
    if(n<b){
        return 1;
    }
    else{
        return 1+numCifras(n/b,b);
    }
}


// Pre:  n >= 0 ∧ i >= 1 ∧ 2 <= b <= 10
// Post: cifra(n,b,i) = (n / b^(i-1)) % b
int cifra(const int n, const int i, const int b = 10){
    if(i==1){
        return n%b;
    }
    else{
        return cifra(n/b,i-1,b);
    }
}

// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: cifraMayor(n,b) = (Max α∊[1,∞].cifra(n,α,b))
int cifraMayor(const int n, const int b = 10){
    if(n<b){
        return n;
    }
    else{
        int aux=cifraMayor(n/b,b);
        if(aux>(n%b)){
            return aux;
        }
        else{
            n%b;
        }
    }
}


// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: cifraMasSignificativa(n) = n / b^(NC-1)
//       ∧ (n >= b^(NC-1) ∧ n < b^NC)
int cifraMasSignificativa(const int n, const int b = 10){
    if(n<b){
        return n;
    }
    else{
        return cifraMasSignificativa(n/b,b);
    }
}


// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: sumaCifras(n,b) = (∑ α∊[1,∞].cifra(n,α,b))
int sumaCifras(const int n, const int b = 10){
    if(n<b){
        return n;
    }
    else{
        return n%b+sumaCifras(n/b,b);
    }
}

bool tMayord(const int n, const int d, const int b=10){
    if(cifra(n,1,b)<d && n!=0){
        return false;
    }
    else if(n!=0){
        return tMayord(n/b,d,b);
    }
    else{
        return true;
    }
}

#endif
