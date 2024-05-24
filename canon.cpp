#include "canon.h"

canon::canon(unsigned int scale) {
    pixmap_management = new sprites(":/canon1.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(canon_pixel_x_size,
                                       canon_pixel_y_size);
    //setPixmap();
    set_animations();

    setX(0);
    setY(0);
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

}

void canon::set_keys(unsigned int *keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = keys[i];
}

void canon::move(unsigned int key)
{
    if(key == keys[0]){
        setPixmap(pixmap_management->get_current_pixmap(0));
        setY(y()-canon_speed);
    }
    else if(key == keys[1]){
        setPixmap(pixmap_management->get_current_pixmap(0));
        setY(y()+canon_speed);
    }

}

canon::~canon()
{
    delete pixmap_management;
}

QRect canon::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*canon_pixel_y_size);
    dim.setWidth(1*canon_pixel_x_size);

    return dim;
}


void canon::set_animations()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*canon_pixel_y_size);
    dim.setWidth(1*canon_pixel_x_size);

    pixmap_management->add_new_animation(dim,0);
}

