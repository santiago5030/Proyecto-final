#include "nivel.h"
#include "ui_nivel.h"
#include "mainwindow.h"
#include <QDebug>

Nivel::Nivel(int _opcion, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nivel)
{
    ui->setupUi(this);
    scene= new QGraphicsScene(0,0,700,300);
    ui-> graphicsView -> setScene(scene);

    l1= new QGraphicsLineItem(0,0,700,0);
    l2= new QGraphicsLineItem(0,0,0,300);
    l3= new QGraphicsLineItem(700,0,700,300);
    l4= new QGraphicsLineItem(0,300,700,300);
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);

    opcion=_opcion;
    switch(opcion){
    case 1:
        fondo=":/imagenes/fondo1";
        imagecubo=":/imagenes/cubo";
        imagepincho=":/imagenes/pincho";
        imagenave=":/imagenes/nave1";
        imagerocket=":/imagenes/obs";
        music="qrc:/songs/The Seven Seas.mp3";
        limite_i=180;
        limite_i2=180;
        control=40;
        control2=30;
        control3=20;
        vel=10;
        break;
    case 2:
        fondo=":/imagenes/fondo2";
        imagecubo=":/imagenes/cubo2";
        imagepincho=":/imagenes/pincho2";
        imagenave=":/imagenes/nave2";
        imagerocket=":/imagenes/obs2";
        music="qrc:/songs/VikingArena.mp3";
        limite_i=200;
        limite_i2=220;
        control=30;
        control2=20;
        control3=20;
        vel=12;
        break;
    case 3:
        fondo=":/imagenes/fondo3";
        imagecubo=":/imagenes/cubo3";
        imagepincho=":/imagenes/pincho3";
        imagenave=":/imagenes/nave3";
        imagerocket=":/imagenes/obs3";
        music="qrc:/songs/AirborneRobots.mp3";
        limite_i=220;
        limite_i2=240;
        control=30;
        control2=20;
        control3=20;
        vel=14;
        break;
    }
    ui-> graphicsView-> setBackgroundBrush(QBrush(QImage(fondo)));

    cubo= new Modojuego(40,260,40,40,imagecubo);
    scene->addItem(cubo);

    pincho= new Modojuego(670,272,24,25,imagepincho);
    scene->addItem(pincho);
    spike.append(pincho);

    srand(time(NULL));
    li=limite_i;
    li2=limite_i2;
    ls=620;
    cout<<"nivel opcion: "<<opcion<<endl;

    altura.append(20);
    altura.append(130);
    altura.append(220);

    rango=li+ rand()% ((ls+1)-li);
    cout<<"primero: "<<rango<<endl;

    ui->lcdNumber_2->display(intentos);

    musica= new QMediaPlayer(this);
    musica->setMedia(QUrl(music));

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
    if(!spike.isEmpty()){
        pinchos();
        colision();
        Saltar();
    }
    else{
        if(rocket.isEmpty()){
            delete cubo;
            cont2=0;
            nave= new Modojuego(40,270,55,40,imagenave);
            scene->addItem(nave);
            elemento=new Modojuego(650,20,80,80,imagerocket);
            scene->addItem(elemento);
            rocket.append(elemento);
            height= 0 + rand()% 3;
            rango=li2+ rand()% ((ls+1)-li2);
        }
        Nave();
        colision2();
    }
    Score();
    Musica();
    if(cont>=control){
        dist+=2;
        cont=0;
        if((li+20)< ls){
            li+=20;
        }
        if((li2+20) < ls){
            li2+=20;
        }
        if(dist == vel+2){
            control2=70;
        }
    }
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

void Nivel::pinchos()
{
    if(spike.last()->pos().x() < -rango && cont2 <= control2){
        spike.append(new Modojuego(670,272,24,25,imagepincho));
        scene->addItem(spike.last());
        rango=li+ rand()% ((ls+1)-li);
        cout<<"rango: "<<rango<<endl;
        cout<<"contador2: "<<cont2<<endl;
        cout<<"con vel: "<<cont<<endl;
        cout<<"velocidad: "<<dist<<endl;
        cout<<"control2: "<<control2<<endl;
    }
    for(int i=0; i < spike.size(); i++){
        spike.at(i)->setX(spike.at(i)->pos().x()-dist);
        if(spike.at(i)->pos().x() < -700){
            delete spike.at(i);
            spike.removeAt(i);
        }
    }
}

void Nivel::colision()
{
    for(int i=0; i < spike.size(); i++){
        if(cubo->collidesWithItem(spike.at(i))){
            timer->stop();
            musica->stop();
        }
    }
}

void Nivel::Score()
{
    score+=1;
    ui->lcdNumber->display(score);
}

void Nivel::Nave()
{
    if(rocket.last()->pos().x() < -rango && cont2 <= control3){
        rocket.append(new Modojuego(650,altura.at(height),80,80,imagerocket));
        scene->addItem(rocket.last());
        rango=li2 + rand()% ((ls+1)-li2);
        height= 0 + rand()% 3;
        cont2++;
        cout<<"rango nave: "<<rango<<endl;
        cout<<"altura: "<<height<<endl;
        cout<<"contador2: "<<cont2<<endl;
        cout<<"control3: "<<control3<<endl;
    }
    for(int i=0; i < rocket.size(); i++){
        rocket.at(i)->setX(rocket.at(i)->pos().x()-dist);
        if(rocket.at(i)->pos().x() < -700){
            delete rocket.at(i);
            rocket.removeAt(i);
        }
    }
    if(rocket.isEmpty()){
        delete nave;
        cubo= new Modojuego(40,260,40,40,imagecubo);
        scene->addItem(cubo);

        pincho= new Modojuego(670,272,24,25,imagepincho);
        scene->addItem(pincho);
        spike.append(pincho);
        rango=li+ rand()% ((ls+1)-li);
        cont2=0;
    }
}

void Nivel::colision2()
{
    for(int i=0; i < rocket.size(); i++){
        if(nave->collidesWithItem(rocket.at(i))){
            timer->stop();
            musica->stop();
        }
    }
}

void Nivel::Musica()
{
    if(musica->position()== musica->duration()){
        musica->play();
    }
}

void Nivel::on_pushButton_clicked()
{
    MainWindow *menu= new MainWindow;
    timer->stop();
    musica->stop();
    intentos=0;
    if(score > highscore){
        highscore= score;
    }
    menu->show();
    close();
}

void Nivel::keyPressEvent(QKeyEvent *accion)
{
    if(accion ->key()== Qt::Key_Space && !spike.isEmpty()){
        saltar=true;
        cont++;
        cont2++;
    }
    if(accion ->key()== Qt::Key_M && spike.isEmpty() && timer->isActive()){
        if(nave->pos().y() > -270){
            nave->setY(nave->pos().y()-18);
        }
    }
    if(accion ->key()== Qt::Key_N && spike.isEmpty() && timer->isActive()){
        if(nave->pos().y() < -20){
            nave->setY(nave->pos().y()+18);
        }
    }
    if(accion->key()== Qt::Key_R){
        timer->start(20);
        musica->play();
        cont=0;
        cont2=0;
        dist=vel;
        score=0;
        li=limite_i;
        li2=limite_i2;
        ls=620;
        intentos++;
        if(score > highscore){
            highscore= score;
        }
        ui->lcdNumber_2->display(intentos);
        if(!spike.isEmpty()){
            cubo->setPos(0,0);
            for(int i=0; i< spike.size()-1; i++){
                delete spike.at(i);
                spike.removeAt(i);
            }
            spike.last()->setPos(0,0);
        }
        else{
            for(int i=0; i < rocket.size()-1; i++){
                delete rocket.at(i);
                rocket.removeAt(i);
            }
            rocket.last()->setPos(0,0);
        }
    }
}
