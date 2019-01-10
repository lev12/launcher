#ifndef REQUESTFILEMOCK_H
#define REQUESTFILEMOCK_H

#include "network/requestFile.h"
#include <QTimer>

class RequestFileMock : public RequestFile
{
public:
    RequestFileMock(QUrl UrlFile, QFileInfo File);
    virtual bool parse(QByteArray data);
private:
    QUrl *urlFile;
    QFileInfo *file;
private slots:
    void recive ();
};

#endif // REQUESTFILEMOCK_H
