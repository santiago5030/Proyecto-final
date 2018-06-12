#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString nuevo1;
    QList<QString> list1;
    MainWindow w(nuevo1,list1);
    w.show();

    return a.exec();
}
