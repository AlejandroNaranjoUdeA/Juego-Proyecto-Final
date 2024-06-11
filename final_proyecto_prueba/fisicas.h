#ifndef FISICAS_H
#define FISICAS_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#define time_period 100
class fisicas : public QObject {
    Q_OBJECT

public:
    fisicas( int x, int y, int w, int h, QGraphicsPixmapItem *item);

    void set_movement_type(QString type);

private slots:
    void time_step();

private:
    float x, y, vx, vy;
    float x_dimension, y_dimension, w, h;
    QGraphicsPixmapItem *item;
    QTimer *time;
    QString type;

    void set_initial_conditions(float x, float y, float vx, float vy);
    float get_phisical_x(float x);
    float get_phisical_y(float y);
    float get_simulated_x(float x);
    float get_simulated_y(float y);
    void calculate_cinematics(float ax, float ay);
    void calculate_parabolic_dynamics();
    void calculate_MRU_dynamics();
};



#endif // FISICAS_H
