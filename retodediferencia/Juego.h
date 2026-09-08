#ifndef JUEGO_H
#define JUEGO_H

#include "Conjunto.h"

const int CANTIDAD_SECRETOS = 5;

void iniciarJuego();
void generarConjuntoSecreto(Conjunto& conjunto, int cantidad);
bool validarRango(int numero, int min, int max);
int pedirNumero(int min, int max);
Conjunto pedirConjuntoPrueba();
void evaluarConjuntoPrueba(const Conjunto& secreto, const Conjunto& prueba);

#endif
