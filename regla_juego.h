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

#define game_scale_factor 3
#define game_map_rows 13
#define game_map_col 31
#define game_map_size_col 16
#define game_map_size_fil 13
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

    canon *canones;
    void setup_canon();
    void set_canon_keys();
    void setup_scene();


    unsigned int bomberman_keys[5];
    float difficult = 0.1;


signals:
    void game_scene_changed();

};

#endif // REGLA_JUEGO_H
