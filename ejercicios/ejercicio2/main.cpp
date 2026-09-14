#include <iostream>

using namespace std;

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

void imprimirArray(const int arr[], int n) {
    cout << "< ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << ">\n";
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Entrada:\n";
    imprimirArray(arr, n);

    waterfall(arr, n);

    cout << "Salida:\n";
    imprimirArray(arr, n);

    return 0;
}
