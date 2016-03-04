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
    if(x < 0 || x > width()-1 || y < 0 || y > height()-1) {
        const pair<int, int> & position = make_pair(0, 0);
        return position;
    }
    const pair<int, int>& position = positions[x + y * instance->width()];
    return position;
}

const Piece & Configuration::getPiece(int x, int y) const {
    const Piece & piece = instance->get_vectPieces()->at(getPair(x, y).first-1);
    return piece;
}

const Piece & Configuration::getPiece(int id) const {
    const Piece & piece = instance->getPiece(id);
    return piece;
}

PairColors * Configuration::getRotatedMotif(int x, int y) const {
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
            ind = (int)i;
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

vector<pair<int, int>> Configuration::getAdjacent(int x, int y) const {
    vector<pair<int, int> > swne(4);

    pair<int, int> pos;
    // Récupération Sud
    pos = getPair(x, y+1);
    swne[0] = pos;
    // Récupération Est
    pos = getPair(x-1, y);
    swne[1] = pos;
    // Récupération Nord
    pos = getPair(x, y-1);
    swne[2] = pos;
    // Récupération Ouest
    pos = getPair(x+1, y);
    swne[3] = pos;

    return swne;
}

ostream& Configuration::print(ostream& out){
    for(int i=0 ; i<instance->width() ; ++i) {
        for(int j=0 ; j<instance->height() ; ++j) {
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
    const PairColors* swne;
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
    const PairColors* swne;
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
    const PairColors* swne;
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
    const PairColors * swne;
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
    const PairColors * swne = piece.rotate(pair.second);
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

PairColors Configuration::getNorthMotifSouthPiece(int current_piece_indice){
    Piece south_piece = instance->getPiece(current_piece_indice + width());
    int rotation = positions[getPosition(south_piece)].second;

    return south_piece.rotate(rotation)[2];
}

PairColors Configuration::getWestMotifEastPiece(int current_piece_indice){
    Piece east_piece = instance->getPiece(current_piece_indice +1);
    int rotation = positions[getPosition(east_piece)].second;

    return east_piece.rotate(rotation)[1];
}

/** Vérifiée **/
bool Configuration::motifs_match(PairColors first_motif, PairColors second_motif)
{
#if DEBUG_MOTIF_MATCH
    cout<< "Comparaison : " << first_motif << " - " << second_motif << endl;
#endif
    if (first_motif != second_motif || first_motif == Black_Black){
        cout << "Une erreur. ";
        return false;
    }
    else {
        cout << "Pas d'erreur. ";
        return true;
    }

//    if(first_motif == Black_Black) return false;
//    if(second_motif == Black_Black) return false;
//    if(first_motif != second_motif) return false;
//    return true;
}

int Configuration::checkPieces(){
    int nb_errors= 0;

    int begin_last_raw= height()*width() -width(); //seuil au-delà duquel une case est dans la derniere ligne

    // Parcours de toutes les cases du plateau, dernière case exceptée
    for(int i=0; i < (height()*width()-1) -1; ++i){
        int current_x= i % width();
        int current_y= i / width();

        PairColors current_piece_east_motif= getRotatedMotif(i)[3];
        PairColors current_piece_south_motif= getRotatedMotif(i)[0];

        #if DEBUG_CHECK_PIECES
        cout << "Piece n°" << i << endl;
        #endif

        //derniere colonne
        if(current_x == width()-1){
            PairColors south_piece_north_motif= getRotatedMotif(i+width())[2];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }
        }
        //derniere ligne
        else if(i > begin_last_raw){
            PairColors east_piece_west_motif= getRotatedMotif(i+1)[1];
            if(!motifs_match(current_piece_east_motif, east_piece_west_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece EST" << endl;
                #endif
                ++nb_errors;
            }
        }
        //ni derniere ligne ni derniere colonne
        else {
            PairColors south_piece_north_motif= getRotatedMotif(i+width())[2];
            if(!motifs_match(current_piece_south_motif, south_piece_north_motif)){
                #if DEBUG_CHECK_PIECES
                cout << "Erreur piece COURANTE - piece SUD" << endl;
                #endif
                ++nb_errors;
            }

            PairColors east_piece_west_motif= getRotatedMotif(i+1)[1];
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

//int Configuration::checkPieces(){
////    /**
////      Algo :
////            Initialiser un vector de bool (vect[i] = 1 si la pièce i a déjà été traité)
////            Tant qu'il reste des pièces à vérifier faire
////                Prendre une pièce P qui n'est pas dans vect
////                Comparer P à ses pièces adjacentes (S et E ayant subit la rotation)
////                Ajouter P à vect (indice de la pièce P à 1 dans vect)
////            Fin TantQue
////    */
//    int nb_errors = 0;

//    for(int i= 0; i< height()*width()-1; ++i) {
//#if DEBUG_POS_ERRORS  or DEBUG_NB_ERROR_PIECE
//        int local_errors = 0;
//#endif
//        // Position de la pièce courante
//        int current_x= i % width();
//        int current_y= i / width();

//        cout<< "Verif erreurs pos "<< current_x<< ";"<< current_y<< endl;

//        pair<int, int> current_piece= positions[i];
//        int id_piece = current_piece.first;
//        #if DEBUG_POS_ERRORS
//            cout << "Piece n° " << i << " ; id_piece = " << id_piece << endl;
//        #endif

//        Piece piece= instance->getPiece(id_piece);
//        PairColors * id_motifs= piece.rotate(current_piece.second);

//        // On stock les motifs de la pièce utiles pour les comparaisons avec les pièces adjacentes
//        PairColors  south_motif = id_motifs[0];
//        PairColors  east_motif = id_motifs[3];

//        // Cas de la derniere ligne du puzzle - est seulement
//        if( (height()-1 == current_y) ){
//            cout << "DERNIERE LIGNE"<< endl;
//            PairColors east_piece_west_motif = getWestMotifEastPiece(i);
//            if(!motifs_match(east_piece_west_motif, east_motif) ){
//                cout << "motif ouest : "<< east_piece_west_motif<< " != "<< east_motif << ", motif est"<< endl;
//                ++nb_errors;
//                #if DEBUG_POS_ERRORS
//                    cout <<  " Il y a une erreur (tot : "<< nb_errors<< ") dernière ligne entre en pos ["<< current_x << ";"
//                         << current_y<< "] et celle à sa droite"<< endl;
//                    ++local_errors;
//                #endif
//            }

//        } else {
//            cout << "NON DERNIERE LIGNE"<< endl;
//            if(current_x == width() -1){ // Cas derniere case d'une ligne : comparaison sud seulement
//                cout << "DERNIERE COLONNE"<< endl;
//                PairColors south_piece_north_motif = getNorthMotifSouthPiece(i);

////                return (south_piece_north_motif != south_motif || south_motif == Black_Black)
//                if ( !motifs_match(south_piece_north_motif, south_motif) ) { // Deuxième condition : Si les pièces sont égales et noires (donc south_piece_north_motif == Black_Black)
//                    ++nb_errors;
//                    #if DEBUG_POS_ERRORS
//                        cout << " Il y a une erreur (tot : "<< nb_errors<< "), sur la derniere colonne, entre les piece en pos ["<< current_x << ";"<< current_y<< "] et et celle en dessous"<< endl;
//                        ++local_errors;
//                    #endif
//                }
//            } else { // Cas général : comparaison  Est-Ouest et Sud-Nord

//                cout << "MILIEU"<< endl;
//                // Récupération des motifs Est ou Ouest
//                PairColors east_piece_west_motif = getWestMotifEastPiece(i);

//                 // Vérification Est-Ouest
//                if( !motifs_match(east_motif, east_piece_west_motif) ) {
//                    ++nb_errors;
//                    #if DEBUG_POS_ERRORS
//                        cout << " Il y a une erreur (tot : "<< nb_errors<< "), entre les piece en pos ["<< current_x << ";"<< current_y<< "] et celle à sa droite"<< endl;
//                        ++local_errors;
//                    #endif
//                }

//                PairColors south_piece_north_motif = getNorthMotifSouthPiece(i);
//                // Vérification Sud-Nord
//                if( !motifs_match(south_piece_north_motif, south_motif) ) {
//                    cout << "motif nord : "<< south_piece_north_motif<< " != "<< south_motif<< ", motif sud"<< endl;
//                    ++nb_errors;
//                    #if DEBUG_POS_ERRORS
//                        cout << " Il y a une erreur (tot : "<< nb_errors<< "), entre les piece en pos ["<< current_x << ";"<< current_y << "] et celle en dessous"<< endl;
//                        ++local_errors;
//                    #endif
//                }
//            } // Fin_else dernière colonne
//        } // Fin_else dernière ligne
//        #if DEBUG_NB_ERROR_PIECE
//            cout << "iteration " << i << " erreurs -> " << local_errors << endl;
//        #endif

//    }//fin parcours pieces
//    clog << "pair noire : "<< Black_Black;

//    return nb_errors;
//}



int Configuration::constraintPieces() {
    vector<int> misplaces(height()*width());

    for(int j=0 ; j<height() ; j++) {
        for(int i=0 ; i<width() ; i++) {
            pair<int, int> p = getPair(i, j);
            // Vérification d'Angles
            if((j == 0 && i == 0)||(j== 0 && i == width()-1)||(j==height()-1 && i==0)||(j==height()-1 && i==width()-1)) {
                 if(!constraintEdges(i,j)) misplaces[i + j*width()] = p.first;
            // Vérification de Lignes
            } else if(j == 0 || j == height()-1) {
                 if(!constraintRowsXtrem(i,j)) misplaces[i + j*width()] = p.first;
            // Vérification de Colonnes
            } else if(i == 0 || i == width()-1) {
                 if(!constraintColsXtrem(i,j)) misplaces[i + j*width()] = p.first;
            // Vérification des autres (devraient-elles être sur les bords ?)
            } else {
                 Piece piece = getPiece(i, j);
                 int rot;
                 for(int k=0 ; k<4 ; k++) {
                     rot =  piece.get_motif()[k];
                     if(rot == 0) {
                         misplaces[i + j*width()] = p.first;
                         break;
                     }
                 }
            }
        }
    }
    // Vérification d'Adjacences pour chaque pièce (à partir de la première pièce bien placée)
    pair<int, int> well_placed = make_pair(-1, -1);
    bool found = false;
    for(int j=0 ; j<height() && !found ; j++) {
        for(int i=0 ; i<width() && !found ; i++) {
            int n = misplaces[i + j*width()];
            if(n == 0) {
                well_placed = make_pair(i, j);
                found = true;
            }
        }
    }

    pair<int, int> piece = getPair(well_placed.first, well_placed.second);
    PairColors * swne = getPiece(piece.first).rotate(piece.second);

    vector<pair<int, int> > p_SWNE = getAdjacent(well_placed.first, well_placed.second);
    for(int k = 0 ; k<4 ; k++) {
        pair<int, int> p_k = p_SWNE[k];
        if(p_k.first != 0) {
            PairColors * swne_aux = getPiece(p_k.first).rotate(p_k.second);
            pair<int, int> XYaux = getCase(p_k.first);
            if(k == 0 && swne[k] != swne_aux[2])    // Les couleurs Sud-Nord sont différentes
                misplaces[XYaux.first + XYaux.second * width()] = p_k.first;
            else if(k == 1 && swne[k] != swne_aux[3]) // Les couleurs Ouest-Est sont différentes
                 misplaces[XYaux.first + XYaux.second * width()] = p_k.first;
            else if(k == 2 && swne[k] != swne_aux[0])   // Les couleurs Nord-Sud sont différentes
                 misplaces[XYaux.first + XYaux.second * width()] = p_k.first;
            else if(k == 3 && swne[k] != swne_aux[1])   // Les couleurs Est-Ouest sont différentes
                 misplaces[XYaux.first + XYaux.second * width()] = p_k.first;
        }
    }

    int n = 0;
    for(auto i : misplaces) {
        if(i != 0)
            n++;
    }

//    cout << "Pièces mal placées (ID) : " << n << endl;
//    for(auto i : misplaces) {
//        if(i != 0 ) {
//            pair<int, int> pos = getCase(i);
//            cout << "\tPièce à la position : (" << pos.first << "," << pos.second << ")" << endl;
//        }
//    }

    return n;
}
