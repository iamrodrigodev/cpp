#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

void configurarConsola() {
    HANDLE handleConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infoCursor;
    infoCursor.dwSize = 100;
    infoCursor.bVisible = FALSE;
    SetConsoleCursorInfo(handleConsola, &infoCursor);
}

void mostrarGameOver(int puntuacion, int manzanasComidas) {
    cout << "\nJuego Terminado!\n";
    cout << "Puntuacion final: " << puntuacion << "\n";
    cout << "Manzanas comidas: " << manzanasComidas << "\n\n";
}

void ejecutarPartida() {
    system("cls");

    Gusano gusano(ANCHO_TABLERO / 2, ALTO_TABLERO / 2);
    Tablero tablero;
    tablero.reiniciar(gusano);

    int puntuacion = 0;
    int manzanasComidas = 0;
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        tablero.dibujar(gusano, puntuacion, manzanasComidas);

        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'x' || tecla == 'X') {
                juegoTerminado = true;
                break;
            }
            gusano.cambiarDireccion(tecla);
        }

        gusano.mover();

        if (tablero.hayColisionPared(gusano) || gusano.colisionaConCuerpo()) {
            juegoTerminado = true;
            break;
        }

        if (tablero.comioManzana(gusano)) {
            gusano.crecer();
            puntuacion += 10;
            manzanasComidas++;
            tablero.generarManzana(gusano);
        }

        Sleep(80);
    }

    tablero.dibujar(gusano, puntuacion, manzanasComidas);
    mostrarGameOver(puntuacion, manzanasComidas);
}

void iniciarJuego() {
    srand(time(nullptr));
    configurarConsola();

    char opcion = 's';
    while (opcion == 's' || opcion == 'S') {
        ejecutarPartida();

        while (_kbhit()) {
            _getch();
        }

        cout << "Deseas jugar otra partida? (S / N): ";
        cin >> opcion;
    }

    cout << "\nGracias por jugar al Gusano!\n";
}
