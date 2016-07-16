#include "server.h"

server::server()
{
    server_tcp = new QTcpServer();
    server_tcp->listen(QHostAddress::Any,80);
    connect (server_tcp, SIGNAL(newConnection()), this, );
}
