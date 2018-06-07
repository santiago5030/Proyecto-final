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
    void leer();
    bool getinicio();
    QString getusuario();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Inicio *ui;
    QString usuario,con,user,nombre_archivo,password;
    bool ban;
};

#endif // INICIO_H
