#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include <map>

#include "coordinates.h"
#include "configuration.h"
#include "piece_model.h"

class Board : public std::vector< Piece* >
{
private:
    Configuration* disposition;

public:
    Board(Configuration* config);

    int height()    const { return disposition->height(); }
    int width()     const { return disposition->width(); }
    const Configuration& getConfig() const { return *disposition; }

    std::vector<std::pair<Piece*, Coordinates>* >* getPlaced();
    std::list<Coordinates>* getUnplaced();
    void clearPlaced();
    void clearUnplaced();
};

#endif // BOARD_H
