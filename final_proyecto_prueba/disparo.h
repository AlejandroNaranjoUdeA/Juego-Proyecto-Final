#ifndef DISPARO_H
#define DISPARO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sprites.h"


#define disparo_pixel_x_size 16
#define disparo_pixel_y_size 16
#define disparo_speed 8

class disparo: public QObject, public QGraphicsPixmapItem
{
public:
    disparo(unsigned int scale, int x, int y, int w, int h);
    ~disparo();

private:
    QRect set_complete_sprites();
    void set_animations();
    sprites *pixmap_management;

    QTimer *time;
    float x, y, vx, vy;
    float time_period; // Tiempo en ms
    int x_dimension, y_dimension;
    int w, h;
    void set_initial_conditions(float x, float y, float vx, float vy);
    float get_phisical_x(float x);
    float get_phisical_y(float y);
    QString type;

private slots:
    void time_step();

};

#endif // DISPARO_H
