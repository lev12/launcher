#include "abstractRequestForApplication.h"
#include "abstractRequestForApplication.h"

AbstractRequestForApplication::AbstractRequestForApplication(QString *serverAddress, unsigned short serverPort) : AbstractRequest (serverAddress,serverPort)
{

}

QString AbstractRequestForApplication::getRequestParam(QString token,QString app)
{
    QString requestParam("?");
    requestParam.append(getTokenParam(token));
    requestParam.append("&");
    requestParam.append(getApplicationParam(app));
    return requestParam;
}
