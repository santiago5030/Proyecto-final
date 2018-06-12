#include "modojuego.h"

Modojuego::Modojuego(int _x, int _y, int _ancho, int _largo, QString _image)
{
    x=_x;
    y=_y;
    ancho=_ancho;      //Construccion de las dimensiones del objeto
    largo=_largo;
    image=_image;
}
QRectF Modojuego::boundingRect() const{
    return QRectF(x,y,ancho,largo);     //Recuadro que se genera de acuerdo a las dimensiones establecidas
}
void Modojuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPixmap pixmap;
    pixmap.load(image);
    painter-> drawPixmap(boundingRect(), pixmap,pixmap.rect());  //imagen que se carga de acuerdo al Boundingrect
}
