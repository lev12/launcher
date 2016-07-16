#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include "file.h"

class server
{
private:
    QTcpServer *server_tcp;

private slots:
    void Connect ();
public:
    server();
};

#endif // SERVER_H
