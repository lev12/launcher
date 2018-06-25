#include "requestVersion.h"

RequestVersion::RequestVersion(QString *serverAddress, unsigned short serverPort, QString Token, QString *app, QString *version) : AbstractRequest (serverAddress,serverPort)
{
    init (*version, *app);
    token = new QString (Token);
    getCheckVersion(verName, appName);
}

bool RequestVersion::parse(QByteArray data)
{
    QString errorstr = "parser version  ";
    errorstr.append(data);
    throw errorstr;
}

bool RequestVersion::init(QString versionName, QString applicationName)
{
    verName = new QString (versionName);
    appName = new QString (applicationName);

    QString pathVersion = ".//";
    pathVersion.append(_Data);
    pathVersion.append(applicationName);
    pathVersion.append("/");
    pathVersion.append(versionName);
    verPath = new QDir (pathVersion);

    return true;
}

bool RequestVersion::getCheckVersion(QString *VerName, QString *AppName)
{
    AbstractRequest *reqestCheckVer = new RequestCheckVersion (serverAddress, *serverPort, *token, *AppName, *VerName);
    connect(reqestCheckVer, AbstractRequest::replyServer, this, RequestVersion::receiveCheckVersion);
    return true;
}

bool RequestVersion::getVersionInfo(QString *VerName, QString *AppName)
{
    AbstractRequest *reqestVerInfo = new RequestVersionInfo (serverAddress, *serverPort, *token, *AppName, *VerName);
    connect(reqestVerInfo, AbstractRequest::replyServer, this, RequestVersion::receiveVersionInfo);
    return true;
}

bool RequestVersion::getFileListVersion(QString *VerName, QString *AppName)
{
    AbstractRequest *reqestFileListVer = new RequestFileListVersion (serverAddress, *serverPort, *token, *AppName, *VerName);
    connect(reqestFileListVer, AbstractRequest::replyServer, this, RequestVersion::receiveFileListVersion);
    return true;
}

bool RequestVersion::getFile()
{
    QUrl absUrlFile (absoluteUrlPath(verFileReletivePathList->at(*indexDownloadFile)));
    QFileInfo absFilePath (QFileInfo(absoluteFilePath(verFileReletivePathList->at(*indexDownloadFile))));
    AbstractRequest *reqestFileListVer = new RequestFile (absUrlFile, absFilePath);
    connect(reqestFileListVer, AbstractRequest::replyServer, this, RequestVersion::receiveFinishFileDownload);
    return true;
}

QUrl RequestVersion::absoluteUrlPath(QString reletiveFilePath)
{
    QString resaultstr (getUrlServer());
    resaultstr.append("/app/");
    resaultstr.append(*appName);
    resaultstr.append("/");
    resaultstr.append(*verName);
    resaultstr.append("/");
    resaultstr.append(reletiveFilePath);
    qDebug () << resaultstr;
    return QUrl (resaultstr);
}

QString RequestVersion::absoluteFilePath(QString reletiveFilePath)
{
    QString resault (".//");
    resault.append(_Data);
    resault.append(*appName);
    resault.append("/");
    resault.append(*verName);
    resault.append("/");
    resault.append(reletiveFilePath);
    qDebug () << resault;
    return resault;
}

void RequestVersion::receiveCheckVersion(QList<NetworkData> *response)
{
    QString isVerStr = response->at(0).value;
    qDebug () << isVerStr;
    bool isVer;
    if (isVerStr == "true")
    {
        isVer = true;
    }
    else if (isVerStr == "false")
    {
        isVer = false;
    }
    else
    {
        qDebug () << "check version error response";
        throw "check version error response";
    }

    if (isVer)
    {
        getVersionInfo (verName, appName);
    }
    else
    {
        throw QString ("error");
        QList <NetworkData> *responseCheckVersion;
        NetworkData netData;
        netData.key = "this version not found";
        netData.value = "false";
        responseCheckVersion->operator <<(netData);
        replyServer(response);
    }

    return;
}

void RequestVersion::receiveVersionInfo(QList<NetworkData> *response)
{
    QStringList verInfoKey;
    QStringList verInfoValue;

    foreach (NetworkData netdatatemp, *response)
    {
        verInfoKey << netdatatemp.key;
        verInfoValue << netdatatemp.value;
    }

    QString pathCfgVersion = verPath->absolutePath();
    pathCfgVersion.append("/version_config.cfg");
    Config cfgVersion (pathCfgVersion);
    for (int i(0); i < verInfoKey.length(); i++)
    {
        cfgVersion.set(verInfoKey.at(i), verInfoValue.at(i));
    }
    cfgVersion.save();
    getFileListVersion(verName, appName);
}

void RequestVersion::receiveFileListVersion(QList<NetworkData> *response)
{
    verFileReletivePathList = new QStringList ();
    indexDownloadFile = new int;
    *indexDownloadFile = 0;

    foreach (NetworkData netdatatemp, *response)
    {
        QString tempFileReletivePath (netdatatemp.value);
        QString restempFileReletivePath = tempFileReletivePath.split("\\/").join("/");
        verFileReletivePathList->operator <<(restempFileReletivePath);
    }
    getFile ();
}

void RequestVersion::receiveFinishFileDownload(QList<NetworkData> *response)
{
    if (verFileReletivePathList->length()-1 > *indexDownloadFile)
    {
        qDebug () << *indexDownloadFile;
        *indexDownloadFile = *indexDownloadFile + 1;
        getFile ();
    }
    else
    {
        qDebug () << "finish!!!!!!!!!!!!";
    }
}
