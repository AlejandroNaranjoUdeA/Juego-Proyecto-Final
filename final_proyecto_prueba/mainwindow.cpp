
#include <QScreen> //para hallar el tamaño
#include "mainwindow.h"
#include "ui_mainwindow.h"

//para el manejo de archivos
#include <QFile>
#include <QTextStream>
#include <QMessageBox> //mostrar mensajes emergentes


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanas)
    , timer(new QTimer(this)) // Inicializar el temporizador
{
    ui->setupUi(this);
    setup_game_rules();
    set_mainwindow();


    gameWindow1 = ui->Game_window;
    gameWindow2 = ui->Game_window_2;
    gameWindow3 = ui->Game_window_3;
    gameWindow4 = ui->Game_window_4;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::jugar_oprimir);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::registrarse_oprimir); // Conectar el nuevo botón
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::login); //concectar con el boton de iniciar sesion para guardar la informacion
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::iniciar_secion); // conectar con el boton iniciar sesion para iniciar el juego

    connect(timer, &QTimer::timeout, this, &MainWindow::showGameWindow1); // Conectar el temporizador con la función showGameWindow1

    // Obtener el tamaño de la pantalla disponible
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // Ajustar la geometría de las ventanas secundarias para que coincidan con el tamaño de la ventana principal

    gameWindow2->setGeometry(0, 0, screenWidth, screenHeight);
    gameWindow3->setGeometry(0, 0, screenWidth, screenHeight);
    gameWindow4->setGeometry(0, 0, screenWidth, screenHeight);

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
    gameWindow4->hide();

    // Establecer la imagen en gameWindow4
    QPixmap pixmap(":/level1 imagen juego.jpg"); // Asegúrate de que la ruta sea correcta
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents(true); // Esto asegura que la imagen se ajuste al QLabel
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
    gameWindow4->show();
    timer->start(5000); //tiempo en que aparezca gameWindow4
}

void MainWindow::showGameWindow1()
{
    gameWindow4->hide();
    gameWindow1->show();
}


void MainWindow::registrarse_oprimir()
{
    gameWindow2->hide();
    gameWindow3->show(); // Mostrar Game_window_3
}

void MainWindow::login()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    // Verificar si los campos de usuario y contraseña no están vacíos
    if (username.isEmpty() || password.isEmpty()) {
        //muestra una ventana emergente como advertencia si el espacio esta en blanco
        QMessageBox::warning(this, "Error", "Por favor ingrese un nombre de usuario y una contraseña.");
            return;
    }

    QFile file("registro.txt");

    // Verificar si el archivo se puede abrir en modo de añadido (append)
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar el usuario.");
        return;
    }

    QTextStream out(&file);
    out << username << "," << password << "\n"; //guarda el usuario y contraseña

    QMessageBox::information(this, "Registro", "Usuario registrado exitosamente."); //muestra una ventana emergente


    //continuacion....

}

void MainWindow::iniciar_secion(){
    gameWindow3->hide();
    gameWindow4->show();
    timer->start(5000); // Iniciar el temporizador para 5 segundos
    disconnect(timer, &QTimer::timeout, this, &MainWindow::showGameWindow1); // Desconectar cualquier otra conexión del temporizador
    connect(timer, &QTimer::timeout, this, &MainWindow::showGameWindowAfterLogin); // Conectar el temporizador a showGameWindowAfterLogin
}

void MainWindow::showGameWindowAfterLogin()
{
    timer->stop(); // Detener el temporizador
    gameWindow4->hide();
    gameWindow1->show();
}
