#include "log.h"

Log::Log(QString PathLog)
{
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh-mm-ss");

    QString logFileName = "/";
    logFileName.append(date);
    logFileName.append("_");
    logFileName.append(time);
    logFileName.append("_sever.log");

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
    head();
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
    case sreverOut:
        InOutTransfer = "<< server";
        break;
    case clientIn:
        InOutTransfer = ">> client";
        break;
    case null:
        InOutTransfer = "NULL";
    default:
        break;
    }

    send.append(tempClassMassage);
    send.append("] ");

    if (InOutTransfer != "NULL")
    {
        send.append("[");
        send.append(InOutTransfer);
        send.append("] ");
    }

    send.append("[");
    send.append(text);
    send.append("]\n");

    QTextStream print (logFile);
    print.operator <<(send);

    printf(send.toLocal8Bit());

    return;
}

void Log::head()
{
    QTextStream stream (logFile);

    QString printHeadInLog = "[----------------------------LOG FILE SERVER----------------------------]\n";
    printHeadInLog.append("[Date]       "); printHeadInLog.append(QDate::currentDate().toString("dd:MM:yyyy"));
    printHeadInLog.append("\n");
    printHeadInLog.append("[Time]       "); printHeadInLog.append(QTime::currentTime().toString());
    printHeadInLog.append("\n");

    stream.operator <<(printHeadInLog);

    return;
}
