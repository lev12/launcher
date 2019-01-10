#ifndef UIGENERALAPPLICATION_H
#define UIGENERALAPPLICATION_H

#include <QFrame>
#include <QString>
#include <QList>
#include <QIcon>

#include "globalVariable.h"

namespace Ui {
class UiGeneralApplication;
}

class UiGeneralApplication : public QFrame
{
    Q_OBJECT

public:
    struct News
    {
        QString Title;
    };

    explicit UiGeneralApplication (QWidget *parent = 0, QString *AppName = NULL, QIcon *AppIcon = NULL);
    bool setVerListComboBox (QStringList *versions);
    bool setCurrentVersion (QString *version);
    bool setWhatNew (QList <News> news);
    bool setPlatforms (QList<PlatformType> *platform);
    bool setSupportLanguage (QStringList *language);
    bool setMinimumSystemRequirements (QString *text);
    bool setRecommendedSystemRequirements (QString *text);



    ~UiGeneralApplication ();
private:
    Ui::UiGeneralApplication *ui;
    QIcon *appIcon;
    QString *appName;

private slots:
    void on_pushButton_startVersion_clicked ();

signals:
    void pushStartButton ();
};

#endif // UIGENERALAPPLICATION_H
