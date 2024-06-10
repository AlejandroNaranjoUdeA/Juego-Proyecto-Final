#include "regla_juego.h"

regla_juego::regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));
    this->graph = graph;
    labels = game_labels;
    setup_scene();
    generate_fondo();
    setup_canon();
    setup_minas();
    labels[1]->setText("vidas: 7");
    labels[2]->setText("puntos: 0");

    // Configurar temporizador para comprobar colisiones
    timek = new QTimer(this);
    connect(timek, &QTimer::timeout, this, &regla_juego::checkCollisions);
    timek->start(16); // Aproximadamente 60 FPS
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
            setup_enemigos(0, 5); // Columna 5
        } else if (fil == 6) {
            setup_rocas(fil-1, 8); // Columna 7
            setup_rocas(fil+2, 8); // Columna 8
        } else if (fil == 7) {
            setup_enemigos(0, 9); // Columna 9
        } else if (fil == 9) {
            setup_rocas(fil-5, 12); // Columna 10
            setup_rocas(fil-2, 12); // Columna 11
            setup_rocas(fil+2, 12); // Columna 12
        } else if (fil >= 10) {
            if ((fil - 10) % 2 == 0) {
                setup_enemigos(0, 13); // Columna 13
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
    int x =game_scale_factor*col * game_map_size_col;
    int y =game_scale_factor* fil * game_map_size_fil;
    enemy->set_initial_conditions(x, y, 1, 1);
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


void regla_juego::key_event(QKeyEvent *event)
{
    bool is_valid = true;

    if(static_cast<unsigned int>(event->key())==canon_keys[0]) is_valid = object_up_movement(canones, canon_speed);
    else if(static_cast<unsigned int>(event->key())== canon_keys[1]) is_valid = object_down_movement(canones, canon_speed);
    else if (static_cast<unsigned int>(event->key()) == canon_keys[2]) is_valid = true;

    canones->move(event->key(),is_valid);
}


void regla_juego::set_canon_keys()
{
    canon_keys[0] = Qt::Key_W;
    canon_keys[1] = Qt::Key_S;
    canon_keys[2] = Qt::Key_K;
}

void regla_juego::setup_canon()
{
    set_canon_keys();

    canones = new canon(game_scale_factor);
    canones->set_keys(canon_keys);
    scene->addItem(canones);
    connect(canones,SIGNAL(is_moving(QGraphicsPixmapItem*,bool,bool)),this,SLOT(set_focus(QGraphicsPixmapItem*,bool,bool)));
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

void regla_juego::move_canon_right()
{
    const unsigned int speed = 8; // Define la velocidad de movimiento
    move_object_right(canones, speed);
}

void regla_juego::move_object_right(QGraphicsPixmapItem *item, unsigned int speed)
{
    if (object_right_movement(item, speed)) // Verifica si el movimiento a la derecha es válido
    {
        item->setX(item->x() + speed); // Mueve el objeto a la derecha
    }
    else{
        timek->stop();
        timek->deleteLater();
        delete timek;
    }
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
            handle_roca_collision(bala, timer);
        }
        if (check_collision_with_enemy(bala)) {
            handle_barco_collision(bala, timer);
        }
    });
    timer->start(100);
}

void regla_juego::setup_minas(){
    minas= new mina(game_scale_factor);
    scene->addItem(minas);

    checkCollisions();
}

void regla_juego::checkCollisions() {
    // Comprobar colisiones entre el cañón y las minas
    for (mina *m : minass) {
        if (canones->collidesWithItem(m)) {
            m->startExplosion();
            // Puedes añadir lógica adicional aquí, como reducir vidas, etc.
        }
    }
}


void regla_juego::handle_barco_collision(disparo *bala, QTimer *timer) {
    scene->removeItem(bala);
    timer->stop();
    timer->deleteLater();
    delete timer;
    // Eliminar el barco
    for (auto enemy : enemies) {
        if (bala->collidesWithItem(enemy)) {
            scene->removeItem(enemy);
            enemies.removeOne(enemy);
            enemies_eliminated++;
            delete enemy;
            break;
        }
    }
    int lives = get_points_from_label();
    if (lives >= 0)
    {
        update_point_in_label(lives + 1000);
    }
    if (enemies_eliminated == 2){
        timek = new QTimer(this);
        connect(timek, &QTimer::timeout, this, &regla_juego::move_canon_right);
        timek->start(100);
    }
    int cantidad_enemigos = enemies.size();
    if (cantidad_enemigos==0) borrarElementos();
}
void regla_juego::borrarElementos() {
    QList<QGraphicsItem*> elementos = scene->items();
    for (QGraphicsItem* elemento : elementos) {
        scene->removeItem(elemento);
        delete elemento;
    }
    generate_fondo();

}
void regla_juego::handle_roca_collision(disparo *bala, QTimer *timer) {
    // Eliminar la bala y detener el temporizador
    scene->removeItem(bala);
    timer->stop();
    timer->deleteLater();
    for (auto roca : rocars) {
        if (bala->collidesWithItem(roca)) {
            roca->hit();
            if (roca->isDestroyed()) {
                scene->removeItem(roca);
                rocars.removeOne(roca);
                delete roca;
            }
            break;
        }
    }
    int lives = get_lives_from_label();
    if (lives > 0)
    {
        update_lives_in_label(lives - 1);
    }
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

bool regla_juego::object_right_movement(QGraphicsPixmapItem *item, unsigned int speed)
{
    int xf1,xf2,yf1,yf2, width, height;
    bool valid_1, valid_2;
    width = item->pixmap().width();
    height = item->pixmap().height();

    xf1 = item->x() + width -1 + speed;
    yf1 = item->y();
    xf2 = item->x() + width -1 + speed;
    yf2 = item->y() + height -1;

    valid_1 = blocks[yf1/(blocks_pixel_y_size*game_scale_factor)][xf1/(blocks_pixel_x_size*game_scale_factor)]->get_type()!=1;
    valid_2 = blocks[yf2/(blocks_pixel_y_size*game_scale_factor)][xf2/(blocks_pixel_x_size*game_scale_factor)]->get_type()!=1;
    return valid_1 && valid_2;
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

int regla_juego::get_lives_from_label()
{
    QString text = labels[1]->text();
    QStringList parts = text.split(": ");
    if (parts.size() == 2)
    {
        bool ok;
        int lives = parts[1].toInt(&ok);
        if (ok)
        {
            return lives;
        }
    }
    return 0;
}

void regla_juego::update_lives_in_label(int lives)
{
    labels[1]->setText("vidas: " + QString::number(lives));
}

int regla_juego::get_points_from_label()
{
    QString text = labels[2]->text();
    QStringList parts = text.split(": ");
    if (parts.size() == 2)
    {
        bool ok;
        int point = parts[1].toInt(&ok);
        if (ok)
        {
            return point;
        }
    }
    return 0; // Default en caso de error
}

void regla_juego::update_point_in_label(int lives)
{
    labels[2]->setText("puntos: " + QString::number(lives));
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


