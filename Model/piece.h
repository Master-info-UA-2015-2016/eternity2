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
     * Definition des motifs d'une piece
     * @param south_motif
     * @param west_motif
     * @param north_motif
     * @param east_motif
     * @author GARNIER Antoine
     */
    void set_motifs(PairColors south_motif, PairColors west_motif, PairColors north_motif, PairColors east_motif){
        motif[South]= south_motif;
        motif[West]= west_motif;
        motif[North]= north_motif;
        motif[East]= east_motif;
    }

    /**
     * La pièce doit-elle être placée dans un coin ?
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool isCorner() const;

    /**
     * La pièce doit-elle être placée sur un rebord ?
     * @return
     * @author FOURMOND Jérôme
     */
    bool isBorder() const;

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     * @author FOURMOND Jérôme
     */
    std::ostream& print(std::ostream& out) const;

    /**
     * Affichage d'une piece
     * @param out
     * @param r
     * @return
     * @author FOURMOND Jérôme
     */
    friend std::ostream& operator<<(std::ostream& out, const Piece& r)
    { return r.print(out); }

    /**
     * Applique une rotation a une piece et retourne les motifs de cette piece
     * @param nbRotation
     * @return
     * @author DAVID Florian
     */
    PairColors* rotate(int nbRotation) const;
};

#endif // PIECE_MODEL_H
