#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>
#include <QDebug>
#include "config.h"

namespace Ui {
class settings;
}

class settings : public QFrame
{
    Q_OBJECT

public:
    settings(QWidget *parent = 0, Config *cfg = NULL);
    ~settings();

private slots:
    void on_pushButton_clicked();

    void on_lenguageComboBox_currentIndexChanged(int index);

public slots:
    void save();

private:
    Ui::settings *ui;
    Config *conf;
    bool fullScrean = false;
    int lenguage = 0;
};

#endif // SETTINGS_H
