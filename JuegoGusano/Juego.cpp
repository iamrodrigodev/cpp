#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

using namespace std;

const int VELOCIDAD_MS = 120;

#ifndef _WIN32
termios configOriginal;
#endif

void configurarConsola() {
#ifndef _WIN32
    tcgetattr(STDIN_FILENO, &configOriginal);
    termios configModificada = configOriginal;
    configModificada.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &configModificada);
#endif
    cout << "\033[?25l";
}

void restaurarConsola() {
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &configOriginal);
#endif
    cout << "\033[?25h";
}

void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

bool hayTecla() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
#endif
}

char leerTecla() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int flecha = _getch();
        if (flecha == 72) return 'w';
        if (flecha == 80) return 's';
        if (flecha == 75) return 'a';
        if (flecha == 77) return 'd';
    }
    return (char)ch;
#else
    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) <= 0) {
        return 0;
    }
    if (ch == 27) {
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
            if (seq[0] == '[') {
                if (seq[1] == 'A') return 'w';
                if (seq[1] == 'B') return 's';
                if (seq[1] == 'D') return 'a';
                if (seq[1] == 'C') return 'd';
            }
        }
    }
    return ch;
#endif
}

void vaciarBufferTeclas() {
    while (hayTecla()) {
        leerTecla();
    }
}

void mostrarGameOver(int puntuacion, int manzanasComidas) {
    cout << "\nJuego Terminado!\n";
    cout << "Puntuacion final: " << puntuacion << "\n";
    cout << "Manzanas comidas: " << manzanasComidas << "\n\n";
}

void ejecutarPartida() {
    limpiarPantalla();

    Gusano gusano(ANCHO_TABLERO / 2, ALTO_TABLERO / 2);
    Tablero tablero;
    tablero.reiniciar(gusano);

    int puntuacion = 0;
    int manzanasComidas = 0;
    int vidas = 3;
    bool juegoTerminado = false;

    tablero.dibujar(gusano, puntuacion, manzanasComidas, vidas);

    while (!juegoTerminado && vidas > 0) {
        while (hayTecla()) {
            char tecla = leerTecla();
            if (tecla == 'x' || tecla == 'X') {
                juegoTerminado = true;
                break;
            }
            gusano.cambiarDireccion(tecla);
        }

        if (juegoTerminado) {
            break;
        }

        gusano.mover();

        if (tablero.hayColisionPared(gusano) || gusano.colisionaConCuerpo()) {
            vidas--;
            tablero.dibujar(gusano, puntuacion, manzanasComidas, vidas);

            if (vidas > 0) {
                this_thread::sleep_for(chrono::milliseconds(800));
                gusano.reiniciar(ANCHO_TABLERO / 2, ALTO_TABLERO / 2);
                tablero.generarManzana(gusano);
                tablero.dibujar(gusano, puntuacion, manzanasComidas, vidas);
                continue;
            } else {
                juegoTerminado = true;
                break;
            }
        }

        if (tablero.comioManzana(gusano)) {
            gusano.crecer();
            puntuacion += 10;
            manzanasComidas++;
            tablero.generarManzana(gusano);
        }

        tablero.dibujar(gusano, puntuacion, manzanasComidas, vidas);
        this_thread::sleep_for(chrono::milliseconds(VELOCIDAD_MS));
    }

    tablero.dibujar(gusano, puntuacion, manzanasComidas, vidas);
    mostrarGameOver(puntuacion, manzanasComidas);
}

void iniciarJuego() {
    srand(time(nullptr));
    configurarConsola();

    char opcion = 's';
    while (opcion == 's' || opcion == 'S') {
        ejecutarPartida();

        restaurarConsola();
        vaciarBufferTeclas();

        cout << "Deseas jugar otra partida? (S / N): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            configurarConsola();
        }
    }

    restaurarConsola();
    cout << "\nGracias por jugar al Gusano!\n";
}
