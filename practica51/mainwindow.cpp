#include "mainwindow.h"

//CONSTRUCTOR

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() {}


// CONSTRUIMOS LA INTERFAZ
void MainWindow::setupUI() {
    setWindowTitle("Práctica 5 — Juego de Partículas");
    setFixedSize(1100, 650);

    // CETRAL WIDGET ES EL LIENZO DONDE SE PINTA LA INTERFAZ
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *layoutPrincipal = new QHBoxLayout(centralWidget);
    layoutPrincipal->setSpacing(10);
    layoutPrincipal->setContentsMargins(5, 5, 5, 5);

    // ── Escena y vista ────────────────────────────
    scene = new GameScene(this);
    view  = new QGraphicsView(scene, centralWidget);
    view->setFixedSize(900, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setTransform(QTransform());

    // ── Panel controles ───────────────────────────
    QWidget     *panelControles  = new QWidget(centralWidget);
    QVBoxLayout *layoutControles = new QVBoxLayout(panelControles);
    panelControles->setFixedWidth(170);
    layoutControles->setSpacing(8);

    lblTurno = new QLabel("Turno: Jugador 1", panelControles);
    lblTurno->setAlignment(Qt::AlignCenter);
    lblTurno->setStyleSheet(
        "font-size: 15px; font-weight: bold; color: blue;"
        );

    lblAngulo    = new QLabel("Ángulo: 45°", panelControles);
    sliderAngulo = new QSlider(Qt::Horizontal, panelControles);
    sliderAngulo->setMinimum(0);
    sliderAngulo->setMaximum(180);
    sliderAngulo->setValue(45);

    lblVelocidad    = new QLabel("Velocidad: 80", panelControles);
    sliderVelocidad = new QSlider(Qt::Horizontal, panelControles);
    sliderVelocidad->setMinimum(10);
    sliderVelocidad->setMaximum(200);
    sliderVelocidad->setValue(80);

    btnDisparar = new QPushButton("¡Disparar!", panelControles);
    btnDisparar->setStyleSheet(
        "QPushButton {"
        "  background-color: #E24B4A;"
        "  color: white;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "  border-radius: 6px;"
        "}"
        "QPushButton:hover { background-color: #c0392b; }"
        "QPushButton:disabled { background-color: #aaaaaa; }"
        );

    layoutControles->addWidget(lblTurno);
    layoutControles->addSpacing(15);
    layoutControles->addWidget(lblAngulo);
    layoutControles->addWidget(sliderAngulo);
    layoutControles->addSpacing(8);
    layoutControles->addWidget(lblVelocidad);
    layoutControles->addWidget(sliderVelocidad);
    layoutControles->addSpacing(20);
    layoutControles->addWidget(btnDisparar);
    layoutControles->addStretch();

    layoutPrincipal->addWidget(view);
    layoutPrincipal->addWidget(panelControles);

    conectarSenales();
}

void MainWindow::conectarSenales() {
    connect(sliderAngulo,    &QSlider::valueChanged,
            this,            &MainWindow::onAnguloChanged);

    connect(sliderVelocidad, &QSlider::valueChanged,
            this,            &MainWindow::onVelocidadChanged);

    connect(btnDisparar,     &QPushButton::clicked,
            this,            &MainWindow::onDisparar);

    // NUEVO: reactivar botón cuando termina el turno
    connect(scene,           &GameScene::turnoTerminado,
            this,            &MainWindow::onTurnoTerminado);
}

void MainWindow::onAnguloChanged(int valor) {
    lblAngulo->setText("Ángulo: " + QString::number(valor) + "°");
}

//SLOTS----- RESPUESTAS A EVENTOS ------------------

void MainWindow::onVelocidadChanged(int valor) {
    lblVelocidad->setText("Velocidad: " + QString::number(valor));
}

void MainWindow::onDisparar() {
    if (scene->hayTiroEnVuelo()) return;

    double angulo    = sliderAngulo->value();
    double velocidad = sliderVelocidad->value();

    scene->disparar(angulo, velocidad);
    btnDisparar->setEnabled(false);
}

// NUEVO: se llama cuando GameScene emite turnoTerminado
void MainWindow::onTurnoTerminado(int turno) {
    lblTurno->setText("Turno: Jugador " + QString::number(turno));
    btnDisparar->setEnabled(true);
}
