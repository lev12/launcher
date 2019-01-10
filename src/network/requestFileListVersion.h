#ifndef REQUESTFILELISTVERSION_H
#define REQUESTFILELISTVERSION_H

#include "abstractRequestForVersion.h"

class RequestFileListVersion : public AbstractRequestForVersion
{
public:
    RequestFileListVersion();
    RequestFileListVersion(QString *serverAddress, unsigned short serverPort, QString token, QString app, QString ver);
    virtual bool parse (QByteArray data);
private:

    QNetworkReply *netReply;
    const QString method = "fileList";

private slots:
    void readData ();
};

#endif // REQUESTFILELISTVERSION_H
