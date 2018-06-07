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
    QFile archivo(nombre_archivo);
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    int n=0;
    while(!in.atEnd()){
        QString linea=in.readLine();
        while(linea[n] != ';'){
            user+=linea[n];
            n++;
        }
        if(user==usuario){
            for(int i=n+1; i < linea.length();i++){
                password+=linea[i];
            }
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
    return ban;
}

QString Inicio::getusuario()
{
    return usuario;
}

void Inicio::on_pushButton_clicked()
{
    usuario=ui->lineEdit->text();
    con=ui->lineEdit_2->text();
    if(usuario.length() > 15 || con.length() > 15){
        QMessageBox::information(this,"Iniciar Sesion","El usuario y la contraseña contienen menos de 15 caracteres");
    }
    if(usuario.isEmpty() || con.isEmpty()){
        QMessageBox::information(this,"Iniciar Sesion","Debes completar el registro");
    }
    if(usuario.length() <= 15 && con.length() <=15 && !usuario.isEmpty() && !con.isEmpty()){
        leer();
        if(user!= usuario){
            QMessageBox::information(this,"Iniciar Sesion","El usuario no se encuentra registrado");
            user.clear();
        }
        else{
            if(con==password){
                QMessageBox::information(this,"Iniciar Sesion","Se ha iniciado sesion correctamente");
                ban=true;
                close();
            }
            else{
                password.clear();
            }
        }
    }
}
