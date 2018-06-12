#include "nivel.h"
#include "ui_nivel.h"
#include "mainwindow.h"
#include <QDebug>

Nivel::Nivel(int _opcion, bool _ban, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nivel)
{
    ui->setupUi(this);
    scene= new QGraphicsScene(0,0,700,300);    //Se crea la escena
    ui-> graphicsView -> setScene(scene);      //Se establece la escena al view

    l1= new QGraphicsLineItem(0,0,700,0);
    l2= new QGraphicsLineItem(0,0,0,300);
    l3= new QGraphicsLineItem(700,0,700,300);
    l4= new QGraphicsLineItem(0,300,700,300);
    scene->addItem(l1);                          //Se crea y grafiga las lineas entorno a la escena
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);

    opcion=_opcion;          //inicializacion de la variable que generara el nivel de acuerdo a lo seleccionado
    switch(opcion){          //switch case que genera el nivel de acuerdo a la opcion
    case 1:
        fondo=":/imagenes/fondo1";
        imagecubo=":/imagenes/cubo";
        imagepincho=":/imagenes/pincho";
        imagenave=":/imagenes/nave1";                  //imagenes del fondo y los objetos del nivel
        imagerocket=":/imagenes/obs";
        music="qrc:/songs/The Seven Seas.mp3";
        limite_i=180;
        limite_i2=180;           //intervalo con que se generara un pincho y un obstaculo
        control=40;
        control2=30;             //Control de velocidad, generacion de cubo y nave
        control3=20;
        vel=10;            //Velocidad
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
    ban=_ban;        //Bandera que indica el estodo del multijugador
    if(ban){
        intentos=2;     //La variable intentos es tomada ahora como vidas
        highscore=0;    //inicializacion del mayor puntaje
        ui->label->setText("Vidas");   //Cambio del contador de intentos por vidas
    }
    ui-> graphicsView-> setBackgroundBrush(QBrush(QImage(fondo)));    //se establece el fondo

    cubo= new Modojuego(40,260,40,40,imagecubo);          //Se crea el cubo
    scene->addItem(cubo);

    pincho= new Modojuego(670,272,24,25,imagepincho);     //Se crea un pincho
    scene->addItem(pincho);
    spike.append(pincho);

    srand(time(NULL));
    li=limite_i;         //Se inicializa las variables que generaran los pinchos aleatoriamente
    li2=limite_i2;
    ls=620;

    altura.append(20);
    altura.append(130);       //Lista de las alturas con que se generaran los obstaculos
    altura.append(220);

    rango=li+ rand()% ((ls+1)-li);        //Rango/distancia con que se genera un pincho de otro

    ui->lcdNumber_2->display(intentos);  //intentos que se muestran en el nivel

    musica= new QMediaPlayer(this);      //Objeto para reproducir la musica del nivel
    musica->setMedia(QUrl(music));

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(actualizar()));  //timer que simula el juego
}

Nivel::~Nivel()
{
    delete ui;
    delete cubo;
    delete pincho;
}

void Nivel::actualizar()  //Metodo que simula el juego actualizando todas las condiciones de los objetos
{
    if(!spike.isEmpty()){  //Se genera el juego con cubo
        pinchos();
        colision();
        Saltar();
    }
    else{
        if(rocket.isEmpty()){  //Se genera la nave
            delete cubo;
            cont2=0;
            nave= new Modojuego(40,270,55,40,imagenave);
            scene->addItem(nave);
            elemento=new Modojuego(650,20,80,80,imagerocket);  //inicializacion de las condiciones de la nave
            scene->addItem(elemento);
            rocket.append(elemento);
            height= 0 + rand()% 3;
            rango=li2+ rand()% ((ls+1)-li2);
        }
        Nave();
        colision2();
    }
    Score();        //actualizacion del puntaje
    Musica();       //Control de musica
    if(cont>=control){          //aumenta la velocidad cada ciertos saltos
        dist+=2;       //aumento de la velocidad
        cont=0;
        if((li+20)< ls){         //Aumento de los intervalos de generacionde pinchos y obstaculos
            li+=20;
        }
        if((li2+20) < ls){
            li2+=20;
        }
        if(dist == vel+2){
            control2=50;
        }
    }
    if(ban){
        Multi();   //Multijugador
    }
}

void Nivel::Saltar()          //Salto
{
    if(saltar){
        cubo->setY(cubo->pos().y()-10);   //aumenta la posicion en y
    }
    else{
        if(cubo->pos().y()!= 0){
            cubo->setY(cubo->pos().y()+10);  //regresa a la posicion original en y
        }
    }
    if(cubo->pos().y() < -80){      //control de la distancia que sube el cubo en el salto
        saltar=false;
    }
}

void Nivel::pinchos()
{
    if(spike.last()->pos().x() < -rango && cont2 <= control2){    //Agrega pinchos de acuerdo a un rango y un control
        spike.append(new Modojuego(670,272,24,25,imagepincho));   //crea un nuevo pincho y lo agreaga a la lista
        scene->addItem(spike.last());
        rango=li+ rand()% ((ls+1)-li);       //genera un rango aleatorio de acuerdo a los intervalos actuales
    }
    for(int i=0; i < spike.size(); i++){               //ciclo que itera sobre los pinchos de la lista
        spike.at(i)->setX(spike.at(i)->pos().x()-dist);     //Movimiento de los pinchos en x de acuerdo a la velocidad
        if(spike.at(i)->pos().x() < -700){
            delete spike.at(i);        //cuando un pincho llega al final se elimina el objeto y se elimina de la lista
            spike.removeAt(i);
        }
    }
}

void Nivel::colision()
{
    for(int i=0; i < spike.size(); i++){         //ciclo que evalua cada pincho de la lista
        if(cubo->collidesWithItem(spike.at(i))){     //detecta si el cubo ha colisionado con algun pincho de la lista
            timer->stop();          //Se detiene el timer y la musica
            musica->stop();
            if(ban){
                intentos--;    //Se le resta a las vidas
                ui->lcdNumber_2->display(intentos); //Se muestra las vidas actuales
            }
        }
    }
}

void Nivel::Score()
{
    score+=1;             //Se incrementa el score de acuerdo al timer
    ui->lcdNumber->display(score);
}

void Nivel::Nave()
{
    if(rocket.last()->pos().x() < -rango && cont2 <= control3){ //Agrega un obstaculo dependiendo del rango
        rocket.append(new Modojuego(650,altura.at(height),80,80,imagerocket));
        scene->addItem(rocket.last());                                  //Agrega un obstaculo con altura aleatoria
        rango=li2 + rand()% ((ls+1)-li2);                 //Genera un rango y una altura aleatoria
        height= 0 + rand()% 3;
        cont2++;
    }
    for(int i=0; i < rocket.size(); i++){                  //ciclo que itera sobre los obstaculos
        rocket.at(i)->setX(rocket.at(i)->pos().x()-dist);  //Movimiento de los obstaculos de acuerdo a la velocidad
        if(rocket.at(i)->pos().x() < -700){
            delete rocket.at(i);            //Elimina el objeto y lo elimina de la lista
            rocket.removeAt(i);
        }
    }
    if(rocket.isEmpty()){                     //Al finalizar se vuelve a generar el cubo y un pincho
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
    for(int i=0; i < rocket.size(); i++){            //Ciclo que itera sobre los obstaculos de la lista
        if(nave->collidesWithItem(rocket.at(i))){   //Detecta si la nave ha colisionado con algun abstaculo de la lista
            timer->stop();       //Se detiene el timer y la musica
            musica->stop();
            if(ban){
                intentos--;     //Se le resta a las vidas
                ui->lcdNumber_2->display(intentos);    //Se muestra las vidas actuales
            }
        }
    }
}

void Nivel::Musica()
{
    if(musica->position()== musica->duration()){   //Si la musica llega al fianl se vuelve a reproducir
        musica->play();
    }
}

void Nivel::setusuario(QString _usuario)
{
    usuario=_usuario;        //Setea el usuario
}

void Nivel::setlist(QList<QString> lista)
{
    for(int i=0; i < lista.size(); i++){    //Setea la lista de puntajes
        scores.append(lista.at(i));
    }
}

void Nivel::setscore()
{
    score=0;
    highscore=0;
    if(!scores.isEmpty()){
        highscore=scores.at(opcion-1).toInt();  //Asigna el puntaje del nivel convertido a entero
    }
    else{
        for(int i=0; i<3; i++){         //Si no hay datos rellena la lista con 0
            scores.append("0");
        }
    }
}

void Nivel::Multi()
{
    if(intentos == 0 && !multi.isEmpty()){
        if(score > highscore){           //Evalua el ultimo puntaje obtenido si es mayor lo cambia
            highscore=score;
        }
        multi.append(highscore);       //Agreaga el puntaje a la lista
        QMessageBox::information(this,"Jugador "+QString::number(multi.size()),"Mayor puntaje obtenido: "+
                                 QString::number(highscore));
        QMessageBox::StandardButton nuevo;
        nuevo=QMessageBox::question(this,"Nuevo","Quiere agregar otro jugador?", QMessageBox::Yes | QMessageBox::No);
        if(nuevo == QMessageBox::Yes){
            highscore=0;
            score=0;               //inicializacion de variables
            intentos=2;
            ui->lcdNumber_2->display(intentos);
        }
        if(nuevo == QMessageBox::No){
            int n=0;
            mayor(n);     //calcula el maoy puntaje obtenido
            QMessageBox::information(this,"Puntaje","El ganador es el jugador "+QString::number(n)+"\n\nPuntaje: "
                                     +QString::number(multi.at(n-1)));
        }       //indica el jugador y el puntaje del mayor
    }
    if(intentos == 0 && multi.isEmpty()){
        if(score > highscore){
            highscore=score;
        }
        multi.append(highscore);
        QMessageBox::information(this,"Jugador 1","Mayor puntaje obtenido: "+QString::number(highscore));
        highscore=0;
        score=0;
        intentos=2;
        ui->lcdNumber_2->display(intentos);
    }
}

void Nivel::mayor(int &n)
{
    int mayor=0;
    for(int i=0; i < multi.size(); i++){ //ciclo que itera sobre los puntajes de la lista
        if(multi[i] > mayor){
            mayor=multi[i];
            n=i+1;               //Asigna el indice + 1 del con mayor puntaje de la lista
        }
    }
}

void Nivel::on_pushButton_clicked()
{
    timer->stop();
    musica->stop();
    intentos=0;
    if(!ban){
        if(score > highscore){
            highscore= score;
        }
        if(!scores.isEmpty()){
            QString nuevo=QString::number(highscore);
            if(nuevo != scores.at(opcion-1)){
                scores.replace(opcion-1,nuevo);        //Si se obtuvo un puntaje mayor lo reemplaza en la lista
            }
        }
    }
    MainWindow *menu=new MainWindow(usuario,scores);  //Se crea un objeto del menu principal con los datos actualizados
    menu->show();
    close();
}

void Nivel::keyPressEvent(QKeyEvent *accion)
{
    if(accion ->key()== Qt::Key_Space && !spike.isEmpty()){
        if(cubo->pos().y() == 0){     //Detecta si se esta presionando la tecla espacio para saltar
            saltar=true;              //solo se puede saltar si se esta en la posicion original
            cont++;
            cont2++;
        }
    }
    if(accion ->key()== Qt::Key_M && spike.isEmpty() && timer->isActive()){
        if(nave->pos().y() > -270){                        //Evalua si la nave esta en un rango de movimieno permitido
            nave->setY(nave->pos().y()-18);                //Mueve la nave hacia arriba
        }
    }
    if(accion ->key()== Qt::Key_N && spike.isEmpty() && timer->isActive()){
        if(nave->pos().y() < -20){                 //Evalua si la nave esta en un rango de movimieno permitido
            nave->setY(nave->pos().y()+18);        //Mueve la nave hacia abajo
        }
    }
    if(accion->key()== Qt::Key_R){  //Reinicia las condiciones iniciales del juego al presionar R
        if(!ban){
            timer->start(20);         //inicia el timer y la musica
            musica->play();
            cont=0;
            cont2=0;
            dist=vel;
            li=limite_i;
            li2=limite_i2;
            ls=620;
            intentos++;             //Aumenta los intentos en 1
            if(score > highscore){
                highscore= score;
            }
            score=0;
            ui->lcdNumber_2->display(intentos);
            if(!spike.isEmpty()){
                cubo->setPos(0,0);
                for(int i=0; i< spike.size()-1; i++){
                    delete spike.at(i);
                    spike.removeAt(i);
                }
                spike.last()->setPos(0,0);                  //inicializa las listas de pinchos y obstaculos
            }
            else{
                for(int i=0; i < rocket.size()-1; i++){
                    delete rocket.at(i);
                    rocket.removeAt(i);
                }
                rocket.last()->setPos(0,0);
            }
            if(intentos==1){
                setscore();
            }
        }
        else{
            if(intentos != 0){
                timer->start(20);
                musica->play();
                cont=0;
                cont2=0;
                dist=vel;
                li=limite_i;
                li2=limite_i2;
                ls=620;
                if(score > highscore){
                    highscore= score;
                }
                score=0;
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
    }
}
