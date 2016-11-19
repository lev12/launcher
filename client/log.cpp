#include "log.h"

Log::Log(QString PathLog)
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh-mm-ss");

    QString logFileName = "/";
    logFileName.append(date);
    logFileName.append("_");
    logFileName.append(time);
    logFileName.append("_client.log");

    QString pathFileLog = PathLog;
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

void Log::print(QString text, type classMessages, transfer InOut)
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

    QString InOutTransfer;
    switch (InOut) {
    case sreverIn:
        InOutTransfer = "<< server";
        break;
    case clientOut:
        InOutTransfer = ">> client";
        break;
    case null:
        InOutTransfer = "NULL";
    default:
        break;
    }

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

bool Log::compression()
{
    qDebug () << "compression start";

    logFile->close();
    logFile->open(QIODevice::ReadOnly);
    QString path = QFileInfo(*logFile).absolutePath();
    path.append("/file.log.compression");
    QFile compressionFile (path);
    compressionFile.open(QIODevice::WriteOnly);
    QTextStream streamCompression(&compressionFile);

    QTextStream stream (logFile);
    stream.readLine();

    while (true)
    {
        QString temp = stream.readLine();
        qDebug () << temp;

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
        }
        else if (temp.split(" ").length() >= 3 && temp.split("[").length() == 4 && temp.split("]").length() == 4)
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
            cmd.append(tempTime);
            cmd.append(":");

            QString tempCmd = temp.split(" ").at(2);
            tempCmd.remove(0,1);
            tempCmd.remove("]");
            cmd.append(tempCmd);

            streamCompression.operator <<(cmd);
        }
        streamCompression.operator <<(":");
    }
}
