#include "board.h"

Board::Board(Configuration *config) :
    disposition(config)
{

}

Board::~Board()
{
    delete disposition;
}
