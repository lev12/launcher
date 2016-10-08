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
#include "versionmanager.h"

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
    VersionManager *versionmanager;

    bool showVersionManager;
    QHBoxLayout *VMHB;

    QStringList versionsNetwork;

    QStringList sortVersions (QStringList versions);
public slots:
    void connectServer ();
    void listVersion ();
    void endDownloadFile ();
    void open();
    void updateButton();
    void updateDownload();
    void removeVersionManager();
    void deleteVersionVersionManager();
    void downloadVersionVersionManager();

signals:
    void getListVersions ();
    void downloadVersion ();

public:
    Application();
    void init (Network *netWork, QString AppName, QComboBox *cb, QPushButton *StartButton, QHBoxLayout *pb);
    void getlistversion ();
    void downloadversion (QString typeString, QString number);
    void refresh ();
    void openFolder();
    void openVersionManager(QHBoxLayout *widget);

    QString getItemComboBox  ();
    void fillingComboBox     ();
};

#endif // APPLICATION_H
