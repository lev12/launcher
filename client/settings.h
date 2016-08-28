#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>

namespace Ui {
class settings;
}

class settings : public QFrame
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::settings *ui;

    bool fullScrean = false;
};

#endif // SETTINGS_H
