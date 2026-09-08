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

void juego1_ConjuntoSecreto() {
    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;

    cout << "\n[Juego 1: Conjunto Secreto]\n";
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

    cout << "Has ganado el Juego 1 en " << intentos << " intentos.\n";
}

void juego2_RetoInterseccion() {
    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;
    int redefiniciones = 3;

    cout << "\n[Juego 2: Reto de Interseccion]\n";
    cout << "Se han elegido " << secreto.tamanho() << " numeros secretos entre 0 y " << (TAM - 1) << ".\n";
    cout << "Propon tu Conjunto de Prueba inicial P:\n";

    Conjunto prueba = pedirConjuntoPrueba();
    Conjunto inter = secreto.interseccion(prueba);
    cout << "Interseccion (S n P): ";
    inter.imprimir();
    cout << "\n";

    while (!secreto.esta_vazio()) {
        cout << "1. Adivinar un numero\n";
        cout << "2. Redefinir conjunto de prueba (Opciones restantes: " << redefiniciones << ")\n";
        cout << "Elige una opcion (1 o 2): ";
        int opcion = 0;
        cin >> opcion;

        if (opcion == 1) {
            int intento = pedirNumero(0, TAM - 1);
            intentos++;

            if (secreto.existe(intento)) {
                cout << ">> Felicidades! Adivinaste el numero " << intento << ".\n";
                secreto.remover(intento);
                cout << ">> Quedan " << secreto.tamanho() << " numero(s) en el conjunto secreto.\n\n";
            } else {
                cout << ">> El numero " << intento << " no esta en el conjunto secreto.\n\n";
            }
        } else if (opcion == 2) {
            if (redefiniciones > 0) {
                prueba = pedirConjuntoPrueba();
                inter = secreto.interseccion(prueba);
                cout << "Interseccion (S n P): ";
                inter.imprimir();
                cout << "\n";
                redefiniciones--;
            } else {
                cout << ">> Ya no tienes opciones para redefinir el conjunto de prueba.\n\n";
            }
        } else {
            cout << "[!] Opcion invalida. Ingresa 1 o 2.\n\n";
        }
    }

    cout << "Has ganado el Juego 2 en " << intentos << " intentos de adivinanza.\n";
}

void juego3_RetoDiferencia() {
    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;
    int redefiniciones = 3;

    cout << "\n[Juego 3: Reto de Diferencia]\n";
    cout << "Se han elegido " << secreto.tamanho() << " numeros secretos entre 0 y " << (TAM - 1) << ".\n";
    cout << "Propon tu Conjunto de Prueba inicial P:\n";

    Conjunto prueba = pedirConjuntoPrueba();
    
    Conjunto inter = secreto.interseccion(prueba);
    int aciertos = inter.tamanho();
    double porcentaje = (double)aciertos / prueba.tamanho() * 100.0;

    cout << "Aciertos en tu prueba: " << aciertos << " de " << prueba.tamanho() << " (" << porcentaje << "%).\n";

    if (porcentaje < 10.0) {
        cout << "Acertaste menos del 10%. Pistas de diferencia reveladas:\n";
        cout << "Diferencia (S - P): ";
        secreto.diferencia(prueba).imprimir();
        cout << "Diferencia (P - S): ";
        prueba.diferencia(secreto).imprimir();
        cout << "\n";
    } else {
        cout << "Interseccion (S n P): ";
        inter.imprimir();
        cout << "\n";
    }

    while (!secreto.esta_vazio()) {
        cout << "1. Adivinar un numero\n";
        cout << "2. Redefinir conjunto de prueba (Opciones restantes: " << redefiniciones << ")\n";
        cout << "Elige una opcion (1 o 2): ";
        int opcion = 0;
        cin >> opcion;

        if (opcion == 1) {
            int intento = pedirNumero(0, TAM - 1);
            intentos++;

            if (secreto.existe(intento)) {
                cout << ">> Felicidades! Adivinaste el numero " << intento << ".\n";
                secreto.remover(intento);
                cout << ">> Quedan " << secreto.tamanho() << " numero(s) en el conjunto secreto.\n\n";
            } else {
                cout << ">> El numero " << intento << " no esta en el conjunto secreto.\n\n";
            }
        } else if (opcion == 2) {
            if (redefiniciones > 0) {
                prueba = pedirConjuntoPrueba();
                
                inter = secreto.interseccion(prueba);
                aciertos = inter.tamanho();
                porcentaje = (double)aciertos / prueba.tamanho() * 100.0;

                cout << "Aciertos en tu prueba: " << aciertos << " de " << prueba.tamanho() << " (" << porcentaje << "%).\n";

                if (porcentaje < 10.0) {
                    cout << "Acertaste menos del 10%. Pistas de diferencia reveladas:\n";
                    cout << "Diferencia (S - P): ";
                    secreto.diferencia(prueba).imprimir();
                    cout << "Diferencia (P - S): ";
                    prueba.diferencia(secreto).imprimir();
                    cout << "\n";
                } else {
                    cout << "Interseccion (S n P): ";
                    inter.imprimir();
                    cout << "\n";
                }

                redefiniciones--;
            } else {
                cout << ">> Ya no tienes opciones para redefinir el conjunto de prueba.\n\n";
            }
        } else {
            cout << "[!] Opcion invalida. Ingresa 1 o 2.\n\n";
        }
    }

    cout << "Has ganado el Juego 3 en " << intentos << " intentos de adivinanza.\n";
}

void iniciarMenu() {
    srand(time(nullptr));

    while (true) {
        cout << "--- MENU DE JUEGOS ---\n";
        cout << "1. Juego 1: Generacion del Conjunto Secreto\n";
        cout << "2. Juego 2: Reto de Interseccion\n";
        cout << "3. Juego 3: Reto de Diferencia\n";
        cout << "4. Salir\n";
        cout << "Elige una opcion (1 - 4): ";
        int opcion = 0;
        cin >> opcion;

        if (!validarRango(opcion, 1, 4)) {
            continue;
        }

        if (opcion == 1) {
            juego1_ConjuntoSecreto();
        } else if (opcion == 2) {
            juego2_RetoInterseccion();
        } else if (opcion == 3) {
            juego3_RetoDiferencia();
        } else if (opcion == 4) {
            cout << "Gracias por jugar. Hasta luego!\n";
            break;
        }
    }
}
