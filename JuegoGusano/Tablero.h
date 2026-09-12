#ifndef TABLERO_H
#define TABLERO_H

#include "Gusano.h"

const int ANCHO_TABLERO = 30;
const int ALTO_TABLERO = 20;

class Tablero {
private:
    int manzanaX;
    int manzanaY;

public:
    Tablero();
    void reiniciar(const Gusano& gusano);
    void generarManzana(const Gusano& gusano);
    bool hayColisionPared(const Gusano& gusano) const;
    bool comioManzana(const Gusano& gusano) const;
    void dibujar(const Gusano& gusano, int puntuacion, int manzanasComidas) const;
    int getManzanaX() const;
    int getManzanaY() const;
};

#endif
