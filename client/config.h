#ifndef CONFIG_H
#define CONFIG_H

#include <QTextStream>

class config
{
private:
    struct str_conf{
    QString str_height;
    int height;
    QString str_width;
    int width;
    };

    void init();
public:
    str_conf data;
    config();
    bool create();
    bool refresh();
    int get(QString str);
};

#endif // CONFIG_H
