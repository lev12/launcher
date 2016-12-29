#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QFrame>
#include <QDebug>

#include "config.h"
#include "log.h"
#include "settings.h"
#include "sendmassage.h"

namespace Ui {
class SettingsMenu;
}

class SettingsMenu : public QFrame
{
    Q_OBJECT

public:

    config *cfg;
    Log *log;
    settings *setting;
    SendMassage *sendmessage;

    explicit SettingsMenu(QWidget *parent, config *conf, Log *logfile);
    ~SettingsMenu();
    void closef();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_close_clicked();

public slots:

signals:
    void close();

private:
    Ui::SettingsMenu *ui;
};

#endif // SETTINGSMENU_H
