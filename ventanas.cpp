#include "ventanas.h"
#include "ui_ventanas.h"

ventanas::ventanas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanas)
{
    ui->setupUi(this);
    setup_game_rules();
    set_mainwindow();
}

ventanas::~ventanas()
{
    delete ui;
    delete game;
}

void ventanas::keyPressEvent(QKeyEvent *event)
{
    game->key_event(event);
}

void ventanas::setup_game_rules()
{
    QVector<QLabel *> labels;

    labels.push_back(ui->L_nivel);
    labels.push_back(ui->L_vidas);
    labels.push_back(ui->L_puntos);

    game = new regla_juego(ui->graphicsView,labels);

    connect(game,SIGNAL(game_scene_changed()),this,SLOT(set_mainwindow()));
}

void ventanas::set_mainwindow()
{
    ui->Game_window->setGeometry(0,0,ui->graphicsView->width(),
                                 ui->graphicsView->height()+blocks_pixel_y_size*game_scale_factor);
    ui->graphicsView->setGeometry(0,blocks_pixel_y_size*game_scale_factor,
                                  ui->graphicsView->width(),
                                  ui->graphicsView->height());
    setGeometry(x(),y(),ui->Game_window->width(),ui->Game_window->height());
}