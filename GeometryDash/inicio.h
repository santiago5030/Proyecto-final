#ifndef INICIO_H
#define INICIO_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Inicio;
}

class Inicio : public QWidget
{
    Q_OBJECT

public:
    explicit Inicio(QWidget *parent = 0);
    ~Inicio();

public slots:
    void leer();          //Metodo para leer el archivo donde se encuentre registrado el ususario
    bool getinicio();     //Metodo get para determinar si se ha logrado iniciar sesion
    QString getusuario(); //Metodo para obtener el usuario que ha iniciado sesion
private slots:
    void on_pushButton_clicked();   //Boton de login (iniciar sesion)

private:
    Ui::Inicio *ui;
    QString usuario,con,user,nombre_archivo,password; // variables de control
    bool ban;
};

#endif // INICIO_H
