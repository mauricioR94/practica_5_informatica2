#ifndef PARTICULA_H
#define PARTICULA_H

#include <cmath>
#include <fstream>
using namespace std;

class Particula {
private:
    double x, y;
    double velX, velY;
    double masa;         // NUEVO
    double radio;        // NUEVO
    double g;
    double tiempoX, tiempoY;
    double ang;
    int dir;
    bool colX;

public:
    // Constructor actualizado: recibe masa y radio
    Particula(double xIn, double yIn, double velIn, double angIn,
              double gravedad, double masa, double radio);

    // Métodos existentes
    void actualizarPosicion(double dt, double ancho, double alto,
                            ofstream &archivo);
    void actualizarValores(double xIn, double yIn);
    bool estaQuieto() const;

    // NUEVOS: colisión entre partículas
    bool colisionaCon(const Particula& otra) const;
    void fusionarCon(Particula& otra);

    // NUEVOS: getters (solo lectura, por eso son const)
    double getX()     const;
    double getY()     const;
    double getMasa()  const;
    double getRadio() const;
    double getVelX()  const;
    double getVelY()  const;
};

#endif
