#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>

#include <QObject>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QProcess>
#include <QUrl>
#include <QDesktopServices>

#include "files.h"
#include "network.h"

class Application : public Files
{
    Q_OBJECT
private:

    QString appName;
    QComboBox *comboBox;
    QPushButton *startButton;
    QHBoxLayout *pbHb;
    QProgressBar *progressBar;
    Network *network;

    QStringList versionsNetwork;


public slots:
    void connectServer ();
    void listVersion ();
    void endDownloadFile ();
    void open();
    void updateButton();
    void updateDownload();

signals:
    void getListVersions ();
    void downloadVersion ();

public:
    Application();
    void init (Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton, QHBoxLayout *pb);
    void getlistversion ();
    void downloadversion ();
    void refresh ();
    void openFolder();

    QString getItemComboBox  ();
    void fillingComboBox     ();
};

#endif // APPLICATION_H
