#ifndef NIVEL_H
#define NIVEL_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>
#include "modojuego.h"

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
    void mover(Modojuego*);
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
    int intentos=0,score=0,dist=8;
    bool saltar= false;

};

#endif // NIVEL_H
