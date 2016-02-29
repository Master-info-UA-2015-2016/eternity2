#include "motif.h"

Motif::Motif()
{

}

Motif::Motif(QColor *inte, QColor *exte) :
    color_int(inte), color_ext(exte)
{

}

Motif::Motif(AvailableColors col1, AvailableColors col2)
{
    QColor* tmp;

    //couleur interieure
    switch(col1){
        case White:
            *tmp = White;
            break;
        case Black:
            *tmp = Black;
            break;
        case Gray:
            *tmp = Gray;
            break;
        case Brown:
            *tmp = Brown;
            break;
        case Orange:
            *tmp = Orange;
            break;
        case Pink:
            *tmp = Pink;
            break;
        case Red:
            *tmp = Yellow;
            break;
        case Yellow:
            *tmp = Yellow;
            break;
        case LightGreen:
            *tmp = LightGreen;
            break;
        case DarkGreen:
            *tmp = DarkGreen;
            break;
        case LightBlue:
            *tmp = LightBlue;
            break;
        case DarkBlue:
            *tmp = DarkBlue;
            break;
        case Purple:
            *tmp = Purple;
            break;

    }
    color_int = tmp;

    //couleur exterieure
    switch(col2){
        case White:
            *tmp = White;
            break;
        case Black:
            *tmp = Black;
            break;
        case Gray:
            *tmp = Gray;
            break;
        case Brown:
            *tmp = Brown;
            break;
        case Orange:
            *tmp = Orange;
            break;
        case Pink:
            *tmp = Pink;
            break;
        case Red:
            *tmp = Yellow;
            break;
        case Yellow:
            *tmp = Yellow;
            break;
        case LightGreen:
            *tmp = LightGreen;
            break;
        case DarkGreen:
            *tmp = DarkGreen;
            break;
        case LightBlue:
            *tmp = LightBlue;
            break;
        case DarkBlue:
            *tmp = DarkBlue;
            break;
        case Purple:
            *tmp = Purple;
            break;
    }
    color_ext = tmp;
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

void Motif::set_colors(AvailableColors color_1, AvailableColors color_2)
{

}
