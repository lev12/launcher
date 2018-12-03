#ifndef UIAPPLICATIONREQUIREMETS_H
#define UIAPPLICATIONREQUIREMETS_H

#include <QFrame>

namespace Ui {
class UiApplicationRequiremets;
}

class UiApplicationRequiremets : public QFrame
{
    Q_OBJECT

public:
    explicit UiApplicationRequiremets(QWidget *parent = nullptr);
    ~UiApplicationRequiremets();

private:
    Ui::UiApplicationRequiremets *ui;
};

#endif // UIAPPLICATIONREQUIREMETS_H
