#include <iostream>
#include <fstream>
#include "Particula.h"

using namespace std;

int main() {
    // Archivo para guardar posiciones
    ofstream archivo("trayectoria_particula.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." <<endl;
        return 1;
    }

    // Parámetros iniciales
    double xIn = 50;
    double yIn = 250;
    double velIn = 100;
    double ang = 65;
    double g = 9.81;

    double masa  = 1.0;   // NUEVO
    double radio = 10.0;  // NUEVO (en píxeles)

    // Dimensiones (como límites de la “escena”)
    double ancho = 900;
    double alto = 700;

    // Crear la partícula
    Particula p(xIn, yIn, velIn, ang, g,masa, radio);

    double dt = 0.1;

    // Simulación
    while (!p.estaQuieto()) {
        p.actualizarPosicion(dt, ancho, alto, archivo);
    }

    archivo.close();
    cout << "Simulación completada. Datos guardados en trayectoria_particula.txt\n";
    return 0;
}
