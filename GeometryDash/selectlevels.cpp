#include "selectlevels.h"
#include "ui_selectlevels.h"
#include "mainwindow.h"

selectlevels::selectlevels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectlevels)
{
    ui->setupUi(this);
    scene= new QGraphicsScene(0,0,500,300);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imagenes/menuprincipal2")));
    ban=false;
}

selectlevels::~selectlevels()
{
    delete ui;
}

void selectlevels::setusuario(QString _usuario)
{
    usuario=_usuario;          //Setea el usuario
}

void selectlevels::setlist(QList<QString> lista)
{
    for(int i=0; i < lista.size(); i++){   //Setea la lista de puntajes
        scores.append(lista.at(i));
    }
}

void selectlevels::datos()
{
    if(!usuario.isNull()){
        level->setusuario(usuario);   //Setea el usuario del nivel
    }
    if(!scores.isEmpty()){
        level->setlist(scores);       //Setea la lista de puntajes del nivel
    }
}

void selectlevels::setban(bool _ban)
{
    ban=_ban;
}

void selectlevels::on_pushButton_4_clicked()
{
    MainWindow *N= new MainWindow(usuario,scores);
    N->show();
    close();
}

void selectlevels::on_pushButton_clicked()
{
    level= new Nivel(1,ban);    //Crea el nivel indicando que nivel se construira
    datos();
    level->show();         //Abre la ventana del nivel
    close();
}

void selectlevels::on_pushButton_2_clicked()
{
    level= new Nivel(2,ban);
    datos();
    level->show();
    close();
}

void selectlevels::on_pushButton_3_clicked()
{
    level= new Nivel(3,ban);
    datos();
    level->show();
    close();
}
