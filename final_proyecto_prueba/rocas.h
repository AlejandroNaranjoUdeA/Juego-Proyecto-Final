#ifndef ROCAS_H
#define ROCAS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define rocas_pixel_x_size 16
#define rocas_pixel_y_size 16

class rocas: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    rocas(unsigned int scale);
    ~rocas();
    void hit();
    bool isDestroyed() const;

private:
    void set_animations();
    QRect set_complete_sprites();
    sprites *pixmap_management;
    int hitCount=0;
    const int maxHits = 3;

};

#endif // ROCAS_H
