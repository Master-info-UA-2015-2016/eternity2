#include "configuration.h"

using namespace std;

Configuration::Configuration() :
    instance()
{

}

Configuration::Configuration(const Instance* _instance) :
    instance(_instance)
{}

Configuration::Configuration(const string& fileName)
{
    Instance* inst= new Instance();

    if (!inst->tryLoadFile(fileName)){
        cerr << "Impossible de charger le fichier " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    else { instance = inst; }
}

vector<pair<int, int> >& Configuration::getVectPosition() {
    return vectPosition;
}

const pair<int, int>& Configuration::getPair(int x, int y) const {
    const pair<int, int>& position = vectPosition[x + y * instance->width()];
    return position;
}

const Piece & Configuration::getPiece(int x, int y) const {
    const Piece & piece = instance->get_vectPieces()->at(getPair(x, y).first-1);
    return piece;
}

int Configuration::getPosition(const Piece& p) const {
    bool found = false;
    int ind = 0;
    while(!found) {
        if(vectPosition[ind].first == p.get_id())
            found = true;
        else ind++;
    }
    return ind;
}

ostream& Configuration::print(ostream& out){
    for(int i=0 ; i<instance->width() ; ++i) {
        for(int j=0 ; j<instance->height() ; ++j) {
            pair<int, int> p = getPair(i, j);

            out << "Case (" << i << "," << j << ") : \tID = " << p.first << "\tRotation = " << p.second << "\tSONE = ";

            const Piece& P = getPiece(i, j);

            const int* swne ;
            if(p.second != 0) {
                swne = rotate(P.get_motif(), p.second );
            } else {
                swne = P.get_motif();
            }

            for(int l=0; l<MAX_CARD; ++l){
                if(l==0)
                    out << "[" << swne[l] << ",";
                else if(l==MAX_CARD-1)
                    out << swne[l] << "]";
                else
                    out << swne[l] << ",";
            }
            out << endl;
        }
    }

    for(int i=0 ; i<instance->width(); i++) {
        for(int j=0 ; j<instance->height() ; j++) {
            pair<int, int> p = getPair(j, i);
            cout << "\t" << p.first << " ";
        }
        cout << endl;
    }

    return out;
}

int* Configuration::rotate(const int* motif,int nbRotation){
    int* tmp = new int;
    copy(motif, motif+4, tmp);

    for(int i=0 ; i<nbRotation ; i++)
        std::rotate(tmp, tmp+3 , tmp+4);

    return tmp;
}

bool Configuration::tryLoadFile(const string &fileName){
    if( instance->width() * instance->height() == 0){
        cerr << "Aucune instance n'est chargée" << endl;
        return false;
    }else{
        ifstream f(fileName.c_str());

        if(!f){
            cerr << "Erreur pendant l'ouverture du fichier" << endl;
            return false;
        } else {

            string line;

            while(getline(f,line)){

                vector<string>& tokens = explode(line);

                vectPosition.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(vectPosition.size() != (unsigned)(instance->width() * instance->height()) ){
                cerr << "Fichier de configuration incomplet" << endl;
                return false;
            } else {
                return true;
            }
        }
    }
}

void Configuration::randomConfiguration() {
    int i_rot;
    srand(time(NULL));
    vector<int> pieces_id;

    // Travail uniquement sur l'id des pieces
    for(const Piece & p : *(instance->get_vectPieces()) ) {
        pieces_id.push_back(p.get_id());
    }
    // Mélange aléatoire
    random_shuffle(pieces_id.begin(), pieces_id.end());

    while(!pieces_id.empty()) {
        // Récupération de la pièce (id)
        int p = pieces_id.back();
        pieces_id.pop_back();
        // Choix aléatoire de la rotation
        i_rot = rand() % 4;
        pair<int, int> piece;
            piece.first = p;
            piece.second = i_rot;
        // Ajout de la pair
        placePiece(piece);
    }
}

vector<Configuration*>&  Configuration::generateRandomConfigurations(const Instance * instance, int limit) {
    vector<Configuration*>& configurations= *(new vector<Configuration*>);

    srand(time(NULL));

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        Configuration* configuration= new Configuration(instance);
        configuration->randomConfiguration();

        configurations.push_back(configuration);
    }

    return configurations;
}

bool Configuration::constraintRows() {
    const int * swne;
    // Vérification de la première ligne (Contrainte Ligne Nord)
    for(int i=0 ; i<instance->width() ; i++) {
        const pair<int, int> & pair = getPair(i, 0);
        const Piece & P = getPiece(i, 0);
        swne = rotate(P.get_motif(), pair.second);
        if(swne[2] != 0) {
            cout << "\t(*)" << P;
            return false;
        }
    }
    // Vérification de la seconde ligne (Contrainte Ligne Sud)
    for(int i=0 ; i<instance->width() ; i++) {
        const pair<int, int> & pair = getPair(i, instance->height()-1);
        const Piece & P = getPiece(i, instance->height()-1);
        swne = rotate(P.get_motif(), pair.second);
        if(swne[0] != 0) {
            cout << "\t(*)" << P;
            return false;
        }
    }
    return true;
}

bool Configuration::constraintCols() {
    const int * swne;
    // Vérification de la première colonne (Contrainte Colonne Ouest)
    for(int i=0 ; i<instance->height() ; i++) {
        const pair<int, int> & pair = getPair(0, i);
        const Piece & P = getPiece(0, i);
        swne = rotate(P.get_motif(), pair.second);
        if(swne[1] != 0) {
            cout << "\t(*)" << P;
            return false;
        }
    }
    // Vérification de la seconde colonne (Contrainte Colonne Est)
    for(int i=0 ; i<instance->height() ; i++) {
        const pair<int, int> & pair = getPair(instance->width()-1, i);
        const Piece & P = getPiece(instance->width()-1, i);
        swne = rotate(P.get_motif(), pair.second);
        if(swne[3] != 0) {
            cout << "\t(*)" << P;
            return false;
        }
    }
    return true;

}

bool Configuration::constraintEdges() {
    const int * swne;
    pair<int, int> pair;
    // Coin Nord-Ouest
    pair = getPair(0,0);
    Piece P = getPiece(0,0);
    swne = rotate(P.get_motif(), pair.second);
    if(swne[1] != 0 || swne[2] != 0) {
        cout << "\t(*)" << P;
        return false;
    }
    // Coin Nord-Est
    pair = getPair(0,instance->width()-1);
    P = getPiece(0,instance->width()-1);
    swne = rotate(P.get_motif(), pair.second);
    if(swne[3] != 0 || swne[2] != 0) {
        cout << "\t(*)" << P;
        return false;
    }
    // Coin Sud-Ouest
    pair = getPair(instance->height()-1,0);
    P = getPiece(instance->height()-1,0);
    swne = rotate(P.get_motif(), pair.second);
    if(swne[1] != 0 || swne[0] != 0) {
        cout << "\t(*)" << P;
        return false;
    }
    // Coin Sud-Est
    pair = getPair(instance->height()-1, instance->height()-1);
    P = getPiece(instance->height()-1, instance->height()-1);
    swne = rotate(P.get_motif(), pair.second);
    if(swne[3] != 0 || swne[0] != 0) {
        cout << "\t(*)" << P;
        return false;
    }

    return true;
}

int Configuration::checkPieces(){
    /**
      Algo :
            Initialiser un vector de bool (vect[i] = 1 si la pièce i a déjà été traité)
            Tant qu'il reste des pièces à vérifier faire
                Prendre une pièce P qui n'est pas dans vect
                Comparer P à ses pièces adjacentes (S, W, N, E)
                Ajouter P à vect (indice de la pièce P à 1 dans vect)
            Fin TantQue
    */
    int res = 0;

    return res;
}
