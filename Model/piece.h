#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H

#include <iostream>
#include <algorithm>

#include "motif.h"

enum Cardinal{ South = 0, West = 1, North= 2, East= 3 };

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
     * La pièce doit-elle être placée dans un coin ?
     * @return boolean
     */
    bool isEdge();

    /**
     * La pièce doit-elle être placée sur un rebord ?
     * @return
     */
    bool isBorder();

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
