#include "selectlevels.h"
#include "ui_selectlevels.h"
#include "mainwindow.h"

selectlevels::selectlevels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectlevels)
{
    ui->setupUi(this);
    level= new Nivel();
    scene= new QGraphicsScene(0,0,500,300);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imagenes/menuprincipal2")));
}

selectlevels::~selectlevels()
{
    delete ui;
}

void selectlevels::on_pushButton_4_clicked()
{
    MainWindow *N= new MainWindow;
    N->show();
    close();
}

void selectlevels::on_pushButton_clicked()
{
    level->show();
    close();
}
