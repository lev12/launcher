#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QDebug>

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

    QStringList versions;

public slots:
    void connectServer ();
    void listVersion ();

signals:
    void getListVersions ();

public:
    Application();
    void init (Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton);

    QString getItemComboBox  ();
    void FillingComboBox     ();
    void open();
};

#endif // APPLICATION_H
