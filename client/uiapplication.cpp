#include "uiapplication.h"
#include "ui_uiapplication.h"

UiApplication::UiApplication(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UiApplication)
{
    ui->setupUi(this);

    menuVert = new MenuVertical ();
    ui->horizontalLayout->addWidget(menuVert);

    appName = NULL;
    appIcon = NULL;
    language = NULL;
    platforms = NULL;
    minSysRequiremets = NULL;
    recommendedSysRequiremets = NULL;
    currentVersion = NULL;
    activePage = NULL;

}

UiApplication::~UiApplication()
{
    delete ui;
}

bool UiApplication::initName(QString *name)
{
    appName = name;
    return true;
}

bool UiApplication::initIcon(QIcon *icon)
{
    //TODO
    return true;
}

bool UiApplication::initSupportLanguage(QStringList *Language)
{
    language = Language;

    return true;
}

bool UiApplication::initPlatforms(QList<Platform> *Platforms)
{
    platforms = Platforms;

    return true;
}

bool UiApplication::initMinimumSystemRequirements(QString *text)
{
    minSysRequiremets = text;
    
    return true;
}
bool UiApplication::initRecommendedSystemRequirements(QString *text)
{
    recommendedSysRequiremets = text;
    
    return true;
}

bool UiApplication::initVersionList(QStringList *versionsList)
{
    versions = versionsList;

    return true;
}

void UiApplication::setCurrentVersion(QString *version)
{
    currentVersion = version;
    
    return;
}

bool UiApplication::setActivePage(int i)
{
    renderFrame(i);
    return true;
}

bool UiApplication::renderFrame(int i)
{
    removeActiveFrame();

    QWidget *frame;
    if (i == 1)
    {
        frame = createGeneralPage();
        if (frame == NULL)
        {
            activePage = new int(0);
            return false;
        }
        activePage = new int(0);
    }
    ui->horizontalLayout->addWidget(frame);
    return true;
}

bool UiApplication::removeActiveFrame()
{
    if (activePage == NULL)
    {
        return false;
    }

    if (*activePage == 1)
    {
        ui->horizontalLayout->removeWidget(generalApplication);
        delete generalApplication;
        activePage = 0;
        return true;
    }
    return false;
}

QFrame* UiApplication::createGeneralPage()
{
    generalApplication = new UiGeneralApplication(this, appName, appIcon);
    generalApplication->setVerListComboBox(versions);
    generalApplication->setCurrentVersion(currentVersion);
    generalApplication->setPlatforms(platforms);
    generalApplication->setSupportLanguage(language);
    generalApplication->setMinimumSystemRequirements(minSysRequiremets);
    generalApplication->setRecommendedSystemRequirements(recommendedSysRequiremets);
    return generalApplication;
}

void UiApplication::showGeneral()
{
    renderFrame(1);
    return;
}

void UiApplication::showVersionMenager()
{
    renderFrame(2);
    return;
}

void UiApplication::showSettings()
{
    renderFrame(3);
    return;
}

void UiApplication::startApp()
{

}
