#ifndef GENERAL_H
#define GENERAL_H

#include <QFrame>
#include "settingsmenu.h"
#include "global_variable.h"
#include "background.h"
#include "menu.h"

namespace Ui {
class General;
}

class General : public QFrame
{
    Q_OBJECT

public:
    General(QWidget *parent = 0, Menu *menuGen = 0, Log *logfile = 0);

    virtual appInfo getAppInfo ();

    ~General();

    Menu *menu;
    config *cfg;
    Log *log;
    bool showSettings = false;
    SettingsMenu *settingMenu;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

public slots:
    void on_pushButton_clicked();
    void closeSettingsMenu();

signals:
    void fullScreenMode();
    void normalMode();

private:
    Ui::General *ui;
    appInfo appinfo;
};

#endif // GENERAL_H
