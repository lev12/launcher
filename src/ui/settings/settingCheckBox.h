#ifndef SETTINGCHECKBOX_H
#define SETTINGCHECKBOX_H

#include <QFrame>

namespace Ui {
class settingCheckbox;
}

class settingCheckbox : public QFrame
{
    Q_OBJECT

public:
    explicit settingCheckbox(QString text,QWidget *parent = nullptr);
    ~settingCheckbox();

    void setText (QString text);

private:
    Ui::settingCheckbox *ui;
};

#endif // SETTINGCHECKBOX_H
