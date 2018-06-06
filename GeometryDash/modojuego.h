#ifndef MODOJUEGO_H
#define MODOJUEGO_H
#include <QGraphicsItem>
#include <QPainter>


class Modojuego : public QGraphicsItem
{
private:
    int x,y,ancho,largo;
    QString image;
public:
    Modojuego(int _x,int _y,int _ancho,int _largo, QString _image);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MODOJUEGO_H
