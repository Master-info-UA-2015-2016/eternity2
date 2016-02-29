#include "motif.h"

Motif::Motif()
{

}

Motif::Motif(QColor *inte, QColor *exte) :
    color_int(inte), color_ext(exte)
{

}

Motif::set_color_int(QColor *col)
{
    color_int = col;
}

Motif::set_color_ext(QColor *col)
{
    color_ext = col;
}

Motif::get_color_int()
{
    return color_int;
}

Motif::get_color_ext()
{
    return color_ext;
}

//definition de 2 couleurs propres a un motif en fonction de son id
Motif::set_colors(int color_1, int color_2)
{
    //couleur interieure
    switch(color_1){
        case 0:

        break;
        case 1:

        break;
        case 2:

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        case 6:

        break;
        case 7:

        break;
        case 8:

        break;
        case 9:

        break;
        case 10:

        break;
        case 11:

        break;
        case 12:

        break;
        default:

        break;
    }

    //couleur exterieure
    switch(color_2){
        case 0:

        break;
        case 1:

        break;
        case 2:

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        case 6:

        break;
        case 7:

        break;
        case 8:

        break;
        case 9:

        break;
        case 10:

        break;
        case 11:

        break;
        case 12:

        break;
        default:

        break;
    }
}
