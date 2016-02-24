#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H
/*
 * Classe représentant une pièce. haque pièce dispose d'un identifiant et d'un tableau
 * de 4 entiers représentant les différentes couleurs de la pièce.
 * Par convention, l'ensemble est ordonné de la manière suivante :
 *  Sud - Ouest - Nord - Est
 *
 * @author Ugo
 * @author Florian
 */

#define MAX_CARD 4

#include "coordinates.h"
#include "cell.h"

class Piece : public Cell
{
private:
    int id;
    int color[MAX_CARD];
    Coordinates pos;

public:
    /*
     * Constructeur
     */
    Piece(int col, int row, int _id, int tab[]);

    bool has_piece() const { return true; }
    /**
     * @brief getPos
     * @return position de la pièce dans le plateau
     * @author Florian
     */
    const Coordinates& getPos()	const	{ return pos; }

    /*
     * Rotation de la pièce.
     * On décalera simplement la valeur de chaque case d'un rang vers la
     * droite. Ainsi, on effectuera systématiquement une rotation horaire.
     *
     */
    void rotate();
};

#endif // PIECE_MODEL_H
