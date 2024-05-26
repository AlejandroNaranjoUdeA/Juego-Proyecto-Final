#include "disparo.h"

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

}

disparo::~disparo(){
    delete pixmap_management;
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


