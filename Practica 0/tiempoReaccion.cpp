#include <iostream>
#include <ctime>
using namespace std;


int main(int numArg, char* args[]) {
    int entero = atoi (args[1]);
    string linea;
    if (args[1] == 0){
        cout << "1) " << "Pulse la tecla de fin de línea, por favor ...";
        time_t t1 = time ( nullptr );
        getline(cin,linea);
        time_t t2 = time ( nullptr );
        int segundos = t2-t1;
        cout <<"Su tiempo de reacción ha sido de "<< segundos <<" segundos" << endl;
        cout << endl;
    }
    else{
        for(int i =0; i<entero;i++){
            cout << i+1 << ") " << "Pulse la tecla de fin de línea, por favor ...";
            time_t t1 = time ( nullptr );
            getline(cin,linea);
            time_t t2 = time ( nullptr );
            int segundos = t2-t1;
            cout <<"Su tiempo de reacción ha sido de "<< segundos <<" segundos" << endl;
            cout << endl;
        }
    }
}
