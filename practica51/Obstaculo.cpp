#include "obstaculo.h"

Obstaculo::Obstaculo(double x, double y, double ancho, double alto, double e) {
    this->x     = x;
    this->y     = y;
    this->ancho = ancho;
    this->alto  = alto;
    this->e     = e;
}
bool Obstaculo::detectarColision(const Particula& p) const {
    // Bordes del obstáculo
    double obsIzq = x;
    double obsDer = x + ancho;
    double obsSup = y;
    double obsInf = y + alto;

    // Bordes de la partícula
    double pIzq = p.getX() - p.getRadio();
    double pDer = p.getX() + p.getRadio();
    double pSup = p.getY() - p.getRadio();
    double pInf = p.getY() + p.getRadio();

    // sobreposiicion con la caja
    bool solapaX = pDer > obsIzq && pIzq < obsDer;
    bool solapaY = pInf > obsSup && pSup < obsInf;

    return solapaX && solapaY;
}
void Obstaculo::resolverColision(Particula& p) const {


    double overlapIzq = (p.getX() + p.getRadio()) - x;
    double overlapDer = (x + ancho) - (p.getX() - p.getRadio());
    double overlapSup = (p.getY() + p.getRadio()) - y;
    double overlapInf = (y + alto)  - (p.getY() - p.getRadio());

    double minOverlap = overlapIzq;
    int cara = 0;  // 0=izq, 1=der, 2=sup, 3=inf

    if (overlapDer < minOverlap) { minOverlap = overlapDer; cara = 1; }
    if (overlapSup < minOverlap) { minOverlap = overlapSup; cara = 2; }
    if (overlapInf < minOverlap) { minOverlap = overlapInf; cara = 3; }

    // cual cara fue impactada
    if (cara == 0 || cara == 1) {
        // vertical
        p.setVelX(-e * p.getVelX());
    } else {
        // horizontal
        p.setVelY(-e * p.getVelY());
    }
}
