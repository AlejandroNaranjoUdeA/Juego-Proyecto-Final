#ifndef CANON_H
#define CANON_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"


#define canon_pixel_x_size 25
#define canon_pixel_y_size 25
#define canon_speed 8


class canon : public QObject, public QGraphicsPixmapItem
{

signals:
    void apunto_diparo(); // Declaración de la señal
    void is_moving(QGraphicsPixmapItem *,bool);


private slots:
    void senal(); // Declaración del slot

public:
    canon(unsigned int scale);
    void set_keys(unsigned int *keys);
    void move(unsigned int key, bool is_valid);
    ~canon();

private:
    QRect set_complete_sprites();
    void set_animations();
    sprites *pixmap_management;
    unsigned int keys[4];
};

#endif // CANON_H
