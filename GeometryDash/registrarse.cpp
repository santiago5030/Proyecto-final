#include "registrarse.h"
#include "ui_registrarse.h"

Registrarse::Registrarse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registrarse)
{
    ui->setupUi(this);
    nombre_archivo="registro.txt";
    nombre_archivo2="puntaje.txt";
}

Registrarse::~Registrarse()
{
    delete ui;
}

void Registrarse::leer()
{
    QFile archivo(nombre_archivo);            //Se abre el archivo en modo lectura
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    QString linea;
    while(!in.atEnd()){             //Ciclo que itera sobre las lineas del archivo
        linea= in.readLine();
        for(int i=0; linea[i] != ';'; i++){  //Ciclo que extrae el usuario de cada linea
            user+=linea[i];
        }
        if(user==usuario){     //Verificamos que el usuario no se encuentre registrado
            QMessageBox::information(this,"Registro","El usuario ya se encuentra registrado");
            break;
        }
        user.clear();
    }
    archivo.close();
}

void Registrarse::agregar()
{
    QFile archivo(nombre_archivo); //Abrimos el archivo en modo agregar
    if(!archivo.open(QIODevice::Append | QIODevice::Text)){
        return;
    }
    QTextStream out(&archivo);
    out <<usuario<<";"<<con<<"\n";  //Escribimos el usuario segudo de un ; y la contraseña
    archivo.close();
}

void Registrarse::agregar2()
{
    QFile archivo(nombre_archivo2);  //Abrimos el archivo en modo agregar
    if(!archivo.open(QIODevice::Append | QIODevice::Text)){
        return;
    }
    QTextStream out(&archivo);
    out <<usuario<<";"<<0<<";"<<0<<";"<<0<<";"<<"\n";  //Escribimos el usuario con los puntajes iniciales dividido por ;
    archivo.close();
}

void Registrarse::on_pushButton_clicked()
{
    usuario= ui->lineEdit->text();  //Guardamos los datos ingresados
    con=ui->lineEdit_2->text();
    if(usuario.length() > 15 || con.length() > 15){
        QMessageBox::information(this,"Registrarse","El usuario y contraseña deben contener menos de 15 caracteres");
    }
    if(usuario.isEmpty() || con.isEmpty()){
        QMessageBox::information(this,"Registro","Debes llenar el registro");
    }
    if(usuario.length() <= 15 && con.length() <=15 && !usuario.isEmpty() && !con.isEmpty()){
        leer();
        if(user!=usuario){
            agregar();     //Se escribe en los archivos si no se encuentra registrado
            agregar2();
            QMessageBox::information(this,"Registro","El registro se ha hecho correctamente");
        }
        close();
    }
}
