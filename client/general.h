#ifndef GENERAL_H
#define GENERAL_H

#include <QFrame>
#include "settings.h"
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
    explicit General(QWidget *parent = 0,Menu *menuGen = 0);

    virtual appInfo getAppInfo ();

    ~General();

    Menu *menu;
    config *cfg;
    bool showSettings = false;
    settings *setting;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

signals:
    void fullScreenMode();
    void normalMode();

private:
    Ui::General *ui;
    appInfo appinfo;
};

#endif // GENERAL_H
