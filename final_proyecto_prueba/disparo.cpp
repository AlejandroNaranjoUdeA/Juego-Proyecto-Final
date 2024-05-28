#include "disparo.h"
#include "rocas.h"
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

disparo::disparo(unsigned int scale, int x, int y, int w, int h)
{
    pixmap_management = new sprites(":/bala.jpeg",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(disparo_pixel_x_size,
                                       disparo_pixel_y_size);
    //setPixmap();
    set_animations();

    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0));

    //move parabolico

    x_dimension = 4;
    y_dimension = 4;
    this->w = w;
    this->h = h;
    set_initial_conditions(x, y, 15, 10); // Valores iniciales
    time_period = 100; // Tiempo en ms

    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &disparo::time_step);
    time->start(time_period);

}

disparo::~disparo(){
    delete pixmap_management;
    delete time;
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


void disparo::set_initial_conditions(float x, float y, float vx, float vy) {
    this->x = get_phisical_x(x);
    this->y = get_phisical_y(y);
    this->vx = vx;
    this->vy = vy;
}
float disparo::get_phisical_x(float x) {
    return x_dimension * x / w;
}

float disparo::get_phisical_y(float y) {
    return y_dimension - y_dimension * y / h;
}

void disparo::time_step() {
    // Movimiento parabólico
    float ax = 0;
    float ay = -9.8;

    x += vx * time_period / 1000.0;
    y += vy * time_period / 1000.0;
    vx += ax * time_period / 1000.0;
    vy += ay * time_period / 1000.0;

    // Actualiza la posición de la bala
    setPos(w * x / x_dimension, h * (y_dimension - y) / y_dimension);
}
