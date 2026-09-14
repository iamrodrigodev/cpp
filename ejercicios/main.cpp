#include <iostream>

using namespace std;

void split(const int arr[], int n, int parte1[], int& n1, int parte2[], int& n2) {
    n1 = (n + 1) / 2;
    n2 = (n + 1) / 2;
    int inicio2 = n - n2;

    for (int i = 0; i < n1; i++) {
        parte1[i] = arr[i];
    }

    for (int i = 0; i < n2; i++) {
        parte2[i] = arr[inicio2 + i];
    }
}

void imprimirArray(const int arr[], int n) {
    cout << " array = < ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << ">\n";
}

int main() {
    int n;
    cout << "Ingrese la cantidad de elementos (0 para usar el ejemplo): ";
    if (!(cin >> n) || n <= 0) {
        int arr[] = {1, 2, 3, 4, 5};
        int tam = 5;

        int parte1[100];
        int parte2[100];
        int n1 = 0;
        int n2 = 0;

        split(arr, tam, parte1, n1, parte2, n2);

        cout << "\nEntrada:\n";
        imprimirArray(arr, tam);
        cout << "Salida:\n";
        imprimirArray(parte1, n1);
        imprimirArray(parte2, n2);

        return 0;
    }

    int arr[100];
    cout << "Ingrese los " << n << " elementos: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int parte1[100];
    int parte2[100];
    int n1 = 0;
    int n2 = 0;

    split(arr, n, parte1, n1, parte2, n2);

    cout << "\nEntrada:\n";
    imprimirArray(arr, n);
    cout << "Salida:\n";
    imprimirArray(parte1, n1);
    imprimirArray(parte2, n2);

    return 0;
}
