#include "log.h"

log::log(QString PathLog)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             qDebug() << address.toString();
    }


    QString logFileName = "launcer_log_file_";
    logFileName.append(QTime::currentTime()); logFileName.append(".log");

    QString pathFileLog = PathLog;
    pathFileLog.append(logFileName);
    logFile = new QFile(pathFileLog);

    QTextStream stream (logFile);

    QString time = "Start time:     ";
    time.append(QTime::currentTime()); time.append("\n");
    stream.operator <<(time);

    QHostAddress::LocalHost;
}

void log::print(QString text)
{
    QTextStream print (logFile);

    print.operator <<(text);
    return;
}
