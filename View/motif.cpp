#include "motif.h"
#include "../Model/piece_model.h"

Motif::Motif(QColor *inte, QColor *exte) :
    color_int(inte), color_ext(exte)
{

}

Motif::Motif(AvailableColors col_int, AvailableColors col_ext)
{
    color_int= getQColorFromInt(col_int);
    color_ext= getQColorFromInt(col_ext);
}


Motif::Motif(int id_motif)
{
    id = id_motif;
//    color_ext= new QColor;
//    color_int= new QColor;
    switch(id_motif){
        case Black_Black:
            set_colors(Black, Black);
            break;
        case Gray_Brown:
            set_colors(Gray, Brown);
            break;
        case Pink_Brown:
            set_colors(Pink, Brown);
            break;
        case Red_Brown:
            set_colors(Red, Brown);
            break;
        case Yellow_Brown:
            set_colors(Yellow, Brown);
            break;
        case Red_LightGreen:
            set_colors(Red, LightGreen);
            break;
        case LightBlue_Brown:
            set_colors(LightBlue, Brown);
            break;
        case Purple_Brown:
            set_colors(Purple, Brown);
            break;
            //fin full brown - 8 couleurs

        case Gray_Orange:
            set_colors(Gray, Orange);
            break;
        case LightGreen_Pink:
            set_colors(LightGreen, Pink);
            break;
        case Yellow_Red:
            set_colors(Yellow, Red);
            break;
        case Purple_Gray:
            set_colors(Purple, Gray);
            break;
        case LightGreen_Orange:
            set_colors(LightGreen, Orange);
            break;
        case LightBlue_Purple:
            set_colors(LightBlue, Purple);
            break;
        case Orange_LightBlue:
            set_colors(Orange, LightBlue);
            break;
        case DarkBlue_Orange:
            set_colors(DarkBlue, Orange);
            break;
        case Purple_Orange:
            set_colors(Purple, Orange);
            break;
        //fin full Orange - 17 couleurs au total

        case Gray_DarkGreen:
            set_colors(Gray, DarkGreen);
            break;
        case Pink_DarkGreen:
            set_colors(Pink, DarkGreen);
            break;
        case Red_DarkGreen:
            set_colors(Red, DarkGreen);
            break;
        case Yellow_DarkGreen:
            set_colors(Yellow, DarkGreen);
            break;
        case LightBlue_DarkGreen:
            set_colors(LightBlue, DarkGreen);
            break;
        case DarkBlue_DarkGreen:
            set_colors(DarkBlue, DarkGreen);
            break;
        case Purple_DarkGreen:
            set_colors(Purple, DarkGreen);
            break;
        //fin full DarkGreen - 24 couleurs au total

        //si pair de couleurs non reconnue, motif blanc
        default:
            set_colors(White, White);
            break;
    }//fin switch
}

void Motif::set_color_int(QColor *col)
{
    color_int = col;
}

void Motif::set_color_ext(QColor *col)
{
    color_ext = col;
}


QColor* Motif::getQColorFromInt(int color) const{
    QColor* tmp= new QColor;

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

QColor* Motif::get_color_int() const
{
    return color_int;
}

QColor* Motif::get_color_ext() const
{
    return color_ext;
}

void Motif::set_colors(AvailableColors exte, AvailableColors inte)
{
    color_int= getQColorFromInt(inte);
    color_ext= getQColorFromInt(exte);
}

std::ostream& Motif::print(std::ostream& out) const{
    out << "Couleurs du motif (int ; ext) : ";

    switch(id){
        case Black_Black:
            out << "Black ; Black";
            break;
        case Gray_Brown:
            out << "Gray ; Brown";
            break;
        case Pink_Brown:
            out << "Pink ; Brown";
            break;
        case Red_Brown:
            out << "Red ; Brown";
            break;
        case Yellow_Brown:
            out << "Yellow ; Brown";
            break;
        case Red_LightGreen:
            out << "Red ; LightGreen";
            break;
        case LightBlue_Brown:
            out << "LightBlue ; Brown";
            break;
        case Purple_Brown:
            out << "Purple ; Brown";
            break;
            //fin full brown - 8 couleurs

        case Gray_Orange:
            out << "Gray ; Orange";
            break;
        case LightGreen_Pink:
            out << "LightGreen ; Pink";
            break;
        case Yellow_Red:
            out << "Yellow ; Red";
            break;
        case Purple_Gray:
            out << "Purple ; Gray";
            break;
        case LightGreen_Orange:
            out << "LightGreen ; Orange";
            break;
        case LightBlue_Purple:
            out << "LightBlue ; Purple";
            break;
        case Orange_LightBlue:
            out << "Orange ; LightBlue";
            break;
        case DarkBlue_Orange:
            out << "DarkBlue ; Orange";
            break;
        case Purple_Orange:
            out << "Purple ; Orange";
            break;
        //fin full Orange - 17 couleurs au total

        case Gray_DarkGreen:
            out << "Gray ; DarkGreen";
            break;
        case Pink_DarkGreen:
            out << "Pink ; DarkGreen";
            break;
        case Red_DarkGreen:
            out << "Red ; DarkGreen";
            break;
        case Yellow_DarkGreen:
            out << "Yellow ; DarkGreen";
            break;
        case LightBlue_DarkGreen:
            out << "LightBlue ; DarkGreen";
            break;
        case DarkBlue_DarkGreen:
            out << "DarkBlue ; DarkGreen";
            break;
        case Purple_DarkGreen:
            out << "Purple ; DarkGreen";
            break;
        //fin full DarkGreen - 24 couleurs au total

        //si pair de couleurs non reconnue, motif blanc
        default:
            out << "White ; White";
            break;
    }//fin switch

    return out;
}
