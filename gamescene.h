#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <vector>
#include "particula.h"
#include "obstaculo.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);
    ~GameScene();

    void disparar(double angulo, double velocidad);
    int  getTurnoActual()  const;
    bool hayTiroEnVuelo()  const;

signals:
    void turnoTerminado(int nuevoTurno);
    void juegoTerminado(QString ganador);

private slots:
    void actualizarFrame();

private:
    // Lógica
    Particula              *particulaActual;
    std::vector<Obstaculo>  obstaculosJ1;  // base jugador 1
    std::vector<Obstaculo>  obstaculosJ2;  // base jugador 2

    // Visual — obstáculos
    std::vector<QGraphicsRectItem*>  itemsJ1;
    std::vector<QGraphicsRectItem*>  itemsJ2;
    std::vector<QGraphicsTextItem*>  labelsJ1;
    std::vector<QGraphicsTextItem*>  labelsJ2;

    // Visual — proyectil
    QGraphicsEllipseItem *itemParticula;

    // Visual — jugadores (rivales)

    QGraphicsPixmapItem *rivalJ1;
    QGraphicsPixmapItem *rivalJ2;

    // Visual — cañones
    QGraphicsRectItem *canonJ1;
    QGraphicsRectItem *canonJ2;

    // Etiqueta turno
    QGraphicsTextItem *lblTurnoScene;

    // Control
    QTimer  *timer;
    int      turnoActual;
    bool     proyectilEnVuelo;

    // Dimensiones
    const double ANCHO = 900;
    const double ALTO  = 600;
    const double dt    = 0.05;

    // Factor de daño
    const double FACTOR_DANIO = 0.1;

    // Métodos privados
    void inicializarEscena();
    void dibujarBaseJugador1();
    void dibujarBaseJugador2();
    void dibujarCanones();
    void verificarColisiones();
    void verificarFinTurno();
    void cambiarTurno();
    void actualizarLabelsResistencia();
    void aplicarDanio(std::vector<Obstaculo>& obstaculos,
                      std::vector<QGraphicsRectItem*>& items,
                      std::vector<QGraphicsTextItem*>& labels);
};

#endif
