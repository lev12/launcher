#ifndef UIAPPLICATIONINSTALLED_H
#define UIAPPLICATIONINSTALLED_H

#include <QFrame>

namespace Ui {
class UiApplicationInstalled;
}

class UiApplicationInstalled : public QFrame
{
    Q_OBJECT

public:
    explicit UiApplicationInstalled(QWidget *parent = nullptr);
    ~UiApplicationInstalled();

private:
    Ui::UiApplicationInstalled *ui;
};

#endif // UIAPPLICATIONINSTALLED_H
