#include "launcherConfig.h"

LauncherConfig::LauncherConfig() : Config (".//application_config.cfg")
{
    defaultCfg = new Config (":/other/configDefaltParametr.txt");
    if (isEmpty())
    {
        setDefaultParametr();
    }
}

LauncherConfig::~LauncherConfig()
{
    delete defaultCfg;
}

LauncherConfig &LauncherConfig::instance()
{
    static LauncherConfig obj;
    return obj;
}

unsigned short LauncherConfig::getWidth()
{
    bool isOk;
    unsigned short width = Config::get(keyWidth).at(0).toUShort(&isOk);
    if (!isOk)
    {
        setDefaultWidth();
        Config::save();
        width = Config::get(keyWidth).at(0).toUShort(&isOk);
        if (!isOk) throw Exception (1250,QString ("width not correct in config"));
    }
    return width;
}

unsigned short LauncherConfig::getHeight()
{
    bool isOk;
    unsigned short height = Config::get(keyHeight).at(0).toUShort(&isOk);
    if (!isOk)
    {
        setDefaultHeight();
        Config::save();
        height = Config::get(keyHeight).at(0).toUShort(&isOk);
        if (!isOk) throw Exception (1251,QString ("height not correct in config"));
    }
    return height;
}

bool LauncherConfig::getFullScrean()
{
    bool isFullScrean = false;
    QString fullScreanStr = Config::get(keyFullScrean).at(0);

    if (fullScreanStr != "true" || fullScreanStr == "false")
    {
        setDefaultFullScrean();
        Config::save();
        QString fullScreanStr = Config::get(keyFullScrean).at(0);
    }

    if (fullScreanStr == "true")
    {
        isFullScrean = true;
    }
    else if (fullScreanStr == "false")
    {
        isFullScrean =false;
    }
    else
    {
        throw Exception (1252,QString ("fullScrean not correct in config"));
    }
    return isFullScrean;
}

QStringList LauncherConfig::getLanguage()
{
    QStringList languages = Config::get(keyLanguage);
    if (languages.count() == 0)
    {
        setDefaultLanguage();
        Config::save();
        languages = Config::get(keyLanguage);
        if (languages.count() == 0) throw Exception (1253,QString ("language not correct in config"));
    }
    return languages;
}

unsigned int LauncherConfig::getStartPage()
{
    bool isOk;
    unsigned int startPage = Config::get(keyHeight).at(0).toUInt(&isOk);
    if (!isOk)
    {
        setDefaultHeight();
        Config::save();
        startPage = Config::get(keyHeight).at(0).toUShort(&isOk);
        if (!isOk) throw Exception (1254,QString ("start page not correct in config"));
    }
    return startPage;
}

QUrl LauncherConfig::getServerAddress()
{
    bool isOk = true;
    bool isOkPort = true;
    QString serverIpStr = Config::get(keyIpServer).at(0);
    unsigned short serverPortStr = Config::get(keyPortServer).at(0).toUShort(&isOkPort);
    if (serverIpStr == "")
    {
        setDefaultServerAddress();
        isOk = false;
    }
    if (!isOkPort)
    {
        setDefaultServerPort();
        isOk = false;
    }

    if (!isOk)
    {
        Config::save();
        isOk = true;
        serverIpStr = Config::get(keyIpServer).at(0);
        if (serverIpStr == "") isOk = false;
        serverPortStr = Config::get(keyPortServer).at(0).toUShort(&isOkPort);
        if (!isOk && !isOkPort) throw Exception (1255,QString ("server address not correct in config"));
    }
    QString serverUrlSrt = "http://" + serverIpStr + "/" + QString(serverPortStr);
    return QUrl(serverUrlSrt);
}

unsigned short LauncherConfig::getServerPort()
{
    bool isOk;
    unsigned short serverPort = Config::get(keyPortServer).at(0).toUShort(&isOk);
    if (!isOk)
    {
        setDefaultServerPort();
        Config::save();
        serverPort = Config::get(keyPortServer).at(0).toUShort(&isOk);
        if (!isOk) throw Exception (1256,QString ("server port not correct in config"));
    }
    return serverPort;
}

Log::state LauncherConfig::getLogState()
{
    bool isOk;
    Log::state logState = Log::logging;
    switch (Config::get(keyLogState).at(0).toUShort(&isOk)) {
    case 0:
        logState = Log::noLogging;
        break;
    case 1:
        logState = Log::logging;
        break;
    case 2:
        logState = Log::loggingAndSend;
        break;
    }
    if (!isOk)
    {
        setDefaultLogState();
        Config::save();
        switch (Config::get(keyLogState).at(0).toUShort(&isOk))
        {
        case 0:
            logState = Log::noLogging;
            break;
        case 1:
            logState = Log::logging;
            break;
        case 2:
            logState = Log::loggingAndSend;
            break;
        }
        if (!isOk) throw Exception (1257,QString ("log state not correct in config"));
    }

    return logState;
}

QDir LauncherConfig::getLogFolder()
{
    QString logFolderDirPath = Config::get(keyLogFolderPath).at(0);
    if (logFolderDirPath == "")
    {
        setDefaultLogFolder();
        Config::save();
        logFolderDirPath = Config::get(keyLogFolderPath).at(0);
        if (logFolderDirPath == "") throw Exception (1258,QString ("log folder path not correct in config"));
    }
    return QDir(logFolderDirPath);
}

unsigned int LauncherConfig::getCountLogFile()
{
    bool isOk;
    unsigned int countLogFile = Config::get(keyCountLogFile).at(0).toUInt(&isOk);
    if (!isOk)
    {
        setDefaultCountLogFile();
        Config::save();
        countLogFile = Config::get(keyCountLogFile).at(0).toUShort(&isOk);
        if (!isOk) throw Exception (1259,QString ("count log file not correct in config"));
    }
    return countLogFile;
}

bool LauncherConfig::setWidth(unsigned short width)
{
    return Config::set(keyWidth,QString::number(width));
}

bool LauncherConfig::setHeight(unsigned short height)
{
    return Config::set(keyHeight,QString::number(height));
}

bool LauncherConfig::setFullScrean(bool state)
{
    QString stateStr;
    if (state)
    {
        stateStr = "true";
    }
    else
    {
        stateStr = "false";
    }
    return Config::set(keyFullScrean,stateStr);
}

bool LauncherConfig::setLanguage(QString lanuguage)
{
    return Config::set(keyLanguage,lanuguage);
}

bool LauncherConfig::setStartPage(int idPage)
{
    return Config::set(keyStartPage,QString::number(idPage));
}

bool LauncherConfig::setServerAddress(QUrl address)
{
    return Config::set(keyIpServer,address.host());
}

bool LauncherConfig::setServerPort(unsigned short port)
{
    return Config::set(keyPortServer,QString::number(port));
}

bool LauncherConfig::setLogState(Log::state state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Log::state>();
    return Config::set(keyPortServer,metaEnum.valueToKey(state));
}

bool LauncherConfig::setLogFolder(QDir folder)
{
    return Config::set(keyPortServer,folder.absolutePath());
}

bool LauncherConfig::setCountLogFile(int count)
{
    return Config::set(keyCountLogFile,QString::number(count));
}

bool LauncherConfig::setDefaultParametr()
{
    if (!Config::clear()) return false;
    foreach (QString item, defaultCfg->getConfigKeyName())
    {
        Config::set(item,defaultCfg->get(item));
    }
    return true;
}

bool LauncherConfig::setDefaultWidth()
{
    return Config::set(keyWidth,defaultCfg->get(keyWidth));
}

bool LauncherConfig::setDefaultHeight()
{
    return Config::set(keyHeight,defaultCfg->get(keyHeight));
}

bool LauncherConfig::setDefaultFullScrean()
{
    return Config::set(keyFullScrean,defaultCfg->get(keyFullScrean));
}

bool LauncherConfig::setDefaultLanguage()
{
    return Config::set(keyLanguage,defaultCfg->get(keyLanguage));
}

bool LauncherConfig::setDefaultStartPage()
{
    return Config::set(keyStartPage,defaultCfg->get(keyStartPage));
}

bool LauncherConfig::setDefaultServerAddress()
{
    return Config::set(keyIpServer,defaultCfg->get(keyIpServer));
}

bool LauncherConfig::setDefaultServerPort()
{
    return Config::set(keyPortServer,defaultCfg->get(keyPortServer));
}

bool LauncherConfig::setDefaultLogState()
{
    return Config::set(keyLogState,defaultCfg->get(keyLogState));
}

bool LauncherConfig::setDefaultLogFolder()
{
    return Config::set(keyLogFolderPath,defaultCfg->get(keyLogFolderPath));
}

bool LauncherConfig::setDefaultCountLogFile()
{
    return Config::set(keyCountLogFile,defaultCfg->get(keyCountLogFile));
}
