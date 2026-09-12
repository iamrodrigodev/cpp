#include "Tablero.h"
#include <iostream>
#include <cstdlib>

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
        manzanaX = 1 + rand() % (ANCHO_TABLERO - 2);
        manzanaY = 1 + rand() % (ALTO_TABLERO - 2);

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
    if (gusano.getX() <= 0 || gusano.getX() >= ANCHO_TABLERO - 1 ||
        gusano.getY() <= 0 || gusano.getY() >= ALTO_TABLERO - 1) {
        return true;
    }
    return false;
}

bool Tablero::comioManzana(const Gusano& gusano) const {
    return (gusano.getX() == manzanaX && gusano.getY() == manzanaY);
}

void Tablero::dibujar(const Gusano& gusano, int puntuacion, int manzanasComidas, int vidas) const {
    cout << "\033[H";

    for (int y = 0; y < ALTO_TABLERO; y++) {
        for (int x = 0; x < ANCHO_TABLERO; x++) {
            if (x == gusano.getX() && y == gusano.getY()) {
                cout << 'O';
            } else {
                bool esCuerpo = false;
                for (int i = 0; i < gusano.getLongitud(); i++) {
                    if (gusano.getCuerpoX(i) == x && gusano.getCuerpoY(i) == y) {
                        esCuerpo = true;
                        break;
                    }
                }
                if (esCuerpo) {
                    cout << 'o';
                } else if (y == 0 || y == ALTO_TABLERO - 1 || x == 0 || x == ANCHO_TABLERO - 1) {
                    cout << '#';
                } else if (x == manzanaX && y == manzanaY) {
                    cout << '@';
                } else {
                    cout << ' ';
                }
            }
        }
        cout << "\033[K\n";
    }

    cout << "\nPuntuacion: " << puntuacion 
         << " | Manzanas: " << manzanasComidas 
         << " | Vidas: " << vidas 
         << " | Longitud: " << gusano.getLongitud() << "\033[K\n";
    cout << "Elementos: Manzana (@) | Cabeza (O) | Cuerpo (o)\033[K\n";
    if (gusano.getDireccion() == DETENIDO) {
        cout << "Presiona una flecha o W, A, S, D para iniciar | X (salir)\033[K\n";
    } else {
        cout << "Controles: Flechas o W, A, S, D | X (salir)\033[K\n";
    }
}

int Tablero::getManzanaX() const {
    return manzanaX;
}

int Tablero::getManzanaY() const {
    return manzanaY;
}
