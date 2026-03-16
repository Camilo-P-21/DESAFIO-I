#include <iostream>
using namespace std;

void mostrarPiezas(unsigned char piezas[4]){
    for(int i=0; i < 4; i++){
        for(int j=0; j < 8; j++){
            if(piezas[i]&(1 <<(7-j)))
                cout<<"#";
            else {
                cout<<"-";
            }
        }
        cout<<endl;
    }
}
void dibujarTablero(char **tablero, int ancho, int alto,
                    unsigned char pieza[4], int posX, int posY){

    for(int i=0;i<alto;i++){

        for(int j=0;j<ancho;j++){

            char c = tablero[i][j];

            int filaPieza = i - posY;

            if(filaPieza >=0 && filaPieza <4){

                for(int bit=0;bit<8;bit++){

                    if(pieza[filaPieza] & (1 << (7-bit))){

                        int xPieza = posX + bit;

                        if(xPieza == j)
                            c = '#';
                    }
                }
            }

            cout << c;
        }

        cout << endl;
    }

}

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
            tablero[i][j]= '*';
        }
    }

    for(int i=0; i < alto; i++){
        for(int j=0; j < ancho; j++){
            cout << tablero[i][j];
        }
        cout << endl;
    }

    unsigned char piezas[7][4]={

        {
            0b11100000,
            0b01000000,
            0b00000000,
            0b00000000
        },

        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000
        },

        {
            0b11000000,
            0b11000000,
            0b00000000,
            0b00000000
        },

        {
            0b00111000,
            0b00100000,
            0b11100000,
            0b00000000
        },
        {
            0b11100000,
            0b00100000,
            0b00111000,
            0b00000000
        },
        {
            0b00100000,
            0b00100000,
            0b01100000,
            0b00000000
        },
        {
            0b01000000,
            0b01000000,
            0b01110000,
            0b00000000
        },
    };
    unsigned char *piezaActual=piezas[0];
    int posX=0;
    int posY=0;
    char tecla;

    while(true){
        system("cls");
        cout << endl;
        dibujarTablero(tablero, ancho, alto, piezaActual, posX, posY);

        cout << "Mover (W A S D): ";
        cin >> tecla;
        if(tecla == 'a'){
            posX--;
        }
        if(tecla == 'd'){
        posX++;
        }
        if(tecla == 's'){
            posY++;
            cout << "La pieza bajo a fila: " << posY << endl;
        }
        if(tecla == 'w'){

            unsigned char temp = piezaActual[0];

            piezaActual[0] = piezaActual[1];
            piezaActual[1] = piezaActual[2];
            piezaActual[2] = piezaActual[3];
            piezaActual[3] = temp;
        }
    }
}
