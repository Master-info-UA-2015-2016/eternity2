
#include "configuration.h"

using namespace std;

Configuration::Configuration() {}

vector<pair<int, int> >& Configuration::getVectPosition() {
    return vectPosition;
}

pair<int, int> Configuration::getPiece(int x, int y) {
    pair<int, int> position = vectPosition.at(x*nbRows + y*nbCols - (x+y));
    return position;
}

int Configuration::getPosition(Piece p) {
    bool found = false;
    int ind = 0;
    while(!found) {
        if(vectPosition[ind].first == p.get_id())
            found = true;
        else ind++;
    }
    return ind;
}

void Configuration::addPosition(pair<int, int> position) {
    vectPosition.push_back(position);
}

bool Configuration::isValid() {
    return (unsigned)(nbRows * nbCols) == vectPosition.size();
}
