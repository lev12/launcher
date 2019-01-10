#ifndef UIAPPLICATIONVERSIONMANAGER_H
#define UIAPPLICATIONVERSIONMANAGER_H

#include <QFrame>

namespace Ui {
class UiApplicationVersionManager;
}

class UiApplicationVersionManager : public QFrame
{
    Q_OBJECT

public:
    explicit UiApplicationVersionManager(QWidget *parent = nullptr);
    ~UiApplicationVersionManager();

private:
    Ui::UiApplicationVersionManager *ui;
};

#endif // UIAPPLICATIONVERSIONMANAGER_H
