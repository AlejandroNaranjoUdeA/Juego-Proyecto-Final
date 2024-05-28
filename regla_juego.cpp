#include "regla_juego.h"

regla_juego::regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));
    this->graph = graph;
    labels = game_labels;    
    setup_scene();
    setup_canon();
    setup_enemigos(3,3);
    setup_enemigos(3,8);
    setup_enemigos(5,3);
    setup_enemigos(5,5);
    setup_enemigos(6,8);
    //generate_map();
}

regla_juego::~regla_juego()
{
    delete scene;
}

void regla_juego::key_event(QKeyEvent *event)
{
    canones->move(event->key());
}

void regla_juego::generate_map() {
    unsigned int barco_col = 1;
    unsigned int roca_col = 3;
    for (unsigned int fil = 0; fil < game_map_rows; fil++) {
        for (unsigned int col = 0; col < game_map_col; col++) {
            // Borde del mapa y dos últimas columnas en blanco
            if (fil == 0 || fil == game_map_rows - 1 || col == 0 || col >= game_map_col - 2 || (col % 2 == 0 && fil % 2 == 0)) {
                continue; // Deja este espacio vacío o agrega el borde
            }
            // Columna específica para barcos
            if (col == barco_col) {
                setup_enemigos(fil, col);
                continue;
            }
            // Columna específica para rocas
            if (col == roca_col) {
                setup_rocas(fil, col);
                continue;
            }
            // Asignar aleatoriamente enemigos y rocas en el resto del mapa
            if (bernoulli_event()) {
                setup_enemigos(fil, col);
            } else {
                setup_rocas(fil, col);
            }
        }
    }
}

bool regla_juego::bernoulli_event()
{
    return (rand()/float(RAND_MAX)) < difficult;
}

void regla_juego::setup_enemigos(int fil, int col)
{
    enemigos *enemy = new enemigos(game_scale_factor);
    enemy->setPos(game_scale_factor*col * game_map_size_col,game_scale_factor* fil * game_map_size_fil);
    scene->addItem(enemy);
    enemies.append(enemy);
}

void regla_juego::setup_rocas(int fil, int col)
{
    rocas *roca = new rocas(game_scale_factor);
    roca->setPos(game_scale_factor*col * game_map_size_col,game_scale_factor* fil * blocks_pixel_y_size);
    scene->addItem(roca);
}

void regla_juego::setup_canon()
{
    set_canon_keys();

    canones = new canon(game_scale_factor);
    canones->set_keys(canon_keys);
    scene->addItem(canones);
    connect(canones, SIGNAL(apunto_diparo()), this, SLOT(setup_disparo()));
}


void regla_juego::setup_disparo() {
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
    canon_keys[0] = Qt::Key_W;
    canon_keys[1] = Qt::Key_S;
    canon_keys[2] = Qt::Key_K;
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










