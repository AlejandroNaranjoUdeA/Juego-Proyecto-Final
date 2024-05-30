#include <QScreen> //hallar tamano de la interfaz
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanas)
{
    ui->setupUi(this);
    setup_game_rules();
    set_mainwindow();

    gameWindow1 = ui->Game_window;
    gameWindow2 = ui->Game_window_2;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::boton_oprimir);

    // Mostrar solo la ventana de inicio al comienzo
    gameWindow1->hide();
    gameWindow2->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    game->key_event(event);
}


void MainWindow::setup_game_rules()
{
    QVector<QLabel *> labels;


    labels.push_back(ui->L_nivel);
    labels.push_back(ui->L_vidas);
    labels.push_back(ui->L_puntos);

    game = new regla_juego(ui->graphicsView,labels);

    connect(game,SIGNAL(game_scene_changed()),this,SLOT(set_mainwindow()));
}

void MainWindow::set_mainwindow()
{
    ui->Game_window->setGeometry(0,0,ui->graphicsView->width(),
                                 ui->graphicsView->height()+blocks_pixel_y_size*game_scale_factor);
    ui->graphicsView->setGeometry(0,blocks_pixel_y_size*game_scale_factor,
                                  ui->graphicsView->width(),
                                  ui->graphicsView->height());
    setGeometry(x(),y(),ui->Game_window->width(),ui->graphicsView->height());
}

void MainWindow::boton_oprimir()
{
    gameWindow2->hide();
    gameWindow1->show();
}

void MainWindow::showGameWindow2()
{
    // Obtener el tamaño de la pantalla
    QSize screenSize = QApplication::primaryScreen()->availableSize();

    // Configurar el tamaño de gameWindow2 para que ocupe toda la pantalla
    gameWindow2->setGeometry(0, 0, screenSize.width(), screenSize.height());

    graph->setGeometry(0,0,
                       game_scale_factor*blocks_pixel_x_size*game_map_size_col,
                       game_scale_factor*blocks_pixel_y_size*game_map_size_fil);
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,graph->width()-2, graph->height()-2);
    graph->setScene(scene);

    emit game_scene_changed();

    gameWindow1->hide();
    gameWindow2->show();
}


