#ifndef MENUVERTICAL_H
#define MENUVERTICAL_H

#include <QFrame>

namespace Ui {
class MenuVertical;
}

class MenuVertical : public QFrame
{
    Q_OBJECT

public:
    explicit MenuVertical(QFrame *parent = 0);
    ~MenuVertical();

    bool setQuickStartText(QString str);

private:
    Ui::MenuVertical *ui;

signals:
    void pushGeneral();
    void pushVersionMenager();
    void pushSettings();
    void pushQuickStart();
private slots:
    void on_generalbutton_clicked();
    void on_versionmenagerbutton_clicked();
    void on_settingbutton_clicked();
    void on_quickstartbutton_clicked();
};

#endif // MENUVERTICAL_H
