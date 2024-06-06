#include "enemigos.h"

enemigos::enemigos(unsigned int scale): angle(0), speed(0.05), xAmplitude(2.0), acceleration(0.6), friction(0.95), velocity(0, 0), time_period(16)
{

    pixmap_management = new sprites(":/boats.jpg", scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(enemy_pixel_x_size, enemy_pixel_y_size);

    set_animations();
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
    dim.setHeight(4*enemy_pixel_y_size);
    dim.setWidth(6*enemy_pixel_x_size);

    return dim;
}

void enemigos::set_animations() {
    QRect dim;
    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * enemy_pixel_y_size);
    dim.setWidth(1 * enemy_pixel_x_size);
    pixmap_management->add_new_animation(dim, 4);

    // Animación hacia abajo a la derecha
    dim.setX(3 * enemy_pixel_x_size);
    dim.setY(1 * enemy_pixel_y_size);
    dim.setHeight(1 * enemy_pixel_y_size);
    dim.setWidth(1 * enemy_pixel_x_size);
    pixmap_management->add_new_animation(dim, 1);

    // Animación hacia abajo a la izquierda
    dim.setX(3 * enemy_pixel_x_size);
    dim.setY(0);
    dim.setHeight(1 * enemy_pixel_y_size);
    dim.setWidth(1 * enemy_pixel_x_size);
    pixmap_management->add_new_animation(dim, 1);
}

void enemigos::set_initial_conditions(float x, float y, float vx, float vy)
{
    setPos(x, y);
    velocity.setX(vx);
    velocity.setY(vy);
}

void enemigos::apply_physics(float ax, float ay)
{

    velocity.setX(velocity.x() + ax * time_period / 1000.0);
    velocity.setY(velocity.y() + ay * time_period / 1000.0);
    velocity.setX(velocity.x() * friction);
    velocity.setY(velocity.y() * friction);
    // Actualizar la posición
    setPos(this->x() + velocity.x() * time_period / 1000.0, this->y() + velocity.y() * time_period / 1000.0);
}

void enemigos::updatePosition()
{
    // Movimiento sinusoidal en X
    float x = xAmplitude * std::sin(angle);
    // Aplicar física al movimiento con aceleración en Y
    apply_physics(0, acceleration);
    // Ajustar la posición con el movimiento sinusoidal en X
    setX(this->x() + x);
    setY(this -> y()+ velocity.y());

    // Actualizar sprite dependiendo de la dirección del movimiento
    //update_sprite();

    if(velocity.x() > 0 ){
        setPixmap(pixmap_management->get_current_pixmap(1, enemy_pixel_x_size, enemy_pixel_y_size));
    }
    else if(velocity.x() < 0){
        setPixmap(pixmap_management->get_current_pixmap(2, enemy_pixel_x_size, enemy_pixel_y_size));
    }
    else{
        setPixmap(pixmap_management->get_current_pixmap(0, enemy_pixel_x_size, enemy_pixel_y_size));

    }

    angle += speed;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
}

void enemigos::update_sprite(){

    if(velocity.x() > 0 ){
        setPixmap(pixmap_management->get_current_pixmap(1, enemy_pixel_x_size, enemy_pixel_y_size));
    }
    else if(velocity.x() < 0){
        setPixmap(pixmap_management->get_current_pixmap(2, enemy_pixel_x_size, enemy_pixel_y_size));
    }
    else{
        setPixmap(pixmap_management->get_current_pixmap(0, enemy_pixel_x_size, enemy_pixel_y_size));

    }
}
