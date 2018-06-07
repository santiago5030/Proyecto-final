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
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "modojuego.h"

using namespace std;

namespace Ui {
class Nivel;
}

class Nivel : public QWidget
{
    Q_OBJECT

public:
    explicit Nivel(int, QWidget *parent = 0);
    ~Nivel();
public slots:
    void actualizar();
    void Saltar();
    void pinchos();
    void colision();
    void Score();
    void Nave();
    void colision2();
    void Musica();
private slots:
    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *accion);

private:
    Ui::Nivel *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *l1;
    QGraphicsLineItem *l2;
    QGraphicsLineItem *l3;
    QGraphicsLineItem *l4;
    QTimer *timer;
    QMediaPlayer *musica;
    Modojuego *cubo,*pincho,*nave,*elemento;
    QList<Modojuego*> spike;
    QList<Modojuego*> rocket;
    QList<int> altura;
    int limite_i,limite_i2,vel,opcion;
    QString fondo, imagecubo,imagenave,imagepincho,imagerocket,music;
    int intentos=0,score=0,dist,cont=0;
    int rango,li,ls,control,highscore=0,li2,control2,control3,cont2=0,height;
    bool saltar= false;

};

#endif // NIVEL_H
