#include "requestFile.h"

RequestFile::RequestFile(QUrl UrlFile, QFileInfo file)
{
    /*if (!(UrlFile.isValid()) || UrlFile.isEmpty())
    {
        throw "no valid url";
    }
    if (!(file.isFile()))
    {
        throw "is no file";
    }*/

    sendRequest(UrlFile);
    downloadFile = new QFile (file.absoluteFilePath());
    QDir mkDir;
    mkDir.mkpath(file.absolutePath());
    netReply = getNetReply();
    if (!(downloadFile->open(QFile::WriteOnly)))
    {
        throw "no creating file";
    }
    connect(netReply,QNetworkReply::readyRead, this, RequestFile::readData);
}

RequestFile::~RequestFile()
{
    downloadFile->close();

}


bool RequestFile::parse(QByteArray data)
{
    downloadFile->close();
    QList <NetworkData> *response = new QList <NetworkData> ();
    NetworkData netData;
    netData.key = "filePath";
    netData.value = QFileInfo(*downloadFile).absoluteFilePath();
    response->operator <<(netData);
    replyServer(response);
    deleteLater();
    return true;
}

void RequestFile::readData()
{
    downloadFile->write(netReply->readAll());
}
