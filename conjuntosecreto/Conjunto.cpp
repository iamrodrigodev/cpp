#include "Conjunto.h"
#include <iostream>

using namespace std;

Conjunto::Conjunto() {
    cantidad = 0;
    for (int i = 0; i < TAM; i++) {
        elementos[i] = false;
    }
}

bool Conjunto::insertar(int elemento) {
    if (elemento < 0 || elemento >= TAM) {
        return false;
    }

    if (elementos[elemento]) {
        return false;
    }

    elementos[elemento] = true;
    cantidad++;
    return true;
}

bool Conjunto::remover(int elemento) {
    if (elemento < 0 || elemento >= TAM) {
        return false;
    }

    if (!elementos[elemento]) {
        return false;
    }

    elementos[elemento] = false;
    cantidad--;
    return true;
}

bool Conjunto::existe(int elemento) const {
    if (elemento < 0 || elemento >= TAM) {
        return false;
    }
    return elementos[elemento];
}

int Conjunto::tamanho() const {
    return cantidad;
}

bool Conjunto::esta_vazio() const {
    return cantidad == 0;
}

void Conjunto::imprimir() const {
    cout << "{ ";
    bool primero = true;
    for (int i = 0; i < TAM; i++) {
        if (elementos[i]) {
            if (!primero) {
                cout << ", ";
            }
            cout << i;
            primero = false;
        }
    }
    cout << " }" << endl;
}
