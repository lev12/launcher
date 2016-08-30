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

    w.setGeometry(100,100,cfg.get("width").toInt(),
                  cfg.get("height").toInt());

    QString fullScreanStr = cfg.get("fullScrean");
    if (fullScreanStr == "false")
    {
        w.showNormal();
    }
    else if (fullScreanStr == "true")
    {
        w.showMaximized();
    }

    w.show();



    return a.exec();
}
