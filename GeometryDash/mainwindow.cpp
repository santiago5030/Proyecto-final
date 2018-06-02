#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    n= new selectlevels();
    scene= new QGraphicsScene(0,0,500,500);
    ui-> graphicsView-> setScene(scene);

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imagenes/menuprincipal")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    n->show();
    close();
}
