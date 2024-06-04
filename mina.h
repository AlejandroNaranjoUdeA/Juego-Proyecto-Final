#ifndef MINA_H
#define MINA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprites.h"

#define mina_pixel_x_size 16
#define mina_pixel_y_size 16


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

    //para las fisicas del movimiento circular:
    QTimer *timer;
    float angle;
    float radius;
    float centerX, centerY;
    float speed;
};

#endif // MINA_H
