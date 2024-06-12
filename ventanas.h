#ifndef VENTANAS_H
#define VENTANAS_H

#include <QMainWindow>
#include "regla_juego.h"
#include <QKeyEvent>

#include <QScreen>

#include <QFile>
#include <QTextStream>
#include <QMessageBox> //mostrar mensajes emergentes


QT_BEGIN_NAMESPACE
namespace Ui { class ventanas; }
QT_END_NAMESPACE

class ventanas : public QMainWindow
{
    Q_OBJECT

public:
    ventanas(QWidget *parent = nullptr);
    ~ventanas();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::ventanas *ui;
    regla_juego *game;
    //juego:
    QWidget *gameWindow1;
    //menu:
    QWidget *gameWindow2;
    //registro:
    QWidget *gameWindow3;

    QTimer *timer; //se declara el temporizador para las ventanas de los niveles
    void restartGame();

private slots:
    void set_mainwindow();
    void jugar_oprimir(); //funcion para el boton jugar
    void registrarse_oprimir(); //funcion para el boton registrarse
    void iniciar_secion();
    void login();
    void mostrar_mensaje(bool win);
    void setup_game_rules();
};

#endif // VENTANAS_H



