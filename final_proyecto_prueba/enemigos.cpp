#include "enemigos.h"

enemigos::enemigos(unsigned int scale)
    : angle(0), speed(0.05), xAmplitude(3.0), ySpeed(1.5) {

    pixmap_management = new sprites(":/boats.jpg", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(enemy_pixel_x_size, enemy_pixel_y_size);
    set_animations();

    setX(500); // ubicar el barco enemigo en la parte superior derecha
    setY(0);
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0, enemy_pixel_x_size,enemy_pixel_y_size));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &enemigos::updatePosition);
    timer->start(16); // Aproximadamente 60 FPS
}

enemigos::~enemigos() {
    delete pixmap_management;
    delete timer;
}

QRect enemigos::set_complete_sprites() {
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(7 * enemy_pixel_y_size);
    dim.setWidth(4 * enemy_pixel_x_size);
    return dim;
}

void enemigos::set_animations() {
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * enemy_pixel_y_size);
    dim.setWidth(4 * enemy_pixel_x_size);
    pixmap_management->add_new_animation(dim, 4);
}

void enemigos::updatePosition() {
    float x = xAmplitude * std::sin(angle);  // Movimiento sinusoidal en X
    float y = ySpeed;  // Movimiento constante hacia abajo

    setPos(this->x() + x, this->y() + y);

    angle += speed;
    if (angle > 2 * M_PI) { // El ángulo no pasa 2pi para evitar desbordamiento y que se reinicie el movimiento
        angle -= 2 * M_PI;  // Reiniciar el ángulo para evitar desbordamiento
    }
}

