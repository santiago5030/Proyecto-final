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
    void leer();
    void agregar();
    void agregar2();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Registrarse *ui;
    QString usuario,con,nombre_archivo,user,nombre_archivo2;
};

#endif // REGISTRARSE_H
