#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>
#include <QImage>
#include <QString>
#include <QBrush>
#include <QPalette>
#include <QPainter>

class background
{

private:
    QBrush *brush;
    QPalette *palette;
public:
    background(QWidget *parent, QString path);

    QImage *image;
    QString *pathImage;

#endif // BACKGROUND_H
