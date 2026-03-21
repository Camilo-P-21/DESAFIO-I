#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void dibujarTablero(char **tablero, int ancho, int alto,
                    unsigned char pieza[4], int posX, int posY){

    for(int i=0;i<alto;i++){
        for(int j=0;j<ancho;j++){

            char c = tablero[i][j];

            int filaPieza = i - posY;

            if(filaPieza >=0 && filaPieza <4){

                for(int bit=0;bit<4;bit++){

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

void rotar(unsigned char pieza[4]){

    unsigned char nueva[4] = {0};

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            if(pieza[i] & (1 << (7-j))){
                nueva[j] |= (1 << (7-(3-i)));
            }
        }
    }

    for(int i=0;i<4;i++){
        pieza[i] = nueva[i];
    }
}

bool hayColision(char **tablero, int ancho, int alto,
                 unsigned char pieza[4], int posX, int posY){

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            if(pieza[i] & (1 << (7-j))){

                int x = posX + j;
                int y = posY + i;

                if(x < 0 || x >= ancho || y >= alto){
                    return true;
                }

                if(y >= 0 && tablero[y][x] == '#'){
                    return true;
                }
            }
        }
    }

    return false;
}

void fijarPieza(char **tablero, unsigned char pieza[4], int posX, int posY){

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            if(pieza[i] & (1 << (7-j))){

                int x = posX + j;
                int y = posY + i;

                if(y >= 0){
                    tablero[y][x] = '#';
                }
            }
        }
    }
}

void eliminarFilas(char **tablero, int ancho, int alto){

    for(int i=0;i<alto;i++){

        bool llena = true;

        for(int j=0;j<ancho;j++){
            if(tablero[i][j] != '#'){
                llena = false;
                break;
            }
        }

        if(llena){
            for(int k=i; k>0; k--){
                for(int j=0;j<ancho;j++){
                    tablero[k][j] = tablero[k-1][j];
                }
            }
            for(int j=0;j<ancho;j++){
                tablero[0][j] = '*';
            }

            i--;
        }
    }
}

int main(){

    int ancho, alto;

    cout<<"Ingrese ancho del tablero: ";
    cin>>ancho;

    cout<<"Ingrese alto del tablero: ";
    cin>>alto;

    if(ancho < 8 || ancho % 8 != 0 || alto < 8){
        cout<<"Dimensiones invalidas (min 8 y ancho multiplo de 8)\n";
        return 0;
    }

    srand(time(NULL));

    char **tablero = new char*[alto];
    for(int i=0;i<alto;i++){
        tablero[i] = new char[ancho];
    }

    for(int i=0;i<alto;i++){
        for(int j=0;j<ancho;j++){
            tablero[i][j] = '*';
        }
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

int tipo = rand() % 7;

int posX = ancho/2 - 2;
int posY = 0;

char tecla;

while(true){

    dibujarTablero(tablero, ancho, alto, piezas[tipo], posX, posY);

    cout<<"Mover W A S D para Cambiar pieza (Q) ";
    cin>>tecla;

    if(tecla == 'a'){
        posX--;
        if(hayColision(tablero, ancho, alto, piezas[tipo], posX, posY)){
            posX++;
        }
    }

    if(tecla == 'd'){
        posX++;
        if(hayColision(tablero, ancho, alto, piezas[tipo], posX, posY)){
            posX--;
        }
    }

    if(tecla == 's'){
        posY++;

        if(hayColision(tablero, ancho, alto, piezas[tipo], posX, posY)){
            posY--;

            fijarPieza(tablero, piezas[tipo], posX, posY);

            eliminarFilas(tablero, ancho, alto);

            tipo = rand() % 7;
            posX = ancho/2 - 2;
            posY = 0;

            if(hayColision(tablero, ancho, alto, piezas[tipo], posX, posY)){
                system("cls");
                cout<<"GAME OVER\n";
                break;
            }
        }
    }

    if(tecla == 'w'){
        rotar(piezas[tipo]);

        if(hayColision(tablero, ancho, alto, piezas[tipo], posX, posY)){
            rotar(piezas[tipo]);
            rotar(piezas[tipo]);
            rotar(piezas[tipo]);
        }
    }

    if(tecla == 'q'){
        tipo = (tipo + 1) % 7;
    }
}
}
