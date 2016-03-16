#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include <map>
#include <assert.h>

#include "coordinates.h"
#include "configuration.h"
#include "piece.h"

class Board
{
private:
    Configuration* disposition;

public:
    /**
     * Constructeur d'un plateau
     * @param config Configuration initialisant le plateau
     * @author Florian David
     */
    Board(Configuration* config = NULL);

    virtual ~Board();

    /*** Getters & setters  ***/
    int get_height()    const { assert(disposition != NULL); return disposition->get_height(); }
    int get_width()     const { assert(disposition != NULL); return disposition->get_width(); }
    const Configuration& getConfig() const { return *disposition; }

    /**
     * Essaie de tourner une pièce afin d'obtenir des appareillages
     * @param id identifiant de la pièce
     * @return le nombre d'erreurs de motifs sur cette pièce après rotation ou non
     * @author Florian
     * @SEE voir si on l'utilise
     */
    int betterRotatePiece(int piece_id);
    /**
     * Essaie de tourner une pièce afin d'obtenir des appareillages
     * @param x abscisse de la pièce
     * @param y ordonnée de la pièce
     * @return le nombre d'erreurs de motifs sur cette pièce après rotation ou non
     * @author Florian David
     */
    int betterRotatePiece(int x, int y);

    /**
     * @brief get_random_piece_coord - useful for selecting a random piece of the board
     * @return Des coordonnees x et y aleatoires pour une piece du plateau
     * @author GARNIER Antoine
     */
    const std::pair<int, int> get_random_piece_coord() const;

//    /**
//     * @brief permutation_current_piece_random_piece
//     * @param current_piece_x
//     * @param current_piece_y
//     * @author GARNIER Antoine
//     * TODO COMMENT @AsCris A QUOI SERT LA FONCTIONS ????
//     */
//    void permutation_current_piece_random_piece(int current_piece_x, int current_piece_y);

    //void Board::permutation_current_piece_random_piece(int current_piece_x, int current_piece_y){
    //    std::pair<int, int> random_piece= get_random_piece_coord();
    //    int random_piece_x= random_piece.first;
    //    int random_piece_y= random_piece.second;

    //    if((random_piece.first != current_piece_x) || (random_piece.second != current_piece_y)){
    //        permutation_two_pieces(current_piece_x, current_piece_y, random_piece_x, random_piece_y);
    //    }
    //    #if DEBUG_RANDOM_PERMUTATION
    //    cout << "Erreur dans tentative de permutation : current_piece == random_piece !" << endl;
    //    #endif
    //}

    /**
     * @brief random_rotation_random_piece
     * @author GARNIER Antoine
     * TODO COMMENT faut pas déconner ... @Ascris
     */
    void random_rotation_random_piece();
};

#endif // BOARD_H
