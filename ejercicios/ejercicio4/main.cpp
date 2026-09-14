#include <iostream>

using namespace std;

void encontrarBloquePositivo(const int arr[], int tam, int& inicioMax, int& longMax) {
    inicioMax = -1;
    longMax = 0;

    int inicioActual = -1;
    int longActual = 0;

    for (int i = 0; i < tam; i++) {
        if (arr[i] > 0) {
            if (longActual == 0) {
                inicioActual = i;
            }
            longActual++;

            if (longActual > longMax) {
                longMax = longActual;
                inicioMax = inicioActual;
            }
        } else {
            longActual = 0;
            inicioActual = -1;
        }
    }
}

void imprimirArreglo(const int arr[], int inicio, int longitud) {
    cout << "[";
    for (int i = 0; i < longitud; i++) {
        cout << arr[inicio + i];
        if (i < longitud - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

int main() {
    int caso1[] = {1, 2, -1, 3, 4, -2, 5};
    int tam1 = sizeof(caso1) / sizeof(caso1[0]);

    cout << "Caso 1:\n";
    cout << "Entrada: ";
    imprimirArreglo(caso1, 0, tam1);
    int inicio1 = -1;
    int long1 = 0;
    encontrarBloquePositivo(caso1, tam1, inicio1, long1);
    cout << "Bloque: ";
    imprimirArreglo(caso1, inicio1, long1);
    cout << "Longitud: " << long1 << "\n\n";

    int caso2[] = {-3, -2, -5};
    int tam2 = sizeof(caso2) / sizeof(caso2[0]);

    cout << "Caso 2:\n";
    cout << "Entrada: ";
    imprimirArreglo(caso2, 0, tam2);
    int inicio2 = -1;
    int long2 = 0;
    encontrarBloquePositivo(caso2, tam2, inicio2, long2);
    cout << "Bloque: ";
    imprimirArreglo(caso2, inicio2, long2);
    cout << "Longitud: " << long2 << "\n\n";

    int caso3[] = {1, 2, 3, 4};
    int tam3 = sizeof(caso3) / sizeof(caso3[0]);

    cout << "Caso 3:\n";
    cout << "Entrada: ";
    imprimirArreglo(caso3, 0, tam3);
    int inicio3 = -1;
    int long3 = 0;
    encontrarBloquePositivo(caso3, tam3, inicio3, long3);
    cout << "Bloque: ";
    imprimirArreglo(caso3, inicio3, long3);
    cout << "Longitud: " << long3 << "\n";

    return 0;
}
