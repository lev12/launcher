#ifndef MENUGENERAL_H
#define MENUGENERAL_H

#include <QFrame>

namespace Ui {
class MenuGeneral;
}

class MenuGeneral : public QFrame
{
    Q_OBJECT

public:
    explicit MenuGeneral(QWidget *parent = 0);
    ~MenuGeneral();

    bool setUserName (QString name_str);

private:
    Ui::MenuGeneral *ui;

signals:
    void pushNews();
    void pushApplication();
    void pushNotification();
    void pushDownloads();
    void pushSetting();

private slots:
    void on_newsbutton_clicked();
    void on_aplicatonbutton_clicked();
    void on_notificationbutton_clicked();
    void on_downloadbutton_clicked();
    void on_settingbutton_clicked();
};

#endif // MENUGENERAL_H
