#ifndef UIAPPLICATIONOVERVIEW_H
#define UIAPPLICATIONOVERVIEW_H

#include <QFrame>

namespace Ui {
class UiApplicationOverview;
}

class UiApplicationOverview : public QFrame
{
    Q_OBJECT

public:
    explicit UiApplicationOverview(QWidget *parent = nullptr);
    ~UiApplicationOverview();

private:
    Ui::UiApplicationOverview *ui;
};

#endif // UIAPPLICATIONOVERVIEW_H
