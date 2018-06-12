#ifndef NIVEL_H
#define NIVEL_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <stdlib.h>
#include <time.h>
#include "modojuego.h"
#include <iostream>

using namespace std;

namespace Ui {
class Nivel;
}

class Nivel : public QWidget
{
    Q_OBJECT

public:
    explicit Nivel(int, bool, QWidget *parent = 0);
    ~Nivel();
public slots:
    void actualizar(); //Metodo que actualiza el juego en cada ciclo del timer
    void Saltar();     //Metodo para gerenar el salto
    void pinchos();    //Metodo que genera los pinchos
    void colision();   //Metodo que detecta colisiones entre el cubo y los pinchos
    void Score();      //Metodo que genera el puntaje durante el juego
    void Nave();       //Metodo que genera la nave con sus obstaculos
    void colision2();  //Metodo que detecta colisiones entre la nave y los obstaculos
    void Musica();     //Metodo para reproducir la musica del nivel
    void setusuario(QString);     //Metodo para setear el usuario
    void setlist(QList<QString>); //Metodo para setear la lista de puntajes
    void setscore();              //Metodo para inicializar la variable del puntaje de cada nivel
    void Multi();                 //Metodo para generar el multijugador
    void mayor(int&);             //Metodo para calcular el puntaje mayor en el multijugador
private slots:
    void on_pushButton_clicked();           //Boton para regresar al menu principal
    void keyPressEvent(QKeyEvent *accion);  //Acciones/eventos con el teclado

private:
    Ui::Nivel *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *l1;
    QGraphicsLineItem *l2;
    QGraphicsLineItem *l3;
    QGraphicsLineItem *l4;
    QTimer *timer;                                            //Variables de inicializacion, control y simulacion
    QMediaPlayer *musica;
    Modojuego *cubo,*pincho,*nave,*elemento;
    QList<Modojuego*> spike;
    QList<Modojuego*> rocket;
    QList<int> altura;
    QList<QString> scores;
    QList<int> multi;
    int limite_i,limite_i2,vel,opcion;
    QString fondo, imagecubo,imagenave,imagepincho,imagerocket,music,usuario;
    int intentos=0,score=0,dist,cont=0;
    int rango,li,ls,control,highscore=0,li2,control2,control3,cont2=0,height;
    bool saltar= false,ban;
};

#endif // NIVEL_H
