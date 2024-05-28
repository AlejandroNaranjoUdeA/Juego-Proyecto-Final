#include "disparo.h"
#include "rocas.h"
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

disparo::disparo(unsigned int scale)
{
    pixmap_management = new sprites(":/bala.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(disparo_pixel_x_size,
                                       disparo_pixel_y_size);
    //setPixmap();
    set_animations();

    setX(0);
    setY(0);
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

    // Crea un temporizador para mover el disparo
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &disparo::move);
    timer->start(50); // Mueve el disparo cada 50 ms

}

disparo::~disparo(){
    delete pixmap_management;
    delete timer;
}

QRect disparo::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*disparo_pixel_y_size);
    dim.setWidth(1*disparo_pixel_x_size);

    return dim;
}


void disparo::set_animations()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*disparo_pixel_y_size);
    dim.setWidth(1*disparo_pixel_x_size);

    pixmap_management->add_new_animation(dim,0);
}


void disparo::move()
{
    // Mueve el disparo hacia arriba
    setPos(x(), y() - 10);

    // Verifica colisiones con otros items en la escena
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (auto item : colliding_items)
    {
        // Si el disparo colisiona con una roca
        if (typeid(*item) == typeid(rocas))
        {
            // Remueve ambos objetos de la escena
            scene()->removeItem(this);
            scene()->removeItem(item);

            // Elimina los objetos
            delete this;
            delete item;

            return;
        }
    }
}
