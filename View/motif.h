#ifndef MOTIF_H
#define MOTIF_H

#include <QColor> 

//couleurs utilisables
enum AvailableColors{White, Black, Gray, Brown, Orange, Pink, Red, Yellow, LightGreen, DarkGreen, LightBlue, DarkBlue, Purple};
enum PairColors{Black_Black, Gray_Brown, Pink_Brown, Red_Brown, Yellow_Brown, LightGreen_Brown, LightBlue_Brown,
                     Purple_Brown, Gray_Orange, Pink_Orange, Red_Orange, Yellow_Orange, LightGreen_Orange,
                    DarkGreen_Orange, LightBlue_Orange, DarkBlue_Orange, Purple_Orange, Gray_DarkGreen, Pink_DarkGreen,
                    Red_DarkGreen, Yellow_DarkGreen, LightBlue_DarkGreen, DarkBlue_DarkGreen, Purple_DarkGreen};
class Motif
{
private:
    QColor* color_int;
    QColor* color_ext;

public:
    Motif();
    Motif(QColor* inte, QColor* exte);
    Motif(AvailableColors col_int, AvailableColors col_ext);

    void set_color_int(QColor* col);
    void set_color_ext(QColor* col);

    QColor* getQColorFromInt(int color);

//    TODO @Antoine (@AsCris)
    QColor* get_color_int();
    QColor* get_color_ext();

//definition de 2 couleurs propres a un motif en fonction de son id
    void set_colors(AvailableColors color_1, AvailableColors color_2);
};

#endif // MOTIF_H
