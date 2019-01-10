#ifndef UIMAINMENU_H
#define UIMAINMENU_H

#include <QFrame>

namespace Ui {
class UiMainMenu;
}

class UiMainMenu : public QFrame
{
    Q_OBJECT

public:
    explicit UiMainMenu(QWidget *parent = nullptr);
    ~UiMainMenu();

signals:
    void clickedHomePage();
    void clickedInstalledApplication();

private slots:
    void on_homebutton_clicked();
    void on_installedApplicatonButton_clicked();

private:
    Ui::UiMainMenu *ui;
};

#endif // UIMAINMENU_H
