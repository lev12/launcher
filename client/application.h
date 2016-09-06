#ifndef APPLICATION_H
#define APPLICATION_H

#include <QComboBox>

#include "files.h"

class Application : Files
{
private:

    QComboBox *g_cb;

public:
    Application();

    QString getItemComboBox  (QComboBox *cb);
    void FillingComboBox     (QComboBox *cb);
    bool open();
};

#endif // APPLICATION_H
