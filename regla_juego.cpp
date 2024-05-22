#include "regla_juego.h"

regla_juego::regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels)
{
    srand(time(NULL));

    this->graph = graph;
    labels = game_labels;
    setup_scene();
    setup_canon();

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
                       game_scale_factor*blocks_pixel_y_size*game_map_size_col,
                       game_scale_factor*blocks_pixel_y_size*game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,graph->width()-2, graph->height()-2);
    graph->setScene(scene);

    emit game_scene_changed();
}
