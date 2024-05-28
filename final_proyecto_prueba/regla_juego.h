#ifndef REGLA_JUEGO_H
#define REGLA_JUEGO_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <QObject>
#include <QTimer>

#include "canon.h"
#include "enemigos.h"
#include "rocas.h"
#include "disparo.h"

#define game_scale_factor 3
#define game_map_rows 16
#define game_map_col 16
#define game_map_size_col 31
#define game_map_size_fil 31
#define blocks_pixel_x_size 16
#define blocks_pixel_y_size 16

class regla_juego : public QObject
{
    Q_OBJECT
public:
    regla_juego(QGraphicsView *graph, QVector<QLabel *> game_labels);
    ~regla_juego();
    void key_event(QKeyEvent *event);

private:
    QGraphicsView *graph;
    QVector<QLabel *> labels;
    QGraphicsScene *scene;
    QVector<enemigos *> enemies;

    enemigos *enemy;
    canon *canones;
    rocas *roca;
    disparo *bala;

    void setup_canon();
    void setuo_enemigos();
    void setup_rocas();
    void set_canon_keys();
    void setup_scene();
    bool check_collision_with_enemy(QGraphicsPixmapItem *item);

    unsigned int bomberman_keys[5];
    float difficult = 0.1;

    bool object_right_movement(QGraphicsPixmapItem *item, unsigned int speed);

private slots:
    void setup_disparo();

signals:
    void game_scene_changed();

};

#endif // REGLA_JUEGO_H
