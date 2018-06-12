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
    explicit MainWindow(QString, QList<QString>, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void cargar();      //Metodo que carga los datos
    void guardar();     //Metodo que guarda los datos
    void datos();              //Metodo que se encarga de transferir los datos
private slots:
    void on_pushButton_clicked();             //Boton para seleccionar nivel

    void on_actionRegistrarse_triggered();    //Menu opciones: Registrarse

    void on_actionIniciar_Sesion_2_triggered(); //Menu opciones: Iniciar sesion

    void on_actionCargar_triggered();          //Menu opciones: Cargar

    void on_pushButton_2_clicked();           //Boton para ver las estadisticas del usuario

    void on_actionGuardar_triggered();       //Menu opciones: Guardar

    void on_pushButton_3_clicked();          //Boton multijugador

private:
    Ui::MainWindow *ui;
    selectlevels *n;       //Se crea objetos de las otras ventanas para acceder
    Registrarse *n2;
    Inicio *nuevo;
    QGraphicsScene *scene;
    QString usuario;         //Variable que almacena el usuario
    QList<QString> scores;   //Lista que almacena los puntajes del usuario
};

#endif // MAINWINDOW_H
