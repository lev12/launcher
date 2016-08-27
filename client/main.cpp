#include "mainwindow.h"
#include <QApplication>
#include "config.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QTextStream>

int main(int argc, char *argv[])
{
    config cfg;



    QApplication a(argc, argv);
    MainWindow w;

    w.setGeometry(500,500,cfg.get("height"),cfg.get("width"));
    w.show();



    return a.exec();
}
