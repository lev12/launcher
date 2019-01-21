#include "settingSpinBox.h"

SettingSpinBox::SettingSpinBox(int defaultValue, QString text, QWidget *parent) :
    QFrame (parent)
{
    this->resize(362, 50);
    this->setMinimumSize(QSize(100, 50));
    this->setMaximumSize(QSize(16777215, 50));
    //this->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 127);"));
    hBoxLayout = new QHBoxLayout (this);
    hBoxLayout->setSpacing(0);
    hBoxLayout->setContentsMargins(0, 0, 0, 0);

    spinBox = new QSpinBox (this);
    QSizePolicy sizePolicy (QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    spinBox->setSizePolicy(sizePolicy);
    spinBox->setValue(defaultValue);
    spinBox->setMinimumSize(QSize(50,50));
    spinBox->setMaximumSize(QSize(50,50));
    spinBox->setButtonSymbols(QSpinBox::NoButtons);
    spinBox->setRange(0,16000000);
    hBoxLayout->addWidget(spinBox);

    hSpacer = new QSpacerItem (40,20, QSizePolicy::Maximum, QSizePolicy::Minimum);
    hBoxLayout->addItem(hSpacer);

    label = new QLabel (this);
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy1);
    label->setMinimumSize(QSize(50,50));
    label->setMaximumSize(QSize(25000,25000));
    hBoxLayout->addWidget(label);

    label->setText(text);
}

SettingSpinBox::~SettingSpinBox()
{

}
