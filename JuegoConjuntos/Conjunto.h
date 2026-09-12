#ifndef CONJUNTO_H
#define CONJUNTO_H

const int TAM = 100;

class Conjunto {
private:
    int numeros[TAM];
    int cantidad;

public:
    Conjunto();
    bool insertar(int elemento);
    bool remover(int elemento);
    bool existe(int elemento) const;
    int tamanho() const;
    bool esta_vazio() const;
    void imprimir() const;
    Conjunto interseccion(const Conjunto& otro) const;
    Conjunto diferencia(const Conjunto& otro) const;
};

#endif
