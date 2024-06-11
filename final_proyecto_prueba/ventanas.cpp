#include "ventanas.h"
#include "ui_ventanas.h"

ventanas::ventanas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanas)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    setup_game_rules();
    set_mainwindow();

    gameWindow1 = ui->Game_window;
    gameWindow2 = ui->Game_window_2;
    gameWindow3 = ui->Game_window_3;
    gameWindow4 = ui->Game_window_4;
    gameWindow5 = ui->Game_window_5;
    gameWindow6 = ui->Game_window_6;


    connect(ui->pushButton, &QPushButton::clicked, this, &ventanas::jugar_oprimir);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ventanas::registrarse_oprimir); // Conectar el nuevo botón
    connect(ui->pushButton_3, &QPushButton::clicked, this, &ventanas::login); //concectar con el boton de iniciar sesion para guardar la informacion
    connect(ui->pushButton_3, &QPushButton::clicked, this, &ventanas::iniciar_secion); // conectar con el boton iniciar sesion para iniciar el juego

    connect(timer, &QTimer::timeout, this, &ventanas::showGameWindow1); // Conectar el temporizador con la función showGameWindow1

    // Obtener el tamaño de la pantalla disponible
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    gameWindow2->setGeometry(0, 0, screenWidth, screenHeight);
    gameWindow3->setGeometry(0, 0, screenWidth, screenHeight);
    gameWindow4->setGeometry(0, 0, screenWidth, screenHeight);

    ui->backgroundLabel->setPixmap(QPixmap(":/fondo menu principal.jpeg"));
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
    gameWindow5->hide();

    // Establecer la imagen en gameWindow4
    QPixmap pixmap(":/level1 imagen juego.jpeg"); // Asegúrate de que la ruta sea correcta
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents(true); // Esto asegura que la imagen se ajuste al QLabel

    connect(game, SIGNAL(loseorwin(bool)), this, SLOT(mostrar_mensaje(bool )));

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
    connect(game, SIGNAL(cambio()), this, SLOT(setup_game_rules()));


    /*if(labels[0]->text()=="nivel: 2"){

        gameWindow1->hide();
        gameWindow5->show();
        QTimer::singleShot(3000, this, [this]() {
            gameWindow5->hide();
            gameWindow1->show();
        });
    }*/

        /*gameWindow1->hide();
        gameWindow5->show();
        timer->start(3000); //3 segundos
        disconnect(timer, &QTimer::timeout, this, &ventanas::mostrar_nivel2);
        connect(timer, &QTimer::timeout, this, &ventanas::mostrar_nivel2_imagen);



        //timer->stop();
        //gameWindow5->hide();
        //gameWindow1->show();
    }*/

    /*else if(labels[0]->text()=="nivel: 3"){
        gameWindow1->hide();
        gameWindow6->show();
        timer->start(3000); //3 segundos
        timer->stop();
        gameWindow6->hide();
        gameWindow1->show();

    }*/
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

void ventanas::mostrar_nivel2(){
    gameWindow5->show();
    gameWindow1->hide();
}

void ventanas::mostrar_nivel2_imagen(){
    timer->stop();
    gameWindow5->hide();
    gameWindow1->show();
}


void ventanas::jugar_oprimir()
{
    gameWindow2->hide();
    gameWindow4->show();
    timer->start(3000); //tiempo en que aparezca gameWindow4
}

void ventanas::showGameWindow1()
{
    gameWindow4->hide();
    gameWindow1->show();
}


void ventanas::registrarse_oprimir()
{

    gameWindow2->hide();
    gameWindow3->show(); // Mostrar Game_window_3

}


void ventanas::login()
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

    QTextStream in(&file);
    QString line;
    bool userExists = false;

    // Leer el archivo línea por línea para verificar si el usuario ya existe
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() > 1 && parts[0] == username) {
            userExists = true;
            break;
        }
    }

    // Si el usuario no existe, añadirlo con el nivel 1
    if (!userExists) {
        QTextStream out(&file);
        file.seek(file.size()); // Mover el cursor al final del archivo
        out << username << "," << password << "," << "1" << "\n"; // Añadir usuario, contraseña y nivel 1

    } else {
        QMessageBox::warning(this, "Error", "El usuario ya existe.");
    }

    //QTextStream out(&file);
    //out << username << "," << password << "\n"; //guarda el usuario y contraseña

    QMessageBox::information(this, "Registro", "Usuario registrado exitosamente."); //muestra una ventana emergente




}

void ventanas::iniciar_secion(){

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese un nombre de usuario y una contraseña.");
            return;
    }

    QFile file("registro.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para leer el usuario.");
        return;
    }

    QTextStream in(&file);
    QString line;
    int userLevel = -1;
    bool loginSuccess = false;

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() > 2 && parts[0] == username && parts[1] == password) {
            userLevel = parts[2].toInt();
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        updateLevelLabel(userLevel);  // Actualizar el QLabel con el nivel del usuario
        gameWindow3->hide();
        gameWindow4->show();
        timer->start(3000);
        disconnect(timer, &QTimer::timeout, this, &ventanas::showGameWindow1);
        connect(timer, &QTimer::timeout, this, &ventanas::showGameWindowAfterLogin);
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
    }
}


void ventanas::showGameWindowAfterLogin()
{
    timer->stop(); // Detener el temporizador
    gameWindow4->hide();
    gameWindow1->show();
}


void ventanas::updateLevelLabel(int level)
{
    switch (level) {
    case 1:
        ui->L_nivel->setText("Nivel 1");
        break;
    case 2:
        ui->L_nivel->setText("Nivel 2");
        break;
    case 3:
        ui->L_nivel->setText("Nivel 3");
        break;
    default:
        ui->L_nivel->setText("Nivel desconocido");
        break;
    }
}

void ventanas::mostrar_mensaje(bool win){
    if(win){
        QMessageBox::information(this, "WINNN", "GANASTEEEE.");
    }
    else if (win==false){
        QMessageBox::information(this, "LOSEE", "PERDISTEEE .");

    }
}
