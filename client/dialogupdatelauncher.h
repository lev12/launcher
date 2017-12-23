#ifndef DIALOGUPDATELAUNCHER_H
#define DIALOGUPDATELAUNCHER_H

#include <QDialog>
#include <QString>

#include "global_variable.h"

namespace Ui {
class DialogUpdateLauncher;
}

class DialogUpdateLauncher : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpdateLauncher(QWidget *parent = 0, QString ver = "NULL");
    ~DialogUpdateLauncher();

signals:
    void download (QString,versionType,int);

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Download_clicked();

private:
    Ui::DialogUpdateLauncher *ui;

    int version;
};

#endif // DIALOGUPDATELAUNCHER_H
