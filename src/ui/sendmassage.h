#ifndef SENDMASSAGE_H
#define SENDMASSAGE_H

#include <QFrame>

namespace Ui {
class SendMassage;
}

class SendMassage : public QFrame
{
    Q_OBJECT

public:
    explicit SendMassage(QWidget *parent = 0);
    ~SendMassage();

    QString getMessage ();

private:
    Ui::SendMassage *ui;
};

#endif // SENDMASSAGE_H
