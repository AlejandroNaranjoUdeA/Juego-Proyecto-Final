#ifndef ROCAS_H
#define ROCAS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define rocas_pixel_x_size 16
#define rocas_pixel_y_size 16
#define rocas_speed 8

class rocas: public QObject, public QGraphicsPixmapItem
{
public:
    rocas(unsigned int scale);
    ~rocas();

private:

    void set_animations();
    QRect set_complete_sprites();
    sprites *pixmap_management;
};

#endif // ROCAS_H
