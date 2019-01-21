#ifndef LAUNCHERCONFIG_H
#define LAUNCHERCONFIG_H

#include <QLocale>
#include <QUrl>
#include "config.h"
#include "log.h"
#include "Exception.h"
#include <QString>
#include <QMetaEnum>

/*!
 * \brief The LauncherConfig class
 * This class interface to launcher config.
 */

class LauncherConfig : public Config
{
public:
    static LauncherConfig &instance();

    unsigned short getWidth ();
    unsigned short getHeight ();
    bool getFullScrean ();
    QStringList getLanguage();
    unsigned int getStartPage();
    QUrl getServerAddress ();
    unsigned short getServerPort ();
    Log::state getLogState ();
    QDir getLogFolder();
    unsigned int getCountLogFile();

    bool setWidth (unsigned short width);
    bool setHeight (unsigned short height);
    bool setFullScrean (bool state);
    bool setLanguage (QString lanuguage);
    bool setStartPage (int idPage);
    bool setServerAddress (QUrl address);
    bool setServerPort (unsigned short port);
    bool setLogState (Log::state state);
    bool setLogFolder (QDir folder);
    bool setCountLogFile (int count);

    bool setDefaultParametr ();
    bool setDefaultWidth ();
    bool setDefaultHeight ();
    bool setDefaultFullScrean ();
    bool setDefaultLanguage ();
    bool setDefaultStartPage ();
    bool setDefaultServerAddress ();
    bool setDefaultServerPort ();
    bool setDefaultLogState ();
    bool setDefaultLogFolder ();
    bool setDefaultCountLogFile ();
private:
    LauncherConfig();
    ~LauncherConfig();

    const QString pathCfg = ".//application_config.cfg";

    const QString keyWidth = "width";
    const QString keyHeight = "height";
    const QString keyFullScrean = "fullScrean";
    const QString keyLanguage = "language";
    const QString keyStartPage = "startPage";
    const QString keyIpServer = "ipServer";
    const QString keyPortServer = "portServer";
    const QString keyLogState = "logState";
    const QString keyLogFolderPath = "logFolderPath";
    const QString keyCountLogFile = "countLogFile";

    Config *defaultCfg;
};

#endif // LAUNCHERCONFIG_H
