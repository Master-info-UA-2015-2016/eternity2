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

int Board::permutation_two_pieces(int piece1_x, int piece1_y, int piece2_x, int piece2_y){
    std::pair<int, int> tmp= disposition->getPositions()[piece1_x + piece1_y * disposition->get_width()];
    disposition->setPiece(piece1_x, piece1_y, disposition->getPositions()[piece2_x + piece2_y * disposition->get_width()]);
    disposition->setPiece(piece2_x, piece2_y, tmp);
return 0;
}

const std::pair<int, int> Board::get_random_piece_coord() const {
    int piece_x= rand() % 4;
    int piece_y= rand() % 4;
    std::pair<int, int> piece_coord= std::make_pair(piece_x, piece_y);
    return piece_coord;
}

void Board::permutation_current_piece_random_piece(int current_piece_x, int current_piece_y){
    std::pair<int, int> random_piece= get_random_piece_coord();
    int random_piece_x= random_piece.first;
    int random_piece_y= random_piece.second;

    if((random_piece.first != current_piece_x) || (random_piece.second != current_piece_y)){
        permutation_two_pieces(current_piece_x, current_piece_y, random_piece_x, random_piece_y);
    }
    #if DEBUG_RANDOM_PERMUTATION
    cout << "Erreur dans tentative de permutation : current_piece == random_piece !" << endl;
    #endif
}

void Board::random_rotation_random_piece(){
    int random_rotation= rand() % 3 + 1; //rotation de 1 à 3 "crans"
    const std::pair<int, int> piece_coord= get_random_piece_coord();
    int random_piece_coord_x= piece_coord.first;
    int random_piece_coord_y= piece_coord.second;

    //recuperation piece + modifs coord avec rotation
    const Piece& random_piece= disposition->getPiece(random_piece_coord_x, random_piece_coord_y);
    random_piece.rotate(random_rotation);
}
