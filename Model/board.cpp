#include "board.h"

Board::Board(Configuration *config) :
    disposition(config)
{

}

Board::~Board()
{
    delete disposition;
}

//int Board::betterRotatePiece(int piece_id)
//{
//    const Piece& piece= disposition->getPiece(piece_id);
//    const PairColors* piece_motifs= piece.get_motif();

//    // Test des diverses rotation possibles
//    for (int i= 0; i < 4; ++i) {
//        // Test du nombre d'appareillages avec la nouvelle rotation
//         disposition->countNbErrors();
//    }
//}

//int Board::betterRotatePiece(int x, int y)
//{
//    betterRotatePiece(x + y * disposition->get_width() +1); // Les id commencent à 1, alors que le plateau commence à (0,0), donc +1
//}

const std::pair<int, int> Board::get_random_piece_coord() const {
    int piece_x= rand() % 4;
    int piece_y= rand() % 4;
    std::pair<int, int> piece_coord= std::make_pair(piece_x, piece_y);
    return piece_coord;
}

//void Board::random_rotation_random_piece(){
//    int random_rotation= rand() % 3 + 1; //rotation de 1 à 3 "crans"
//    const std::pair<int, int> piece_coord= get_random_piece_coord();
//    int random_piece_coord_x= piece_coord.first;
//    int random_piece_coord_y= piece_coord.second;

//    //recuperation piece + modifs coord avec rotation
//    const Piece& random_piece= disposition->getPiece(random_piece_coord_x, random_piece_coord_y);
//    random_piece.rotate(random_rotation);
//}
