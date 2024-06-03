#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "regla_juego.h"
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class ventanas; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsView *graph;
    QGraphicsScene *scene;

    Ui::ventanas *ui;
    regla_juego *game;

    //juego:
    QWidget *gameWindow1;
    //menu:
    QWidget *gameWindow2;
    //registro:
    QWidget *gameWindow3;

    //niveles del juego:
    QWidget *gameWindow4;

    QTimer *timer; //se declara el temporizador para las ventanas de los niveles


    void setup_game_rules();

private slots:
    void set_mainwindow();
    void jugar_oprimir(); //funcion para el boton jugar
    void registrarse_oprimir(); //funcion para el boton registrarse
    void iniciar_secion();
    void login();
    void showGameWindow1(); // Slot para cambiar a gameWindow1 después de 5 segundos
    void showGameWindowAfterLogin(); // Slot para manejar la lógica de transición después del login


signals:
    void game_scene_changed();
};
#endif // MAINWINDOW_H
