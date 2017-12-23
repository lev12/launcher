#include "client.h"

client::client(QTcpSocket *socket)
{
    logPrint = new Log(LogPath);
    fillingAppList();
    QObject::connect(socket,SIGNAL(readyRead()), SLOT(ReadClient()));
}

void client::ReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    //int idusersocs=clientSocket->socketDescriptor();
    QByteArray out;
    out = clientSocket->readAll();
    QString str_temp = out;

    str_temp.remove(0,str_temp.length()-2);
    if (str_temp == QString("\r\n"))
    {
        out.remove(out.length()-2,2);
    }

    qDebug () << out;
    if (WrongCmd(out))
    {
        logPrint->print(out, Log::error, Log::clientIn);
    }
    else
    {        
        qDebug () << clientSocket;
        logPrint->print(out, Log::info, Log::clientIn);
        parse(out,clientSocket);
    }
}

//parse

bool client::parse (QByteArray data, QTcpSocket* client)
{
    if (parseConnectClient(data,client))   return true;
    if (parseGetListVersions(data,client)) return true;
    if (parseDownloadLog(data,client))     return true;
    if (parseGetVersions(data,client))     return true;
    if (parseCVL(data,client))             return true;

    return false;
}

bool client::parseConnectClient (QByteArray data,QTcpSocket* client)
{
    int versionClient;
    int pos = 0;
    QRegExp rx ("connect:(\\d):");

    if ((pos = rx.indexIn(data, pos)) == -1)
    {
        return false;
    }

    QString send = "connect:";
    send.append("8");
    send.append(":");
    QTextStream os(client);
    os << send;
    logPrint->print (send, Log::info, Log::sreverOut);

    return true;
}

bool client::parseGetListVersions (QByteArray data, QTcpSocket* client)
{
    int pos = 0;
    QRegExp rx ("glv:(.+):");
    QString appName = QString(data);
    appName.remove(0,4);
    appName.remove(appName.length()-1 , 1);
    qDebug () << appName;
    verCon = foundApp (appName);
    //QString(rx.cap(1))
    if ((pos = rx.indexIn(data, pos)) == -1)
    {
        return false;
    }

    QString send = "ver:rlv:";
    send.append(QString::number(verCon.versions.length()));
    send.append(":");
    send.append(add_(rx.cap(1)));
    send.append(":");

    for (QFileInfo temp : verCon.getVersonsList())
    {
        QStringList str = verCon.getVersionName(temp).split(" ");
        send.append(" "); send.append(str[0]); send.append("_"); send.append(str[1]);
    }



    QTextStream os (client);
    os << send;
    logPrint->print (send, Log::info, Log::sreverOut);
    return true;
}

bool client::parseGetVersions (QByteArray data, QTcpSocket *client)
{
    static bool stream;
    static bool streamTransfer;
    static bool streamData;
    static QString appName;
    static QString versionName;
    int pos = 0;

    QRegExp rx ("file:get:(.+):(.+):(\\d+):");

    if ((pos = rx.indexIn(data, pos)) != -1)
    {
        appName = rx.cap(1);

        QString pathFileCount = ".\\data/";

        if (appName != "null")
        {
            pathFileCount.append(appName);
            pathFileCount.append("/");
        }

        if (rx.cap(2) != "null")
        {
            pathFileCount.append(rx.cap(2));
            pathFileCount.append(" ");
        }

        pathFileCount.append(rx.cap(3));

        QDir dir (pathFileCount);
        FileList.clear();
        FillingFileList(dir);
        int countVersions = FileList.length();
        sizeVersion(dir);
        int size_temp = size;

        QTextStream stream(client);
        QString send;


        /*if(!verCon.checkVersion(rx.cap(2),rx.cap(3)))
        {
            logPrint->print("no version", Log::error);
        }*/

        QString tempName;
        if (rx.cap(2) != "null")
        {
            tempName = rx.cap(2); tempName.append("_"); tempName.append(rx.cap(3));
        }else
        {
            tempName = tempName.append(rx.cap(3));
        }

        send.append("file:ul:"); send.append(appName); send.append(":");
        send.append(tempName); send.append(":");
        send.append("exe:"); send.append(verCon.getExeFile(verCon.getFile(rx.cap(2),rx.cap(3))));
        send.append(":"); send.append(QString::number(countVersions));
        send.append(":"); send.append(QString::number(size_temp));
        logPrint->print (send, Log::info, Log::sreverOut);
        stream.operator <<(send);

        versionName = "";
        versionName.append(rx.cap(2));
        versionName.append(" ");
        versionName.append(rx.cap(3));



        return true;
    }



    QRegExp rxFail ("file:fail:");

    if ((pos = rxFail.indexIn(data, pos)) != -1)
    {
        stream = false;
        return true;
    }

    QRegExp rxSuc ("file:ok_reception_file:");

    if ((pos = rxSuc.indexIn(data)) != -1)
    {
        stream = true;
        streamData = true;
    }

    if (stream)
    {
        static int countBlock;
        static int numberFile = 0;
        static QFileInfo streamFile;
        streamFile = FileList.at(numberFile);

        QRegExp rxRec ("file:reception:");

        if ((pos = rxRec.indexIn(data)) != -1)
        {
            streamTransfer = true;
        }

        if (streamTransfer)
        {
            QRegExp rxEndAccepted ("file:accepted");

            if (rxEndAccepted.indexIn(data) != -1)
            {
                if (numberFile == (FileList.count() - 1))
                {
                    client->write("file:ulEnd:");
                    numberFile = 0;
                    streamTransfer = false;
                    streamData = false;
                    stream = false;
                    return true;
                }
                numberFile++;
                streamFile = FileList.at(numberFile);

                QString pathRem = ".//data/";
                pathRem.append(versionName);
                QFileInfo filePathRem (pathRem);
                QString filePath = streamFile.absoluteFilePath();
                filePath.remove(filePathRem.absoluteFilePath());

                int sizeFile = streamFile.size();
                countBlock = qFloor(sizeFile/SizeInternetPackage);
                QString send = streamDataFile(filePath,sizeFile,countBlock);
                client->write(send.toLocal8Bit());
                logPrint->print(send, Log::info, Log::sreverOut);
                streamTransfer = false;
                return true;
            }

            QFile file(streamFile.absoluteFilePath());
            file.open(QIODevice::ReadOnly);
            QByteArray buffer;

            for (int i(0); i <= countBlock; i++)
            {
                buffer = file.read(SizeInternetPackage);
                client->write(buffer);
                client->flush();
                client->waitForBytesWritten();
            }
            client->flush();

            return true;
        }

        if (streamData)
        {
            QTextStream sendStream (client);


            QString nameFile = streamFile.fileName();
            int sizeFile = streamFile.size();

            countBlock = qFloor(sizeFile/SizeInternetPackage);
            QString send = streamDataFile(nameFile, sizeFile, countBlock);
            sendStream.operator <<(send);
            logPrint->print (send, Log::info, Log::sreverOut);
            streamData = false;
            return true;
        }


        return false;

    }
    return false;
}

bool client::parseDownloadLog(QByteArray data, QTcpSocket *client)
{
    QFile file (".//log/12.log");
    static bool stream;

    if ("log:upload:end:" == data)
    {
        stream = false;
        logPrint->print("log upload end", Log::info, Log::clientIn);
    }
    if (stream)
    {
        QString send = "log:reception:";
        file.open(QFile::WriteOnly);
        file.write(data);
        file.flush();
        logPrint->print("log:reception:");
        QTextStream stream (client);
        stream.operator <<(send);
    }

    int pos = 0;
    QRegExp rxData ("log:(.+):(\\d+):(\\d+)");
    if ((pos = rxData.indexIn(data)) != -1)
    {
        client->write("log:accepted:");
        logPrint->print("log:accepted:", Log::info, Log::sreverOut);
        stream = true;
    }

    return false;
}

bool client::parseDisconnect (QByteArray data, QTcpSocket *client)
{
    QRegExp rxDiscon ("disconnect:cln");
    if (rxDiscon.indexIn(data) != -1)
    {
        client->write("disconnect:ser");
        return true;
    }

    return false;
}

bool client::parseCVL(QByteArray data, QTcpSocket *client)
{
    QRegExp rx ("clv:getcurrentversion:");
    if (rx.indexIn(data) == -1) return false;

    QString send = "clv:";
    send.append("1.1");
    send.append(":");

    QTextStream sendStream (client);
    sendStream.operator <<(send);

    return true;
}

QString client::streamDataFile (QString filePath, int sizeFile, int countBlock)
{
    QString send = "file:";
    send.append(filePath); send.append(":");
    send.append(QString::number(sizeFile)); send.append(":");
    send.append(QString::number(countBlock)); send.append(":");
    return send;
}

bool client::WrongCmd (QString data)
{
    QRegExp rx ("wrongCmd");
    if (rx.indexIn(data) == -1) return false;

    return true;
}

void client::FillingFileList (QDir & dir)
{
    QList <QString> lstDirs = dir.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    QList <QFileInfo> lstFiles = dir.entryInfoList(QDir::Files);

    FileList.operator <<(lstFiles);

    foreach (QString tempDir, lstDirs) {
        QString entryAbsPath = dir.absolutePath() + "/" + tempDir;
        QDir dr(entryAbsPath);
        FillingFileList(dr);
    }

    return;
}

void client::sizeVersion (QDir & dir)
{
    size = 0;
    foreach (QFileInfo item, FileList) {
        size = size + item.size() ;
    };

    return;
}

void client::fillingAppList()
{
    QDir dataDir (".//data");
    QList <QString> filesList = dataDir.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < filesList.length(); i++)
    {
        QString appNameTemp = filesList.at(i);
        File file = File(appNameTemp);
        AppList << file;
    }
}

File client::foundApp (QString appName)
{
    //fileTemp = new File();
    for (int i = 0; i < AppList.length(); i++)
    {
        QString tempName = AppList.at(i).getAppName();
        if (tempName == appName)
        {
            File fileTemp = AppList.at(i);
            return fileTemp;
        }
    }
}

QString client::add_(QString str)
{
    QStringList strList = str.split(" ");
    QString strTemp = strList.at(0);
    strTemp.append("_");
    strTemp.append(strList.at(1));
    return strTemp;
}

QString client::delete_(QString str)
{

}
