#include "simulacion.h"
#include <iostream>
int main() {
    ofstream archivo("trayectoria_particula.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // dt más pequeño para evitar tunneling
    Simulacion sim(900, 700, 0.1);

    // Partículas
    sim.agregarParticula(Particula(50,  250, 50, 45,  9.81, 2.0, 10));
    sim.agregarParticula(Particula(100, 300, 50,  45,  9.81, 2.0, 10));
    sim.agregarParticula(Particula(200, 50,  50, 45,  9.81, 2.0, 10 ));
    sim.agregarParticula(Particula(800, 200, 50,  45, 9.81, 2.0, 10));

    // Obstáculos más grandes para evitar tunneling
    sim.agregarObstaculo(Obstaculo(60,  480, 120, 120, 0.6));
    sim.agregarObstaculo(Obstaculo(250, 380, 120, 120, 0.6));
    sim.agregarObstaculo(Obstaculo(450, 330, 120, 120, 0.6));
    sim.agregarObstaculo(Obstaculo(650, 430, 120, 120, 0.6));

    sim.ejecutar(archivo);

    archivo.close();
    cout << "Simulación completada.\n";
    return 0;
}
