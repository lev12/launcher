#include "updatelauncher.h"
#include "ui_updatelauncher.h"

UpdateLauncher::UpdateLauncher(QWidget *parent, QString versionName) :
    QFrame(parent),
    ui(new Ui::UpdateLauncher)
{
    ui->setupUi(this);
    QString tempName = "Version: ";
    tempName.append(versionName);
    ui->label->setText(tempName);
}

UpdateLauncher::~UpdateLauncher()
{
    delete ui;
}
 
