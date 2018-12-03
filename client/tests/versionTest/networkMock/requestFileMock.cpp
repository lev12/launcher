#include "requestFileMock.h"

RequestFileMock::RequestFileMock(QUrl UrlFile, QFileInfo File) :
    RequestFile ()
{
    urlFile = new QUrl (UrlFile);
    file = new QFileInfo (File);
    QTimer::singleShot(600, this, &RequestFileMock::recive);
}

bool RequestFileMock::parse(QByteArray data)
{

}

void RequestFileMock::recive()
{
    QString relPath (urlFile->path());
    relPath = relPath.remove(0,4);
    QString resPath (":/versionTestForNetworkData/");
    resPath.append(relPath);
    QFile::copy(resPath,file->absolutePath());
}
