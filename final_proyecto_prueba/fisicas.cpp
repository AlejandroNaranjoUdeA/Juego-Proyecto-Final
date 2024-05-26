#include "fisicas.h"
#include <QTimer>

fisicas::fisicas(QGraphicsPixmapItem *item): item(item), angle(0), speed(0.05), xSpeed(0.5), ySpeed(0.5), xAmplitude(2.0), yAmplitude(5.0)
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
    float x = xAmplitude * std::cos(angle);  // Velocidad horizontal
    float y = ySpeed * std::sin(angle);  // Velocidad vertical
    item->setPos(item->x() + x, item->y() + y);

    angle += speed;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;  // Reiniciar el ángulo para evitar desbordamiento
    }

    // Ajustar la amplitud vertical para que vaya bajando
    yAmplitude += 0.01;  // Puedes ajustar el valor
}
