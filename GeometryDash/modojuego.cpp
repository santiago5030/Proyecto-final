#include "modojuego.h"

Modojuego::Modojuego(int _x, int _y, int _ancho, int _largo, QString _image)
{
    x=_x;
    y=_y;
    ancho=_ancho;
    largo=_largo;
    image=_image;
}
QRectF Modojuego::boundingRect() const{
    return QRectF(x,y,ancho,largo);
}
void Modojuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPixmap pixmap;
    pixmap.load(image);
    painter-> drawPixmap(boundingRect(), pixmap,pixmap.rect());
}
