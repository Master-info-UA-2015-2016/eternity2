#ifndef PIECEVIEW_H
#define PIECEVIEW_H

#include <QWidget>

#include "../Model/piece.h"
#include "../Model/coordinates.h"
class PieceView
{

private:
    Coordinates pos;
    const Piece& piece;

public:
    /**
     * Constructeur de pièce
     * @param col
     * @param row
     * @param p
     * @author Florian
     */
    PieceView(int col, int row, const Piece& p);

    /**
     * Décrit la cellule comme étant occupée par une pièce
     * @return vrai, on redéfinit la méthode virtuelle de Cell
     * @author Florian
     */
    bool has_piece() const { return true; }

    /**
     * @brief getPos
     * @return La position (coordonnée) de la pièce dans le plateau
     * @author Florian
     */
    const Coordinates& getPos()	const	{ return pos; }
};

#endif // PIECEVIEW_H
