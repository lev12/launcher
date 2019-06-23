#ifndef ABSTARCTWINDOW_H
#define ABSTARCTWINDOW_H

#include <QFrame>

#include <QTime>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QByteArray>

class AbstractWindow : public QFrame
{
public:
    AbstractWindow(unsigned int idtemp, QWidget *parent);
    ~AbstractWindow();

    unsigned int getWindowIndex();
    unsigned int getWindowId();

private:
    unsigned int *index;
    unsigned int *id;
};

#endif // ABSTARCTWINDOW_H
