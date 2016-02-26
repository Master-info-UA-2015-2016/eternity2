#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include <map>

#include "coordinates.h"
#include "piece_model.h"

class Board : public std::vector< std::vector<Piece*>* >
{
private:
//    Configuration disposition;
    Coordinates size;

public:
    Board(Coordinates& _size);

    int height()    const { return size.row; }
    int width()     const { return size.col; }

    std::map<Piece*, Coordinates>* getPlaced();
    std::list<Coordinates>* getUnplaced();
    void clearPlaced();
    void clearUnplaced();
};

#endif // BOARD_H
