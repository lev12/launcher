#include "log.h"

Log::Log(QDir PathLog) : QObject ()
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh-mm-ss");

    QString logFileName = "/";
    logFileName.append(date);
    logFileName.append("_");
    logFileName.append(time);
    logFileName.append("_client.log");

    QString pathFileLog;
    QFileInfo LogFileInfo (PathLog.absolutePath());
    if (LogFileInfo.isDir())
    {
        pathFileLog = PathLog.absolutePath();
    }
    else
    {
        pathFileLog = defaultLogPath;
    }
    pathFileLog.append(logFileName);
    logFile = new QFile(pathFileLog);
    if (!(logFile->open(QIODevice::WriteOnly | QIODevice::Text)))
    {
        printf("[");
        printf(QTime::currentTime().toString().toStdString().c_str());
        printf("] [warning] [not log file]\n");
        QDir createPath(".//");
        if(createPath.mkdir("log"))
        {
            printf("[");
            printf(QTime::currentTime().toString().toStdString().c_str());
            printf("] [info] [create log file]\n");
        }else
        {
            printf("[");
            printf(QTime::currentTime().toString().toStdString().c_str());
            printf("] [error] [failed create log file]\n");
        }
        logFile->open(QIODevice::WriteOnly | QIODevice::Text);
    }
}

Log::~Log()
{

}

void Log::print(QString text, type classMessages)
{
    QString send = "[";
    send.append(QTime::currentTime().toString());
    send.append("] [");
    QString tempClassMassage;

    switch (classMessages) {
    case info:
        tempClassMassage = "info";
        break;
    case warning:
        tempClassMassage = "warning";
        break;
    case error:
        tempClassMassage = "error";
        break;
    case critical_error:
        tempClassMassage = "critical_error";
        break;
    default:
        tempClassMassage = "NULL";
        break;
    }

    /*QString InOutTransfer;
    switch (InOut) {
    case sreverIn:
        InOutTransfer = ">>server";
        break;
    case clientOut:
        InOutTransfer = "<<client";
        break;
    case null:
        InOutTransfer = "NULL";
    default:
        break;
    }*/

    send.append(tempClassMassage);
    send.append("] ");

    /*if (InOutTransfer != "NULL")
    {
        send.append("[");
        send.append(InOutTransfer);
        send.append("] ");
    }*/

    send.append("[");
    send.append(text);
    send.append("]\n");

    QTextStream print (logFile);
    print.operator <<(send);

    return;
}

void Log::head()
{
    QTextStream stream (logFile);

    QString printHeadInLog = "[----------------------------LOG FILE CLIENT----------------------------]\n";
    printHeadInLog.append("[Date] "); printHeadInLog.append(QDate::currentDate().toString("dd:MM:yyyy"));
    printHeadInLog.append("\n");
    printHeadInLog.append("[Time] "); printHeadInLog.append(QTime::currentTime().toString());
    printHeadInLog.append("\n");

    stream.operator <<(printHeadInLog);

    return;
}

void Log::end ()
{
    QTextStream stream (logFile);

    QString printEndInLog;
    printEndInLog.append("[Date] "); printEndInLog.append(QDate::currentDate().toString("dd:MM:yyyy"));
    printEndInLog.append("\n");
    printEndInLog.append("[Time] "); printEndInLog.append(QTime::currentTime().toString());
    printEndInLog.append("\n");
    printEndInLog.append("[----------------------------END LOG FILE----------------------------]");

    stream.operator <<(printEndInLog);

    return;
}

void Log::addMessage(QString message)
{
    logFile->write("<message>\n");
    logFile->write(message.toLocal8Bit());
    logFile->write("\n</message>\n");
    qDebug () << message;
}

void Log::grabber(unsigned int countFileDelete)
{
    if (countFileDelete != 0)
    {
        QString path = QFileInfo (*logFile).absolutePath();
        QDir dir (path);
        QList <QFileInfo> fileList = dir.entryInfoList();

        int index = 0;
        for (int i(0); i < fileList.length(); i++)
        {
            QString fileName = fileList.at(i).fileName();
            QStringList fileNameList = fileName.split("_");
            if (fileNameList.length() == 3)
            {
                if (fileNameList.at(2) == "client.log")
                {
                    index++;
                    if (index >= countFileDelete)
                    {
                        QFile::remove(fileList.at(i).absoluteFilePath());
                    }
                }

            }
        }
    }

}

/*bool Log::compression()
{
    qDebug () << "compression start";

    QTime timelast;
    logFile->close();
    logFile->open(QIODevice::ReadOnly);
    QString path = QFileInfo(*logFile).absolutePath();
    path.append("/file.log.compression");
    QFile compressionFile (path);
    compressionFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream streamCompression(&compressionFile);

    QTextStream stream (logFile);
    stream.readLine();

    while (true)
    {
        QString temp = stream.readLine();

        if (temp == "[----------------------------END LOG FILE----------------------------]")
        {
            break;
        }
        if (temp.split(" ").at(0) == "[Date]")
        {
            QString date = "d:";
            date.append(temp.split(" ").at(1));
            streamCompression.operator <<(date);
        }
        else if (temp.split(" ").at(0) == "[Time]")
        {
            QString date = "t:";
            date.append(temp.split(" ").at(1));
            streamCompression.operator <<(date);

            QStringList timestart = QString(temp.split(" ").at(1)).split(":");
            timelast.setHMS(QString(timestart.at(0)).toInt(),
                            QString(timestart.at(1)).toInt(),
                            QString(timestart.at(2)).toInt());
        }
        else if (temp.split(" ").length() >= 3 && temp.split("[").length() >= 4 && temp.split("]").length() >= 4)
        {
            QString cmd;
            QString tempType = temp.split(" ").at(1);
            tempType.remove(0,1);
            tempType.remove(1,tempType.length()-1);
            cmd.append(tempType);
            cmd.append(":");

            QString tempTime = temp.split(" ").at(0);
            tempTime.remove(0,1);
            tempTime.remove(tempTime.length()-1,1);
            QStringList tempTimeSrt = tempTime.split(":");
            QTime time(QString(tempTimeSrt.at(0)).toInt(),
                       QString(tempTimeSrt.at(1)).toInt(),
                       QString(tempTimeSrt.at(2)).toInt());
            cmd.append(QString::number(timelast.secsTo(time)));
            cmd.append(":");
            timelast = time;

            if (temp.split(" ").at(2) == "[>>server]" || temp.split(" ").at(2) == "[<<client]")
            {
                QString tempTransfer = temp.split(" ").at(2);
                tempTransfer.remove(0,1);
                tempTransfer.remove(1,tempTransfer.length()-1);
                cmd.append(tempTransfer);
                cmd.append(":");

                QString tempCmd = temp.split(" ").at(3);
                tempCmd.remove(0,1);
                tempCmd.remove("]");
                cmd.append(tempCmd);

            }
            else
            {
                QString tempCmd = temp.split(" ").at(2);
                tempCmd.remove(0,1);
                tempCmd.remove("]");
                cmd.append(tempCmd);

            }
            qDebug () << cmd;
            streamCompression.operator <<(cmd);
        }
        streamCompression.operator <<(";");
    }

    compressionFile.flush();
    compressionFile.close();

    if (!compressionHaffman(".//log/file.log.compression",".//log/compression.bin"))
    {
        return false;
    }

    return true;
}

bool Log::compressionHaffman (QString pathInputFile,QString pathOutputFile)
{
    QFile inputFile (pathInputFile);
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QFile outputFile (pathOutputFile);
    if(!outputFile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    qDebug () << "compression hafman";

    QByteArray data = inputFile.readAll();

    QMap<char,int> mass;
    for(int i(0); i<data.length(); i++)
    {
        char ch = data.at(i);
        mass[ch]++;
    }

    QMap<char, int>::iterator i;
    for (i=mass.begin(); i != mass.end(); i++)
    {
        qDebug () << i.key() << " : " << i.value();
    }
    QList <Node*> tree;
    for (i=mass.begin(); i != mass.end(); i++)
    {
        Node *node = new Node();
        node->c = i.key();

        node->n = i.value();
        tree.operator <<(node);
    }

    while (tree.size() !=1)
    {
        for (int i = tree.length()-1; i >= 1; i--)
        {
            for (int j(0); j <i; ++j)
            {
                if (tree.at(j)->n > tree.at(j+1)->n)
                {
                    int foo = tree.at(j)->n;
                    tree.at(j)->n = tree.at(j+1)->n;
                    tree.at(j+1)->n = foo;
                }
            }
        }
        Node *sonL = tree.front();;
        tree.pop_front();
        Node *sonR = tree.front();;
        tree.pop_front();

        Node *parent = new Node(sonL,sonR);
        tree.push_back(parent);
    }

    Node *root = tree.front();

    table = new QMap< char,QVector<bool> >;
    code = new QVector<bool>;
    buildTable(root);

    int count = 0;
    char buf = 0;
    QTextStream strem (&outputFile);

    QMap < char,QVector<bool> >::iterator itable;
    for (itable=table->begin(); itable != table->end(); itable++)
    {
        char c = itable.key();
        strem.operator <<(c);
        QVector <bool> x = table->value(c);
        for (int n(0); n < x.size(); n++)
        {
            buf = buf | x.at(n)<<(7-count);
            count++;
            if (count == 8)
            {
                count = 0;
                strem.operator <<(QString(buf));
                buf = 0;
            }
        }
    }

    for (int i(0); i < data.length(); i++)
    {
        char c = data.at(i);
        QVector <bool> x = table->value(c);
        for (int n(0); n < x.size(); n++)
        {
            buf = buf | x.at(n)<<(7-count);
            count++;
            if (count == 8)
            {
                count = 0;
                strem.operator <<(QString(buf));
                buf = 0;
            }
        }
    }
    outputFile.flush();
    outputFile.close();

    qDebug () << "end compression haffman";

    return true;
}

void Log::buildTable(Node *root)
{
    qDebug () << "left " << QString (root->left!=NULL);
    if (root->left!=NULL)
                      { code->push_back(0);
                      buildTable(root->left);}

    qDebug () << "right " << QString (root->right!=NULL);
    if (root->right!=NULL)
                       { code->push_back(1);
                       buildTable(root->right);}

    if (root->left==NULL && root->right==NULL) table->insert(root->c, *code);

    if (code->length() != 0)
    {
        code->pop_back();
    }
}

Node::Node(Node *l, Node *r) : QObject ()
{
    left = l;
    right = r;
    n = l->n + r->n;
}

Node::Node () : QObject ()
{
    left=right=NULL;
}*/
