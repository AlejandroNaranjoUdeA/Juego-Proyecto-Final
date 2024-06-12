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

    connect(ui->pushButton, &QPushButton::clicked, this, &ventanas::jugar_oprimir);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &ventanas::registrarse_oprimir); // Conectar el nuevo botón
    connect(ui->pushButton_3, &QPushButton::clicked, this, &ventanas::login); //concectar con el boton de iniciar sesion para guardar la informacion
    connect(ui->pushButton_3, &QPushButton::clicked, this, &ventanas::iniciar_secion); // conectar con el boton iniciar sesion para iniciar el juego


    // Obtener el tamaño de la pantalla disponible
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    gameWindow2->setGeometry(0, 0, screenWidth, screenHeight);
    gameWindow3->setGeometry(0, 0, screenWidth, screenHeight);


    ui->backgroundLabel->setPixmap(QPixmap(":/fondo menu principal.jpeg"));
    ui->backgroundLabel->setScaledContents(true); // Para escalar la imagen al tamaño del QLabel
    ui->backgroundLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // Hacer QLabel transparente

    // Hacer que gameWindow2 tenga fondo transparente
    gameWindow2->setAttribute(Qt::WA_TranslucentBackground);
    gameWindow2->setStyleSheet("background: transparent;");
    // Asegurarse de que backgroundLabel esté detrás de otros widgets
    ui->backgroundLabel->lower(); // Mover el QLabel al fondo

    ui->L_nivel->setStyleSheet("QLabel { color : blue; font :  12px 'Arial'; }");
    ui->L_vidas->setStyleSheet("QLabel { color : blue; font :  12px 'Arial'; }");
    ui->L_puntos->setStyleSheet("QLabel { color : blue; font : 12px 'Arial'; }");


    // Mostrar solo la ventana de inicio al comienzo
    gameWindow1->hide();
    gameWindow2->show();
    gameWindow3->hide();

    connect(game, SIGNAL(loseorwin(bool)), this, SLOT(mostrar_mensaje(bool)));

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
}

void ventanas::set_mainwindow()
{
    ui->Game_window->setGeometry(0, 0, ui->graphicsView->width(),
                                 ui->graphicsView->height() + blocks_pixel_y_size * game_scale_factor);
    ui->graphicsView->setGeometry(0, blocks_pixel_y_size * game_scale_factor,
                                  ui->graphicsView->width(),
                                  ui->graphicsView->height());
    setGeometry(x(), y(), ui->Game_window->width(), ui->Game_window->height());
}


void ventanas::jugar_oprimir()
{
    gameWindow2->hide();
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

    QTextStream out(&file);
    out << username << "," << password << "\n"; //guarda el usuario y contraseña
    QMessageBox::information(this, "Registro", "Usuario registrado exitosamente."); //muestra una ventana emergente
    //continuacion....


}

void ventanas::iniciar_secion(){
    gameWindow3->hide();
    gameWindow1->show();
}



void ventanas::mostrar_mensaje(bool win) {
     qDebug() << "Señal loseorwin recibida con valor:" << win;
    if (win==true) {
        qDebug() << "haciendo que gane";
        QMessageBox msgBox;
        msgBox.setWindowTitle("WINNN");
        msgBox.setText("¡GANASTE!");
        msgBox.setInformativeText("¿Deseas jugar de nuevo o salir del juego?");
        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Retry);

        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Retry:
            restartGame();
            break;
        case QMessageBox::Close:
            QCoreApplication::quit();
            break;
        default:
            break;
        }
    } else if (win==false) {
        QMessageBox::information(this, "LOSEE", "¡PERDISTE!");
        QCoreApplication::quit();
    }
}

void ventanas::restartGame() {
    gameWindow1->hide();
    gameWindow2->show();
    gameWindow3->hide();

}
