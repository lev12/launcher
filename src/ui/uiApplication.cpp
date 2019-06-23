#include "uiApplication.h"
//#include "ui_uiApplication.h"

UiApplication::UiApplication(QString *AppName, QWidget *parent) :
    AbstractWindow (12,parent)
{

    if (this->objectName().isEmpty())
        this->setObjectName(QLatin1String("UiApplication"));
    this->resize(685, 480);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(400, 400));
    this->setMaximumSize(QSize(16777215, 16777215));
    this->setAutoFillBackground(false);
    this->setStyleSheet(QLatin1String("background-color: rgba(0, 0, 0, 20);"));
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);
    this->setLineWidth(0);
    horizontalLayout_2 = new QHBoxLayout(this);
    horizontalLayout_2->setSpacing(0);
    horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
    horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
    horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);

    horizontalLayout_2->addLayout(horizontalLayout);
    retranslateUi(this);

    initName (AppName);
}

UiApplication::~UiApplication()
{

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
    platforms = new QList<PlatformType>;

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
    *appIcon = *icon;

    return true;
}

bool UiApplication::setSupportLanguage(QStringList *Language)
{
    *language = *Language;

    return true;
}

bool UiApplication::setPlatforms(QList<PlatformType> *Platforms)
{
    *platforms = *Platforms;

    return true;
}

bool UiApplication::setMinimumSystemRequirements(QString *text)
{
    *minSysRequiremets = *text;

    return true;
}

bool UiApplication::setRecommendedSystemRequirements(QString *text)
{
    *recommendedSysRequiremets = *text;

    return true;
}

bool UiApplication::setVersionList(QStringList *versionsList)
{
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
        activePage = new int(0);
        horizontalLayout->addWidget(frame);
    }
    return true;
}

bool UiApplication::removeActiveFrame()
{
    if (activePage == nullptr)
    {
        return false;
    }

    if (*activePage == 1)
    {
        horizontalLayout->removeWidget(generalApplication);
        delete generalApplication;
        *activePage = 0;
        return true;
    }
    return false;
}

QFrame* UiApplication::createGeneralPage()
{
    generalApplication = new UiGeneralApplication(this, appName, appIcon);
    if (versions != nullptr)
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

void UiApplication::retranslateUi(QFrame *UiApplication)
{
    UiApplication->setWindowTitle(tr("UiApplication"));
}
