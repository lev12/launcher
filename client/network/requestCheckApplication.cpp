#include "requestCheckApplication.h"

RequestCheckApplication::RequestCheckApplication(QString serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool RequestCheckApplication::parse(QByteArray data)
{

}
