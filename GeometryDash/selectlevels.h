#ifndef SELECTLEVELS_H
#define SELECTLEVELS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include "nivel.h"

namespace Ui {
class selectlevels;
}

class selectlevels : public QWidget
{
    Q_OBJECT

public:
    explicit selectlevels(QWidget *parent = 0);
    ~selectlevels();

public slots:
    void setusuario(QString);     //Metodo para setear el usuario
    void setlist(QList<QString>); //Metodo para setear la lista de puntajes
    void datos();               //Metodo que se encarga de transferir los datos
    void setban(bool);          //Metodo para setear la bandera del multijugador
private slots:
    void on_pushButton_4_clicked(); //Boton para regresar al menu principal

    void on_pushButton_clicked();   //Boton nivel 1

    void on_pushButton_2_clicked(); //Boton nivel 2

    void on_pushButton_3_clicked(); //Boton nivel 3

private:
    Ui::selectlevels *ui;
    Nivel *level;          //Se crea un objeto de la clase nivel
    QGraphicsScene *scene;
    QString usuario;        //Variable que almacena el usuario
    QList<QString> scores; //Lista que almacena los puntajes del usuario
    bool ban;              //Bandera multijugador
};

#endif // SELECTLEVELS_H
