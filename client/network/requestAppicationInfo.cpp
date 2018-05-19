#include "requestAppicationInfo.h"

requestAppicationInfo::requestAppicationInfo(QString serverAddress, unsigned short serverPort,QString token,QString app) : AbstractRequestForApplication (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token,app)));
}

bool requestAppicationInfo::parse(QByteArray data)
{

}
