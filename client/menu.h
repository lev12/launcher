#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <QString>
#include "global_variable.h"

namespace Ui {
class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

    appInfo getShowWiget ();
    bool setShowWiget (int i);
    void addAppInfo (appInfo info);

    QWidget *showApp;
    int showIndex;
    QList <appInfo> appinfo;
    Ui::Menu *ui;

signals:

    void swithWidget();

private slots:
    void on_pushButtonElectricalSimulator_clicked();
    void on_LaunherPushButton_clicked();
};

#endif // MENU_H
