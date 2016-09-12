#ifndef GENERAL_H
#define GENERAL_H

#include <QFrame>
#include "settings.h"
#include "global_variable.h"
#include "background.h"

namespace Ui {
class General;
}

class General : public QFrame
{
    Q_OBJECT

public:
    explicit General(QWidget *parent = 0);
    ~General();

    config *cfg;
    bool showSettings = false;
    settings *setting;

private:
    Ui::General *ui;
};

#endif // GENERAL_H
