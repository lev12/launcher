#include "settingCheckBox.h"
#include "ui_settingCheckBox.h"

settingCheckbox::settingCheckbox(QString text, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::settingCheckbox)
{
    ui->setupUi(this);
    setText(text);
}

settingCheckbox::~settingCheckbox()
{
    delete ui;
}

void settingCheckbox::setText(QString text)
{
    ui->label->setText(text);
}
