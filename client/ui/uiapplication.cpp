#include "uiapplication.h"
#include "ui_uiapplication.h"

UiApplication::UiApplication(QWidget *parent, QString *AppName) :
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
    versions = NULL;

    initName (AppName);
}

UiApplication::~UiApplication()
{
    delete ui;
}

QString *UiApplication::getCurrentVersion()
{
    return currentVersion;
}


//init

bool UiApplication::initName(QString *name)
{
    appName = name;
    return true;
}

bool UiApplication::initIcon()
{
    appIcon = new QIcon ();

    return true;
}

bool UiApplication::initSupportLanguage()
{
    language = new QStringList;

    return true;
}

bool UiApplication::initPlatforms()
{
    platforms = new QList<Platform>;

    return true;
}

bool UiApplication::initMinimumSystemRequirements()
{
    minSysRequiremets = new QString;
    
    return true;
}
bool UiApplication::initRecommendedSystemRequirements()
{
    recommendedSysRequiremets = new QString;
    
    return true;
}

bool UiApplication::initVersionList()
{
    versions = new QStringList;

    return true;
}

//set
bool UiApplication::setIcon(QIcon *icon)
{
    if (appIcon == NULL) initIcon();
    *appIcon = *icon;

    return true;
}

bool UiApplication::setSupportLanguage(QStringList *Language)
{
    if (language == NULL) initSupportLanguage();
    *language = *Language;

    return true;
}

bool UiApplication::setPlatforms(QList<Platform> *Platforms)
{
    if (platforms == NULL) initPlatforms();
    *platforms = *Platforms;

    return true;
}

bool UiApplication::setMinimumSystemRequirements(QString *text)
{
    if (minSysRequiremets == NULL) initMinimumSystemRequirements();
    *minSysRequiremets = *text;

    return true;
}

bool UiApplication::setRecommendedSystemRequirements(QString *text)
{
    if (recommendedSysRequiremets == NULL) initRecommendedSystemRequirements();
    *recommendedSysRequiremets = *text;

    return true;
}

bool UiApplication::setVersionList(QStringList *versionsList)
{
    if (versions == NULL) initVersionList();
    *versions = *versionsList;

    return true;
}

void UiApplication::setCurrentVersion(QString *version)
{
    *currentVersion = *version;
    
    return;
}

bool UiApplication::setActivePage(int i) //TODO rename
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
    if (versions != NULL)
    {
        generalApplication->setVerListComboBox(versions);
        generalApplication->setCurrentVersion(currentVersion);
        generalApplication->setPlatforms(platforms);
        generalApplication->setSupportLanguage(language);
        generalApplication->setMinimumSystemRequirements(minSysRequiremets);
        generalApplication->setRecommendedSystemRequirements(recommendedSysRequiremets);
    }

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
