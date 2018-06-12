#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString _nuevo, QList<QString> list, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    usuario=_nuevo;                        //Contruccion de los datos del usuario
    for(int i=0; i < list.size(); i++){
        scores.append(list.at(i));
    }
    n= new selectlevels();                    //Definimos los objetos de las otras ventanas
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
    QFile archivo("puntaje.txt");                                //Se abre el archivo de puntajes en modo lectura
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    QString linea,user,puntaje;
    int num=0;
    while(!in.atEnd()){               //Ciclo que itera sobre las lineas y se almacena en una variable
        linea=in.readLine();
        while(linea[num] != ';'){     //Ciclo que extrae el usuario para cargar sus datos
            user+=linea[num];
            num++;
        }
        if(user==usuario){                //Verificamos que el usuario se encuenre en el archivo
            for(int i=0; i<3; i++){        //Ciclo para extraer los 3 puntajes de cada nivel
                num+=1;
                while(linea[num]!= ';'){   //Extraemos cada puntaje separado por ;
                    puntaje+=linea[num];
                    num++;
                }
                scores.append(puntaje);     //Agregamos el puntaje a la lista
                puntaje.clear();
            }
            break;
        }
        user.clear();
        num=0;
    }
}

void MainWindow::guardar()
{
    QFile archivo("puntaje.txt");        //Abrimos el archivo de puntajes en modo lectura
    QFile archivo2("temp.txt");          //Creamos un archivo temporal en modo escritura
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    if(!archivo2.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    QTextStream out(&archivo2);
    QString linea,user;          //Variables para almacenar las lineas y el usuario
    int num=0;
    bool ban=true;             //Bandera que indica el estado de la busqueda para modificar
    while(!in.atEnd()){        //Cilco que itera sobre las lineas del archivo de puntajes
        linea=in.readLine();
        if(ban){
            while(linea[num]!= ';'){     //Extraemos el usuario de la linea
                user+=linea[num];
                num++;
            }
            if(user==usuario){    //Verificamos que sea el usuario al cual se le realizara la modificacion del puntaje
                out<<usuario<<";"<<scores.at(0)<<";"<<scores.at(1)<<";"<<scores.at(2)<<";"<<"\n";
                ban=false;
            }                  //Escribimos los nuevos puntajes en el archivo temporal y cambiamos el estado de busqueda
            else{
                out <<linea<<"\n";
            }
            user.clear();
            num=0;
        }                                //Las lineas que no se modifican se escriben igual en el archivo temporal
        else{
            out <<linea<<"\n";
        }
    }
    archivo.close();
    archivo2.close();
    remove("puntaje.txt");            //Eliminamos el archivo de puntajes
    rename("temp.txt","puntaje.txt"); //Renombramos el archivo temporal como el archivo de puntajes actual
}

void MainWindow::datos()
{
    if(usuario.isNull() && nuevo->getinicio()){  //Verificamos si no se ha cargado el usuario y se ha iniciado sesion
        usuario=nuevo->getusuario();             //Cargamos el usuario que ha iniciado sesion en la variable
    }
    if(!usuario.isNull()){
        n->setusuario(usuario);      //Se setea el usuario de la siguiente ventana
    }
    if(!scores.isEmpty()){
        n->setlist(scores);        //Se setea la lista de puntajes de la siguiente ventana
    }
}

void MainWindow::on_pushButton_clicked()
{
    datos();
    n->show();      //Abrimos la ventana de seleccion de nivel
    close();
}

void MainWindow::on_actionRegistrarse_triggered()
{
    n2= new Registrarse();     //Se crea y abre la ventana para registrar el usuario
    n2->show();
}

void MainWindow::on_actionIniciar_Sesion_2_triggered()
{
    nuevo->show();     //Se abre la ventana para iniciar sesion
}

void MainWindow::on_actionCargar_triggered()
{
    if(usuario.isNull() && nuevo->getinicio()){
        usuario=nuevo->getusuario();
    }
    if(!usuario.isNull() && scores.isEmpty()){  //Verificamos que se haya iniciado sesion y no haya datos anteriores
        cargar(); //Se cargan los datos
        QMessageBox::information(this,"Cargar","Los datos se han cargado correctamente");
    }
    else{
        if(usuario.isNull()){
            QMessageBox::information(this,"Cargar","Debes iniciar sesion para cargar los datos");
        }
        else{
            if(!scores.isEmpty()){
                QMessageBox::StandardButton opcion;
                opcion=QMessageBox::question(this,"Cargar","Estas seguro que quieres cargar los datos?",
                                             QMessageBox::Yes | QMessageBox::No);
                if(opcion== QMessageBox::Yes){
                    cargar();
                    QMessageBox::information(this,"Cargar","Los datos se han cargado correctamente");
                }
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!scores.isEmpty()){
        int total=0;
        for(int i=0; i< scores.size(); i++){ //ciclo para calcular la suma total de los puntajes parciales
            total+=scores.at(i).toInt();
        }
        QMessageBox::information(this,usuario,"Estadisticas:\n\nNivel 1: "+scores.at(0)+"\n"+"Nivel 2: "+scores.at(1)+"\n"
                                +"Nivel 3: "+scores.at(2)+"\n\n"+"Puntaje global: "+QString::number(total));
    }
    else{
        QMessageBox::information(this,"usuario","Estadisticas:\n\nNivel 1: 0\nNivel 2: 0\n"
                                "Nivel 3: 0\n\nPuntaje global: 0");
    }  //En caso de que no se haya cargado los datos se muestra los puntajes iniciales
}

void MainWindow::on_actionGuardar_triggered()
{
    if(usuario.isNull() && nuevo->getinicio()){
        usuario=nuevo->getusuario();
    }
    if(!usuario.isNull() && !scores.isEmpty()){  //Verificamos que el usuario este cargado y haya datos para guardar
        QMessageBox::StandardButton opcion;
        opcion=QMessageBox::question(this,"Guardar","Esta seguro que desea guardar los datos?",
                                     QMessageBox::Yes | QMessageBox::No);
        if(opcion == QMessageBox::Yes){
            guardar();
            QMessageBox::information(this,"Guardar","Los datos se han guardado correctamente");
        }
    }
    if(usuario.isNull()){
        QMessageBox::information(this,"Guardar","Debes iniciar sesion para guardar los datos");
    }
    else{
        if(scores.isEmpty()){  //En caso de que no se haya cargado los datos se advierte de guardar sin cargar
            QMessageBox::StandardButton opcion2;
            opcion2=QMessageBox::question(this,"Guardar","No se han cargado los datos\n\nQuieres guardar de todos modos?",
                                  QMessageBox::Yes | QMessageBox::No);
            if(opcion2==QMessageBox::Yes){
                for(int i=0; i<3;i++){
                    scores.append("0");
                }
                guardar();
                QMessageBox::information(this,"Guardar","Los datos se han guardado correctamente");
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    n->setban(true);   //Bandera que indica el multijugador
    datos();
    n->show();         //Se abre la ventana de seleccion de niveles
    close();
}
