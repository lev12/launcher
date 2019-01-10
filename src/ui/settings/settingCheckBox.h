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
    explicit settingCheckbox(QWidget *parent = nullptr);
    ~settingCheckbox();

private:
    Ui::settingCheckbox *ui;
};

#endif // SETTINGCHECKBOX_H
