#include "board.h"

Board::Board(Configuration *config) :
    disposition(config)
{

}

Board::~Board()
{
    delete disposition;
}


int Board::betterRotatePiece(int piece_id)
{
    const Piece& piece= disposition->getPiece(piece_id);
    const PairColors* piece_motifs= piece.get_motif();

    // Test des diverses rotation possibles
    for (int i= 0; i < 4; ++i) {
        // Test du nombre d'appareillages avec la nouvelle rotation
         disposition->countNbErrors();
    }
}

int Board::betterRotatePiece(int x, int y)
{
    betterRotatePiece(x + y * disposition->get_width() +1); // Les id commencent à 1, alors que le plateau commence à (0,0), donc +1
}
