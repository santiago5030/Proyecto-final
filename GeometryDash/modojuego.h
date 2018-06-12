#ifndef MODOJUEGO_H
#define MODOJUEGO_H
#include <QGraphicsItem>
#include <QPainter>


class Modojuego : public QGraphicsItem
{
private:
    int x,y,ancho,largo; //Dimensiones del objeto
    QString image;       //imagen que se cargara en el objeto
public:
    Modojuego(int _x,int _y,int _ancho,int _largo, QString _image); //Constructor
    QRectF boundingRect() const;                                    //Recuadro que se generara entorno al objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};   //Metodo que cargara la imagen de acuerdo a las dimensiones establecidas en el Boundingrect

#endif // MODOJUEGO_H
