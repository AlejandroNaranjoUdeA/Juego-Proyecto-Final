#include "enemigos.h"


enemigos::enemigos(unsigned int scale): angle(0), speed(0.05), xAmplitude(3.0)
{
    pixmap_management = new sprites(":/barcos.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(enemy_pixel_x_size,
                                       enemy_pixel_y_size);
    //setPixmap();
    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0,enemy_pixel_x_size,enemy_pixel_y_size));

    /*timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &enemigos::updatePosicion);
    timer->start(16); // Aproximadamente 60 FPS
*/

}

enemigos::~enemigos()
{
    delete pixmap_management;
    delete timer;

}

void enemigos::updatePosicion()
{
    float x = xAmplitude * std::sin(angle);  // Movimiento sinusoidal en X
    float y = enemy_speed;  // Movimiento constante hacia abajo

    setPos(this->x() + x, this->y() + y);

    angle += speed;
    if (angle > 2 * M_PI) { // El ángulo no pasa 2pi para evitar desbordamiento y que se reinicie el movimiento
        angle -= 2 * M_PI;  // Reiniciar el ángulo para evitar desbordamiento
    }
}

QRect enemigos::set_complete_sprites()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(4*enemy_pixel_y_size);
    dim.setWidth(6*enemy_pixel_x_size);

    return dim;

}

void enemigos::set_animations()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1*enemy_pixel_y_size);
    dim.setWidth(6*enemy_pixel_x_size);

    pixmap_management->add_new_animation(dim,6);
}


