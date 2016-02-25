#ifndef CELL_H
#define CELL_H

class Cell
{

public:
    Cell();

    virtual bool has_piece() const { return false; }

};

#endif // CELL_H
