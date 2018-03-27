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
    UiApplication(QWidget *parent = 0);
    ~UiApplication();

    bool initName(QString *name);
    bool initIcon(QIcon *icon);
    bool initSupportLanguage (QStringList *Language);
    bool initPlatforms(QList<Platform> *Platforms);
    bool initMinimumSystemRequirements(QString *text);
    bool initRecommendedSystemRequirements(QString *text);
    bool initVersionList(QStringList *versionsList);
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
    QList<Platform> *platforms;
    QString *minSysRequiremets;
    QString *recommendedSysRequiremets;
    QString *currentVersion;
    QStringList *versions;

    QFrame *createGeneralPage();

    bool removeActiveFrame();
    bool renderFrame (int i);
    QList<Platform> strToPlatform (QStringList platformStrList);

private slots:
    void showGeneral();
    void showVersionMenager();
    void showSettings();
    void startApp();
};

#endif // UIAPPLICATION_H
