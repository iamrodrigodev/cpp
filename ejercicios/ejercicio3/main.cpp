#include <iostream>

using namespace std;

void reversa(int arr[], int tam, int N) {
    if (N <= 1 || tam <= 1) {
        return;
    }

    for (int i = 0; i < tam; i += N) {
        int inicio = i;
        int fin = i + N - 1;
        if (fin >= tam) {
            fin = tam - 1;
        }

        while (inicio < fin) {
            int temp = arr[inicio];
            arr[inicio] = arr[fin];
            arr[fin] = temp;
            inicio++;
            fin--;
        }
    }
}

void imprimirArray(const int arr[], int n) {
    cout << "< ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << ">\n";
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int tam1 = sizeof(arr1) / sizeof(arr1[0]);
    int N1 = 3;

    cout << "Entrada:\n";
    imprimirArray(arr1, tam1);
    cout << "N = " << N1 << "\n";

    reversa(arr1, tam1, N1);

    cout << "Salida:\n";
    imprimirArray(arr1, tam1);

    cout << "\n";

    int arr2[] = {1, 2, 3, 4, 5, 6};
    int tam2 = sizeof(arr2) / sizeof(arr2[0]);
    int N2 = 4;

    cout << "Entrada:\n";
    imprimirArray(arr2, tam2);
    cout << "N = " << N2 << "\n";

    reversa(arr2, tam2, N2);

    cout << "Salida:\n";
    imprimirArray(arr2, tam2);

    return 0;
}
