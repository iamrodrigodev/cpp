#include "Tablero.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

Tablero::Tablero() {
    manzanaX = 0;
    manzanaY = 0;
}

void Tablero::reiniciar(const Gusano& gusano) {
    generarManzana(gusano);
}

void Tablero::generarManzana(const Gusano& gusano) {
    bool ocupado = true;

    while (ocupado) {
        manzanaX = 1 + rand() % (M - 2);
        manzanaY = 1 + rand() % (M - 2);

        ocupado = false;

        if (gusano.getX() == manzanaX && gusano.getY() == manzanaY) {
            ocupado = true;
            continue;
        }

        for (int i = 0; i < gusano.getLongitud(); i++) {
            if (gusano.getCuerpoX(i) == manzanaX && gusano.getCuerpoY(i) == manzanaY) {
                ocupado = true;
                break;
            }
        }
    }
}

bool Tablero::hayColisionPared(const Gusano& gusano) const {
    if (gusano.getX() <= 0 || gusano.getX() >= M - 1 ||
        gusano.getY() <= 0 || gusano.getY() >= M - 1) {
        return true;
    }
    return false;
}

bool Tablero::comioManzana(const Gusano& gusano) const {
    return (gusano.getX() == manzanaX && gusano.getY() == manzanaY);
}

void Tablero::dibujar(const Gusano& gusano, int puntuacion, int manzanasComidas, int vidas) const {
    string salida = "\033[H";

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < M; x++) {
            if (x == gusano.getX() && y == gusano.getY()) {
                salida += "O";
            } else {
                bool esCuerpo = false;
                for (int i = 0; i < gusano.getLongitud(); i++) {
                    if (gusano.getCuerpoX(i) == x && gusano.getCuerpoY(i) == y) {
                        salida += "o";
                        esCuerpo = true;
                        break;
                    }
                }
                if (esCuerpo) {
                    salida += "o";
                } else if (y == 0 || y == M - 1 || x == 0 || x == M - 1) {
                    salida += "#";
                } else if (x == manzanaX && y == manzanaY) {
                    salida += "@";
                } else {
                    salida += " ";
                }
            }
        }
        salida += "\033[K\n";
    }

    salida += "\nPuntuacion: " + to_string(puntuacion) + 
              " | Manzanas: " + to_string(manzanasComidas) + 
              " | Vidas: " + to_string(vidas) + 
              " | Longitud: " + to_string(gusano.getLongitud() + 1) + "\033[K\n";
    salida += "Elementos: Manzana (@) | Cabeza (O) | Cuerpo (o)\033[K\n";
    if (gusano.getDireccion() == DETENIDO) {
        salida += "Presiona una flecha o W, A, S, D para iniciar | X (salir)\033[K\n";
    } else {
        salida += "Controles: Flechas o W, A, S, D | X (salir)\033[K\n";
    }

    cout << salida;
}

int Tablero::getManzanaX() const {
    return manzanaX;
}

int Tablero::getManzanaY() const {
    return manzanaY;
}
