#include "versions.h"


versions::versions(QComboBox *cb)
{
    client = new QTcpSocket();
    client->connectToHost("192.168.1.15",1234);
    getVersionListOnServer(client);
    g_cb = cb;
    dir.mkdir("data");
    init ();
}

void versions::init()
{
    dir.cd(".//data");
    QList <QFileInfo> temp;
    temp = dir.entryInfoList();


    temp.erase(temp.begin(),temp.begin()+2);

    if (!temp.length() == 0)
    {
        int rem_index(0);
        for (int i(0); i<=(temp.length()+1); i++)
        {

            if(!temp.at(i-rem_index).isDir())
            {

                temp.takeAt(i-rem_index);
                rem_index++;


            }else
            {
                if(!checkVersion(temp.at(i-rem_index)))
                {
                    temp.takeAt(i-rem_index);
                    rem_index++;
                }

            }
        }
    }

    versions_bin = temp;
    return;
}

bool versions::getVersionListOnServer (QTcpSocket *client)
{
    QString send = "get list version";
    client->write( send.toLocal8Bit() );
    return true;
}

bool versions::connectNet (QTcpSocket *client)
{
    QString send = connect;
    send.append("1");
    client->write(send);
}

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

    for (int i(0); versions_bin.length() > i+1;i++)
    {
        if(nameVesion == versions_bin.at(i).baseName())
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

bool versions::open()
{
    QString item = getItemComboBox(g_cb);
    QString exe = "./data/";
    exe.append(item);
    exe.append("/");
    QFile temp(exe);
    exe.append(getExeFile(temp));


    QStringList arguments;
    arguments << "-style" << "fusion";
    QProcess vec;
    vec.start(exe,arguments);
    vec.waitForFinished(-1);
    return true;
}

void versions::FillingComboBox (QComboBox *cb)
{
    for (int i(1);versions_bin.length() > i;i++)
    {
        cb->addItem(getVersionName(versions_bin.at(i-1)));
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
    return current;
}
