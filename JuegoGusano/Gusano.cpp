#include "Gusano.h"

Gusano::Gusano(int inicioX, int inicioY) {
    reiniciar(inicioX, inicioY);
}

void Gusano::reiniciar(int inicioX, int inicioY) {
    x = inicioX;
    y = inicioY;
    longitud = 0;
    direccion = DETENIDO;

    for (int i = 0; i < MAX_CUERPO; i++) {
        cuerpoX[i] = 0;
        cuerpoY[i] = 0;
    }
}

void Gusano::cambiarDireccion(char tecla) {
    if (tecla == 'w' || tecla == 'W') {
        if (longitud == 0 || cuerpoY[0] != y - 1) {
            direccion = ARRIBA;
        }
    } else if (tecla == 's' || tecla == 'S') {
        if (longitud == 0 || cuerpoY[0] != y + 1) {
            direccion = ABAJO;
        }
    } else if (tecla == 'a' || tecla == 'A') {
        if (longitud == 0 || cuerpoX[0] != x - 1) {
            direccion = IZQUIERDA;
        }
    } else if (tecla == 'd' || tecla == 'D') {
        if (longitud == 0 || cuerpoX[0] != x + 1) {
            direccion = DERECHA;
        }
    }
}

void Gusano::mover() {
    if (direccion == DETENIDO) {
        return;
    }

    for (int i = longitud - 1; i > 0; i--) {
        cuerpoX[i] = cuerpoX[i - 1];
        cuerpoY[i] = cuerpoY[i - 1];
    }

    if (longitud > 0) {
        cuerpoX[0] = x;
        cuerpoY[0] = y;
    }

    if (direccion == ARRIBA) {
        y--;
    } else if (direccion == ABAJO) {
        y++;
    } else if (direccion == IZQUIERDA) {
        x--;
    } else if (direccion == DERECHA) {
        x++;
    }
}

void Gusano::crecer() {
    if (longitud < MAX_CUERPO) {
        longitud++;
    }
}

bool Gusano::colisionaConCuerpo() const {
    if (direccion == DETENIDO) {
        return false;
    }

    for (int i = 0; i < longitud; i++) {
        if (x == cuerpoX[i] && y == cuerpoY[i]) {
            return true;
        }
    }
    return false;
}

int Gusano::getX() const {
    return x;
}

int Gusano::getY() const {
    return y;
}

int Gusano::getLongitud() const {
    return longitud;
}

int Gusano::getCuerpoX(int indice) const {
    return cuerpoX[indice];
}

int Gusano::getCuerpoY(int indice) const {
    return cuerpoY[indice];
}

Direccion Gusano::getDireccion() const {
    return direccion;
}
