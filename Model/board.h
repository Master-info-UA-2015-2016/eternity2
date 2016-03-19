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
};

#endif // BOARD_H
