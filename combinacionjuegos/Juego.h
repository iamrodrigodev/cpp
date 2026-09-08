#ifndef JUEGO_H
#define JUEGO_H

#include "Conjunto.h"

const int CANTIDAD_SECRETOS = 5;

bool validarRango(int numero, int min, int max);
int pedirNumero(int min, int max);
Conjunto pedirConjuntoPrueba();
void generarConjuntoSecreto(Conjunto& conjunto, int cantidad);

void juego1_ConjuntoSecreto();
void juego2_RetoInterseccion();
void juego3_RetoDiferencia();

void iniciarMenu();

#endif
