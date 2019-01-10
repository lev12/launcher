#ifndef UIHOMEPAGE_H
#define UIHOMEPAGE_H

#include <QFrame>
#include <QList>
#include <QDebug>
#include <QMap>
#include "abstractApplication.h"

namespace Ui {
class UiHomePage;
}

class UiHomePage : public QFrame
{
    Q_OBJECT

public:
    explicit UiHomePage(QList<AbstractApplication*> applist, QWidget *parent = nullptr);
    ~UiHomePage();
private slots:
    void reciveClicked(UiApplicationItem *app);
signals:
    void clikedApplication(UiApplication *app);
private:
    Ui::UiHomePage *ui;
    QList<AbstractApplication*> *applicationlist;
    QMap<AbstractApplication*,UiApplicationItem*> *applicationMap;
};

#endif // UIHOMEPAGE_H
