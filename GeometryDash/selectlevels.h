#ifndef SELECTLEVELS_H
#define SELECTLEVELS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include "nivel.h"

namespace Ui {
class selectlevels;
}

class selectlevels : public QWidget
{
    Q_OBJECT

public:
    explicit selectlevels(QWidget *parent = 0);
    ~selectlevels();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::selectlevels *ui;
    Nivel *level;
    QGraphicsScene *scene;
    int n;
};

#endif // SELECTLEVELS_H
