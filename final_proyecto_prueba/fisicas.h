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
    float xAmplitude; // Amplitud del movimiento horizontal
    float ySpeed; // Velocidad del descensol

};

#endif // FISICAS_H


