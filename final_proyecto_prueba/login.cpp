#include "login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

login::login(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel("Usuario:", this);
    usernameLineEdit = new QLineEdit(this);
    QLabel *passwordLabel = new QLabel("Contraseña:", this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Iniciar Sesión", this);
    connect(loginButton, &QPushButton::clicked, this, &login::onLoginButtonClicked);

    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    setLayout(layout);
}

login::~login(){
}

void login::onLoginButtonClicked(){
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (verifyUser(username, password)) {
        QMessageBox::information(this, "Login", "Inicio de sesión exitoso.");
            accept();
    } else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Registro", "Usuario no encontrado. ¿Desea registrarse?",
                                                            QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            addUser(username, password);
            QMessageBox::information(this, "Registro", "Usuario registrado exitosamente.");
            accept();
        }
    }
}

bool login::verifyUser(const QString &username, const QString &password) {
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 2 && parts[0] == username && parts[1] == password) {
            return true;
        }
    }
    return false;
}

void login::addUser(const QString &username, const QString &password) {
    QFile file("users.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << username << "," << password << "\n";
}
