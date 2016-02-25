#include "piece_view.h"

PieceView::PieceView(int col, int row, const Piece& p) :
        Cell(), pos(col, row), piece(p)
{

}
