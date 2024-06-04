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

#include "ecenario.h"
#include "canon.h"
#include "enemigos.h"
#include "rocas.h"
#include "disparo.h"
#include "mina.h"

#define game_scale_factor 3
#define game_map_rows 12
#define game_map_col 17
#define game_map_size_col 16
#define game_map_size_fil 16


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
    ecenario *blocks[game_map_rows][game_map_col];
    QVector<enemigos *> enemies;
    QVector<rocas *> rocars;
    enemigos *enemy;
    rocas *roca;
    mina *minas;
    disparo *bala;
    canon *canones;
    QGraphicsItem* elemento;
    int enemies_eliminated;
    void generate_fondo();
    void generate_nivel1();
    void generate_nivel2();
    void generate_nivel3();


    void setup_enemigos( int fil, int col);
    void setup_rocas(int fil,  int col);
    QTimer *timek;
    void move_object_right(QGraphicsPixmapItem *item, unsigned int speed);
    void setup_canon();

    void setup_minas();
    void set_canon_keys();
    void setup_scene();
    void handle_barco_collision(disparo *bala, QTimer *timer);
    void borrarElementos();
    void handle_roca_collision(disparo *bala, QTimer *timer);
    bool check_collision_with_enemy(QGraphicsPixmapItem *item);
    bool check_collision_with_roca(QGraphicsPixmapItem *item);
    unsigned int canon_keys[3];
    bool object_right_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_down_movement(QGraphicsPixmapItem *item, unsigned int speed);
    bool object_up_movement(QGraphicsPixmapItem *item, unsigned int speed);
    int get_lives_from_label();
    void update_lives_in_label(int lives);
    int get_points_from_label();
    void update_point_in_label(int lives);
private slots:
    void setup_disparo();
    void set_focus(QGraphicsPixmapItem *item, bool is_x_focus, bool is_y_focus);

    void move_canon_right();

signals:
    void game_scene_changed();
    void move_rigtht();

};

#endif // REGLA_JUEGO_H
