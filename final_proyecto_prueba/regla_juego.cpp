#include "regla_juego.h"

regla_juego::regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));

    this->graph = graph;
    labels = game_labels;
    setup_scene();
    setup_canon();
    setuo_enemigos();
    setup_rocas();
    setup_minas();

}
regla_juego::~regla_juego()
{
    delete scene;
}

void regla_juego::key_event(QKeyEvent *event)
{
    canones->move(event->key());
}

void regla_juego::setup_canon()
{
    set_canon_keys();

    canones = new canon(game_scale_factor);
    canones->set_keys(bomberman_keys);
    scene->addItem(canones);
    connect(canones, SIGNAL(apunto_diparo()), this, SLOT(setup_disparo()));

}

void regla_juego::setup_minas(){
    minas= new mina(game_scale_factor);
    scene->addItem(minas);
}

void regla_juego::setuo_enemigos(){
    enemy = new enemigos(game_scale_factor);
    scene->addItem(enemy);
}

void regla_juego::setup_rocas(){
    roca = new rocas(game_scale_factor);
    scene->addItem(roca);
}

void regla_juego::setup_disparo(){
    int width = canones->pixmap().width();
    int height = canones->pixmap().height();

    bala = new disparo (game_scale_factor, canones->x() + width, canones->y() - width, width, height);
    bala->setPos(canones->x() + width, canones->y() - width);
    scene->addItem(bala);

    // Crear un temporizador para verificar colisiones periódicamente
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        if (check_collision_with_enemy(bala)) {
            // Eliminar la bala y detener el temporizador
            scene->removeItem(bala);
            timer->stop();
            timer->deleteLater();
            delete timer;

            // Eliminar el barco
            for (auto enemy : enemies) {
                if (bala->collidesWithItem(enemy)) {
                    scene->removeItem(enemy);
                    enemies.removeOne(enemy);
                    delete enemy;
                    break;
                }
            }
        }
    });
    timer->start(100);
}

bool regla_juego::check_collision_with_enemy(QGraphicsPixmapItem *item) {
    for (auto enemy : enemies) { // Iterar sobre todos los enemigos
        if (item->collidesWithItem(enemy)) {
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisión
}

void regla_juego::set_canon_keys()
{
    bomberman_keys[0] = Qt::Key_W;
    bomberman_keys[1] = Qt::Key_S;
    bomberman_keys[2] = Qt::Key_K;

}
void regla_juego::setup_scene()
{
    graph->setGeometry(0,0,
                       game_scale_factor*blocks_pixel_x_size*game_map_size_col,
                       game_scale_factor*blocks_pixel_y_size*game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,graph->width()-2, graph->height()-2);
    graph->setScene(scene);

    emit game_scene_changed();
}
