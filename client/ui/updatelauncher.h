#ifndef UPDATELAUNCHER_H
#define UPDATELAUNCHER_H

#include <QFrame>
#include <QString>

namespace Ui {
class UpdateLauncher;
}

class UpdateLauncher : public QFrame
{
    Q_OBJECT

public:
    explicit UpdateLauncher(QWidget *parent = 0, QString versionName = NULL);
    ~UpdateLauncher();

private:
    Ui::UpdateLauncher *ui;
};

#endif // UPDATELAUNCHER_H
