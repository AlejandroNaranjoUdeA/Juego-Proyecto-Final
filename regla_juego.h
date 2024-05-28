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
#define game_map_rows 13
#define game_map_col 15
#define game_map_size_col 16
#define game_map_size_fil 16
#define blocks_pixel_x_size 20
#define blocks_pixel_y_size 13

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
    rocas *roca;
    disparo *bala;
    void generate_map();
    bool bernoulli_event();

    void setup_enemigos( int fil, int col);
    void setup_rocas(int fil,  int col);
    canon *canones;
    void setup_canon();
    void set_canon_keys();
    void setup_scene();
    bool check_collision_with_enemy(QGraphicsPixmapItem *item);

    unsigned int canon_keys[3];
    float difficult = 0.1;
    bool object_right_movement(QGraphicsPixmapItem *item, unsigned int speed);
private slots:
    void setup_disparo();

signals:
    void game_scene_changed();

};

#endif // REGLA_JUEGO_H
