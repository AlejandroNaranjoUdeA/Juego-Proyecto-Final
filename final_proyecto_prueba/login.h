#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class login: public QDialog
{
public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void onLoginButtonClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    bool verifyUser(const QString &username, const QString &password);
    void addUser(const QString &username, const QString &password);

};


#endif // LOGIN_H
