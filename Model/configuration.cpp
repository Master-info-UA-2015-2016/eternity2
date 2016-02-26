#include "configuration.h"

using namespace std;

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
}
