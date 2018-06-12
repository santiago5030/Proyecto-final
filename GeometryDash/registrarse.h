#ifndef REGISTRARSE_H
#define REGISTRARSE_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Registrarse;
}

class Registrarse : public QWidget
{
    Q_OBJECT

public:
    explicit Registrarse(QWidget *parent = 0);
    ~Registrarse();
public slots:
    void leer();      //Medoto que lee el archivo
    void agregar();   //Metodo que lo agrega el usuario al archivo de registro
    void agregar2();  //Metodo que lo agrega al usuario archivo de puntajes
private slots:
    void on_pushButton_clicked(); //Boton de registrarse

private:
    Ui::Registrarse *ui;
    QString usuario,con,nombre_archivo,user,nombre_archivo2; //Variables de control
};

#endif // REGISTRARSE_H
