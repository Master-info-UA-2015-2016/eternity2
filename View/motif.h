#ifndef MOTIF_H
#define MOTIF_H

#include <QColor> 

//couleurs utilisables
enum AvailableColors{Black, Gray, Brown, Orange, Pink, Red, Yellow, LightGreen, DarkGreen, LightBlue, DarkBlue, Purple};

class Motif
{
private:
    QColor* color_int;
    QColor* color_ext;

public:
    Motif();
    Motif(QColor* inte, QColor* exte);

    void set_color_int(QColor* col);
    void set_color_ext(QColor* col);

//    TODO @Antoine (@AsCris)
    QColor* get_color_int();
    QColor* get_color_ext();

//definition de 2 couleurs propres a un motif en fonction de son id
    void set_colors(int color_1, int color_2);
};

#endif // MOTIF_H
