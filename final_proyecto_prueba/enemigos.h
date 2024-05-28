#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprites.h"

#define enemy_pixel_x_size 31
#define enemy_pixel_y_size 31
#define enemy_speed 8

class enemigos : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    enemigos(unsigned int scale);
    ~enemigos();
    void move(unsigned int key);

private slots:
    void updatePosition();

private:
    QRect set_complete_sprites();
    void set_animations();
    sprites *pixmap_management;
    QTimer *timer;
    float angle;
    float speed;
    float xAmplitude; // Amplitud del movimiento horizontal
    float ySpeed; // Velocidad del descenso
};

#endif // ENEMIGOS_H
