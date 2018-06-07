#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    n= new selectlevels();
    nuevo= new Inicio();
    scene= new QGraphicsScene(0,0,500,500);
    ui-> graphicsView-> setScene(scene);

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imagenes/menuprincipal")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargar()
{
    QFile archivo("puntaje.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    QString linea,user,puntaje;
    int num=0;
    while(!in.atEnd()){
        linea=in.readLine();
        while(linea[num] != ';'){
            user+=linea[num];
            num++;
        }
        if(user==usuario){
            for(int i=0; i<3; i++){
                num+=1;
                while(linea[num]!= ';'){
                    puntaje+=linea[num];
                    num++;
                }
                scores.append(puntaje);
                puntaje.clear();
            }
            break;
        }
        user.clear();
        num=0;
    }
}

void MainWindow::on_pushButton_clicked()
{
    n->show();
    close();
}

void MainWindow::on_actionRegistrarse_triggered()
{
    n2= new Registrarse();
    n2->show();
}

void MainWindow::on_actionIniciar_Sesion_2_triggered()
{
    nuevo->show();
}

void MainWindow::on_actionCargar_triggered()
{
    if(nuevo->getinicio()){
        usuario=nuevo->getusuario();
    }
    if(!usuario.isNull()){
        cargar();
        QMessageBox::information(this,"Cargar","Los datos se han cargado correctamente");
    }
    else{
        QMessageBox::information(this,"Cargar","Debes iniciar sesion para cargar los datos");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!scores.isEmpty()){
        int total=0;
        for(int i=0; i< scores.size(); i++){
            total+=scores.at(i).toInt();
        }
        QMessageBox::information(this,usuario,"Estadisticas:\n\nNivel 1: "+scores.at(0)+"\n"+"Nivel 2: "+scores.at(1)+"\n"
                                +"Nivel 3: "+scores.at(2)+"\n\n"+"Puntaje global: "+QString::number(total));
    }
    else{
        QMessageBox::information(this,"usuario","Estadisticas:\n\nNivel 1: 0\nNivel 2: 0\n"
                                "Nivel 3: 0\n\nPuntaje global: 0");
    }
}
