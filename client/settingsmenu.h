#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QFrame>
#include <QDebug>

#include "config.h"
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
    settings *setting;
    SendMassage *sendmessage;

    explicit SettingsMenu(QWidget *parent, config *conf);
    ~SettingsMenu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public slots:
    void closePressButton();

signals:
    void close();

private:
    Ui::SettingsMenu *ui;
};

#endif // SETTINGSMENU_H
