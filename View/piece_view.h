#ifndef PIECEVIEW_H
#define PIECEVIEW_H

#include <QWidget>

#include "../Model/piece_model.h"
#include "../Model/coordinates.h"
#include "cell.h"

class PieceView : public Cell
{

private:
    Coordinates pos;
    const Piece& piece;

public:
    PieceView(int col, int row, const Piece& p);

    /**
     * Décrit la cellule comme étant occupée par une pièce
     * @return vrai, on redéfinit la méthode virtuelle de Cell
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
