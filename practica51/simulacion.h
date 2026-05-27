#ifndef SIMULACION_H
#define SIMULACION_H

#include <vector>
#include <fstream>
#include "particula.h"
#include "obstaculo.h"

using namespace std;

class Simulacion {
private:
    vector<Particula>  particulas;
    vector<Obstaculo>  obstaculos;
    double ancho, alto;
    double dt;

public:
    Simulacion(double ancho, double alto, double dt);

    void agregarParticula(const Particula& p);
    void agregarObstaculo(const Obstaculo& o);

    void ejecutar(ofstream& archivo);

private:
    void colisionParedes(Particula& p);
    void verificarColisionesObstaculos(Particula& p);
    void verificarColisionesParticulas(ofstream& archivo);
    bool todasQuietas() const;
};

#endif
