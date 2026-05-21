#include <cmath>
#include "Particula.h"

// CONSTRUCTOR
Particula::Particula(double xIn, double yIn, double velIn, double angIn,
                     double gravedad, double masa, double radio) {
    x = xIn;
    y = yIn;
    g = gravedad;
    this->masa  = masa;    // "this->" porque el parámetro se llama igual
    this->radio = radio;   // que el atributo privado
    tiempoX = 0;
    tiempoY = 0;
    ang  = angIn;
    dir  = 1;
    colX = true;

    velX = velIn * cos(ang * (M_PI / 180));
    velY = velIn * sin(ang * (M_PI / 180));
}

void Particula::actualizarPosicion(double dt, double ancho, double alto, ofstream &archivo){
    // Calcular nuevas posiciones
    double xNuevo = x + velX * tiempoX * dir;
    double yNuevo = y - (velY * tiempoY - 0.5 * g * tiempoY * tiempoY);

    // Guardar en archivo
    archivo << xNuevo << " " << yNuevo << " "<< velX << " " << velY << "\n";

    // Verificar colisiones horizontales (PARED DERECHA)
    if (xNuevo > ancho || xNuevo < 0) {
        colX = true;
        actualizarValores(xNuevo, yNuevo);
    }


    // Verificar colisiones verticales (rebote en suelo)
    if (yNuevo > alto || yNuevo < 0) {
        yNuevo = (yNuevo > alto) ? alto : 0;
        colX = false;
        actualizarValores(xNuevo, yNuevo);
        velY *= 0.7;
        if (fabs(velY) < 1.0)
            velY = 0;
    }

    tiempoX += dt;
    tiempoY += dt;
}

void Particula::actualizarValores(double xIn, double yIn) {
    if (colX) {
        dir *= -1;
        x = xIn;
        tiempoX = 0;
    } else {
        x = xIn;
        y = yIn;

        /*calcula el ángulo actual del vector velocidad,
          y el signo negativo lo invierte para simular
          el rebote.*/
        ang = -atan2(velY, velX) * 180 / M_PI;
        tiempoY = 0;
        tiempoX = 0;
    }
}

bool Particula::estaQuieto() const{
    return (velY == 0);
}

//para que exixta colision (distancia_entre_centros  <=  radio1 + radio2)
bool Particula::colisionaCon(const Particula& otra) const {
    double dx       = this->x - otra.x;
    double dy       = this->y - otra.y;
    double distancia = sqrt(dx*dx + dy*dy);

    return distancia <= (this->radio + otra.radio);
}

void Particula::fusionarCon(Particula& otra) {
    double masaTotal = this->masa + otra.masa;

    // Conservación de momento: nueva velocidad ponderada por masa
    double nuevaVelX = (this->masa * this->velX + otra.masa * otra.velX)
                       / masaTotal;
    double nuevaVelY = (this->masa * this->velY + otra.masa * otra.velY)
                       / masaTotal;

    // La partícula actual absorbe a la otra
    this->velX  = nuevaVelX;
    this->velY  = nuevaVelY;
    this->masa  = masaTotal;
    this->radio = sqrt(this->radio * this->radio
                       + otra.radio * otra.radio);

}

// getters
double Particula::getX()const {
    return x;
}
double Particula::getY() const {
    return y;
}
double Particula::getMasa()  const {
    return masa;
}
double Particula::getRadio() const {
    return radio;
}
double Particula::getVelX()  const {
    return velX;
}
double Particula::getVelY()  const {
    return velY;
}

