#include "mina.h"

mina::mina(unsigned int scale): angle(0), radius(100), centerX(280), centerY(300), speed(0.05)
{
    pixmap_management = new sprites(":/mina.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(mina_pixel_x_size,
                                       mina_pixel_y_size);

    set_animations();

    setX(centerX + radius * cos(angle));
    setY(centerY + radius * sin(angle));
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0,mina_pixel_x_size,mina_pixel_y_size));


    // Configurar el temporizador para actualizar la posición
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mina::updatePosition);
    timer->start(16); // Aproximadamente 60 FPS
}

mina::~mina(){
    delete pixmap_management;
    delete timer;
}


void mina::set_animations(){
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*mina_pixel_y_size);
    dim.setWidth(4*mina_pixel_x_size);

    pixmap_management->add_new_animation(dim,4);
}

QRect mina::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*mina_pixel_y_size);
    dim.setWidth(1*mina_pixel_x_size);

    return dim;
}

void mina::updatePosition() {
    angle += speed;
    if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    float x = centerX + radius * cos(angle);
    float y = centerY + radius * sin(angle);
    setPos(x, y);
}
