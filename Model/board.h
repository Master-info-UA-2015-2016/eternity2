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
     * Retourne les coordonnees x et y d'une piece aleatoire du plateau
     * @return Des coordonnees x et y aleatoires pour une piece du plateau
     * @author GARNIER Antoine
     */
    const std::pair<int, int> get_random_piece_coord() const;

};

#endif // BOARD_H
