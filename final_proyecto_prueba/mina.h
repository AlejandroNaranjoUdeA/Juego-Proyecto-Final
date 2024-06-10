#ifndef MINA_H
#define MINA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>
#include "sprites.h"

#define mina_pixel_x_size 36
#define mina_pixel_y_size 63

class mina: public QObject, public QGraphicsPixmapItem
{

public:
    mina(unsigned int scale);
    ~mina();

    void set_initial_conditions(float x, float y, float vx, float vy);
    void apply_physics(float ax, float ay);
    void updatePosition();

    void startExplosion();


private:

    QVector<QPixmap> explosionFrames;
    QTimer *explosionTimer;
    int currentFrame;

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


private slots:
    void nextFrame();

};

#endif // MINA_H
