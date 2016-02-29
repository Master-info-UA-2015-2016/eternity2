#include "motif.h"

Motif::Motif()
{

}

Motif::Motif(QColor *inte, QColor *exte) :
    color_int(inte), color_ext(exte)
{

}

void Motif::set_color_int(QColor *col)
{
    color_int = col;
}

void Motif::set_color_ext(QColor *col)
{
    color_ext = col;
}

QColor* Motif::get_color_int()
{
    return color_int;
}

QColor* Motif::get_color_ext()
{
    return color_ext;
}
