#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>


class server
{
private:
    QTcpServer *server_tcp;

public:
    server();
};

#endif // SERVER_H
