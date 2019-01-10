#include "uigeneralapplication.h"
#include "ui_uigeneralapplication.h"

UiGeneralApplication::UiGeneralApplication(QWidget *parent, QString *AppName, QIcon *AppIcon) :
    QFrame(parent),
    ui(new Ui::UiGeneralApplication)
{
    ui->setupUi(this);

    if (AppName == NULL)
    {
        appName = new QString ("No Name");
    }
    else
    {
        appName = AppName;
    }

    if (AppIcon == NULL)
    {
        appIcon = NULL;
    }
    else
    {
        appIcon = AppIcon;
    }
}

UiGeneralApplication::~UiGeneralApplication()
{
    delete ui;
}

bool UiGeneralApplication::setVerListComboBox(QStringList *versions)
{
    ui->comboBox_version->addItems(*versions);
    return true;
}

bool UiGeneralApplication::setCurrentVersion(QString *version)
{
    ui->comboBox_version->setCurrentText(*version);
    return true;
}

bool UiGeneralApplication::setWhatNew(QList<News> news)
{
    return true;
}

bool UiGeneralApplication::setPlatforms(QList<PlatformType> *platform)
{
    if (platform == NULL)
    {
        return false;
    }

    QStringList plstrlist;
    foreach (PlatformType pl, *platform)
    {
        if (pl == PC) plstrlist.operator <<("PC");
        else if (pl == MAC) plstrlist.operator <<("Mac");
        else if (pl == Android) plstrlist.operator <<("Android");
        else if (pl == IOS) plstrlist.operator <<("IOS");
        else if (pl == XBox) plstrlist.operator <<("XBox");
        else if (pl == PlayStation) plstrlist.operator <<("PlayStation");
    }

    QString plstr = "platform: ";
    foreach (QString str, plstrlist)
    {
        plstr.append(str);
        plstr.append(", ");
    }


    ui->label_platform->setText(plstr);
    return true;
}

bool UiGeneralApplication::setSupportLanguage(QStringList *language)
{
    if (language == NULL)
    {
        return false;
    }

    QString langstr = "language: ";
    for (int i(0), languageSize = language->size(); i < languageSize; i++)
    {
        /*QString str;
        if (language->at(i) == Russian) str.append("Russian");
        else if (language->at(i) == English) str.append("English");

        langstr.append(str);*/
        langstr.append(language->at(i));
        if (languageSize == i+1)
        {
            langstr.append(", ");
        }

    }
    ui->label_language->setText(langstr);
    return true;
}

bool UiGeneralApplication::setMinimumSystemRequirements(QString *text)
{
    ui->label_minimumSystemRequirements->setText(*text);
    return true;
}

bool UiGeneralApplication::setRecommendedSystemRequirements(QString *text)
{
    ui->label_recommendedSystemRequirements->setText(*text);
    return true;
}

void UiGeneralApplication::on_pushButton_startVersion_clicked()
{
    pushStartButton();
}
