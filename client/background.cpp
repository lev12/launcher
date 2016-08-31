#include "background.h"


background::background(QWidget *parent, QString path)
{
    pathImage = new QString(path);
    image = new QImage ();
    brush = new QBrush ();
    palette = new QPalette ();
    brush->setTextureImage(QImage(pathImage->toLocal8Bit()).scaled(QSize(3840,2160),
                           Qt::KeepAspectRatioByExpanding));
    palette->setBrush(QPalette::Background, *brush);
    parent->setPalette(*palette);
}
