#ifndef ABSTRACTREQUEST_H
#define ABSTRACTREQUEST_H

#include <QObject>
#include <QString>
#include <QList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "globalVariable.h"
#include "networkData.h"

class AbstractRequest : public QObject
{
    Q_OBJECT
public:
    AbstractRequest (QObject *parent = nullptr);
    AbstractRequest (QString *ServerAddress, unsigned short ServerPort = 80, QObject *parent = nullptr);
    ~AbstractRequest ();

    QString getTokenParam (QString token);
    QString getApplicationParam (QString app);
    QString getVersionParam (QString ver);
    virtual QString getRequestParam (QString token);
    QString getRequestUrl (QString method, QString param);
    bool sendRequest(QString url);
    bool sendRequest(QUrl url);

    static QString _toSpace(QString str);
    static QString spaceTo_(QString str);
    static QString deleteForRx (QString data);

    QNetworkAccessManager *netManager;
    bool isEmptyRequest() const;

private:
    const QString keyToken = "token";
    const QString keyApplication = "app";
    const QString keyVersion = "ver";

    bool *emptyRequest;
    QNetworkReply *realyServer;
    bool sendRequestUrl(QUrl url);
protected:

    QString *serverAddress;
    unsigned short *serverPort;

    QNetworkReply *getNetReply();
    QString getUrlServer();

    virtual bool parse (QByteArray data) = 0;
signals:
    void replyServer (QList<NetworkData> *response);

public slots:
    void readServer(QNetworkReply *reply);
};

#endif // ABSTRACTREQUEST_H
