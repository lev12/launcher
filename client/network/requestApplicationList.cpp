#include "requestApplicationList.h"

RequestApplicationList::RequestApplicationList(QString serverAddress, int serverPort, QString token) : AbstractRequest (serverAddress,serverPort)
{
    sendRequest(getRequestUrl(method,getRequestParam(token)));
}

bool RequestApplicationList::parse(QByteArray data)
{

}
