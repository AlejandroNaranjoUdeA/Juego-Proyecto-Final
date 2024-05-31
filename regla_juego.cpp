#include "regla_juego.h"

regla_juego::regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));
    this->graph = graph;
    labels = game_labels;    
    setup_scene();
    generate_fondo();
    setup_canon();
    labels[1]->setText("vidas: 7");

}

regla_juego::~regla_juego()
{
    delete scene;
}


void regla_juego::generate_fondo() {
    for (unsigned int fil = 0; fil < game_map_rows; fil++) {
        for (unsigned int col = 0; col < game_map_col; col++) {
            // Borde del mapa
            if (fil == 0 || fil == game_map_rows - 1  || col == game_map_col - 1) {
                blocks[fil][col] = new ecenario(game_scale_factor, 1); // Borde con tipo 1
            } else {
                blocks[fil][col] = new ecenario(game_scale_factor, 2); // Fondo con tipo 2
            }
            blocks[fil][col]->setX(game_scale_factor * blocks_pixel_x_size * col);
            blocks[fil][col]->setY(game_scale_factor * blocks_pixel_y_size * fil);
            scene->addItem(blocks[fil][col]);
        }
    }
    //generate_nivel1();
    generate_nivel2();
    //generate_nivel3();

}
void regla_juego::generate_nivel1() {
    labels[0]->setText("nivel: 1");
    for (unsigned int fil = 3; fil < game_map_rows - 1; fil++) {
        if (fil == 3) {
            setup_rocas(fil, 4); // Columna 4
        } else if (fil == 4) {
            setup_enemigos(1, 5); // Columna 5
        } else if (fil == 6) {
            setup_rocas(fil-1, 8); // Columna 7
            setup_rocas(fil+2, 8); // Columna 8
        } else if (fil == 7) {
            setup_enemigos(fil, 9); // Columna 9
        } else if (fil == 9) {
            setup_rocas(fil-5, 12); // Columna 10
            setup_rocas(fil-2, 12); // Columna 11
            setup_rocas(fil+2, 12); // Columna 12
        } else if (fil >= 10) {
            if ((fil - 10) % 2 == 0) {
                setup_enemigos(1, 13); // Columna 13
            }
        }
    }
}

void regla_juego::generate_nivel2() {
    labels[0]->setText("nivel: 2");
    for (unsigned int fil = 3; fil < game_map_rows - 1; fil++) {
        if (fil == 3) {
            setup_rocas(fil, 4);
            setup_rocas(fil+2, 4);
            setup_enemigos(fil+1, 4);
        } else if (fil == 4) {
            setup_enemigos(3, 5);
            setup_enemigos(fil+5, 5);
        } else if (fil == 6) {
            setup_rocas(fil-1, 8);
            setup_rocas(fil+2, 8);
            setup_rocas(fil+4, 8);
            setup_rocas(fil+3, 8);
            setup_rocas(fil-3, 8);
        } else if (fil == 7) {
            setup_enemigos(fil, 9);
            setup_enemigos(fil-5, 10);
        } else if (fil == 9) {
            setup_rocas(fil-5, 12);
            setup_rocas(fil-2, 12);
            setup_rocas(fil+2, 12);
            setup_minas();
        } else if (fil >= 10) {
            if ((fil - 10) % 2 == 0) {
                setup_enemigos(1, 13);
            }
        }
    }
}

void regla_juego::generate_nivel3()
{
    labels[0]->setText("nivel: 3");

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
    rocars.append(roca);
}

void regla_juego::told_enemy()
{

}
void regla_juego::key_event(QKeyEvent *event)
{
    bool is_valid = true;

    if(static_cast<unsigned int>(event->key())==canon_keys[0]) is_valid = object_up_movement(canones, canon_speed);
    else if(static_cast<unsigned int>(event->key())== canon_keys[1]) is_valid = object_down_movement(canones, canon_speed);
    else if (static_cast<unsigned int>(event->key()) == canon_keys[2]) is_valid = true;
    canones->move(event->key(),is_valid);

}
void regla_juego::setup_canon()
{
    set_canon_keys();

    canones = new canon(game_scale_factor);
    canones->set_keys(canon_keys);
    scene->addItem(canones);
    //connect(canones,SIGNAL(is_moving(QGraphicsPixmapItem*,bool,bool)),this,SLOT(set_focus(QGraphicsPixmapItem*,bool,bool)));
    connect(canones, SIGNAL(apunto_diparo()), this, SLOT(setup_disparo()));
}


void regla_juego::set_focus(QGraphicsPixmapItem *item, bool is_x_focus, bool is_y_focus)
{
    int item_w = item->pixmap().width(), item_h = item->pixmap().height();
    scene->setSceneRect(is_x_focus*((item->x()+item_w/2)-scene->width()/2),
                        is_y_focus*((item->y()+item_h/2)-scene->height()/2),
                        scene->width(),
                        scene->height());
}

void regla_juego::setup_disparo() {
    int width = canones->pixmap().width();
    int height = canones->pixmap().height();

    bala = new disparo (game_scale_factor, canones->x() + width, canones->y() - width, width, height);
    bala->setPos(canones->x() + width, canones->y() - width);
    scene->addItem(bala);

    // Crear un temporizador por si el disparo da.
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        if (check_collision_with_roca(bala)){
            scene->removeItem(bala);
            timer->stop();
            timer->deleteLater();

        }
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
            return true;
        }
    }
    return false;
}



bool regla_juego::check_collision_with_roca(QGraphicsPixmapItem *item) {
    for (auto roca : rocars) { // Iterar sobre todas las rocas
        if (item->collidesWithItem(roca)) {
            return true;
        }
    }
    return false;
}




bool regla_juego::object_down_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1, xf2, yf1, yf2, width, height;
    bool valid_1, valid_2;

    width = item->pixmap().width();
    height = item->pixmap().height();

    xf1 = item->x();
    yf1 = item->y() + height - 1 + speed;
    xf2 = item->x() + width - 1;
    yf2 = item->y() + height - 1 + speed;

    valid_1 = blocks[yf1 / (blocks_pixel_y_size * game_scale_factor)][xf1 / (blocks_pixel_x_size * game_scale_factor)]->get_type() !=1;
    valid_2 = blocks[yf2 / (blocks_pixel_y_size * game_scale_factor)][xf2 / (blocks_pixel_x_size * game_scale_factor)]->get_type() !=1;

    return valid_1 && valid_2;
}





bool regla_juego::object_up_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1, xf2, yf1, yf2, width;
    bool valid_1, valid_2;

    width = item->pixmap().width();

    xf1 = item->x();
    yf1 = item->y() - speed;
    xf2 = item->x() + width - 1;
    yf2 = item->y() - speed;

    valid_1 = blocks[yf1 / (blocks_pixel_y_size * game_scale_factor)][xf1 / (blocks_pixel_x_size * game_scale_factor)]->get_type() !=1;
    valid_2 = blocks[yf2 / (blocks_pixel_y_size * game_scale_factor)][xf2 / (blocks_pixel_x_size * game_scale_factor)]->get_type() !=1;

    return valid_1 && valid_2;
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
                       game_scale_factor*game_map_col*game_map_size_col,
                       game_scale_factor*game_map_rows*game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,graph->width()-2, graph->height()-2);
    graph->setScene(scene);

    emit game_scene_changed();
}








void regla_juego::setup_minas(){
    minas= new mina(game_scale_factor);
    scene->addItem(minas);
}









