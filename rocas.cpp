#include "rocas.h"

rocas::rocas(unsigned int scale) {
    pixmap_management = new sprites(":/rocas.jpg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(rocas_pixel_x_size,
                                       rocas_pixel_y_size);

    //setPixmap();
    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0,rocas_pixel_x_size,rocas_pixel_y_size));

}

rocas::~rocas(){
    delete pixmap_management;
}

void rocas::set_animations(){
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*rocas_pixel_y_size);
    dim.setWidth(3*rocas_pixel_x_size);

    pixmap_management->add_new_animation(dim,3);
}

QRect rocas::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*rocas_pixel_y_size);
    dim.setWidth(3*rocas_pixel_x_size);

    return dim;
}

void rocas::hit()
{
    hitCount++;
}

bool rocas::isDestroyed() const
{
    return hitCount >= maxHits;
}

