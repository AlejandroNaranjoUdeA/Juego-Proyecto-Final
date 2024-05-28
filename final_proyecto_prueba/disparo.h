#ifndef DISPARO_H
#define DISPARO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sprites.h"


#define disparo_pixel_x_size 25
#define disparo_pixel_y_size 25
#define diaparo_speed 8

class disparo: public QObject, public QGraphicsPixmapItem
{
public:
    disparo(unsigned int scale);
    ~disparo();

public slots:
    void move();

private:
    QRect set_complete_sprites();
    void set_animations();
    sprites *pixmap_management;
    QTimer *timer;

};

#endif // DISPARO_H
