#include "motif.h"

Motif::Motif()
{

}

Motif::Motif(QColor *inte, QColor *exte) :
    color_int(inte), color_ext(exte)
{

}


QColor* Motif::getQColorFromInt(int color){
    QColor* tmp= new QColor;

    //couleur interieure
    switch(color){
        case White:
            tmp->setRgb(255,255,255);
            break;
        case Black:
            tmp->setRgb(0,0,0);
            break;
        case Gray:
            tmp->setRgb(128,128,128);
            break;
        case Brown:
            tmp->setRgb(100,50,0);
            break;
        case Orange:
            tmp->setRgb(250,128,0);
            break;
        case Pink:
            tmp->setRgb(250,100,250);
            break;
        case Red:
            tmp->setRgb(255,0,0);
            break;
        case Yellow:
            tmp->setRgb(250,250,0);
            break;
        case LightGreen:
            tmp->setRgb(100,250,100);
            break;
        case DarkGreen:
            tmp->setRgb(0,150,0);
            break;
        case LightBlue:
            tmp->setRgb(100,250,250);
            break;
        case DarkBlue:
            tmp->setRgb(0,0,250);
            break;
        case Purple:
            tmp->setRgb(150,50,250);
            break;

    }
    return tmp;
}

Motif::Motif(AvailableColors col_int, AvailableColors col_ext)
{
    color_int= getQColorFromInt(col_int);
    color_ext= getQColorFromInt(col_ext);
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
