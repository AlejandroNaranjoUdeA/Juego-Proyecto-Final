#include "canon.h"

canon::canon(unsigned int scale) {
    pixmap_management = new sprites(":/canon.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(canon_pixel_x_size,
                                       canon_pixel_y_size);
    //setPixmap();
    set_animations();
    setX(1*scale);
    setY(1*canon_pixel_y_size*scale);

    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0,canon_pixel_x_size,canon_pixel_y_size));

}
canon::~canon()
{
    delete pixmap_management;

}

void canon::set_keys(unsigned int *keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = keys[i];
}


void canon::move(unsigned int key,  bool is_valid)
{
    if (key == keys[0])
    {
        setPixmap(pixmap_management->get_current_pixmap(0, canon_pixel_x_size, canon_pixel_y_size));
        if (is_valid)
        {
            emit is_moving(this, true, true);
            setY(y() - canon_speed);
        }
    }
    else if (key == keys[1])
    {
        setPixmap(pixmap_management->get_current_pixmap(0, canon_pixel_x_size, canon_pixel_y_size));
        if (is_valid)
        {
            setY(y() + canon_speed);
            emit is_moving(this, true, true);
        }
    }
    else if (key == keys[2])
    {
        if (is_valid)
            senal();
    }


}
void canon::senal() {
    emit apunto_diparo();
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



