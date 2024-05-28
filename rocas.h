#ifndef ROCAS_H
#define ROCAS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define rocas_pixel_x_size 31
#define rocas_pixel_y_size 31

class rocas: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    rocas(unsigned int scale);
    ~rocas();

private:
    void set_animations();
    QRect set_complete_sprites();
    sprites *pixmap_management;

};

#endif // ROCAS_H
