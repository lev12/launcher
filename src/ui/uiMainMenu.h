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

    bool getEnableBackButton();
    bool getEnableHomePage();
    bool getEnableSettings();

    void setEnabledBackButton(bool state);
    void setEnabledHomePage(bool state);
    void setEnabledSettings(bool state);

    void enabledAllButton();
    void disabledAllButton();

signals:
    void clickedBack ();
    void clickedHomePage();
    void clickedSettings();

private slots:
    void on_backButton_clicked();
    void on_homeButton_clicked();
    void on_settingButton_clicked();


private:
    Ui::UiMainMenu *ui;
};

#endif // UIMAINMENU_H
