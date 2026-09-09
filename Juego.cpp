#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool validarRango(int numero, int min, int max) {
    if (numero < min || numero > max) {
        cout << "[!] El numero debe estar entre " << min << " y " << max << ".\n\n";
        return false;
    }
    return true;
}

int pedirNumero(int min, int max) {
    int numero = 0;

    while (true) {
        cout << "Ingresa un numero (" << min << " - " << max << "): ";
        cin >> numero;

        if (!validarRango(numero, min, max)) {
            continue;
        }

        return numero;
    }
}

Conjunto pedirConjuntoPrueba() {
    Conjunto prueba;
    int cantidad = 0;

    while (true) {
        cout << "Cuantos numeros tendra tu conjunto de prueba?: ";
        cin >> cantidad;

        if (!validarRango(cantidad, 1, TAM)) {
            continue;
        }
        break;
    }

    for (int i = 0; i < cantidad; i++) {
        int num = pedirNumero(0, TAM - 1);
        prueba.insertar(num);
    }

    return prueba;
}

void generarConjuntoSecreto(Conjunto& conjunto, int cantidad) {
    while (conjunto.tamanho() < cantidad) {
        int numeroAleatorio = rand() % TAM;
        conjunto.insertar(numeroAleatorio);
    }
}

void mostrarEstado(int restantes, int intentos, int pistas) {
    cout << "Numeros restantes: " << restantes << " | Intentos: " << intentos << " | Pistas restantes: " << pistas << "\n";
}

void mostrarMenu() {
    cout << "1. Adivinar un numero\n";
    cout << "2. Usar Interseccion con Conjunto de Prueba\n";
    cout << "3. Usar Diferencia con Conjunto de Prueba (Regla < 10%)\n";
    cout << "4. Salir del juego\n";
    cout << "Elige una opcion (1 - 4): ";
}

void ejecutarAdivinanza(Conjunto& secreto, int& intentos) {
    int intento = pedirNumero(0, TAM - 1);
    intentos++;

    if (secreto.existe(intento)) {
        cout << "\nCorrecto! Adivinaste el numero " << intento << ".\n";
        secreto.remover(intento);
        cout << "Quedan " << secreto.tamanho() << " numero(s) en el conjunto secreto.\n\n";
    } else {
        cout << "\nEl numero " << intento << " no esta en el conjunto secreto.\n\n";
    }
}

void ejecutarInterseccion(const Conjunto& secreto, int& pistasRestantes) {
    if (pistasRestantes <= 0) {
        cout << "\n[!] Ya no te quedan pistas disponibles para esta partida.\n\n";
        return;
    }

    cout << "\nDefine tu Conjunto de Prueba P:\n";
    Conjunto prueba = pedirConjuntoPrueba();
    Conjunto inter = secreto.interseccion(prueba);

    cout << "\nResultado de la pista:\n";
    cout << "Interseccion (S n P): ";
    inter.imprimir();

    pistasRestantes--;
    cout << "Pistas restantes: " << pistasRestantes << "\n\n";
}

void ejecutarDiferencia(const Conjunto& secreto, int& pistasRestantes) {
    if (pistasRestantes <= 0) {
        cout << "\n[!] Ya no te quedan pistas disponibles para esta partida.\n\n";
        return;
    }

    cout << "\nDefine tu Conjunto de Prueba P:\n";
    Conjunto prueba = pedirConjuntoPrueba();
    Conjunto inter = secreto.interseccion(prueba);

    int aciertos = inter.tamanho();
    double porcentaje = (double)aciertos / prueba.tamanho() * 100.0;

    cout << "\nAciertos en tu prueba: " << aciertos << " de " << prueba.tamanho() << " (" << porcentaje << "%).\n";

    if (porcentaje < 10.0) {
        cout << "Acertaste menos del 10%. Pistas de diferencia reveladas:\n";
        cout << "Diferencia (S - P): ";
        secreto.diferencia(prueba).imprimir();
        cout << "Diferencia (P - S): ";
        prueba.diferencia(secreto).imprimir();
    } else {
        cout << "Acertaste el 10% o mas. Se revela la interseccion:\n";
        cout << "Interseccion (S n P): ";
        inter.imprimir();
    }

    pistasRestantes--;
    cout << "Pistas restantes: " << pistasRestantes << "\n\n";
}

void iniciarJuego() {
    srand(time(nullptr));

    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;
    int pistasRestantes = 3;

    cout << "\nPartida iniciada.\n";
    cout << "Se han elegido " << secreto.tamanho() << " numeros secretos entre 0 y " << (TAM - 1) << ".\n\n";

    while (!secreto.esta_vazio()) {
        mostrarEstado(secreto.tamanho(), intentos, pistasRestantes);
        mostrarMenu();

        int opcion = 0;
        cin >> opcion;

        if (!validarRango(opcion, 1, 4)) {
            continue;
        }

        if (opcion == 1) {
            ejecutarAdivinanza(secreto, intentos);
        } else if (opcion == 2) {
            ejecutarInterseccion(secreto, pistasRestantes);
        } else if (opcion == 3) {
            ejecutarDiferencia(secreto, pistasRestantes);
        } else if (opcion == 4) {
            cout << "\nHas decidido salir de la partida. Gracias por jugar!\n";
            cout << "Los numeros secretos eran: ";
            secreto.imprimir();
            return;
        }
    }

    cout << "\nFelicitaciones! Has adivinado todos los numeros secretos.\n";
    cout << "Completaste la partida con exito en " << intentos << " intentos de adivinanza.\n";
}
