#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "gamescene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDisparar();
    void onAnguloChanged(int valor);
    void onVelocidadChanged(int valor);
    void onTurnoTerminado(int turno);   // NUEVO

private:
    GameScene      *scene;
    QGraphicsView  *view;

    QSlider     *sliderAngulo;
    QSlider     *sliderVelocidad;
    QPushButton *btnDisparar;

    QLabel  *lblAngulo;
    QLabel  *lblVelocidad;
    QLabel  *lblTurno;

    void setupUI();
    void conectarSenales();
};

#endif
