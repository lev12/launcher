#ifndef REQUESTFILE_H
#define REQUESTFILE_H

#include "abstractRequest.h"

class RequestFile : public AbstractRequest
{
public:
    RequestFile(QUrl UrlFile, QFileInfo file);
    ~RequestFile ();
    virtual bool parse (QByteArray data);

private:
    QNetworkReply *netReply;
    QFile *downloadFile;

private slots:
    void readData ();
};

#endif // REQUESTFILE_H
