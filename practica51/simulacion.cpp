#include "simulacion.h"
#include <cmath>

Simulacion::Simulacion(double ancho, double alto, double dt) {
    this->ancho = ancho;
    this->alto  = alto;
    this->dt    = dt;
}

void Simulacion::agregarParticula(const Particula& p) {
    particulas.push_back(p);
}

void Simulacion::agregarObstaculo(const Obstaculo& o) {
    obstaculos.push_back(o);
}

bool Simulacion::todasQuietas() const {
    for (const Particula& p : particulas) {
        if (!p.estaQuieto()) return false;
    }
    return true;
}

// CORREGIDO: maneja las 4 paredes correctamente
// Suelo con fricción horizontal para que velX
// también llegue a cero y la simulación termine
void Simulacion::colisionParedes(Particula& p) {
    // Pared derecha
    if (p.getX() + p.getRadio() > ancho) {
        p.setVelX(-p.getVelX());
    }
    // Pared izquierda
    if (p.getX() - p.getRadio() < 0) {
        p.setVelX(-p.getVelX());
    }
    // Suelo: inelástico + fricción horizontal
    if (p.getY() + p.getRadio() > alto) {
        p.setVelY(-p.getVelY() * 0.7);
        if (fabs(p.getVelY()) < 0.5) {
            p.setVelY(0);
            // Fricción: reduce velX cada vez que toca el suelo
            p.setVelX(p.getVelX() * 0.85);
            if (fabs(p.getVelX()) < 0.5)
                p.setVelX(0);
        }
    }
    // Techo: perfectamente elástico
    if (p.getY() - p.getRadio() < 0) {
        p.setVelY(-p.getVelY());
    }
}

void Simulacion::verificarColisionesObstaculos(Particula& p) {
    for (Obstaculo& o : obstaculos) {
        if (o.detectarColision(p)) {
            o.resolverColision(p);
        }
    }
}

void Simulacion::verificarColisionesParticulas(ofstream& archivo) {
    for (int i = 0; i < (int)particulas.size(); i++) {
        for (int j = i + 1; j < (int)particulas.size(); j++) {
            if (particulas[i].colisionaCon(particulas[j])) {

                archivo << "COLISION entre particula " << i
                        << " y particula " << j << "\n";

                particulas[i].fusionarCon(particulas[j]);
                particulas.erase(particulas.begin() + j);
                j--;
            }
        }
    }
}

// CORREGIDO: agregado límite de pasos como protección
// para evitar que la simulación corra indefinidamente
void Simulacion::ejecutar(ofstream& archivo) {
    int pasoMaximo = 100000;
    int paso       = 0;

    while (!todasQuietas() && paso < pasoMaximo) {
        paso++;

        for (int i = 0; i < (int)particulas.size(); i++) {
            archivo << "P" << i << " "
                    << particulas[i].getX() << " "
                    << particulas[i].getY() << "\n";

            particulas[i].actualizarPosicion(dt);
            colisionParedes(particulas[i]);
            verificarColisionesObstaculos(particulas[i]);
        }

        verificarColisionesParticulas(archivo);
    }

    // Informar si se llegó al límite
    if (paso == pasoMaximo)
        archivo << "LIMITE DE PASOS ALCANZADO\n";
}
