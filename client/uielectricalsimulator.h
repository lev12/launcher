#ifndef UIELECTRICALSIMULATOR_H
#define UIELECTRICALSIMULATOR_H

#include <QFrame>

namespace Ui {
class UiElectricalSimulator;
}

class UiElectricalSimulator : public QFrame
{
    Q_OBJECT

public:
    explicit UiElectricalSimulator(QWidget *parent = 0);
    ~UiElectricalSimulator();

private:
    Ui::UiElectricalSimulator *ui;
};

#endif // UIELECTRICALSIMULATOR_H
