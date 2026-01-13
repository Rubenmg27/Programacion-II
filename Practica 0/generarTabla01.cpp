#include <iostream>
#include <iomanip>
using namespace std;

int generador ( const int inic , const int final){
    return inic + rand()%(final-inic+1);
}

int main(int numArg, char* args[]) {
    int numNumers = atoi (args[1]);
    int inic = atoi (args[2]);
    int final = atoi (args[3]);
    time_t semilla = time ( nullptr );
    srand ( semilla );
    for(int i=0; i<numNumers;i++){
        cout<<setw(4)<<generador(inic,final);
        if((i+1)%10==0){
            cout<<endl;
        }
    }
}
