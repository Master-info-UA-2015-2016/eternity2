#ifndef MOTIF_VIEW_H
#define MOTIF_VIEW_H

#include <iostream>
#include <QColor> 

//couleurs utilisables
enum AvailableColors{White = -1, Black, Gray, Brown, Orange, Pink, Red, Yellow, LightGreen, DarkGreen, LightBlue, DarkBlue, Purple};

class Motif
{
private:
    int id;
    QColor* color_int;
    QColor* color_ext;

public:
    /**
     *  Constructeur d'un motif à partir de 2 couleurs
     * @param inte
     * @param exte
     * @author Antoine
     */
    Motif(QColor* inte, QColor* exte);
    /**
     *  Constructeur d'un motif à partir de 2 indices de couleurs
     * @param col_int
     * @param col_exte
     * @author Antoine
     */
    Motif(AvailableColors col_int, AvailableColors col_ext);
    /**
     *  Constructeur d'un motif à partir de 2 couleurs
     * @param col_int
     * @param col_exte
     * @author Antoine
     */
    Motif(int id_motif);

    /**
     * Récupère la couleur intérieure
     * @return Le QColor de la couleur intérieure
     * @author Antoine
     */
    QColor* get_color_int() const;
    /**
     * Récupère la couleur extérieure
     * @return Le QColor de la couleur extérieure
     * @author Antoine
     */
    QColor* get_color_ext() const;

    /**
     * Setter couleur intérieure
     * @param Nouvelle couleure intérieure
     * @author Antoine
     */
    void set_color_int(QColor* color);
    /**
     * @brief set_color_ext
     * @param color Nouvelle couleure extérieure
     * @author Antoine
     */
    void set_color_ext(QColor* color);
    /**
     * Definition des 2 couleurs
     * @param exte Identifiant de la couleur extérieure
     * @param inte Identifiant de la couleur intérieure
     * @author Antoine
     */
    void set_colors(AvailableColors exte, AvailableColors inte);

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
     * @author Antoine
     */
    std::ostream& print(std::ostream& out) const;

    /**
     * Redéfinition du flux de sortie
     * @param out
     * @param m
     * @return
     * @author Antoine
     */
    friend std::ostream& operator<<(std::ostream& out, const Motif& m)
    { return m.print(out); }


    /**
     * Retourne la QColor correspond à l'id
     * @param color id de la couleur
     * @return Qcolor correspondante
     * @author Antoine
     */
    static QColor* getQColorFromInt(int color);
};

#endif // MOTIF_VIEW_H
