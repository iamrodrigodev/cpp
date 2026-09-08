#include "Conjunto.h"
#include <iostream>

using namespace std;

Conjunto::Conjunto() {
    cantidad = 0;
}

bool Conjunto::insertar(int elemento) {
    if (elemento < 0 || elemento >= TAM || cantidad >= TAM) {
        return false;
    }

    if (existe(elemento)) {
        return false;
    }

    numeros[cantidad] = elemento;
    cantidad++;
    return true;
}

bool Conjunto::remover(int elemento) {
    for (int i = 0; i < cantidad; i++) {
        if (numeros[i] == elemento) {
            numeros[i] = numeros[cantidad - 1];
            cantidad--;
            return true;
        }
    }
    return false;
}

bool Conjunto::existe(int elemento) const {
    for (int i = 0; i < cantidad; i++) {
        if (numeros[i] == elemento) {
            return true;
        }
    }
    return false;
}

int Conjunto::tamanho() const {
    return cantidad;
}

bool Conjunto::esta_vazio() const {
    return cantidad == 0;
}

void Conjunto::imprimir() const {
    cout << "{ ";
    for (int i = 0; i < cantidad; i++) {
        cout << numeros[i];
        if (i < cantidad - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

Conjunto Conjunto::interseccion(const Conjunto& otro) const {
    Conjunto resultado;
    for (int i = 0; i < cantidad; i++) {
        if (otro.existe(numeros[i])) {
            resultado.insertar(numeros[i]);
        }
    }
    return resultado;
}
