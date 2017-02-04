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
#include "global_variable.h"
#include "network.h"
#include "versionmanager.h"

class Application : public Files
{
    Q_OBJECT
private:

    appInfo app;
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

    void activeButton();
    void deactiveButton();

public:
    Application();
    void init (Network *netWork, appInfo App, QComboBox *cb, QPushButton *StartButton, QHBoxLayout *pb);
    void getlistversion ();
    void downloadversion (QString typeString, QString number, bool uiOnly);
    void refresh (bool updateListVersion);
    void openFolder();
    void openVersionManager(QHBoxLayout *widget);

    QString getItemComboBox  ();
    void fillingComboBox     ();
};

#endif // APPLICATION_H
