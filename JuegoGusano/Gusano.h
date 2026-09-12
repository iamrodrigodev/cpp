#ifndef GUSANO_H
#define GUSANO_H

const int MAX_CUERPO = 500;

enum Direccion {
    DETENIDO,
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

class Gusano {
private:
    int x;
    int y;
    int cuerpoX[MAX_CUERPO];
    int cuerpoY[MAX_CUERPO];
    int longitud;
    Direccion direccion;

public:
    Gusano(int inicioX, int inicioY);
    void reiniciar(int inicioX, int inicioY);
    void cambiarDireccion(char tecla);
    void mover();
    void crecer();
    bool colisionaConCuerpo() const;
    int getX() const;
    int getY() const;
    int getLongitud() const;
    int getCuerpoX(int indice) const;
    int getCuerpoY(int indice) const;
    Direccion getDireccion() const;
};

#endif
