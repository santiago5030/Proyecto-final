#include "nivel.h"
#include "ui_nivel.h"
#include "mainwindow.h"
#include <QDebug>

Nivel::Nivel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nivel)
{
    ui->setupUi(this);
    scene= new QGraphicsScene(0,0,700,300);
    ui-> graphicsView -> setScene(scene);

    ui-> graphicsView-> setBackgroundBrush(QBrush(QImage(":/imagenes/fondo 1")));

    l1= new QGraphicsLineItem(0,0,700,0);
    l2= new QGraphicsLineItem(0,0,0,300);
    l3= new QGraphicsLineItem(700,0,700,300);
    l4= new QGraphicsLineItem(0,300,700,300);
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);

    cubo= new Modojuego(40,260,40,40,":/imagenes/cubo3");
    scene->addItem(cubo);

    pincho= new Modojuego(600,270,30,30,":/imagenes/pincho");
    scene->addItem(pincho);

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(actualizar()));
}

Nivel::~Nivel()
{
    delete ui;
    delete cubo;
    delete pincho;
}

void Nivel::actualizar()
{
    mover(pincho);
    Saltar();
}

void Nivel::Saltar()
{
    if(saltar){
        cubo->setY(cubo->pos().y()-10);
    }
    else{
        if(cubo->pos().y()!= 0){
            cubo->setY(cubo->pos().y()+10);
        }
    }
    if(cubo->pos().y() < -80){
        saltar=false;
    }
}

void Nivel::mover(Modojuego *objeto)
{
    objeto->setPos(objeto->pos().x()-dist,objeto->pos().y());
}

void Nivel::on_pushButton_clicked()
{
    MainWindow *menu= new MainWindow;
    timer->stop();
    menu->show();
    close();
}

void Nivel::keyPressEvent(QKeyEvent *accion)
{
    if(accion ->key()== Qt::Key_Space){
        saltar=true;
    }
    if(accion->key()== Qt::Key_I){
        timer->start(20);
    }
}
