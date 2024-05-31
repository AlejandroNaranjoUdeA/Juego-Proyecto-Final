#ifndef ECENARIO_H
#define ECENARIO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define blocks_pixel_x_size 16
#define blocks_pixel_y_size 16


class ecenario: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ecenario(unsigned int scale, unsigned int type);
    ~ecenario();
    unsigned int get_type();

private:
    sprites *pixmap;
    unsigned int scale, type;
    QRect set_complete_sprites();
    QRect set_borde();
    QRect set_fondo();
    void set_type_block();
};


#endif // ECENARIO_H
