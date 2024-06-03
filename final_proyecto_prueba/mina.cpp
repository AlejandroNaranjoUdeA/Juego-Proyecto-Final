#include "mina.h"

mina::mina(unsigned int scale): position(280, 300), velocity(0, 0), angularVelocity(0.05), acceleration(0.001), tangentialForce(0.2)
{
    pixmap_management = new sprites(":/mina.png",scale);
                        pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(mina_pixel_x_size,
                                       mina_pixel_y_size);
    //setPixmap();
    set_animations();

    setX(280);
    setY(300);
    setZValue(1);
    setPixmap(pixmap_management->get_current_pixmap(0, mina_pixel_x_size,mina_pixel_y_size));
    //setPixmap(pixmap_management->get_current_pixmap(0));

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
    // Actualizar la velocidad angular y aplicar aceleración
    angularVelocity += acceleration;

    // Calcular la componente tangencial de la fuerza
    float tangentialComponent = tangentialForce;

    // Calcular la componente radial de la fuerza
    float radialComponent = 0;  // No hay componente radial en este ejemplo

    // Calcular la fuerza resultante
    QPointF force(tangentialComponent, radialComponent);

    // Aplicar la fuerza a la velocidad
    velocity += force;

    // Calcular la nueva posición usando la velocidad
    position += velocity;

    setPos(position);
}

