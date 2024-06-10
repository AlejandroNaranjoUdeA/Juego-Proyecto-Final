#include "mina.h"

mina::mina(unsigned int scale): angle(0), speed(0.05), radius(8), acceleration(0.01), friction(0.98), velocity(0, 0), time_period(16)
{
    pixmap_management = new sprites(":/mina.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(mina_pixel_x_size, mina_pixel_y_size);

    //setPixmap();
    set_animations();
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0, mina_pixel_x_size , mina_pixel_y_size));

    // Configurar el temporizador para actualizar la posición
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mina::updatePosition);
    timer->start(time_period); // Aproximadamente 60 FPS

    /*explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, this, &mina::nextFrame);
    currentFrame = 0;*/
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
    dim.setWidth(1*mina_pixel_x_size);
    pixmap_management->add_new_animation(dim,1);

    //explosion:
    dim.setX(1);
    dim.setY(0);
    dim.setHeight(1*mina_pixel_y_size);
    dim.setWidth(10*mina_pixel_x_size);
    pixmap_management->add_new_animation(dim,10);


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

void mina::startExplosion() {
    if (!exploted) {
        exploted = true;
        currentFrame = 0;
        explosionTimer->start(100); // Cambiar frame cada 100 ms
    }
}

/*void mina::nextFrame() {
    if (currentFrame < pixmap_management-> animations_size[1]) {
        setPixmap(pixmap_management->get_current_pixmap(1, mina_pixel_x_size, mina_pixel_y_size));
        currentFrame++;
    } else {
        explosionTimer->stop();
        setPixmap(pixmap_management->get_current_pixmap(0, mina_pixel_x_size, mina_pixel_y_size)); // Reset a estado inicial o algún otro estado
    }
}*/


void mina::set_initial_conditions(float x, float y, float vx, float vy) {
    setPos(x, y);
    velocity.setX(vx);
    velocity.setY(vy);
}

void mina::apply_physics(float ax, float ay) {
    velocity.setX(velocity.x() + ax * time_period / 1000.0);
    velocity.setY(velocity.y() + ay * time_period / 1000.0);
    velocity.setX(velocity.x() * friction);
    velocity.setY(velocity.y() * friction);
}

void mina::updatePosition() {
    float ax = -speed * std::sin(angle); // Componente tangencial de la aceleración
    float ay = speed * std::cos(angle);  // Componente radial de la aceleración
    apply_physics(ax, ay);

    float x = radius * std::cos(angle);
    float y = radius * std::sin(angle);

    setPos(this->x() + x, this->y() + y);

    angle += speed;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
}
