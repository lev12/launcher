#ifndef UIAPPLICATIONITEM_H
#define UIAPPLICATIONITEM_H

#include <QFrame>

namespace Ui {
class uiApplicationItem;
}

class uiApplicationItem : public QFrame
{
    Q_OBJECT

public:
    explicit uiApplicationItem(QWidget *parent = 0);
    ~uiApplicationItem();

private:
    Ui::uiApplicationItem *ui;
};

#endif // UIAPPLICATIONITEM_H
