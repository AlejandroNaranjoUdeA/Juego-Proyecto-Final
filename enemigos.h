#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <Qtimer>
#include <cmath>
#include "sprites.h"

#define enemy_pixel_x_size 31
#define enemy_pixel_y_size 31
#define enemy_speed 1.5

class enemigos: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enemigos(unsigned int scale);
    ~enemigos();
    void set_initial_conditions(float x, float y, float vx, float vy);

private slots:
    void updatePosicion();

private:
    QRect set_complete_sprites();
    void set_animations();
    sprites *pixmap_management;
    QTimer *timer;
    void apply_physics(float ax, float ay);
    float angle;
    float speed;
    float xAmplitude;
    float ySpeed;
    float acceleration;
    float friction;
    QPointF velocity;
    float time_period;
};
#endif // ENEMIGOS_H
