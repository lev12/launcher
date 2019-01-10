#ifndef UIAPPLICATIONITEM_H
#define UIAPPLICATIONITEM_H

#include <QFrame>
#include <QIcon>
#include <QString>
#include <QSize>

namespace Ui {
class UiApplicationItem;
}

class UiApplicationItem : public QFrame
{
    Q_OBJECT

public:
    explicit UiApplicationItem(QString &name,QIcon &icon,QWidget *parent = nullptr);
    ~UiApplicationItem();

    QString *getAppName() const;
    QIcon *getAppIcon() const;

private slots:
    void on_applicationButton_clicked();

signals:
    void clicked(UiApplicationItem *app);

private:
    Ui::UiApplicationItem *ui;
    QString *appName;
    QIcon *appIcon;
};

#endif // UIAPPLICATIONITEM_H
