#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>
#include <QDebug>
#include <QLocale>
#include "config.h"
#include "log.h"

namespace Ui {
class settings;
}

class Settings : public QFrame
{
    Q_OBJECT

public:
    Settings(Config &cfg, QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_pushButton_clicked();

    void on_lenguageComboBox_currentIndexChanged(int index);

public slots:
    void save();

private:
    Ui::settings *ui;
    Config *conf;
    bool *fullscrean;
    QLocale::Language *language;
    bool *logState;
    int *interfaceSize;
    bool *checkUpdateLauncher;
};

#endif // SETTINGS_H
