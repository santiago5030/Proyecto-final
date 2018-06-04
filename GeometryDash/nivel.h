#ifndef NIVEL_H
#define NIVEL_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
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
    explicit Nivel(QWidget *parent = 0);
    ~Nivel();
public slots:
    void actualizar();
    void Saltar();
    void pinchos();
    void colision();
    void Score();
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
    Modojuego *cubo,*pincho;
    QList<Modojuego*> spike;
    int intentos=1,score=0,dist=8,cont=0;
    int rango,li,ls,control=30,highscore=0;
    bool saltar= false,ban;

};

#endif // NIVEL_H
