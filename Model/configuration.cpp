#include "configuration.h"

using namespace std;


Configuration::Configuration() {}

Configuration::Configuration(const string& fileName) {
    Instance::tryLoadFile(fileName);
}


/**
 * Génération de configurations aléatoires à partir de l'instance
 * @param instance : Instance en question
 * @param limit : nombre de configuration-s généré-es
 * @return Configuration -s généré-es
 * @author FOURMOND Jérôme
 */
vector<Configuration*>&  Configuration::generateRandomConfigurations(Instance instance, int limit) {
    vector<Configuration*>& configurations= *(new vector<Configuration*>);

    srand(time(NULL));

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        vector<Piece>* remaining_pieces = instance.get_vectPieces();
        random_shuffle(remaining_pieces->begin(), remaining_pieces->end());
        int i_rot;
        Configuration* configuration = new Configuration();
        while(!remaining_pieces->empty()) {
            Piece p = remaining_pieces->back();
            remaining_pieces->pop_back();
            // Choix aléatoire de la rotation
            i_rot = rand() % 4;
            // Création de la pair
            pair<int, int> position;
                position.first = p.get_id();
                position.second = i_rot;
            // Ajout de la pair
            configuration->addPosition(position);
        }
        cout << (*configuration).nbCols << endl;
        configurations.push_back(configuration);
    }

    return configurations;
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
    int* swne; // ???

    for(int i=1; i <= nbCols; ++i){
        for(int j = 1; j <= nbRows; ++j){

            out << "Case " << i << "," << j << " : " <<
                   (vectPosition.at(i+j-2)).first << " .SONE : ";

            if((vectPosition.at(i+j-2)).second != 0 ){

                swne = rotate(this->vectPieces->at(i+j-2).get_motif(), vectPosition.at(i+j-2).second );
            }

            out << "toto" << endl;
        }
    }
    return out;

}
