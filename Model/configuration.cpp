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

const pair<int, int>& Configuration::getPair(int x, int y) const {
    const pair<int, int>& position = positions[x + y * instance->width()];
    return position;
}

const Piece & Configuration::getPiece(int x, int y) const {
    const Piece & piece = instance->get_vectPieces()->at(getPair(x, y).first-1);
    return piece;
}

int * Configuration::getRotatedMotif(int x, int y) const {
    pair<int, int> position = getPair(x, y);
    Piece P = getPiece(x, y);
    return P.rotate(position.second);
}

int Configuration::getPosition(const Piece& p) const {
    bool found = false;
    int ind = 0;
    while(!found) {
        if(positions[ind].first == p.get_id())
            found = true;
        else ind++;
    }
    return ind;
}

int Configuration::getPosition(const int id) const {
    int ind = -1;
    for(unsigned int i=0 ; i<positions.size() ; ++i) {
        if(positions[i].first == id)
            ind = i;
    }
    return ind;
}

pair<int, int> Configuration::getCase(int id) const {
    int pos = getPosition(id);
    int processed_case = 0;
    for(int j=0 ; j<height() ; j++) {
        for(int i=0 ; i<width() ; i++) {
            if(processed_case == pos) return make_pair(i, j);
            processed_case++;
        }
    }
    return make_pair(-1, -1);
}

ostream& Configuration::print(ostream& out){
    for(int i=0 ; i<instance->width() ; ++i) {
        for(int j=0 ; j<instance->height() ; ++j) {
            pair<int, int> p = getPair(i, j);

            out << "Case (" << i << "," << j << ") : \tID = " << p.first << "\tRotation = " << p.second << "\tSONE = ";

            const Piece& piece = getPiece(i, j);

            const int* swne ;
            if(p.second != 0) {
                swne = piece.rotate(p.second );
            } else {
                swne = piece.get_motif();
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

                positions.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(positions.size() != (unsigned)(instance->width() * instance->height()) ){
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

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        Configuration* configuration= new Configuration(instance);
        configuration->randomConfiguration();

        configurations.push_back(configuration);
    }

    return configurations;
}

int Configuration::constraintRowsXtrem() {
    int errors = 0;
    const int * swne;
    // Vérification de la première ligne (Contrainte Ligne Nord)
    for(int i=0 ; i<width() ; i++) {
        const pair<int, int> & pair = getPair(i, 0);
        const Piece & piece = getPiece(i, 0);
        swne = piece.rotate(pair.second);
        if(swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< i << "," << 0 << ")" << piece;
#endif
            errors++;
        }
    }
    // Vérification de la seconde ligne (Contrainte Ligne Sud)
    for(int i=0 ; i<width() ; i++) {
        const pair<int, int> & pair = getPair(i, height()-1);
        const Piece & piece = getPiece(i, height()-1);
        swne = piece.rotate(pair.second);
        if(swne[0] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< i << "," << height()-1 << ")" << piece;
#endif
            errors++;
        }
    }
    return errors;
}

bool Configuration::constraintRowsXtrem(int x, int y) {
    const int * swne;
    if(y != 0 && y != height()-1)
        return true;
    else {
        const pair<int, int> & pair = getPair(x, y);
        const Piece & piece = getPiece(x, y);
        swne = piece.rotate(pair.second);
        if(y == 0)
            return swne[2] == 0 && !(swne[1] == 0 || swne[1] == 0 || swne[3] == 0);
        else if(y == height()-1)
            return swne[0] == 0 && !(swne[1] == 0 || swne[2] == 0 || swne[3] == 0);
        return false;
    }
}

int Configuration::constraintColsXtrem() {
    int errors = 0;
    const int * swne;
    // Vérification de la première colonne (Contrainte Colonne Ouest)
    for(int i=0 ; i<instance->height() ; i++) {
        const pair<int, int> & pair = getPair(0, i);
        const Piece & piece = getPiece(0, i);
        swne = piece.rotate(pair.second);
        if(swne[1] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< 0 << "," << i << ")" << piece;
#endif
            errors++;
        }
    }
    // Vérification de la seconde colonne (Contrainte Colonne Est)
    for(int i=0 ; i<instance->height() ; i++) {
        const pair<int, int> & pair = getPair(instance->width()-1, i);
        const Piece & piece = getPiece(instance->width()-1, i);
        swne = piece.rotate(pair.second);
        if(swne[3] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< instance->width()-1 << "," << i << ")" << piece;
#endif
            errors++;
        }
    }
    return errors;

}

bool Configuration::constraintColsXtrem(int x, int y) {
    const int * swne;
    if(x != 0 && x != width()-1)
        return true;
    else {
        const pair<int, int> & pair = getPair(x, y);
        const Piece & piece = getPiece(x, y);
        swne = piece.rotate(pair.second);
        if(x == 0)
            return swne[1] == 0 && !(swne[0] == 0 || swne[2] == 0 || swne[3] == 0);
        else if(x == width()-1)
            return swne[3] == 0 && !(swne[0] == 0 || swne[1] == 0 || swne[2] == 0);
        return false;
    }
}

int Configuration::constraintEdges() {
    int errors = 0;
    const int * swne;
    pair<int, int> pair;
    // Coin Nord-Ouest
    pair = getPair(0,0);
    Piece piece = getPiece(0,0);
    swne = piece.rotate(pair.second);
    if(swne[1] != 0 || swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< 0 << "," << 0 << ")" << piece;
#endif
        errors++;
    }
    // Coin Nord-Est
    pair = getPair(0,instance->width()-1);
    piece = getPiece(0,instance->width()-1);
    swne = piece.rotate(pair.second);
    if(swne[3] != 0 || swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< 0 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Ouest
    pair = getPair(instance->height()-1,0);
    piece = getPiece(instance->height()-1,0);
    swne = piece.rotate(pair.second);
    if(swne[1] != 0 || swne[0] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << 0 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Est
    pair = getPair(instance->height()-1, instance->width()-1);
    piece = getPiece(instance->height()-1, instance->width()-1);
    swne = piece.rotate(pair.second);
    if(swne[3] != 0 || swne[0] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }

    return errors;
}

bool Configuration::constraintEdges(int x, int y) {
    const pair<int, int> & pair = getPair(x, y);
    const Piece & piece = getPiece(x, y);
    const int * swne = piece.rotate(pair.second);
    if(x == 0 && y == 0)
        return swne[1] == 0 && swne[2] == 0;
    else if(x == 0 && y == height()-1)
        return swne[0] == 0 && swne[1] == 0;
    else if(x == width()-1 && y == 0)
        return swne[2] == 0 && swne[3] == 0;
    else if(x == width()-1 && y == height()-1)
        return swne[0] == 0 && swne[3] == 0;
    return true;
}

int Configuration::getNorthMotifSouthPiece(int current_piece_indice){
    Piece south_piece = instance->getPiece(current_piece_indice + width());
    int rot_south_piece = positions[getPosition(south_piece)].second;

    return south_piece.rotate(rot_south_piece)[2];
}

int Configuration::getWestMotifEastPiece(int current_piece_indice){
    Piece east_piece = instance->getPiece(current_piece_indice +1);
    int rot_east_piece = positions[getPosition(east_piece)].second;

    return east_piece.rotate(rot_east_piece)[1];
}

int Configuration::checkPieces(){
    /**
      Algo :
            Initialiser un vector de bool (vect[i] = 1 si la pièce i a déjà été traité)
            Tant qu'il reste des pièces à vérifier faire
                Prendre une pièce P qui n'est pas dans vect
                Comparer P à ses pièces adjacentes (S et E ayant subit la rotation)
                Ajouter P à vect (indice de la pièce P à 1 dans vect)
            Fin TantQue
    */
    int nb_errors = 0;

    for(int i= 0; i< height()*width()-2; ++i){
        int local_errors = 0;

        pair<int, int> current_piece= positions[i];
        int id_piece = current_piece.first;

        #if DEBUG_POS_ERRORS
            cout << "Piece n° " << i << " ; id_piece = " << id_piece << endl;
        #endif

        int* id_motifs= instance->getPiece(id_piece).rotate(current_piece.second);
        int south_motif = id_motifs[0];
        int east_motif = id_motifs[3];

        //derniere ligne du puzzle - est seulement
        if(i > width()*height() - width()){
            int east_piece_west_motif = getWestMotifEastPiece(i);
            if(east_piece_west_motif != east_motif || east_piece_west_motif == 0){
            #if DEBUG_POS_ERRORS
                cout << "Derniere ligne" << endl;
                cout << "Piece : "<< id_piece << " conflit O-E: " << east_piece_west_motif << " - " << east_motif << endl;
                cout << endl;
            #endif
                ++local_errors;
                ++nb_errors;
            }

        } else
        if(i % width() == width() -1){
            //derniere case d'une ligne - comparaison sud seulement
            int south_piece_north_motif = getNorthMotifSouthPiece(i);

            if(south_piece_north_motif != south_motif || south_piece_north_motif == 0){
                #if DEBUG_POS_ERRORS
                    cout << "Derniere colonne" << endl;
                    cout << "Piece : "<< id_piece << " conflit N-S: " << south_piece_north_motif << " - " << south_motif << endl;
                    cout << endl;
                #endif
                ++local_errors;
                ++nb_errors;
            }

        } else {
            //comparaison sud et est
            int east_piece_west_motif = getWestMotifEastPiece(i);
            int south_piece_north_motif = getNorthMotifSouthPiece(i);

            if(east_piece_west_motif != east_motif || east_piece_west_motif == 0){
                #if DEBUG_POS_ERRORS
                    cout << "Comp EST" << endl;
                    cout << "Piece : "<< id_piece << " conflit O-E: " << east_piece_west_motif << " - " << east_motif << endl;
                #endif
                ++local_errors;
                ++nb_errors;
            }
            if(south_piece_north_motif != south_motif || south_piece_north_motif == 0){
                #if DEBUG_POS_ERRORS
                    cout << "Comp Sud" << endl;
                    cout << "Piece : "<< id_piece << "conflit N-S: " << south_piece_north_motif << " - " << south_motif << endl;
                    cout << endl;
                #endif
                ++local_errors;
                ++nb_errors;
            }
        }

        #if DEBUG_POS_ERROR
            cout << "iteration " << i << " erreurs -> " << local_errors << endl;
        #endif

    }//fin parcours pieces

    return nb_errors;
}

int Configuration::constraintPieces() {
    vector<int> misplaces(height()*width());

    for(int j=0 ; j<height() ; j++) {
        for(int i=0 ; i<width() ; i++) {
            if((j == 0 && i == 0)||(j== 0 && i == width()-1)||(j==height()-1 && i==0)||(j==height()-1 && i==width()-1)) {
                 if(!constraintEdges(i,j)) misplaces[i + j*width()] = getPair(i, j).first;
             } else if(j == 0 || j == height()-1) {
                 if(!constraintRowsXtrem(i,j)) misplaces[i + j*width()] = getPair(i, j).first;
             } else if(i == 0 || i == width()-1) {
                 if(!constraintColsXtrem(i,j)) misplaces[i + j*width()] = getPair(i, j).first;
             } else cout << "(" << i << "," << j << ") - TODO Traitement manquant (non ligne, non colonne, non angle)" << endl;
         }
    }

    cout << "Pièces mal placées (ID) : " << endl;
    for(auto i : misplaces) {
        if(i != 0 ) {
            pair<int, int> pos = getCase(i);
            cout << "\tPièce à la position : (" << pos.first << "," << pos.second << ")" << endl;
        }
    }
    return 0;
}
