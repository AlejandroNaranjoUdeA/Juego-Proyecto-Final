#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"

#define enemy_pixel_x_size 31
#define enemy_pixel_y_size 31
#define enemy_speed 8

class enemigos: public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public:
    enemigos(unsigned int scale);
    void move(unsigned int key);
    ~enemigos();

private:
    QRect set_complete_sprites();
    void set_animations();
    void set_right_enemy();
    void set_left_enemy();
    void set_diagonalup_enemy();
    void set_diagonaldown_enemy();
    sprites *pixmap_management;
};
#endif // ENEMIGOS_H
