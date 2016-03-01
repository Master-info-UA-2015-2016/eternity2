#ifndef MOTIF_H
#define MOTIF_H

#include <iostream>
#include <QColor> 

//couleurs utilisables
enum AvailableColors{White, Black, Gray, Brown, Orange, Pink, Red, Yellow, LightGreen, DarkGreen, LightBlue, DarkBlue, Purple};
enum PairColors{Black_Black, Gray_Orange, Pink_Orange, Red_Orange, Yellow_Orange, LightGreen_Orange,
                    DarkGreen_Orange, LightBlue_Orange, DarkBlue_Orange, Purple_Orange, Gray_DarkGreen, Pink_DarkGreen,
                    Red_DarkGreen, Yellow_DarkGreen, LightBlue_DarkGreen, DarkBlue_DarkGreen, Purple_DarkGreen,
                    Gray_Brown, Pink_Brown, Red_Brown, Yellow_Brown, LightGreen_Brown, LightBlue_Brown, Purple_Brown
               };
class Motif
{
private:
    int id;
    QColor* color_int;
    QColor* color_ext;

public:
    Motif(QColor* inte, QColor* exte);
    Motif(AvailableColors col_int, AvailableColors col_ext);
    Motif(int id_motif);

    QColor* get_color_int() const;
    QColor* get_color_ext() const;

    void set_color_int(QColor* col);
    void set_color_ext(QColor* col);

//definition de 2 couleurs propres a un motif en fonction de son id
    void set_colors(AvailableColors exte, AvailableColors inte);

    QColor* getQColorFromInt(int color) const;

    /**
      * A partir d'un id correspondant aux couleurs d'un motif,
      * créé et retourne le motif (unique) associé
      * @author Antoine
      */
    Motif get_color(int id) const;

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Motif& m)
    { return m.print(out); }
};

#endif // MOTIF_H
