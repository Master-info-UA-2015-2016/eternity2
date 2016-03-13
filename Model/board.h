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
     */
    int betterRotatePiece(int piece_id);
    /**
     * Essaie de tourner une pièce afin d'obtenir des appareillages
     * @param x abscisse de la pièce
     * @param y ordonnée de la pièce
     * @return le nombre d'erreurs de motifs sur cette pièce après rotation ou non
     */
    int betterRotatePiece(int x, int y);

    /**
     * @brief permutation_two_pieces
     * @param indice_piece_1
     * @param indice_piece_2
     * @author GARNIER Antoine
     */
    int permutation_two_pieces(int piece1_x, int piece1_y, int piece2_x, int piece2_y);

    /**
     * @brief get_random_piece_coord - useful for selecting a random piece of the board
     * @return Des coordonnees x et y aleatoires pour une piece du plateau
     * @author GARNIER Antoine
     */
    const std::pair<int, int> get_random_piece_coord() const;

    /**
     * @brief permutation_current_piece_random_piece
     * @param current_piece_x
     * @param current_piece_y
     * @author GARNIER Antoine
     */
    void permutation_current_piece_random_piece(int current_piece_x, int current_piece_y);
};

#endif // BOARD_H
