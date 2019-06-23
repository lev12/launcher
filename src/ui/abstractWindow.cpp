#include "abstractWindow.h"

AbstractWindow::AbstractWindow(unsigned int idtemp, QWidget *parent) : QFrame (parent)
{
    index = new unsigned int;
    id = new unsigned int;

    unsigned int tempIndex = unsigned(int(QDateTime::currentMSecsSinceEpoch()));
    tempIndex = tempIndex + QRandomGenerator::global()->generate();
    tempIndex = unsigned(QCryptographicHash::hash(QString(tempIndex).toLocal8Bit(),QCryptographicHash::Md5).toInt());
    *index = tempIndex;
    *id = idtemp;
}

AbstractWindow::~AbstractWindow()
{
    delete index;
    delete id;
}

unsigned int AbstractWindow::getWindowIndex()
{
    return *index;
}

unsigned int AbstractWindow::getWindowId()
{
    return *id;
}
