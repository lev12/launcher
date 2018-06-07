#include "abstractRequestForVersion.h"
#include "abstractRequestForVersion.h"

AbstractRequestForVersion::AbstractRequestForVersion(QString *serverAddress, unsigned short serverPort) : AbstractRequest (serverAddress,serverPort)
{

}

QString AbstractRequestForVersion::getRequestParam(QString token,QString app,QString ver)
{
    QString requestParam("?");
    requestParam.append(getTokenParam(token));
    requestParam.append("&");
    requestParam.append(getApplicationParam(app));
    requestParam.append("&");
    requestParam.append(getVersionParam(ver));
    return requestParam;
}
