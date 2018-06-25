#include "dialogupdatelauncher.h"
#include "ui_dialogupdatelauncher.h"

DialogUpdateLauncher::DialogUpdateLauncher(QWidget *parent, QString ver) :
    QDialog(parent),
    ui(new Ui::DialogUpdateLauncher)
{
    ui->setupUi(this);
    QString verName = "Version: ";
    verName.append(ver);

    ui->label->setText(verName);

    version = ver.toInt();
}

DialogUpdateLauncher::~DialogUpdateLauncher()
{
    delete ui;
}

void DialogUpdateLauncher::on_pushButton_Cancel_clicked()
{
    this->close();
}

void DialogUpdateLauncher::on_pushButton_Download_clicked()
{
    download("Launcher", VersionType::null, version);
}
