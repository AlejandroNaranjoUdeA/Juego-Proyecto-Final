#include "fisicas.h"


fisicas::fisicas( int x, int y, int w, int h, QGraphicsPixmapItem *item)
    : x_dimension(4), y_dimension(4), w(w), h(h), item(item) {
    set_initial_conditions(x, y, 10, 5);

    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &fisicas::time_step);
    time->start(100); // Suponiendo 100 ms como el tiempo del período
}

void fisicas::set_movement_type(QString type) {
    this->type = type;
    if (type == "parabolic") {
        float initial_vx = 15;
        float initial_vy = 15;
        set_initial_conditions(item->x(), item->y(), initial_vx, initial_vy);
    } else if (type == "MRU") {
        set_initial_conditions(item->x(), item->y(), 5, 0);
    }
}


float fisicas::get_phisical_x(float x) {
    return x_dimension * x / w;
}

float fisicas::get_phisical_y(float y) {
    return y_dimension - y_dimension * y / h;
}

float fisicas::get_simulated_x(float x) {
    return w * x / x_dimension;
}

float fisicas::get_simulated_y(float y) {
    return h * (y_dimension - y) / y_dimension;
}

void fisicas::calculate_cinematics(float ax, float ay) {
    x += vx * time_period / 1000.0;
    y += vy * time_period / 1000.0;
    vx += ax * time_period / 1000.0;
    vy += ay * time_period / 1000.0;

    item->setPos(get_simulated_x(x), get_simulated_y(y));
}

void fisicas::calculate_parabolic_dynamics() {
    float ay = -9.8;
    calculate_cinematics(0, ay);
}

void fisicas::calculate_MRU_dynamics() {
    calculate_cinematics(0, 0);
}

void fisicas::set_initial_conditions(float x, float y, float vx, float vy) {
    this->x = get_phisical_x(x);
    this->y = get_phisical_y(y);
    this->vx = vx;
    this->vy = vy;
}

void fisicas::time_step() {
    if(type == "parabolic") calculate_parabolic_dynamics();
    else if(type == "MRU") calculate_MRU_dynamics();


}
