#include "configuration.h"

using namespace std;

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

Configuration::Configuration(const Configuration &C) {
    instance = C.instance;
    ids_and_rots = C.ids_and_rots;
}

const pair<int, int>& Configuration::getPair(int x, int y) const {
    // Cas où on essaye d'atteindre une pièce à en dehors des bords du plateau ou du plateau
    if(x < -1 || x > get_width() || y < -1 || y > get_height()) {
        cerr << "ERROR getPair : Traitement d'une case en dehors du plateau (" << x << "," << y << ")) " << endl;
        throw out_of_range("getPair");
    }
    // Cas où on essaye d'atteindre une cellule sur un bord du plateau
    //  ou alors qu'on essaye d'atteindre une cellule sans pièce
    //      |=>(la position de la cellule est supérieure au nombre de pièce initialisées)
    else if(x == -1 || x == get_width() || y == -1 || y == get_height() ||
            ( (x+y*instance->get_width()) >= (signed) ids_and_rots.size() )) {
        return *(new pair<int, int>(0, -1));
    }
    else {
        pair<int, int>* id_and_rot = new pair<int, int>(ids_and_rots[x + y * instance->get_width()]);
        return *id_and_rot;
    }
}

const Piece & Configuration::getPiece(int x, int y) const {
    try{
        const Piece & piece = getPiece(getPair(x,y).id);
        return piece;
    } catch (out_of_range oor) {
        throw out_of_range("getPiece");
    }
}

const Piece & Configuration::getPiece(int id) const {
    const Piece & piece = instance->getPiece(id);
    return piece;
}

PairColors * Configuration::getRotatedMotifs(int x, int y) const {
    if(x < 0 || x >= get_width() || y < 0 || y >= get_height()) {
        cerr << "ERROR getRotatedMotif : Traitement d'une case en dehors du plateau"<< endl;
        throw out_of_range("getPiece");
    }
    pair<int, int> piece_pair = getPair(x, y);
    const Piece& piece = getPiece(x, y);
    return piece.rotate(piece_pair.rot);
}

int Configuration::searchPosition(const Piece& p) const {
    bool found = false;
    int ind = 0;
    while(!found) {
        if(ids_and_rots[ind].id == p.get_id())
            found = true;
        else ind++;
    }
    return ind;
}

int Configuration::searchPosition(const int id) const {
    int ind = -1;
    for(unsigned int i=0 ; i<ids_and_rots.size() ; ++i) {
        if(ids_and_rots[i].first == id)
            ind = (int)i;
    }
    return ind;
}

Coordinates& Configuration::getPosition(int id) const {
    int pos = searchPosition(id);
    int processed_case = 0;
    for(int j=0 ; j<get_height() ; j++) {
        for(int i=0 ; i<get_width() ; i++) {
            if(processed_case == pos) return *(new Coordinates(i, j));
            else processed_case++;
        }
    }
    return *(new Coordinates(-1, -1));
}

bool Configuration::addPieceAsCorner(int p_id, int x, int y) {
    assert(isCorner(x, y));

    int p_rot=0;
    placePiece(make_pair(p_id, p_rot));
    // Bonne rotation
    for (p_rot= 1; p_rot < 4 && !areConstraintEdgesRespected(x, y); ++p_rot){
        setPiece(x, y, make_pair(p_id, p_rot));
    }

    cout << p_id << " " << x << " " << y <<  p_rot << endl;

    if (p_rot == 4) {// Si on est sorti de la boucle car on avait essayé toutes les rotations :
        cerr << "Impossible de placer la pièce dans le coin" << endl;
        return false;
    }
    else return true;
}

bool Configuration::addPieceAsBorder(int p_id, int x, int y) {
    assert(isBorder(x, y));

    int p_rot=0;
    placePiece(make_pair(p_id, p_rot));
    // Bonne rotation
    for (p_rot= 1; p_rot < 4 && (!areConstraintRowsXtremRespected(x, y) || !areConstraintColsXtremRespected(x,y)); ++p_rot){
        setPiece(x, y, make_pair(p_id, p_rot));
    }

    if (p_rot == 4) {// Si on est sorti de la boucle car on avait essayé toutes les rotations :
        cerr << "Impossible de placer la pièce sur le bord"<< endl;
        return false;
    }
    else return true;
}

ostream& Configuration::print(ostream& out) const{
    for(int i=0 ; i<instance->get_width() ; ++i) {
        for(int j=0 ; j<instance->get_height() ; ++j) {
            pair<int, int> p = getPair(i, j);

            out << "Case (" << i << "," << j << ") : \tID = " << p.first << "\tRotation = " << p.second << "\tSONE = ";

            const Piece& piece = getPiece(i, j);

            const PairColors* swne ;
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

    for(int i=0 ; i<instance->get_width(); i++) {
        for(int j=0 ; j<instance->get_height() ; j++) {
            pair<int, int> p = getPair(j, i);
            cout << "\t" << p.first << " ";
        }
        cout << endl;
    }

    return out;
}

void Configuration::setPiece(int x, int y, pair<int, int> id_and_rot) {
#if DEBUG_ALTER_PIECES
      cout << "Essaie de placer la pièce (id,rot) : "<< id_and_rot.id<< ","<< id_and_rot.rot <<
              "à la position "<< x<<","<< y<<endl;
      cout << "Taille vecteur : "<< ids_and_rots.size()<< endl;
      if (x+ y * get_width() >= (signed) ids_and_rots.size()){
          cerr << "ATTENTION, vous essayez de set une pièce non placée"<< endl;
      }
#endif
    if(id_and_rot.rot < 0) {
        setPiece(x, y, make_pair(id_and_rot.first, id_and_rot.rot +4));
    }
    else {
        if(id_and_rot.second > 3){
            id_and_rot.rot = (id_and_rot.rot) % 4;
        }
        ids_and_rots[x + y*get_width()] = id_and_rot;
    }
}

void Configuration::rotatePiece(int x, int y, int degree) {
    if(degree < 0)                  // Si la rotation demandée est inférieure à 0
        rotatePiece(x, y, degree+4);
    else if(degree >= 4) // Sinon si la rotation demandée est supérieure à 4
        rotatePiece(x, y, degree % 4);
    else {
        ids_and_rots[x + y * get_width()].second = ids_and_rots[x + y * get_width()].second + degree;
    }
}

void Configuration::permutation_two_pieces(int piece1_x, int piece1_y, int piece2_x, int piece2_y)
{
    std::pair<int, int> tmp_pair= ids_and_rots[piece1_x + piece1_y * get_width()];

    setPiece(piece1_x, piece1_y, ids_and_rots[piece2_x + piece2_y * get_width()]);
    setPiece(piece2_x, piece2_y, tmp_pair);
}

bool Configuration::better_permutation_two_pieces(int piece1_x, int piece1_y, int piece2_x, int piece2_y) {
    int original_eval = countNbErrors();
    int new_eval = original_eval;

    bool permutation_done = false;
    if(isCorner(piece1_x, piece1_y) && isCorner(piece2_x, piece2_y)) {
        permutation_two_pieces(piece1_x, piece1_y, piece2_x, piece2_y);
        permutation_done = true;
    } else if(isBorder(piece1_x, piece1_y) && isBorder(piece2_x, piece2_y)) {
        permutation_two_pieces(piece1_x, piece1_y, piece2_x, piece2_y);
        permutation_done = true;
    } else if(!(isCorner(piece1_x, piece1_y) && isCorner(piece2_x, piece2_y))&&!(isBorder(piece1_x, piece1_y) && isBorder(piece2_x, piece2_y))) {
        permutation_two_pieces(piece1_x, piece1_y, piece2_x, piece2_y);
        permutation_done = true;
    }
    if(permutation_done) {
        new_eval = countNbErrors();
        if(new_eval < original_eval)
            return true;
        // Rotation première pièce
        for(int i=0 ; i<4 ; i++) {
            rotatePiece(piece1_x, piece1_y, i);
            if(new_eval < original_eval)
                return true;
        }
        // Rotation seconde pièce
        for(int i=0 ; i<4 ; i++) {
            rotatePiece(piece2_x, piece2_y, i);
            if(new_eval < original_eval)
                return true;
        }
        return false;
    } else return false;
}

bool Configuration::tryLoadFile(const string &fileName){
    if( instance->get_width() * instance->get_height() == 0){
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

                ids_and_rots.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(ids_and_rots.size() != (unsigned)(instance->get_width() * instance->get_height()) ){
                cerr << "Fichier de configuration incomplet" << endl;
                return false;
            } else {
                return true;
            }
        }
    }
}

const Piece& Configuration::getClosePiece(int current_piece, Cardinal neightboor_card) const {
    switch(neightboor_card){
    case South:
    {
        const Piece& south_piece= instance->getPiece(current_piece + get_width());
        return south_piece;
    }
        break;
    case West:
    {
        const Piece& west_piece= instance->getPiece(current_piece - 1);
        return west_piece;
    }
        break;
    case North:
    {
        const Piece& north_piece= instance->getPiece(current_piece - get_width());
        return north_piece;
    }
        break;
    case East:
    {
        const Piece& east_piece= instance->getPiece(current_piece + 1);
        return east_piece;
    }
        break;
    default:
        break;
    }

//retourne la meme piece si probleme avec le switch
const Piece& error_piece= instance->getPiece(current_piece);
return error_piece;
}

PairColors Configuration::getMotifClosePiece(int current_piece, Cardinal neightboor_card, Cardinal motif_card) const {
    const Piece& neightboor_piece= getClosePiece(current_piece, neightboor_card);
    //piece
    return neightboor_piece.get_motif()[motif_card];
}

/** Vérifiée **/
bool Configuration::motifs_match(PairColors first_motif, PairColors second_motif)
{
#if DEBUG_MOTIF_MATCH
    cout<< "Comparaison : " << first_motif << " - " << second_motif << endl;
#endif
    if (first_motif != second_motif || first_motif == Black_Black){
        #if DEBUG_MOTIF_MATCH
        cout << "Une erreur.";
        #endif
        return false;
    }
    else {
        #if DEBUG_MOTIF_MATCH
        cout << "Pas d'erreur. ";
        #endif
        return true;
    }
}

bool Configuration::pieces_match(int indice_current_piece, Cardinal direction_neightboor_piece){
    Piece current_piece= getPiece(ids_and_rots[indice_current_piece].first);
    const PairColors* motifs_current_piece= current_piece.get_motif();
    PairColors motif_current_piece= motifs_current_piece[direction_neightboor_piece];

    //comparaison piece courante / piece voisine
    switch(direction_neightboor_piece){
    case South:
    {
        PairColors north_motif_neightboor_piece= getMotifClosePiece(indice_current_piece, South, North);
        if(motifs_match(motif_current_piece, north_motif_neightboor_piece)) return true;
        else return false;
    }
        break;
    case West:
    {
        PairColors east_motif_neightboor_piece= getMotifClosePiece(indice_current_piece, West, East);
        if(motifs_match(motif_current_piece, east_motif_neightboor_piece)) return true;
        else return false;
    }
        break;
    case North:
    {
        PairColors south_motif_neightboor_piece= getMotifClosePiece(indice_current_piece, North, South);
        if(motifs_match(motif_current_piece, south_motif_neightboor_piece)) return true;
        else return false;
    }
        break;
    case East:
    {
        PairColors west_motif_neightboor_piece= getMotifClosePiece(indice_current_piece, East, West);
        if(motifs_match(motif_current_piece, west_motif_neightboor_piece)) return true;
        else return false;
    }
        break;
    default:
        break;
    }
return false;
}

int Configuration::getPieceNbErrors(const Piece& current_piece) {
    int nb_errors= 0;
    int indice_current_piece= current_piece.get_id();

    //position de la piece courante (combien de voisins ?)
    int current_piece_pos= searchPosition(indice_current_piece);
    int current_x= current_piece_pos % get_width();
    int current_y= current_piece_pos / get_width();

    if(0 == current_x) //premiere ligne
    {
        if(0 == current_y) //coin nord gauche
        {
            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

        } else if(get_width()-1 == current_y) //coin nord droit
        {
            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

        } else //bord nord
        {
            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;

        }
    } else if(get_height()-1 == current_x) // derniere ligne
    {
        if(0 == current_y) //coin sud gauche
        {
            //comparaison piece_courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;

        } else if(get_width()-1 == current_y) //coin sud droit
        {
            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

        } else //bord sud
        {
            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;

        }
    } else //ni premiere colonne ni premiere ligne
    {
        if(0 == current_y) // bord ouest
        {
            //comparaison piece courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

        } else if(get_height()-1 == current_y) // bord est
        {
            //comparaison piece courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

        } else // interieur puzzle (pieces avec 4 voisins)
        {
            //comparaison piece courante / piece nord
            if(!pieces_match(indice_current_piece, North)) ++nb_errors;

            //comparaison piece courante / piece ouest
            if(!pieces_match(indice_current_piece, West)) ++nb_errors;

            //comparaison piece courante / piece sud
            if(!pieces_match(indice_current_piece, South)) ++nb_errors;

            //comparaison piece courante / piece est
            if(!pieces_match(indice_current_piece, East)) ++nb_errors;
        }
    }

    return nb_errors;
}

int Configuration::rotationForBestPlace(int coord_x, int coord_y) {
    //tester si en tournant la piece indice_piece d'une rotation de val_rot, on obtient moins d'erreurs avec getPieceNbErrors
    const Piece& piece= getPiece(coord_x, coord_y);
    Piece piece_test= piece;
    int local_nb_errors= getPieceNbErrors(piece_test);

    int best_rot= 0;
    int val_best_rot= local_nb_errors;

    for(int i= 1; i < 4; ++i){
        // TODO Changement de @jfourmond ici
        rotatePiece(coord_x, coord_y, i);

        int nb_current_errors= getPieceNbErrors(piece_test);
        if(val_best_rot > nb_current_errors){
            best_rot= i;
            val_best_rot= nb_current_errors;
        }
    }

    return best_rot;
}
