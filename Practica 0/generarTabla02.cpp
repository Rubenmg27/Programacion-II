#include <iostream>
#include <iomanip>
using namespace std;

double randDouble ( const double inic , const double final){
   return (final - inic) * ((double)rand() / (double)RAND_MAX) + inic;
}

int main(int numArg, char* args[]) {
    int numNumers = atoi (args[1]);
    int inic = atoi (args[2]);
    int final = atoi (args[3]);
    time_t semilla = time ( nullptr );
    srand ( semilla );
    double random;
    for(int i=0; i<numNumers;i++){
        cout<<setw(8)<<fixed << setprecision(3)<<randDouble(inic,final);
        if((i+1)%10==0){
            cout<<endl;
        }
    }
}
