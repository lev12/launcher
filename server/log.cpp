#include "log.h"

Log::Log(QString PathLog)
{
    QString logFileName = "launcer_log_file_";
    logFileName.append(QTime::currentTime().toString()); logFileName.append(".log");

    QString pathFileLog = PathLog;
    pathFileLog.append(logFileName);
    logFile = new QFile(pathFileLog);

    QTextStream stream (logFile);

    QString time = "Start time:     ";
    time.append(QTime::currentTime().toString()); time.append("\n");
    stream.operator <<(time);

    //QHostAddress::LocalHost;
}

void Log::print(QString text)
{
    QTextStream print (logFile);

    print.operator <<(text);
    return;
}
