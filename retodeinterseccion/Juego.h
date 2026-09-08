#ifndef JUEGO_H
#define JUEGO_H

#include "Conjunto.h"

const int CANTIDAD_SECRETOS = 5;

void iniciarJuego();
void generarConjuntoSecreto(Conjunto& conjunto, int cantidad);
int pedirNumero(int min, int max);
Conjunto pedirConjuntoPrueba();

#endif
