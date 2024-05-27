#include "fisicas.h"
#include <QTimer>

fisicas::fisicas(QGraphicsPixmapItem *item): item(item), angle(0), speed(0.05), xAmplitude(3.0), ySpeed(1.5)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &fisicas::updatePosition);
}

fisicas::~fisicas(){
    delete timer;
}

void fisicas::start()
{
    timer->start(16); // Aproximadamente 60 FPS
}

void fisicas::updatePosition()
{
    float x = xAmplitude * std::sin(angle);  // Movimiento sinusoidal en X
    float y = ySpeed;  // Movimiento constante hacia abajo

    item->setPos(item->x() + x, item->y() + y);

    angle += speed;
    if (angle > 2 * M_PI) { // el angulo no pasa 2pi para evitar desbordamiento y que se reinicie el movimiento
        angle -= 2 * M_PI;  // Reiniciar el ángulo para evitar desbordamiento
    }
}
