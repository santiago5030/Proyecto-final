#include "inicio.h"
#include "ui_inicio.h"

Inicio::Inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inicio)
{
    ui->setupUi(this);
    nombre_archivo="registro.txt";
    ban=false;
}

Inicio::~Inicio()
{
    delete ui;
}

void Inicio::leer()
{
    QFile archivo(nombre_archivo);                             //Abrimos el archivo de registro el modo lectura
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    int n=0;
    while(!in.atEnd()){
        QString linea=in.readLine();
        while(linea[n] != ';'){        //Ciclo que extrae el ususario de cada linea
            user+=linea[n];
            n++;
        }
        if(user==usuario){
            for(int i=n+1; i < linea.length();i++){ //Verificamos que el usuario ingresado coincida con alguno
                password+=linea[i];                 //registrado
            }                         //Extraemos la contraseña de la linea y verificamos que coincida con la ingresada
            if(con!=password){
                QMessageBox::information(this,"Iniciar Sesion","La contraseña es incorrecta");
            }
            break;
        }
        user.clear();
        n=0;
    }
    archivo.close();
}

bool Inicio::getinicio()
{
    return ban;          //Retorno de bandera que indica si se ha iniciado sesion
}

QString Inicio::getusuario()
{
    return usuario;          //Retorno del usuario que ha iniciado sesion
}

void Inicio::on_pushButton_clicked()
{
    usuario=ui->lineEdit->text();     //Guardamos los datos ingresados
    con=ui->lineEdit_2->text();
    if(usuario.length() > 15 || con.length() > 15){
        QMessageBox::information(this,"Iniciar Sesion","El usuario y la contraseña contienen menos de 15 caracteres");
    }
    if(usuario.isEmpty() || con.isEmpty()){
        QMessageBox::information(this,"Iniciar Sesion","Debes completar el registro");
    }
    if(usuario.length() <= 15 && con.length() <=15 && !usuario.isEmpty() && !con.isEmpty()){ //control de usuario
        leer();
        if(user!= usuario){
            QMessageBox::information(this,"Iniciar Sesion","El usuario no se encuentra registrado");
            user.clear();
        }                    //Verificamos que el usuario se encuentre registrado y la contraseña coincida
        else{
            if(con==password){
                QMessageBox::information(this,"Iniciar Sesion","Se ha iniciado sesion correctamente");
                ban=true;
                close();          //la bandera indica que se ha iniciado sesion
            }
            else{
                password.clear();
                user.clear();
            }
        }
    }
}
