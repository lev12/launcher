#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>
#include "config.h"

namespace Ui {
class settings;
}

class settings : public QFrame
{
    Q_OBJECT

public:
    settings(QWidget *parent = 0, config *cfg = NULL);
    ~settings();

private slots:
    void on_pushButton_clicked();
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

    void on_lenguageComboBox_currentIndexChanged(int index);

signals:
    void close();

private:
    Ui::settings *ui;
    config *conf;
    bool fullScrean = false;
    int lenguage = 0;
};

#endif // SETTINGS_H
