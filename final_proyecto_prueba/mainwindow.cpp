#include <QScreen>
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
    gameWindow3 = ui->Game_window_3;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::jugar_oprimir);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::registrarse_oprimir); // Conectar el nuevo botón

    // Configurar el tamaño de gameWindow2 para que sea grande desde el inicio
    QSize screenSize = QApplication::primaryScreen()->availableSize();
    gameWindow2->setGeometry(0, 0, screenSize.width(), screenSize.height());

    ui->backgroundLabel->setPixmap(QPixmap(":/fondo menu principal.jpg"));
    ui->backgroundLabel->setScaledContents(true); // Para escalar la imagen al tamaño del QLabel
    ui->backgroundLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // Hacer QLabel transparente

    // Hacer que gameWindow2 tenga fondo transparente
    gameWindow2->setAttribute(Qt::WA_TranslucentBackground);
    gameWindow2->setStyleSheet("background: transparent;");


    // Asegurarse de que backgroundLabel esté detrás de otros widgets
    ui->backgroundLabel->lower(); // Mover el QLabel al fondo

    // Mostrar solo la ventana de inicio al comienzo
    gameWindow1->hide();
    gameWindow2->show();
    gameWindow3->hide();
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

void MainWindow::jugar_oprimir()
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

    // Ajustar el tamaño del QLabel de fondo para que cubra toda la pantalla
    ui->backgroundLabel->setGeometry(0, 0, screenSize.width(), screenSize.height());

    // Ajustar el tamaño del QGraphicsView y la QGraphicsScene
    ui->graphicsView->setGeometry(0, 0, screenSize.width(), screenSize.height());
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, screenSize.width(), screenSize.height());
    ui->graphicsView->setScene(scene);

    emit game_scene_changed();

    gameWindow1->hide();
    gameWindow2->show();
}

void MainWindow::registrarse_oprimir()
{
    gameWindow2->hide();
    gameWindow3->show(); // Mostrar Game_window_3
}

