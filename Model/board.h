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
    Board(Configuration* config);

    int height()    const { assert(disposition != NULL); return disposition->height(); }
    int width()     const { assert(disposition != NULL); return disposition->width(); }
    const Configuration& getConfig() const { return *disposition; }

    std::vector<std::pair<Piece*, Coordinates>* >* getPlaced();
    std::list<Coordinates>* getUnplaced();
    void clearPlaced();
    void clearUnplaced();
};

#endif // BOARD_H
