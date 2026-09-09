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

void mostrarEstado(int restantes, int intentos) {
    cout << "Numeros secretos restantes: " << restantes << " | Intentos de adivinanza: " << intentos << "\n";
}

void mostrarMenu(int oportunidadesInterseccion) {
    cout << "1. Adivinar un numero\n";
    cout << "2. Reto de interseccion (" << oportunidadesInterseccion << " oportunidades)\n";
    cout << "3. Reto de diferencia\n";
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

void ejecutarInterseccion(const Conjunto& secreto, int& oportunidades, bool& condicionDiferencia) {
    if (oportunidades <= 0) {
        cout << "\n[!] Ya no puedes utilizar el reto de interseccion. Has agotado tus 3 oportunidades.\n\n";
        return;
    }

    cout << "\nDefine tu Conjunto de Prueba P:\n";
    Conjunto prueba = pedirConjuntoPrueba();
    Conjunto inter = secreto.interseccion(prueba);

    cout << "\nInterseccion (S n P): ";
    inter.imprimir();

    int aciertos = inter.tamanho();
    double porcentaje = (double)aciertos / prueba.tamanho() * 100.0;
    cout << "Aciertos en tu prueba: " << aciertos << " de " << prueba.tamanho() << " (" << porcentaje << "%).\n";

    if (porcentaje < 10.0) {
        condicionDiferencia = true;
        cout << ">> Has acertado menos del 10%. Ahora tienes habilitado el Reto de Diferencia!\n";
    }

    oportunidades--;
    cout << "Oportunidades restantes de interseccion: " << oportunidades << "\n\n";
}

void ejecutarDiferencia(const Conjunto& secreto, bool& condicionDiferencia) {
    if (!condicionDiferencia) {
        cout << "\n[!] Todavia no puedes utilizar el reto de diferencia. Debes haber acertado menos del 10% de los numeros de tu conjunto de prueba.\n\n";
        return;
    }

    cout << "\nCondicion cumplida (< 10% de aciertos). Define un nuevo Conjunto de Prueba P:\n";
    Conjunto prueba = pedirConjuntoPrueba();

    cout << "\n1. Ver diferencia S - P (elementos en secreto que no incluiste)\n";
    cout << "2. Ver diferencia P - S (elementos propuestos que no estan en el secreto)\n";
    cout << "3. Ver ambas diferencias\n";
    cout << "Elige una opcion (1 - 3): ";
    int opDif = 0;
    cin >> opDif;

    if (!validarRango(opDif, 1, 3)) {
        return;
    }

    if (opDif == 1 || opDif == 3) {
        cout << "Diferencia (S - P): ";
        secreto.diferencia(prueba).imprimir();
    }
    if (opDif == 2 || opDif == 3) {
        cout << "Diferencia (P - S): ";
        prueba.diferencia(secreto).imprimir();
    }

    cout << "\n";
}

void iniciarJuego() {
    srand(time(nullptr));

    Conjunto secreto;
    generarConjuntoSecreto(secreto, CANTIDAD_SECRETOS);

    int intentos = 0;
    int oportunidadesInterseccion = 3;
    bool condicionDiferencia = false;

    cout << "\nPartida iniciada.\n";
    cout << "Se han elegido " << secreto.tamanho() << " numeros secretos entre 0 y " << (TAM - 1) << ".\n\n";

    while (!secreto.esta_vazio()) {
        mostrarEstado(secreto.tamanho(), intentos);
        mostrarMenu(oportunidadesInterseccion);

        int opcion = 0;
        cin >> opcion;

        if (!validarRango(opcion, 1, 4)) {
            continue;
        }

        if (opcion == 1) {
            ejecutarAdivinanza(secreto, intentos);
        } else if (opcion == 2) {
            ejecutarInterseccion(secreto, oportunidadesInterseccion, condicionDiferencia);
        } else if (opcion == 3) {
            ejecutarDiferencia(secreto, condicionDiferencia);
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
