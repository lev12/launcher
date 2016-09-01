#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QBrush>
#include <QPalette>
#include <QImage>
#include <QSize>

class background : public QWidget
{
    Q_OBJECT
public:
    explicit background(QWidget *parent = 0, QString pathToImage = NULL);

private:
    QBrush *brush;
    QPalette *palette;
    QImage *image;
    QWidget *widget;

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BACKGROUND_H
