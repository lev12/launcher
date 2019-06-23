#ifndef UIAPPLICATION_H
#define UIAPPLICATION_H

#include <QFrame>
#include <QTranslator>
#include <QHBoxLayout>
#include "uigeneralapplication.h"
#include "ui/abstractWindow.h"

/*!
 * Id 12
 */

namespace Ui {
class UiApplication;
}

class UiApplication : public AbstractWindow
{
    Q_OBJECT

public:
    UiApplication(QString *AppName,QWidget *parent = nullptr);
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
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;

    int *activePage;
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
    void retranslateUi(QFrame *UiApplication);
private slots:
    void showGeneral();
    void showVersionMenager();
    void showSettings();
    void startApp();
};

#endif // UIAPPLICATION_H
