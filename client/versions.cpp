#include "versions.h"


versions::versions(QComboBox *cb)
{
    client = new QTcpSocket();
    client->connectToHost(IPServer,PortServer);
    connectNet(client);
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(readServer()));
    client->waitForReadyRead();


    g_cb = cb;
    dir.mkdir("data");
    init ();
}

void versions::init()
{
    dir.cd(".//data");
    QList <QFileInfo> tempFileList;
    tempFileList = dir.entryInfoList();

    if (!tempFileList.length() == 0)
    {
        int rem_index(0);
        for (int i(0); i<=(tempFileList.length()+1); i++)
        {

            if(!tempFileList.at(i-rem_index).isDir())
            {

                tempFileList.takeAt(i-rem_index);
                rem_index++;


            }else
            {
                if(!checkVersion(tempFileList.at(i-rem_index)))
                {
                    tempFileList.takeAt(i-rem_index);
                    rem_index++;
                }

            }
        }
    }

    versions_bin = tempFileList;
    return;
}



//parse

bool versions::parse (QString data,QTcpSocket *client)
{
    if (parseConnectServer(data, client))
    {
        return true;
    }
    else if(parseListVersions (data, client))
    {
        return true;
    }else if(parseDownloadFile (data, client))
    {
        return true;
    }


    return false;
}

bool versions::parseConnectServer (QString data,QTcpSocket *client)
{
    QRegExp rx (QString("connect:(\\d+):"));

    if (rx.indexIn(data) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool versions::parseListVersions (QString data,QTcpSocket *client)
{
    QStringList cmd = data.split(" ");
    bool stream;
    for (int i(0); i<cmd.count(); i++)
    {
        QRegExp rx (QString("ver:rlv:(\\d+):"));
        int countVersions = 0;


        if ((countVersions = rx.indexIn(cmd.at(i))) != -1)
        {
            stream = true;
        }
            else
        {
            if (stream)
            {
                QStringList dataList = cmd.at(i).split('_');
                QString type = dataList.at(0);
                QString number = dataList.at(1);
                QString name = type; name.append(" "); name.append(number);
                versions_net.operator <<(name);

            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool versions::parseDownloadFile (QString data,QTcpSocket *client)
{
    static bool streamDownload;
    static QString nameVersion;

    int pos = 0;

    if (streamDownload)
    {
        static bool download;
        static QFileInfo fileDownload;
        static int fileSize;

        QRegExp rxDl ("file:(.+):(\\d+):(\\d+)"); //file:(\\.+) (\\.+):(\\d+):
        if (rxDl.indexIn(data) != -1)
        {
            QString pathNewVersion = ".\\data/";
            QStringList tempVersionName = nameVersion.split("_");
            pathNewVersion.append(tempVersionName.at(0));
            pathNewVersion.append(" ");
            pathNewVersion.append(tempVersionName.at(1));
            pathNewVersion.append("/");
            pathNewVersion.append(rxDl.cap(1));

            QFile createFile (pathNewVersion);
            createFile.open(QIODevice::WriteOnly);
            createFile.close();
            fileDownload = createFile;

            fileSize = rxDl.cap(3).toInt();
            client->write("file:reception:");
            download = true;
            return true;
        }

        if (download)
        {
                QRegExp rxEndTransfer ("file:endFile");
                if (rxEndTransfer.indexIn(buff) != -1)
                {
                    QString send = "file:";

                    if(fileDownload.size() >= fileSize)
                    {
                        send.append("accepted");
                    }else{
                        send.append("error");
                    }

                    client->write(send.toLocal8Bit());
                    return true;
                }

                QString path = fileDownload.absoluteFilePath();
                QFile file(path);
                //qDebug () << buff.size();
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
                {
                    qDebug ()  << "Not file";
                }
                file.write(buff);
                file.flush();

            return true;
        }
    }

    QRegExp rx (QString("file:ul:(\.+):exe:(\.+):(\\d+):(\\d+)"));

    if ((pos = rx.indexIn(data)) == -1)
    {
        return false;
    }
    else
    {
        bool success = true;
        nameVersion = rx.cap(1);

        QDir dir (".\\");
        QString diskName = dir.absolutePath();
        QStringList diskNameList = diskName.split(":/");
        QStorageInfo storage;
        storage.setPath(diskNameList.at(0));
        if (storage.bytesFree() > rx.cap(4).toInt())
        {
            success = false;
        }


        QString send = "file:";
        if (success)
        {
            send.append("ok_reception_file:");
            streamDownload = true;
        }
        else
        {
            send.append("fail:");
        }

        QTextStream streamTxt (client);
        streamTxt.operator <<(send);

        return true;
    }
}
//end parse

//net

bool versions::getVersionListOnServer (QTcpSocket *client)
{
    QString send = "glv:";
    QTextStream stream (client);
    stream.operator <<(send);

    return true;
}

bool versions::connectNet (QTcpSocket *client)
{
    QString send = "connect:";
    send.append(QString::number(number_version_launcher));
    send.append(":");
    QTextStream stream (client);
    stream.operator <<(send);
    return true;
}

void versions::readServer()
{
    QByteArray data = client->readAll();
    buff = data;
    if(!parse (data, client))
    {
        QString send = "wrongCmd(";
        send.append(QString (data)); send.append(")");
        QTextStream stream (client);
        stream.operator <<(send);
    }
    //qDebug () << data;
}

bool versions::downloadVersion (QString name, QTcpSocket *client)
{
    QString send = "file:get:";
    QStringList LName = name.split(" ");
    QString SName = LName.at(0);
    SName.append(" ");
    SName.append(LName.at(1));
    send.append(SName);

    QTextStream stream (client);
    stream.operator <<(send);
    return true;
}

//end net

bool versions::addVersion(QString type,QString number)
{
    if(checkVersion(type,number))
    {
        return false;
    }



    return true;
}

bool versions::deleteVersion(QString type,QString number)
{
    if(!checkVersion(type,number))
    {
        return false;
    }

    QString name = getVersionName(getFile(type,number));

    QString path = ".//data/";
            path.append(name);
    QDir dirDel(path);

    removeFolder(dirDel);


    return true;
}

int versions::removeFolder(QDir & dir)
{
  int res = 0;
  QStringList lstDirs = dir.entryList(QDir::Dirs |
                  QDir::AllDirs |
                  QDir::NoDotAndDotDot);
  QStringList lstFiles = dir.entryList(QDir::Files);

  foreach (QString entry, lstFiles)
  {
   QString entryAbsPath = dir.absolutePath() + "/" + entry;
   QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
   QFile::remove(entryAbsPath);
  }

  foreach (QString entry, lstDirs)
  {
   QString entryAbsPath = dir.absolutePath() + "/" + entry;
   QDir dr(entryAbsPath);
   removeFolder(dr);
  }

  if (!QDir().rmdir(dir.absolutePath()))
  {
    res = 1;
  }
  return res;
}

bool versions::checkVersion(QFileInfo path)
{
    QString temp_path_ini = path.absoluteFilePath();
    temp_path_ini.append("/data version.ini");
    QFile cfile(temp_path_ini);
    cfile.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&cfile);
    QString temp;
    QString temp_path = path.absolutePath();

    for (int i(0); i<2; i++)
    {
        stream.operator >>(temp);

        switch (i)
        {
        case 0:



            if(temp == "pre-alpha")
            {
              break;
            }
            if(temp == "alpha")
            {
              break;
            }
            if(temp == "beta")
            {
              break;
            }
            if(temp == "release")
            {
              break;
            }
            return false;
            break;

        case 1:
            break;
        case 2:
            temp_path.append(temp);
            if(!dir.cd (temp_path))
            {
                return false;
            }

            break;
        default:
            break;
        }
    }

    return true;
}

bool versions::checkVersion(QString type, QString number)
{
    QString nameVesion = type;
    nameVesion.append(" ");
    nameVesion.append(number);

    for (int i(0);i < versions_all.length();i++)
    {
        if(nameVesion == versions_all.at(i).name)
        {
            return true;
        }
    }

    return false;
}

QFileInfo versions::getFile (QString type, QString number)
{
    QFileInfo temp;
    QString name = type;
    name.append(" ");
    name.append(number);

    for (int i(0); versions_bin.length() > i+1;i++)
    {
        if(name == versions_bin.at(i).baseName())
        {
            temp = versions_bin.at(i);
            return temp;
        }
    }

    return temp;
}

bool versions::isInstall (QString type, QString number)
{
    bool inst;
    QString name = type; name.append(" "); name.append(number);
    for (int i(0); i < versions_all.length(); i++)
    {
        if (versions_all.at(i).name == name)
        {
            inst = versions_all.at(i).install;
            break;
        }
    }
    return inst;
}

bool versions::open()
{
    /*QString item = getItemComboBox(g_cb);
    QString exe = "./data/";
    exe.append(item);
    exe.append("/");
    QFile temp(exe);
    exe.append(getExeFile(temp));*/

    QString item = getItemComboBox(g_cb);
    QStringList LItem = item.split(" ");
    QString name = LItem.at(1); name.append(" "); name.append(LItem.at(2));
    if (LItem.at(0) == "download")
    {
        downloadVersion(name, client);

    }
    client->waitForReadyRead();
    return true;
    /*QStringList arguments;
    arguments << "-style" << "fusion";
    QProcess vec;
    vec.start(exe,arguments);
    vec.waitForFinished(-1);
    return true;*/
}

void versions::FillingComboBox (QComboBox *cb)
{
    getVersionListOnServer(client);
    client->waitForReadyRead();

    QList <QFileInfo> tempList = versions_bin;

    for (int i(0); i<versions_net.length(); i++)
    {
        QString name = versions_net.at(i);
        ver temp;

        for (int i(0); i < tempList.length(); i++)
        {
            if (name == getVersionName(tempList.at(i)))
            {
                tempList.takeAt(i);
                temp.install = true;
                break;
            }
        }

        temp.name = name;
        versions_all.operator <<(temp);
    }

    for (int i(0); i < tempList.length(); i++)
    {
        ver temp;
        temp.name = getVersionName(tempList.at(i));

        versions_all.operator <<(temp);
    }

    for (int i(0);versions_all.length() > i;i++)
    {
        cb->addItem(versions_all[i].name);
    }

}

QString versions::getVersionName (QFileInfo path)
{
    QString result;
    QString temp;
    QString FullPath = path.absoluteFilePath();
    FullPath.append("/data version.ini");
    QFile file(FullPath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);

    stream.operator >> (result);
    result.append(" ");
    stream.operator >> (temp);
    result.append(temp);

    return result;
}

QString versions::getExeFile (QFileInfo path)
{
    QString result;
    QString temp;
    QString FullPath = path.absoluteFilePath();
    FullPath.append("/data version.ini");
    QFile file(FullPath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);

    stream.operator >>(temp);
    stream.operator >>(temp);
    stream.operator >>(result);

    return result;
}

QString versions::getItemComboBox (QComboBox *cb)
{
    QStringList version;
    bool check;

    QString current = cb->currentText();
    version = current.split(" ");
    check = checkVersion(version.at(0),version.at(1));

    if (!check)
    {
        return NULL;
    }

    if (isInstall(version.at(0),version.at(1)))
    {
        QString download = "download "; download.append(current);
        return download;
    }

    return current;
}
