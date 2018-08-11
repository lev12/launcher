#include "requestFile.h"

RequestFile::RequestFile(QUrl UrlFile, QFileInfo file)
{
    if (!(UrlFile.isValid()) || UrlFile.isEmpty())
    {
        throw "no valid url";
    }

    sendRequest(UrlFile);
    downloadFile = new QFile (file.absoluteFilePath());
    QDir mkDir;
    mkDir.mkpath(file.absolutePath());
    netReply = getNetReply();
    if (!(downloadFile->open(QFile::WriteOnly)))
    {
        if (!(file.isFile()))
        {
            qDebug () << file.absoluteFilePath();
            throw "is no file";
        }
        else
        {
            throw "no creating file";
        }
    }
    netReply->bytesAvailable();
    connect(netReply,QNetworkReply::readyRead, this, RequestFile::readData);
}

RequestFile::~RequestFile()
{
    downloadFile->close();

}


bool RequestFile::parse(QByteArray data)
{
    downloadFile->close();
    netReply->close();

    QList <NetworkData> *response = new QList <NetworkData> ();
    NetworkData netData;
    netData.key = "filePath";
    netData.value = QFileInfo(*downloadFile).absoluteFilePath();
    response->operator <<(netData);
    replyServer(response);
    delete this;
    return true;
}

void RequestFile::readData()
{
    downloadFile->write(netReply->readAll());
    downloadFile->flush();
}
