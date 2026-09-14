#include <iostream>

using namespace std;

void imprimirArray(const int arr[], int n) {
    cout << "< ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << ">\n";
}

void imprimirPunteros(int paso) {
    if (paso == 0) {
        cout << "   ^                     ^\n";
        cout << "curr                 tail\n";
    } else if (paso == 1) {
        cout << "      ^                  ^\n";
        cout << "    curr            tail\n";
    } else if (paso == 2) {
        cout << "          ^              ^\n";
        cout << "       curr           tail\n";
    } else if (paso == 3) {
        cout << "             ^           ^\n";
        cout << "      curr           tail\n";
    } else if (paso == 4) {
        cout << "                ^         ^\n";
        cout << "              curr    tail\n";
    } else if (paso == 5) {
        cout << "                   ^      ^\n";
        cout << "                curr  tail\n";
    } else if (paso == 6) {
        cout << "                      ^  ^\n";
        cout << "                  curr tail\n";
    }
}

void waterfall(int arr[], int n) {
    int curr = 0;
    while (curr < n - 2) {
        int temp = arr[curr + 1];
        for (int i = curr + 1; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[n - 1] = temp;
        curr++;
    }
}

void waterfallPasoAPaso(int arr[], int n) {
    if (n <= 2) {
        return;
    }

    cout << "Paso a paso:\n";
    imprimirArray(arr, n);

    cout << "Llamar a la funcion waterfall\n";
    cout << "< ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "> - Skip the " << arr[0] << "\n";
    imprimirPunteros(0);

    int curr = 0;
    int paso = 1;

    while (curr < n - 2) {
        int valCurr = arr[curr];
        int valRemovido = arr[curr + 1];

        if (curr == 0) {
            cout << "Remover el nro. " << valRemovido << " y moverlo al final\n";
        } else {
            cout << "Salto al " << valCurr << " (curr) y muevo el " << valRemovido << " al final\n";
        }

        for (int i = curr + 1; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[n - 1] = valRemovido;

        curr++;

        cout << "< ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << ">\n";

        imprimirPunteros(paso);
        paso++;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Ejemplo:\n";
    cout << " ";
    imprimirArray(arr, n);

    int arrCopia[100];
    for (int i = 0; i < n; i++) {
        arrCopia[i] = arr[i];
    }
    waterfall(arrCopia, n);

    cout << "Salida:\n";
    imprimirArray(arrCopia, n);

    waterfallPasoAPaso(arr, n);

    return 0;
}
