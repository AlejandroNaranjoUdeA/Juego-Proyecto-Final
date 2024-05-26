#include "enemigos.h"

enemigos::enemigos(unsigned int scale)
{
    pixmap_management = new sprites(":/boats.jpg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(enemy_pixel_x_size,
                                       enemy_pixel_y_size);
    //setPixmap();
    set_animations();

    setX(0);
    setY(0);
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));
//    setPixmap(pixmap_management->get_current_pixmap(0));

    fisica = new fisicas(this);
    fisica->start();


}

enemigos::~enemigos(){

    delete pixmap_management;
    delete fisica;
}

QRect enemigos::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(7*enemy_pixel_y_size);
    dim.setWidth(4*enemy_pixel_x_size);

    return dim;

}

void enemigos::set_animations()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*enemy_pixel_y_size);
    dim.setWidth(4*enemy_pixel_x_size);

    pixmap_management->add_new_animation(dim,4);
}
