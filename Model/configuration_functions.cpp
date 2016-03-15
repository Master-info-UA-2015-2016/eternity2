#include "configuration.h"

using namespace std;


vector<pair<int, int>>& Configuration::getAdjacents(int x, int y) const {
    vector<pair<int, int> >& swne= *(new vector<pair<int, int> >(4));

    pair<int, int> pos;
    // Récupération Sud
    try {
        pos = getPair(x, y+1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
    }
    swne[0] = pos;
    // Récupération Est
    try {
        pos = getPair(x-1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Est" << endl;
    }
    swne[1] = pos;
    // Récupération Nord
    try {
        pos = getPair(x, y-1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Nord" << endl;
    }
    swne[North] = pos;
    // Récupération Ouest
    try {
        pos = getPair(x+1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
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


int Configuration::countNbErrors() const{
    int nb_errors= 0;

    int begin_last_raw= get_height()*get_width() -get_width(); // première case de la derniere ligne

    // Parcours de toutes les cases du plateau, dernière case exceptée
    for(int i=0; i < (get_height()*get_width()-1); ++i){
        int current_x= i % get_width();
//        int current_y= i / get_width();

        PairColors current_piece_east_motif= getRotatedMotif(i)[East];
        PairColors current_piece_south_motif= getRotatedMotif(i)[South];

        #if DEBUG_CHECK_PIECES
        cout << "Piece n°" << i << endl;
        #endif

        //derniere colonne
        if(current_x == get_width()-1){
            PairColors south_piece_north_motif= getRotatedMotif(i+get_width())[North];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }
        }
        //derniere ligne
        else if(i >= begin_last_raw){
            PairColors east_piece_west_motif= getRotatedMotif(i+1)[West];
            if(!motifs_match(current_piece_east_motif, east_piece_west_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece EST" << endl;
                #endif
                ++nb_errors;
            }
        }
        //ni derniere ligne ni derniere colonne
        else {
            PairColors south_piece_north_motif= getRotatedMotif(i+get_width())[North];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }

            PairColors east_piece_west_motif= getRotatedMotif(i+1)[West];
            if(!motifs_match(current_piece_east_motif, east_piece_west_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece EST" << endl;
                #endif
                ++nb_errors;
            }
        }
    }
    return nb_errors;
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

    vector<pair<int, int> > p_SWNE = getAdjacents(x, y);
    for(int i = 0 ; i<4 ; i++) {
        pair<int, int> p_i = p_SWNE[i];
        if(p_i.first != 0) {
            PairColors * swne_aux = getPiece(p_i.first).rotate(p_i.second);
            if(i == 0 && swne[i] != swne_aux[North]) // Les couleurs Sud-Nord sont différentes
                return false;
            else if(i == 1 && swne[i] != swne_aux[East]) // Les couleurs Ouest-Est sont différentes
                return false;
            else if(i == 2 && swne[i] != swne_aux[South]) // Les couleurs Nord-Sud sont différentes
                return false;
            else if(i == 3 && swne[i] != swne_aux[West]) // Les couleurs Est-Ouest sont différentes
                return false;
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

        vector<pair<int, int> > p_SWNE = getAdjacents(well_placed.first, well_placed.second);
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

bool Configuration::canBePlaced(const Piece &piece, int rotation) const {
    PairColors* colors = piece.rotate(rotation);

    cout << colors[0] << endl;

    int current_case = instance->get_pieces()->size();

    int x = current_case % get_width();
    int y = current_case / get_width();

    vector<pair<int, int> > adjacents = getAdjacents(x, y);

    pair<int, int> P;
    PairColors * other_colors;
    for(unsigned int i=0 ; i<adjacents.size() ; i++) {
        P = adjacents[i];
        // Si l'id est != 0 alors regarder la couleur
        if(P.first != 0) {
            other_colors = get_rotated_motifs(P.first);
            if(i == 0 && colors[i] != other_colors[2]) // Les couleurs Sud-Nord sont différentes
                return false;
            else if(i == 1 && colors[i] != other_colors[3]) // Les couleurs Ouest-Est sont différentes
                return false;
            else if(i == 2 && colors[i] != other_colors[0]) // Les couleurs Nord-Sud sont différentes
                return false;
            else if(i == 3 && colors[i] != other_colors[1]) // Les couleurs Est-Ouest sont différentes
                return false;
        }
    }
    // Pas de soucis d'adjacences, mais est-ce que l'emplacement est compatible avec les bordures ou l'angle ?

    return true;
}

bool Configuration::tryPlaceAtEnd(const Piece &piece)
{
    bool is_placed= false;

    int rotation;
    for (rotation= 0; rotation < 4 && !is_placed; ++rotation){
        if (canBePlaced(piece, rotation)) {
            // Elle peut être ajoutée, donc on la place
            placePiece(piece, rotation);
#if DEBUG_CSP
            cout << "Pièce d'id "<< piece.get_id()<<" placée avec rotation de "<< rotation << endl;
#endif
            is_placed = true;
        }
    }

    return is_placed;
}
