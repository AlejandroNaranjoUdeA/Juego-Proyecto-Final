#ifndef MINA_H
#define MINA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprites.h"

#define mina_pixel_x_size 36
#define mina_pixel_y_size 63
#define mina_speed 8

class mina: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    mina(unsigned int scale);
    ~mina();

    void set_initial_conditions(float x, float y, float vx, float vy);
    void apply_physics(float ax, float ay);
    void updatePosition();

public slots:
    void show_explosion_sprites();

signals:
    void collisionDetected();  // Señal para indicar colisión

private:

    void set_animations();
    QRect set_complete_sprites();
    sprites *pixmap_management;
    QTimer *timer;

    float angle;
    float speed;
    float radius;
    float acceleration;
    float friction;
    QPointF velocity;
    int time_period;

    bool exploted;

};

#endif // MINA_H
