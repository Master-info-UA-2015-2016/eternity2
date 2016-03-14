#include "configuration.h"

using namespace std;


vector<pair<int, int>> Configuration::getAdjacent(int x, int y) const {
    vector<pair<int, int> > swne(4);

    pair<int, int> pos;
    // Récupération Sud
    try {
        pos = getPair(x, y+1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
        pos = make_pair(-1,-1);
    }
    swne[0] = pos;
    // Récupération Est
    try {
        pos = getPair(x-1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Est" << endl;
        pos = make_pair(-1,-1);
    }
    swne[1] = pos;
    // Récupération Nord
    try {
        pos = getPair(x, y-1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Nord" << endl;
        pos = make_pair(-1,-1);
    }
    swne[North] = pos;
    // Récupération Ouest
    try {
        pos = getPair(x+1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
        pos = make_pair(-1,-1);
    }
    swne[3] = pos;

    return swne;
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

int Configuration::constraintRowsXtrem() const {
    int errors = 0;
    const PairColors* swne;
    // Vérification de la première ligne (Contrainte Ligne Nord)
    for(int i=0 ; i<get_width() ; i++) {
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
    for(int i=0 ; i<get_width() ; i++) {
        const pair<int, int> & pair = getPair(i, get_height()-1);
        const Piece & piece = getPiece(i, get_height()-1);
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

bool Configuration::isConstraintRowsXtremRespected(int x, int y) const {
    const PairColors* swne;
    if(y != 0 && y != get_height()-1)
        return true;
    else {
        const pair<int, int> & pair = getPair(x, y);
        const Piece & piece = getPiece(x, y);
        swne = piece.rotate(pair.second);
        if(y == 0)
            return swne[2] == 0 && !(swne[1] == 0 || swne[1] == 0 || swne[3] == 0);
        else if(y == get_height()-1)
            return swne[0] == 0 && !(swne[1] == 0 || swne[2] == 0 || swne[3] == 0);
        return false;
    }
}

int Configuration::constraintColsXtrem() const {
    int errors = 0;
    const PairColors* swne;
    // Vérification de la première colonne (Contrainte Colonne Ouest)
    for(int i=0 ; i<instance->get_height() ; i++) {
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
    for(int i=0 ; i<instance->get_height() ; i++) {
        const pair<int, int> & pair = getPair(instance->get_width()-1, i);
        const Piece & piece = getPiece(instance->get_width()-1, i);
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

bool Configuration::isConstraintColsXtremRespected(int x, int y) const {
    const PairColors * swne;
    if(x != 0 && x != get_width()-1)
        return true;
    else {
        const pair<int, int> & pair = getPair(x, y);
        const Piece & piece = getPiece(x, y);
        swne = piece.rotate(pair.second);
        if(x == 0)
            return swne[1] == 0 && !(swne[0] == 0 || swne[2] == 0 || swne[3] == 0);
        else if(x == get_width()-1)
            return swne[3] == 0 && !(swne[0] == 0 || swne[1] == 0 || swne[2] == 0);
        return false;
    }
}

int Configuration::constraintEdges() const {
    int errors = 0;
    const PairColors * swne;
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
    pair = getPair(0,instance->get_width()-1);
    piece = getPiece(0,instance->get_width()-1);
    swne = piece.rotate(pair.second);
    if(swne[3] != 0 || swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< 0 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Ouest
    pair = getPair(instance->get_height()-1,0);
    piece = getPiece(instance->get_height()-1,0);
    swne = piece.rotate(pair.second);
    if(swne[West] != 0 || swne[South] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << 0 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Est
    pair = getPair(instance->get_height()-1, instance->get_width()-1);
    piece = getPiece(instance->get_height()-1, instance->get_width()-1);
    swne = piece.rotate(pair.second);
    if(swne[East] != 0 || swne[South] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }

    return errors;
}

bool Configuration::isConstraintEdgesRespected(int x, int y) const {
    const pair<int, int> & pair = getPair(x, y);
    const Piece & piece = getPiece(x, y);
    const PairColors * swne = piece.rotate(pair.second);
    if(x == 0 && y == 0)
        return swne[West] == 0 && swne[North] == 0;
    else if(x == 0 && y == get_height()-1)
        return swne[South] == 0 && swne[West] == 0;
    else if(x == get_width()-1 && y == 0)
        return swne[North] == 0 && swne[East] == 0;
    else if(x == get_width()-1 && y == get_height()-1)
        return swne[South] == 0 && swne[East] == 0;
    return true;
}

int Configuration::constraintAdjacences() const {
    int n = 0;
    for(int j=0 ; j<get_height() ; j++) {
        for(int i=0 ; i<get_width() ; i++) {
            if(!isConstraintAdjacencesRespected(i, j)) {
#if DEBUG_CONSTRAINT
                cout << "Mauvaise adjacences en (" << i << "," << j << ")" << endl;
#endif
                n++;
            }
        }
    }
    return n/2;
}


bool Configuration::isConstraintAdjacencesRespected(int x, int y) const {
    pair<int, int> piece = getPair(x, y);
    PairColors * swne = getPiece(piece.first).rotate(piece.second);

    vector<pair<int, int> > p_SWNE = getAdjacent(x, y);
    for(int i = 0 ; i<4 ; i++) {
        pair<int, int> p_i = p_SWNE[i];
        if(p_i.first != 0) {
            PairColors * swne_aux = getPiece(p_i.first).rotate(p_i.second);
            if(i == 0 && swne[i] != swne_aux[North]) {    // Les couleurs Sud-Nord sont différentes
#if DEBUG_CONSTRAINT
                cout << "Erreur Sud" << endl;
#endif
                return false;
            }
            else if(i == 1 && swne[i] != swne_aux[East]) { // Les couleurs Ouest-Est sont différentes
#if DEBUG_CONSTRAINT
                cout << "Erreur Ouest" << endl;
#endif
                return false;
            }
            else if(i == 2 && swne[i] != swne_aux[South]) {   // Les couleurs Nord-Sud sont différentes
#if DEBUG_CONSTRAINT
                cout << "Erreur Nord" << endl;
#endif
                return false;
            }
            else if(i == 3 && swne[i] != swne_aux[West]) {   // Les couleurs Est-Ouest sont différentes
#if DEBUG_CONSTRAINT
                cout << "Erreur Est" << endl;
#endif
                return false;
            }
        }
    }
    return true;
}

int Configuration::misplacedPieces() {
    vector<int> misplaces(get_height()*get_width());

    for(int j=0 ; j<get_height() ; j++) {
        for(int i=0 ; i<get_width() ; i++) {
            pair<int, int> p = getPair(i, j);
            // Vérification d'Angles
            if((j == 0 && i == 0)||(j== 0 && i == get_width()-1)||(j==get_height()-1 && i==0)||(j==get_height()-1 && i==get_width()-1)) {
                 if(!isConstraintEdgesRespected(i,j)) misplaces[i + j*get_width()] = p.first;
            // Vérification de Lignes
            } else if(j == 0 || j == get_height()-1) {
                 if(!isConstraintRowsXtremRespected(i,j)) misplaces[i + j*get_width()] = p.first;
            // Vérification de Colonnes
            } else if(i == 0 || i == get_width()-1) {
                 if(!isConstraintColsXtremRespected(i,j)) misplaces[i + j*get_width()] = p.first;
            // Vérification des autres (devraient-elles être sur les bords ?)
            } else {
                 Piece piece = getPiece(i, j);
                 int rot;
                 for(int k=0 ; k<4 ; k++) {
                     rot =  piece.get_motif()[k];
                     if(rot == 0) {
                         misplaces[i + j*get_width()] = p.first;
                         break;
                     }
                 }
            }
        }
    }

    // Vérification d'Adjacences pour chaque pièce (à partir de la première pièce bien placée)
    pair<int, int> well_placed = make_pair(-1, -1);
    bool found = false;
    for(int j=0 ; j<get_height() && !found ; j++) {
        for(int i=0 ; i<get_width() && !found ; i++) {
            int n = misplaces[i + j*get_width()];
            if(n == 0) {
                well_placed = make_pair(i, j);
                found = true;
            }
        }
    }

    if(well_placed.first == -1 || well_placed.second == -1)
        cerr << "Aucune pièce bien placée." << endl;
    else {
        pair<int, int> piece = getPair(well_placed.first, well_placed.second);
        PairColors * swne = getPiece(piece.first).rotate(piece.second);

        vector<pair<int, int> > p_SWNE = getAdjacent(well_placed.first, well_placed.second);
        for(int k = 0 ; k<4 ; k++) {
            pair<int, int> p_k = p_SWNE[k];
            if(p_k.first != 0) {
                PairColors * swne_aux = getPiece(p_k.first).rotate(p_k.second);
                pair<int, int> XYaux = getCase(p_k.first);
                if(k == 0 && swne[k] != swne_aux[North])    // Les couleurs Sud-Nord sont différentes
                    misplaces[XYaux.first + XYaux.second * get_width()] = p_k.first;
                else if(k == 1 && swne[k] != swne_aux[East]) // Les couleurs Ouest-Est sont différentes
                     misplaces[XYaux.first + XYaux.second * get_width()] = p_k.first;
                else if(k == 2 && swne[k] != swne_aux[South])   // Les couleurs Nord-Sud sont différentes
                     misplaces[XYaux.first + XYaux.second * get_width()] = p_k.first;
                else if(k == 3 && swne[k] != swne_aux[West])   // Les couleurs Est-Ouest sont différentes
                     misplaces[XYaux.first + XYaux.second * get_width()] = p_k.first;
            }
        }
    }

    int n = 0;
    for(auto i : misplaces) {
        if(i != 0)
            n++;
    }

#if DEBUG_SHOW_MISPLACED
    cout << "Pièces mal placées (ID) : " << n << endl;
    for(auto i : misplaces) {
        if(i != 0 ) {
            pair<int, int> pos = getCase(i);
            cout << "\tPièce à la position : (" << pos.first << "," << pos.second << ")" << endl;
        }
    }
#endif

    return n;
}

bool Configuration::tryPlaceAtEnd(Piece &piece)
{
    bool is_placed= false;

    // TODO tester les 4 rotations
    int rotation;
    for (rotation= 0; rotation < 4 && !is_placed; ++rotation){
//        if ( canBePlaced(piece, rotation) ) {   // TODO à faire
//            // Elle peut être ajoutée, donc on la place
//            placePiece(piece, rotation);
//            // La pièce est placée, cela entraîne la sortie de la boucle
//            is_placed= true;
//        }
    }

#if DEBUG_CSP
    cout << "Pièce d'id "<< piece.get_id()<<" placée avec rotation de "<< rotation<< endl;
#endif

    return is_placed;
}
