#ifndef UIAPPLICATION_H
#define UIAPPLICATION_H

#include <QFrame>

#include "menuvertical.h"
#include "uigeneralapplication.h"

namespace Ui {
class UiApplication;
}

class UiApplication : public QFrame
{
    Q_OBJECT

public:
    UiApplication(QWidget *parent = 0, QString *AppName = NULL);
    ~UiApplication();

    QString *getCurrentVersion ();

    bool setIcon (QIcon *icon);
    bool setSupportLanguage (QStringList *Language);
    bool setPlatforms(QList<PlatformType> *Platforms);
    bool setMinimumSystemRequirements(QString *text);
    bool setRecommendedSystemRequirements(QString *text);
    bool setVersionList(QStringList *versionsList);
    void setCurrentVersion(QString *version);

    bool setActivePage (int i);
private:
    Ui::UiApplication *ui;

    int *activePage;
    MenuVertical *menuVert;
    UiGeneralApplication *generalApplication;
    
    QString *appName;
    QIcon *appIcon;
    QStringList *language;
    QList<PlatformType> *platforms;
    QString *minSysRequiremets;
    QString *recommendedSysRequiremets;
    QString *currentVersion;
    QStringList *versions;

    bool initName(QString *name);
    bool initIcon();
    bool initSupportLanguage ();
    bool initPlatforms();
    bool initMinimumSystemRequirements();
    bool initRecommendedSystemRequirements();
    bool initVersionList();


    QFrame *createGeneralPage();

    bool removeActiveFrame();
    bool renderFrame (int i);
private slots:
    void showGeneral();
    void showVersionMenager();
    void showSettings();
    void startApp();
};

#endif // UIAPPLICATION_H
