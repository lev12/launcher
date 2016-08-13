#include <QCoreApplication>
#include "server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    server q;

    return a.exec();
}
