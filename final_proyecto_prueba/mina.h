#ifndef MINA_H
#define MINA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprites.h"

#define mina_pixel_x_size 16
#define mina_pixel_y_size 16
#define mina_speed 8

class mina: public QObject, public QGraphicsPixmapItem
{
public:
    mina(unsigned int scale);
    ~mina();
    void move(unsigned int key);

private slots:
    void updatePosition();

private:

    void set_animations();
    QRect set_complete_sprites();
    sprites *pixmap_management;

    QTimer *timer;

    QPointF position;          // Posición de la mina
    QPointF velocity;          // Velocidad de la mina
    float angularVelocity;     // Velocidad angular
    float acceleration;        // Aceleración angular
    float tangentialForce;     // Fuerza tangencial
};

#endif // MINA_H
