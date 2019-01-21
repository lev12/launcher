#ifndef SETTINGSPINBOX_H
#define SETTINGSPINBOX_H

#include <QFrame>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

class SettingSpinBox : public QFrame
{
public:
    SettingSpinBox(int defaultValue, QString text, QWidget *parent = nullptr);
    ~SettingSpinBox();

private:
    QSpinBox *spinBox;
    QLabel *label;
    QHBoxLayout *hBoxLayout;
    QSpacerItem *hSpacer;
};

#endif // SETTINGSPINBOX_H
