#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int devolverAleatorio();
int intentarResolver();

int main(){
    int counter = 1;
    int flag = 1;
    while(flag == 1){
        flag = 7;
        flag = intentarResolver();
        cout<<"=================================================================== INTENTO: "<<counter<<" ==================================================================="<<endl;
        counter++;
    }
    cout<<"Intentos: "<<counter-1<<endl;
    return 0;
}

int intentarResolver(){
    const int size_fila = 8;
    const int size_columna = 8;
    array<array<int, size_fila>, size_columna> tablero = {0};                                                    // Defino el array bidimensional que representa el tablero.
    array<array<int, size_fila>, size_columna> accesibilidad =
    {1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1,};

    int vertical[56] = {1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7};
    int horizontal[56] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7};
    int intentos = 0;

    static int iterador_vertical = 0;
    static int iterador_horizontal = 0;
    int fila_actual = iterador_vertical;                                                                         // Posicion inicial de la reina en sentido vertical.
    int columna_actual = iterador_horizontal;                                                                    // Posicion inicial de la reina en sentido horizontal.
    iterador_horizontal++;
    if(iterador_horizontal >= 8){
        iterador_vertical++;
        iterador_horizontal = 0;
    }
    if(iterador_vertical >= 8){
        iterador_vertical = 0;
    }

    while (intentos < 9){
        intentos++;
        int flag = 0;

        for(unsigned int i = 0; i < 8; i++){
            for(unsigned int j = 0; j < 8; j++){
                if (accesibilidad[i][j] == 1){
                    flag = 7;
                }
            }
        }
        if (flag != 7){
            cout<<"No quedan posiciones, reintentando !"<<endl;
            return 1;
        }

        while (1){
            fila_actual = devolverAleatorio();
            columna_actual = devolverAleatorio();
            if(accesibilidad[fila_actual][columna_actual] == 1){
                break;
            }
        }

        accesibilidad[fila_actual][columna_actual] = 9;
        tablero[fila_actual][columna_actual] = 8;
        for (unsigned int h = 0; h < 56; h++){
            if ((fila_actual + (vertical[h])) >= 0 && (columna_actual + (horizontal[h])) >= 0 &&                // Comprueba que la posicion no se salga de los limites del tablero.
                (fila_actual + (vertical[h])) < 8 && (columna_actual + (horizontal[h])) < 8 ){                  // Permite blanquear las posiciones solo dentro de los limites.

                accesibilidad[fila_actual + vertical[h]][columna_actual + horizontal[h]] = 8;
                tablero[fila_actual + vertical[h]][columna_actual + horizontal[h]] = 1;
            }
        }

        vector<int>invalidos(0,99);
        for (unsigned int x = 0 ; x < 8 ; x++){                                                                  // Comprobacion de posiciones disponibles mediante bucle.
            for (unsigned int y = 0 ; y < 8 ; y++){
                cout<<setw(3)<<tablero[x][y];
            }
            cout<<"                                  ";
            for (unsigned int z = 0 ; z < 8 ; z++){                                                              // Bucle para imprimir la heuristica (estrategia que sigue el caballo).
                cout<<setw(3)<<accesibilidad[x][z];
            }
            cout<<endl;
        }
        if (intentos == 8){
            cout<<"Ocho Reinas Compleatado !"<<endl;
            return 7;
        }
        cout<<"Reina: "<<intentos<<endl;
    }
    return 1;
}

int devolverAleatorio(){
    static int mult = 53;
    mult *=53;
    default_random_engine motor(static_cast<unsigned int>(time(0)*mult));
    uniform_int_distribution<unsigned int> intAleatorio(0, 7);
    return intAleatorio(motor);
}
