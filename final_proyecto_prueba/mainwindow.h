#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "regla_juego.h"
#include <QKeyEvent>

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
    Ui::ventanas *ui;
    regla_juego *game;

    void setup_game_rules();

private slots:
    void set_mainwindow();
};
#endif // MAINWINDOW_H
