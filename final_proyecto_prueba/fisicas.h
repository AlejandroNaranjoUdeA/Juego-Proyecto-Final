#ifndef FISICAS_H
#define FISICAS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <cmath> // para la fisica del seno

class fisicas: public QObject
{
    Q_OBJECT
public:
    fisicas(QGraphicsPixmapItem *item);
    ~fisicas();
    void start();

private slots:
    void updatePosition();

private:
    QGraphicsPixmapItem *item;
    QTimer *timer;
    float angle;
    float speed;
    float xSpeed; // Velocidad horizontal
    float ySpeed; // Velocidad vertical
    float xAmplitude; // Amplitud del movimiento horizontal
    float yAmplitude; //Amplitud del movimiento vertical



};

#endif // FISICAS_H


