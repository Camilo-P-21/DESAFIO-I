#include <iostream>
using namespace std;

int main(){

    int ancho, alto;

    cout<<"ingrese ancho del tablero: ";
    cin>>ancho;

    cout<<"ingrese alto del tablero: ";
    cin>>alto;

    char **tablero = new char*[alto];

    for(int i=0; i < alto; i++){
        tablero[i]= new char[ancho];
    }

    for(int i=0; i < alto; i++){
        for(int j=0; j < ancho; j++){
            tablero[i][j]= '.';
        }
    }

    for(int i=0; i < alto; i++){
        for(int j=0; j < ancho; j++){
            cout << tablero[i][j];
        }
        cout << endl;
    }
    return 0;
}
