#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int pedirNumero(int min, int max) {
    int numero = 0;

    while (true) {
        cout << "Ingresa un numero para adivinar (" << min << " - " << max << "): ";
        cin >> numero;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[!] Entrada invalida. Por favor, ingresa un numero entero.\n\n";
            continue;
        }

        if (numero < min || numero > max) {
            cout << "[!] El numero debe estar entre " << min << " y " << max << ".\n\n";
            continue;
        }

        return numero;
    }
}

void generarConjuntoSecreto(Conjunto& conjunto, int cantidad) {
    while (conjunto.tamanho() < cantidad) {
        int numeroAleatorio = rand() % TAM;
        conjunto.insertar(numeroAleatorio);
    }
}

void iniciarJuego() {
    srand(time(nullptr));

    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;

    cout << "Se han elegido " << secreto.tamanho() << " numeros secretos entre 0 y " << (TAM - 1) << ".\n\n";

    while (!secreto.esta_vazio()) {
        int intento = pedirNumero(0, TAM - 1);
        intentos++;

        if (secreto.existe(intento)) {
            cout << ">> Felicidades! Adivinaste el numero " << intento << ".\n";
            secreto.remover(intento);
            cout << ">> Quedan " << secreto.tamanho() << " numero(s) en el conjunto secreto.\n\n";
        } else {
            cout << ">> El numero " << intento << " no esta en el conjunto secreto.\n\n";
        }
    }

    cout << "Has ganado el juego en " << intentos << " intentos.\n";
}
