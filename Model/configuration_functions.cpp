#include "configuration.h"

using namespace std;


vector<pair<int, int>>& Configuration::getAdjacents(int x, int y) const {
    vector<pair<int, int> >& adjacents_ids_and_rots= *(new vector<pair<int, int> >(4));

    pair<int, int> current_id_and_rot;
    // Récupération Sud
    try {
        current_id_and_rot = getPair(x, y+1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
    }
    adjacents_ids_and_rots[0] = current_id_and_rot;
    // Récupération Est
    try {
        current_id_and_rot = getPair(x-1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Est" << endl;
    }
    adjacents_ids_and_rots[1] = current_id_and_rot;
    // Récupération Nord
    try {
        current_id_and_rot = getPair(x, y-1);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Nord" << endl;
    }
    adjacents_ids_and_rots[North] = current_id_and_rot;
    // Récupération Ouest
    try {
        current_id_and_rot = getPair(x+1, y);
    } catch ( const std::exception & e ) {
        cerr << "Récupération Ouest" << endl;
    }
    adjacents_ids_and_rots[3] = current_id_and_rot;

    return adjacents_ids_and_rots;
}

void Configuration::randomConfiguration() {

//    Tri des pièces par position possible : coins, bords, centre
    vector<int> edge_pieces;
    vector<int> corner_pieces;
    vector<int> pieces_remaining;

    // Travail uniquement sur l'id des pieces
    for(const Piece& piece : (*getPieces()) ) {
        if(piece.isBorder())
            edge_pieces.push_back(piece.get_id());
        else if(piece.isCorner())
            corner_pieces.push_back(piece.get_id());
        else
            pieces_remaining.push_back(piece.get_id());
    }

    // Mélange aléatoire
    random_shuffle(edge_pieces.begin(), edge_pieces.end());
    random_shuffle(corner_pieces.begin(), corner_pieces.end());
    random_shuffle(pieces_remaining.begin(), pieces_remaining.end());

//    Placement des pièces
    int p_rot;
    int p_id;
    for(int row=0 ; row<get_height() ; row++) {
        for(int col=0 ; col<get_width() ; col++) {
            p_rot = 0;
            // Vérification qu'on est bien dans un coin
            if(isCorner(col, row)) {
                p_id = corner_pieces.back();
                corner_pieces.pop_back();
                addPieceAsCorner(p_id, col, row);
            }
            //  Vérification qu'on est bien sur un rebord (pas un coin - par la condition précédente !)
            else if(isBorder(col, row)) {
                // Border
                p_id = edge_pieces.back();
                edge_pieces.pop_back();
                addPieceAsBorder(p_id, col, row);
            }
            // Autre
            else {
                // Autre
                p_id = pieces_remaining.back();
                pieces_remaining.pop_back();
                // Rotation aléatoire
                p_rot = rand() % 4;
                // Ajout de la pair
                placePiece(make_pair(p_id, p_rot));
            }
        }
    }
}

vector<Configuration*>&  Configuration::generateRandomConfigurations(const Instance * instance, int limit) {
    vector<Configuration*>& configurations= *(new vector<Configuration*>);

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        Configuration* configuration= new Configuration(instance);
        configuration->randomConfiguration();

    #if DEBUG_CREATE_CONFIGS
        cout << "Configuration : " << *configuration << endl;
    #endif

        configurations.push_back(configuration);
    }

    return configurations;
}

Configuration* Configuration::getBestRotatedConfig(const Configuration* config){
    Configuration* tmp= new Configuration(*config);
    for(int i= 0; i < tmp->get_width(); ++i){
        for(int j= 0; j < tmp->get_height(); ++j){
            int best_rotation= tmp->rotationForBestPlace(i, j);
            if(0 < best_rotation) //la piece pourrait etre mieux placee
            {
                tmp->rotatePiece(i, j, best_rotation);
            }
        }
    }

    return tmp;
}


int Configuration::countNbErrors() const{
    int nb_errors= 0;

    int begin_last_raw= get_height()*get_width() -get_width(); // première case de la derniere ligne

    // Parcours de toutes les cases du plateau, dernière case exceptée
    for(int i=0; i < (get_height()*get_width()-1); ++i){
        int current_x= i % get_width();
        int current_y= i / get_width();

        PairColors* motifs= getRotatedMotifs(current_x, current_y);
        PairColors current_piece_east_motif= motifs[East];
        PairColors current_piece_south_motif= motifs[South];

        #if DEBUG_CHECK_PIECES
        cout << "Piece n°" << i << endl;
        #endif

        //derniere colonne
        if(current_x == get_width()-1){
            PairColors south_piece_north_motif= getRotatedMotifs(current_x, current_y+1)[North];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }
        }
        //derniere ligne
        else if(i >= begin_last_raw){
            PairColors east_piece_west_motif= getRotatedMotifs(current_x+1, current_y)[West];
            if(!motifs_match(current_piece_east_motif, east_piece_west_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece EST" << endl;
                #endif
                ++nb_errors;
            }
        }
        //ni derniere ligne ni derniere colonne
        else {
            PairColors south_piece_north_motif= getRotatedMotifs(current_x, current_y +1)[North];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }

            PairColors east_piece_west_motif= getRotatedMotifs(current_x+1, current_y)[West];
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

int Configuration::nbErrorsRowsXtrem() const {
    int errors = 0;
    const PairColors* swne;
    // Vérification de la première ligne (Contrainte Ligne Nord)
    for(int i=0 ; i<get_width() ; i++) {
        int rotation= getRotation(i, 0);
        const Piece & piece = getPiece(i, 0);
        swne = piece.rotate(rotation);
        if(swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< i << "," << 0 << ")" << piece;
#endif
            errors++;
        }
    }
    // Vérification de la seconde ligne (Contrainte Ligne Sud)
    for(int i=0 ; i<get_width() ; i++) {
        int rotation= getRotation(i, get_height()-1);
        const Piece & piece = getPiece(i, get_height()-1);
        swne = piece.rotate(rotation);
        if(swne[0] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< i << "," << height()-1 << ")" << piece;
#endif
            errors++;
        }
    }
    return errors;
}

bool Configuration::areConstraintRowsXtremRespected(int x, int y) const {
    if(y != 0 && y != get_height()-1)
        return true;
    else {
        int p_rot= getRotation(x, y);
        const Piece & piece = getPiece(x, y);

        const PairColors* swne;
        swne= piece.rotate(p_rot);

        if(y == 0)
            return swne[North] == Black_Black && !(swne[South] == Black_Black || swne[West] == Black_Black || swne[East] == Black_Black);
        else if(y == get_height()-1)
            return swne[South] == Black_Black && !(swne[West] == Black_Black || swne[North] == Black_Black || swne[East] == Black_Black);
        return false;
    }
}

int Configuration::constraintColsXtrem() const {
    int errors = 0;
    const PairColors* swne;
    // Vérification de la première colonne (Contrainte Colonne Ouest)
    for(int i=0 ; i<instance->get_height() ; i++) {
        int rotation= getRotation(0, i);
        const Piece & piece = getPiece(0, i);
        swne = piece.rotate(rotation);
        if(swne[1] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< 0 << "," << i << ")" << piece;
#endif
            errors++;
        }
    }
    // Vérification de la seconde colonne (Contrainte Colonne Est)
    for(int i=0 ; i<instance->get_height() ; i++) {
        int rotation= getRotation(instance->get_width()-1, i);
        const Piece & piece = getPiece(instance->get_width()-1, i);
        swne = piece.rotate(rotation);
        if(swne[3] != 0) {
#if DEBUG_SHOW_CONFIG
            cout << "\t("<< instance->width()-1 << "," << i << ")" << piece;
#endif
            errors++;
        }
    }
    return errors;

}

bool Configuration::areConstraintColsXtremRespected(int x, int y) const {
    const PairColors * swne;
    if(x != 0 && x != get_width()-1)
        return true;
    else {
        int rotation= getRotation(x, y);
        const Piece & piece = getPiece(x, y);
        swne = piece.rotate(rotation);

        if(x == 0)
            return swne[West] == Black_Black && !(swne[0] == 0 || swne[2] == 0 || swne[3] == 0);
        else if(x == get_width()-1)
            return swne[East] == Black_Black && !(swne[0] == 0 || swne[1] == 0 || swne[2] == 0);
        return false;
    }
}

int Configuration::nbErrorsCorners() const {
    int errors = 0;
    const PairColors * swne;

    // Coin Nord-Ouest
    int rotation= getRotation(0,0);
    Piece piece = getPiece(0,0);
    swne = piece.rotate(rotation);

    if(swne[1] != 0 || swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< 0 << "," << 0 << ")" << piece;
#endif
        errors++;
    }
    // Coin Nord-Est
    rotation= getRotation(0,instance->get_width()-1);
    piece = getPiece(0,instance->get_width()-1);
    swne = piece.rotate(rotation);

    if(swne[3] != 0 || swne[2] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< 0 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Ouest
    rotation= getRotation(instance->get_height()-1,0);
    piece = getPiece(instance->get_height()-1,0);
    swne = piece.rotate(rotation);

    if(swne[West] != 0 || swne[South] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << 0 << ")" << piece;
#endif
        errors++;
    }
    // Coin Sud-Est
    rotation= getRotation(instance->get_height()-1, instance->get_width()-1);
    piece = getPiece(instance->get_height()-1, instance->get_width()-1);
    swne = piece.rotate(rotation);

    if(swne[East] != 0 || swne[South] != 0) {
#if DEBUG_SHOW_CONFIG
        cout << "\t("<< instance->height()-1 << "," << instance->width()-1 << ")" << piece;
#endif
        errors++;
    }

    return errors;
}

bool Configuration::areConstraintCornersRespected(int x, int y) const {
    int rotation= getRotation(x, y);
    const Piece & piece = getPiece(rotation);
    const PairColors * swne = piece.rotate(rotation);

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

int Configuration::nbErrorsAdjacences() const {
    int n = 0;
    for(int j=0 ; j<get_height() ; j++) {
        for(int i=0 ; i<get_width() ; i++) {
            if(!areConstraintAdjacencesRespected(i, j)) {
#if DEBUG_CONSTRAINT
                cout << "Mauvaise adjacences en (" << i << "," << j << ")" << endl;
#endif
                n++;
            }
        }
    }
    return n/2;
}


bool Configuration::areConstraintAdjacencesRespected(int x, int y) const {
    int rotation= getRotation(x, y);
    PairColors * swne = getPiece(x, y).rotate(rotation);

    vector<pair<int, int> > p_SWNE = getAdjacents(x, y);
    for(int i = 0 ; i<4 ; i++) {
        pair<int, int> p_adj = p_SWNE[i];
        if(p_adj.first != 0) {
            PairColors * swne_aux = getPiece(p_adj.first).rotate(p_adj.second);
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

    for(int y=0 ; y < get_height() ; ++y) {
        for(int x=0 ; x < get_width() ; ++x) {
            pair<int, int> p = getPair(x, y);
            // Vérification d'Angles
            if((y == 0 && x == 0)||(y== 0 && x == get_width()-1)||(y==get_height()-1 && x==0)||(y==get_height()-1 && x==get_width()-1)) {
                 if(!areConstraintCornersRespected(x,y)) misplaces[x + y*get_width()] = p.first;
            // Vérification de Lignes
            } else if(y == 0 || y == get_height()-1) {
                 if(!areConstraintRowsXtremRespected(x,y)) misplaces[x + y*get_width()] = p.first;
            // Vérification de Colonnes
            } else if(x == 0 || x == get_width()-1) {
                 if(!areConstraintColsXtremRespected(x,y)) misplaces[x + y*get_width()] = p.first;
            // Vérification des autres (devraient-elles être sur les bords ?)
            } else {
                 Piece piece = getPiece(x, y);
                 int rot;
                 for(int k=0 ; k<4 ; k++) {
                     rot =  piece.get_motif()[k];
                     if(rot == 0) {
                         misplaces[x + y*get_width()] = p.first;
                         break;
                     }
                 }
            }
        }
    }

    // Vérification d'Adjacences pour chaque pièce (à partir de la première pièce bien placée)
    Coordinates well_placed(-1, -1);
    bool found = false;
    for(int y=0 ; y < get_height() && !found ; y++) {
        for(int x=0 ; x < get_width() && !found ; x++) {
            int n = misplaces[x + y*get_width()];
            if(n == 0) {
                well_placed= Coordinates(x, y);
                found = true;
            }
        }
    }

    if(well_placed.col == -1 || well_placed.row == -1)
        cerr << "Aucune pièce bien placée." << endl;
    else {
        int rotation= getRotation(well_placed.col, well_placed.row);
        PairColors * swne = getPiece(well_placed.col, well_placed.row).rotate(rotation);

        vector<pair<int, int> > p_SWNE = getAdjacents(well_placed.col, well_placed.row);
        for(int k = 0 ; k<4 ; k++) {
            pair<int, int> p_k = p_SWNE[k];
            if(p_k.first != 0) {
                PairColors * swne_aux = getPiece(p_k.first).rotate(p_k.second);
                Coordinates XYaux = getPosition(p_k.first);
                if(k == 0 && swne[k] != swne_aux[North])    // Les couleurs Sud-Nord sont différentes
                    misplaces[XYaux.col + XYaux.row * get_width()] = p_k.first;
                else if(k == 1 && swne[k] != swne_aux[East]) // Les couleurs Ouest-Est sont différentes
                     misplaces[XYaux.col+ XYaux.row * get_width()] = p_k.first;
                else if(k == 2 && swne[k] != swne_aux[South])   // Les couleurs Nord-Sud sont différentes
                     misplaces[XYaux.col + XYaux.row* get_width()] = p_k.first;
                else if(k == 3 && swne[k] != swne_aux[West])   // Les couleurs Est-Ouest sont différentes
                     misplaces[XYaux.col + XYaux.row * get_width()] = p_k.first;
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

bool Configuration::canBePlaced(const Piece & piece, int rotation) {
    PairColors* colors = piece.rotate(rotation);

    int current_case = ids_and_rots.size();

    int x = current_case % get_width();
    int y = current_case / get_width();

    vector<pair<int, int> > adjacents = getAdjacents(x, y);
#if DEBUG_CSP
    cout << "Adjacents : "<< endl;
    for (int i = 0; i < 4; ++i){
        cout << adjacents[i].id<< ", "<<adjacents[i].rot <<endl;
    }
#endif

    pair<int, int> P;
    PairColors * other_colors;
    for(unsigned int i=0 ; i<adjacents.size() ; i++) {
        P = adjacents[i];
        // Si l'id est != 0 alors regarder la couleur
        if(P.id != 0) {
            //@TODO a verifier si c'est correct : get_rotated_motifs(P.first) ==> getRotatedMotifs(x, y)
            other_colors = getRotatedMotifs(x, y);
//            other_colors = get_rotated_motifs(P.id);

            if(colors[i] != other_colors[(i+2)%4]) // On vérifie que les motifs adjacents sont identiques
                return false;
            #if DEBUG_CSP
                cout << "Motif : "<< endl;
                for (int i = 0; i < 4; ++i){
                    cout << "comp "<< colors[i]<< " et "<<other_colors[(i+2) %4]<< "(id: "<< P.id<< ")"<< endl;
                }
            #endif
        }
    }
    // Pas de soucis d'adjacences, mais est-ce que l'emplacement est compatible avec les bordures ou l'angle ?
    // TODO appliquer les fonctions de contraintes sur la position ?

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
