#ifndef GENERAL_H
#define GENERAL_H

#include <QFrame>

namespace Ui {
class General;
}

class General : public QFrame
{
    Q_OBJECT

public:
    explicit General(QWidget *parent = 0);
    ~General();

private:
    Ui::General *ui;
};

#endif // GENERAL_H
