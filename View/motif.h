#ifndef MOTIF_H
#define MOTIF_H

#include <QColor> 

class Motif
{
private:
    int id;
    QColor* color_int;
    QColor* color_ext;

public:
    Motif();
//    TODO @Antoine (@AsCris)
//    QColor* get_color_int();
//    QColor* get_color_ext();
};

#endif // MOTIF_H
