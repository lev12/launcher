#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>
#include <QObject>

#include "files.h"

class Application : public Files
{
    Q_OBJECT
private:

    QComboBox *g_cb;

public slots:
    void connectServer ();

signals:
    void getListVersions ();

public:
    Application();

    QString getItemComboBox  (QComboBox *cb);
    void FillingComboBox     (QComboBox *cb);
    void open();
};

#endif // APPLICATION_H
