#include "settingCheckBox.h"
#include "ui_settingCheckBox.h"

settingCheckbox::settingCheckbox(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::settingCheckbox)
{
    ui->setupUi(this);
}

settingCheckbox::~settingCheckbox()
{
    delete ui;
}
