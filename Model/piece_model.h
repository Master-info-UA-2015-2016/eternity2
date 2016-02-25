#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H

#include <iostream>

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
    int color[MAX_CARD];

public:
    /**
     * Constructeur
     */
    Piece(int _id, int tab[]);

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Piece& r)
    { return r.print(out); }

    /**
     * Rotation de la pièce.
     * On décalera simplement la valeur de chaque case d'un rang vers la
     * droite. Ainsi, on effectuera systématiquement une rotation horaire.
     *
     */
    void rotate();
};

#endif // PIECE_MODEL_H
