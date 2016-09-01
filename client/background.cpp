#include "background.h"

background::background(QWidget *parent, QString pathToImage) : QWidget(parent)
{
    qDebug () << pathToImage;

    brush = new QBrush ();
    palette = new QPalette ();
    image = new QImage (pathToImage);
    widget = new QWidget ();
    widget = parent;

    brush->setTextureImage(image->
                           scaled(QSize(parent->width(),parent->height()),
                           Qt::KeepAspectRatioByExpanding));
    palette->setBrush(QPalette::Window, *brush);
    parent->setPalette(*palette);

}

void background::paintEvent (QPaintEvent *event)
{
    brush->setTextureImage(image->
                           scaled(QSize(widget->width(),widget->height()),
                           Qt::KeepAspectRatioByExpanding));
    palette->setBrush(QPalette::Window, *brush);
    widget->setPalette(*palette);
}
