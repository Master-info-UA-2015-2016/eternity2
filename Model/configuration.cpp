
#include "configuration.h"

using namespace std;

Configuration::Configuration(const string &fileNameInstance) {
    Instance::tryLoadFile(fileNameInstance);
}

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

int* Configuration::rotate(int* motif,int nbRotation){
    int* tmp = NULL;

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

                sone = rotate(vectPieces->at(i+j-2).get_motif(), vectPosition.at(i+j-2).second );
            }

            for(int l=0; l<MAX_CARD; ++l){
                out << sone[l] << " ; ";
            }
            out << endl;
        }
    }
    return out;

}

bool Configuration::tryLoadFile(const string &fileName){

    if( (nbCols*nbRows) == 0){
        cerr << "Aucune instance n'est chargée" << endl;
        return false;
    }else{
        ifstream f(fileName.c_str());

        if(!f){
            cerr << "Erreur pendant l'ouverture du fichier" << endl;
            return false;
        }else{

            string line;

            while(getline(f,line)){

                vector<string>& tokens = explode(line);

                vectPosition.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(vectPosition.size() != (unsigned)(nbRows*nbCols) ){
                cerr << "Fichier de configuration incomplet" << endl;
                return false;
            }

        }

    }

    return true;
}
