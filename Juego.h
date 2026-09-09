#ifndef JUEGO_H
#define JUEGO_H

#include "Conjunto.h"

const int CANTIDAD_SECRETOS = 5;

bool validarRango(int numero, int min, int max);
int pedirNumero(int min, int max);
Conjunto pedirConjuntoPrueba();
void generarConjuntoSecreto(Conjunto& conjunto, int cantidad);

void mostrarEstado(int restantes, int intentos);
void mostrarMenu(int oportunidadesInterseccion);

void ejecutarAdivinanza(Conjunto& secreto, int& intentos);
void ejecutarInterseccion(const Conjunto& secreto, int& oportunidades, bool& condicionDiferencia);
void ejecutarDiferencia(const Conjunto& secreto, bool& condicionDiferencia);

void iniciarJuego();

#endif
