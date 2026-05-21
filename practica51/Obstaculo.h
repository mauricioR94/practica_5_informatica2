#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "particula.h"

class Obstaculo {
private:
    double x, y;
    double ancho, alto;
    double e;

public:
    Obstaculo(double x, double y, double ancho, double alto, double e);
    bool detectarColision(const Particula& p) const;
    void resolverColision(Particula& p) const;
    double getX()     const;
    double getY()     const;
    double getAncho() const;
    double getAlto()  const;
};

#endif
