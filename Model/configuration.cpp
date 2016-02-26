
#include "configuration.h"

using namespace std;

<<<<<<< HEAD
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
=======
Configuration::Configuration(){

}

int* Configuration::rotate(int* motif,int nbRotation){
    int* tmp ;

    for(int i = 0; i < nbRotation; ++i){
        tmp[0] = motif[MAX_CARD-1];

        for(int i=1; i<MAX_CARD;++i){
            tmp[i] = motif[i-1];
        }
    }
    // On recopie le résultat dans la variable motif
    for(int j= 0; j < MAX_CARD; ++j){
        motif[j] = tmp[j];
    }

    return tmp;
}

ostream& Configuration::print(ostream& out){
    int* sone;

    for(int i=1; i <= nbCols; ++i){
        for(int j = 1; j <= nbRows; ++j){

            out << "Case " << i << "," << j << " : " <<
                   (vectPosition.at(i+j-2)).first << " .SONE : ";

            if((vectPosition.at(i+j-2)).second != 0 ){

                sone = rotate(this->vectPieces->at(i+j-2).get_motif(), vectPosition.at(i+j-2).second );
            }

            out << "toto" << endl;
        }
    }
    return out;
>>>>>>> load_config
}
