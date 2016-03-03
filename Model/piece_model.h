#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H

#include <iostream>
#include <algorithm>

enum PairColors{Black_Black, Gray_Orange, LightGreen_Pink, Yellow_Red, Purple_Gray, LightGreen_Orange,
                    LightBlue_Purple, Orange_LightBlue, DarkBlue_Orange, Purple_Orange, Gray_DarkGreen, Pink_DarkGreen,
                    Red_DarkGreen, Yellow_DarkGreen, LightBlue_DarkGreen, DarkBlue_DarkGreen, Purple_DarkGreen,
                    Gray_Brown, Pink_Brown, Red_Brown, Yellow_Brown, Red_LightGreen, LightBlue_Brown, Purple_Brown
               };

/**
 * Classe représentant une pièce. haque pièce dispose d'un identifiant et d'un tableau
 * de 4 entiers représentant les différentes couleurs de la pièce.
 * Par convention, l'ensemble est ordonné de la manière suivante :
 *  Sud - Ouest - Nord - Est
 *
 * @author Ugo
 * @author Florian
 */

#define MAX_CARD 4

class Piece
{
private:
    int id;
    PairColors motif[MAX_CARD];

public:
    /**
     * Constructeur
     */
    Piece(int _id, PairColors tab[]);

    /**
     * Getters
     *
     */
    int get_id() const  { return id; }
    const PairColors* get_motif() const   { return motif; }

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, Piece& r)
    { return r.print(out); }


    friend std::ostream& operator<<(std::ostream& out, const Piece& r)
    { return r.print(out); }

    PairColors* rotate(int nbRotation) const;
};

#endif // PIECE_MODEL_H
