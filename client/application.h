#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QVariant>

#include "files.h"
#include "network.h"

class Application : public Files
{
    Q_OBJECT
private:

    QString appName;
    QComboBox *comboBox;
    QPushButton *startButton;
    Network *network;

    QStringList versionsNetwork;


public slots:
    void connectServer ();
    void listVersion ();
    void endDownloadFile ();
    void open();

signals:
    void getListVersions ();
    void downloadVersion ();

public:
    Application();
    void init (Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton);
    void getlistversion ();
    void downloadversion ();

    QString getItemComboBox  ();
    void fillingComboBox     ();
};

#endif // APPLICATION_H
