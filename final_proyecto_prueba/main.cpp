/*#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        MainWindow w;
        QVector<QLabel *> labels;
        regla_juego game(&w, labels);
        w.show();

        return a.exec();
    }

    return 0;
}*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
