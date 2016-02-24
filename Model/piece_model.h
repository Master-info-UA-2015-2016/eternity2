#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H
/*
 * Classe représentant une pièce. haque pièce dispose d'un identifiant et d'un tableau
 * de 4 entiers représentant les différentes couleurs de la pièce.
 * Par convention, l'ensemble est ordonné de la manière suivante :
 *  Sud - Ouest - Nord - Est
 *
 * @author Ugo
 */

#define MAX_CARD 4

class piece_model
{
private:
    int id;
    int color[MAX_CARD];


public:
    /*
     * Constructeur
     */
    piece_model(int _id, int tab[]);

    /*
     * Rotation de la pièce.
     * On décalera simplement la valeur de chaque case d'un rang vers la
     * droite. Ainsi, on effectuera systématiquement une rotation horaire.
     *
     */
    void rotate();
};

#endif // PIECE_MODEL_H
