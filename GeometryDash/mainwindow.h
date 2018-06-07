#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "selectlevels.h"
#include "registrarse.h"
#include "inicio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void cargar();
private slots:
    void on_pushButton_clicked();

    void on_actionRegistrarse_triggered();

    void on_actionIniciar_Sesion_2_triggered();

    void on_actionCargar_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    selectlevels *n;
    Registrarse *n2;
    Inicio *nuevo;
    QGraphicsScene *scene;
    QString usuario;
    QList<QString> scores;
};

#endif // MAINWINDOW_H
