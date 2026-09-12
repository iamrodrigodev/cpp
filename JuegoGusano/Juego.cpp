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

void configurarConsola() {
    cout << "\033[?25l";
}

void restaurarConsola() {
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
    return _getch();
#else
    char ch = 0;
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
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
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        tablero.dibujar(gusano, puntuacion, manzanasComidas);

        if (hayTecla()) {
            char tecla = leerTecla();
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

        this_thread::sleep_for(chrono::milliseconds(80));
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

        vaciarBufferTeclas();

        cout << "Deseas jugar otra partida? (S / N): ";
        cin >> opcion;
    }

    restaurarConsola();
    cout << "\nGracias por jugar al Gusano!\n";
}
