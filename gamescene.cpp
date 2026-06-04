#include "gamescene.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <cmath>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent) {
    turnoActual      = 1;
    proyectilEnVuelo = false;
    particulaActual  = nullptr;
    itemParticula    = nullptr;

    setSceneRect(0, 0, ANCHO, ALTO);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this,  &GameScene::actualizarFrame);

    inicializarEscena();
}

GameScene::~GameScene() {
    delete particulaActual;
}

void GameScene::inicializarEscena() {
    setBackgroundBrush(QBrush(QColor(200, 220, 255)));

    // Suelo
    addRect(0, ALTO - 40, ANCHO, 40,
            QPen(Qt::NoPen),
            QBrush(QColor(100, 180, 100)));

    // Borde de la caja
    addRect(0, 0, ANCHO, ALTO,
            QPen(Qt::black, 3),
            QBrush(Qt::transparent));

    dibujarBaseJugador1();
    dibujarBaseJugador2();
    dibujarCanones();

    // Etiqueta turno
    lblTurnoScene = new QGraphicsTextItem("Turno: Jugador 1");
    lblTurnoScene->setPos(ANCHO/2 - 80, 10);
    lblTurnoScene->setDefaultTextColor(Qt::darkBlue);
    QFont fontTurno;
    fontTurno.setBold(true);
    fontTurno.setPointSize(12);
    lblTurnoScene->setFont(fontTurno);
    addItem(lblTurnoScene);
}

void GameScene::dibujarBaseJugador1() {
    double baseX = 30;
    double baseY = ALTO - 230;

    // Obstáculo superior (resistencia 100)
    obstaculosJ1.push_back(Obstaculo(baseX, baseY, 220, 50, 0.6, 100));

    // Obstáculo lateral izquierdo (resistencia 200)
    obstaculosJ1.push_back(Obstaculo(baseX, baseY + 50, 70, 140, 0.6, 200));

    // Obstáculo lateral derecho (resistencia 200)
    obstaculosJ1.push_back(Obstaculo(baseX + 150, baseY + 50, 70, 140, 0.6, 200));

    for (int i = 0; i < (int)obstaculosJ1.size(); i++) {
        Obstaculo& o = obstaculosJ1[i];

        QGraphicsRectItem *item = addRect(
            o.getX(), o.getY(),
            o.getAncho(), o.getAlto(),
            QPen(Qt::darkGray, 2),
            QBrush(QColor(210, 180, 140))
            );
        itemsJ1.push_back(item);

        QGraphicsTextItem *lbl = new QGraphicsTextItem(
            QString::number((int)o.getResistencia())
            );
        lbl->setPos(
            o.getX() + o.getAncho()/2 - 15,
            o.getY() + o.getAlto()/2 - 10
            );
        lbl->setDefaultTextColor(Qt::black);
        QFont f; f.setBold(true); f.setPointSize(10);
        lbl->setFont(f);
        addItem(lbl);
        labelsJ1.push_back(lbl);
    }

    // Sprite J1 — centrado entre los dos laterales
    QPixmap sprite(":/imagenes/petrosqui.PNG");
    sprite = sprite.scaled(70, 130, Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    rivalJ1 = new QGraphicsPixmapItem(sprite);
    // Centrado: entre lateral izq (baseX+70) y lateral der (baseX+150)
    // espacio disponible = 80px, sprite = 70px → centrado en baseX + 75
    rivalJ1->setPos(baseX + 75, baseY + 55);
    addItem(rivalJ1);
}

void GameScene::dibujarBaseJugador2() {
    double baseX = ANCHO - 250;
    double baseY = ALTO - 230;

    // Obstáculo superior (resistencia 100)
    obstaculosJ2.push_back(Obstaculo(baseX, baseY, 220, 50, 0.6, 100));

    // Obstáculo lateral izquierdo (resistencia 200)
    obstaculosJ2.push_back(Obstaculo(baseX, baseY + 50, 70, 140, 0.6, 200));

    // Obstáculo lateral derecho (resistencia 200)
    obstaculosJ2.push_back(Obstaculo(baseX + 150, baseY + 50, 70, 140, 0.6, 200));

    for (int i = 0; i < (int)obstaculosJ2.size(); i++) {
        Obstaculo& o = obstaculosJ2[i];

        QGraphicsRectItem *item = addRect(
            o.getX(), o.getY(),
            o.getAncho(), o.getAlto(),
            QPen(Qt::darkGray, 2),
            QBrush(QColor(210, 180, 140))
            );
        itemsJ2.push_back(item);

        QGraphicsTextItem *lbl = new QGraphicsTextItem(
            QString::number((int)o.getResistencia())
            );
        lbl->setPos(
            o.getX() + o.getAncho()/2 - 15,
            o.getY() + o.getAlto()/2 - 10
            );
        lbl->setDefaultTextColor(Qt::black);
        QFont f; f.setBold(true); f.setPointSize(10);
        lbl->setFont(f);
        addItem(lbl);
        labelsJ2.push_back(lbl);
    }

    // Sprite J2 — tigre centrado entre laterales
    QPixmap sprite2(":/imagenes/tigreSinFondo.png");
    sprite2 = sprite2.scaled(70, 130, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    rivalJ2 = new QGraphicsPixmapItem(sprite2);
    rivalJ2->setPos(baseX + 75, baseY + 55);
    addItem(rivalJ2);
}

void GameScene::dibujarCanones() {
    canonJ1 = addRect(
        10, 10, 50, 30,
        QPen(Qt::black, 2),
        QBrush(Qt::darkGray)
        );

    canonJ2 = addRect(
        ANCHO - 60, 10, 50, 30,
        QPen(Qt::black, 2),
        QBrush(Qt::darkGray)
        );

    QGraphicsTextItem *t1 = new QGraphicsTextItem("J1");
    t1->setPos(20, 12);
    t1->setDefaultTextColor(Qt::white);
    addItem(t1);

    QGraphicsTextItem *t2 = new QGraphicsTextItem("J2");
    t2->setPos(ANCHO - 50, 12);
    t2->setDefaultTextColor(Qt::white);
    addItem(t2);
}

void GameScene::disparar(double angulo, double velocidad) {
    if (itemParticula != nullptr) {
        removeItem(itemParticula);
        delete itemParticula;
        itemParticula = nullptr;
    }
    if (particulaActual != nullptr) {
        delete particulaActual;
        particulaActual = nullptr;
    }

    double xInicio, yInicio;
    if (turnoActual == 1) {
        xInicio = 35;
        yInicio = 30;
    } else {
        xInicio = ANCHO - 35;
        yInicio = 30;
        angulo  = 180 - angulo;
    }

    particulaActual = new Particula(
        xInicio, yInicio,
        velocidad, angulo,
        9.81, 1.0, 8
        );

    itemParticula = new QGraphicsEllipseItem(
        xInicio - 8, yInicio - 8, 16, 16
        );
    itemParticula->setPen(QPen(Qt::darkRed, 1));
    itemParticula->setBrush(QBrush(Qt::red));
    addItem(itemParticula);

    proyectilEnVuelo = true;
    timer->start(16);
}

void GameScene::actualizarFrame() {
    if (!proyectilEnVuelo || particulaActual == nullptr) return;

    particulaActual->actualizarPosicion(dt);
    verificarColisiones();

    double x = particulaActual->getX();
    double y = particulaActual->getY();
    itemParticula->setRect(x - 8, y - 8, 16, 16);

    verificarFinTurno();
}

void GameScene::verificarColisiones() {
    double x     = particulaActual->getX();
    double y     = particulaActual->getY();
    double radio = particulaActual->getRadio();

    if (x + radio > ANCHO) particulaActual->setVelX(-particulaActual->getVelX());
    if (x - radio < 0)     particulaActual->setVelX(-particulaActual->getVelX());
    if (y - radio < 0)     particulaActual->setVelY(-particulaActual->getVelY());

    if (y + radio > ALTO - 40) {
        particulaActual->setVelY(-particulaActual->getVelY() * 0.7);
        if (fabs(particulaActual->getVelY()) < 1.0) {
            proyectilEnVuelo = false;
            timer->stop();
            cambiarTurno();
            return;
        }
    }

    if (turnoActual == 2) {
        aplicarDanio(obstaculosJ1, itemsJ1, labelsJ1);
    }
    if (turnoActual == 1) {
        aplicarDanio(obstaculosJ2, itemsJ2, labelsJ2);
    }
}

void GameScene::aplicarDanio(std::vector<Obstaculo>& obstaculos,
                             std::vector<QGraphicsRectItem*>& items,
                             std::vector<QGraphicsTextItem*>& labels) {
    for (int i = 0; i < (int)obstaculos.size(); i++) {
        Obstaculo& o = obstaculos[i];
        if (o.estaDestruido()) continue;

        if (o.detectarColision(*particulaActual)) {
            double velTotal = sqrt(
                pow(particulaActual->getVelX(), 2) +
                pow(particulaActual->getVelY(), 2)
                );
            double danio = FACTOR_DANIO * particulaActual->getMasa() * velTotal;

            o.recibirDanio(danio);
            o.resolverColision(*particulaActual);

            labels[i]->setPlainText(
                QString::number((int)o.getResistencia())
                );

            if (o.estaDestruido()) {
                items[i]->setBrush(QBrush(QColor(150, 50, 50, 180)));
                labels[i]->setDefaultTextColor(Qt::red);
                labels[i]->setPlainText("X");
            }
        }
    }
}

void GameScene::verificarFinTurno() {
    if (!proyectilEnVuelo) return;
    double x = particulaActual->getX();
    double y = particulaActual->getY();
    if (x < -50 || x > ANCHO + 50 || y > ALTO + 50) {
        proyectilEnVuelo = false;
        timer->stop();
        cambiarTurno();
    }
}

void GameScene::cambiarTurno() {
    turnoActual = (turnoActual == 1) ? 2 : 1;
    lblTurnoScene->setPlainText(
        "Turno: Jugador " + QString::number(turnoActual)
        );
    emit turnoTerminado(turnoActual);
}

int  GameScene::getTurnoActual() const { return turnoActual;      }
bool GameScene::hayTiroEnVuelo() const { return proyectilEnVuelo; }
