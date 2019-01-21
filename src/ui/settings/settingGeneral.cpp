#include "settingGeneral.h"

SettingsGeneral::SettingsGeneral(QWidget *parent) :
    QFrame(parent)
{
    cfg = &LauncherConfig::instance();
    content = new QVBoxLayout (this);
    this->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));

    uiWidth = new SettingSpinBox (cfg->getWidth(),tr("Width"),this);
    uiHeight = new SettingSpinBox (cfg->getHeight(),tr("Height"),this);
    uiFullScrean = new settingCheckbox(tr("Full Screan"),this);
    uiScale = new SettingSpinBox (100,tr("Scale"),this);

    content->addWidget(uiWidth);

    content->addWidget(uiHeight);

    content->addWidget(uiFullScrean);

    content->addWidget(uiScale);

    QSpacerItem *hSpacerItem = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    content->addSpacerItem(hSpacerItem);
}

SettingsGeneral::~SettingsGeneral()
{

}
