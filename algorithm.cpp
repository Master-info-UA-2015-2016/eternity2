#include "algorithm.h"

using namespace std;

int Algorithm::vicinity(const Configuration & C1, const Configuration & C2) {
    assert(C1.get_ids_and_rots().size() == C2.get_ids_and_rots().size());
    int vicinity = 0;

    for(unsigned int i=0 ; i<C1.get_ids_and_rots().size() ; i++) {
        if(C1.get_ids_and_rots().at(i).first == C2.get_ids_and_rots().at(i).first)
            vicinity++;
    }
    return vicinity;
}

Configuration * Algorithm::getNeighbour(const Configuration & config) {
    Configuration * voisin = new Configuration(config);

    int x, y;
    do {
        x = rand() % (config.get_width()-1);
        y = rand() % (config.get_width()-1);
    } while ( x==0 && y==0 );

    pair<int, int> piece = config.getPair(x, y);
    int rot_add =((rand() % (4)) + piece.second) % 4;

    voisin->rotatePiece(x, y, rot_add);
    return voisin;
}

Configuration * Algorithm::getFirstBetterNeighbour(const Configuration &config) {
    Configuration  * cpy = new Configuration(config);
    for(int j=0 ; j<config.get_height() ; j++) {
        for(int i=0 ; i<config.get_width() ; i++) {

            for(int l=0 ; l<config.get_height() ; l++) {
                for(int k=0 ; k<config.get_width() ; k++) {
                    bool res = cpy->better_permutation_two_pieces(i, j, k, l);
                    if(res) return cpy;
                    else {
                        free(cpy);
                        cpy = new Configuration(config);
                    }
                }
            }
        }
    }
    // Pas de meilleur voisin
    return cpy;
}

vector<Configuration *> Algorithm::get_neighbours(Configuration & C, vector<Configuration *> configurations) {
    vector<Configuration *> neightbours;
    int i = 0;
    int vic_max = 0;
    for(auto config : configurations) {
        int vic = Algorithm::vicinity(C, (*config));
        if(vic != C.get_width()*C.get_height()) {
            if(vic > vic_max) {
                vic_max = vic;
                neightbours.clear();
                neightbours.push_back(config);
            } else if(vic == vic_max)
                    neightbours.push_back(config);
        }
        i++;
    }
    return neightbours;
}

Configuration* Algorithm::make_son(const Configuration *parent1, const Configuration parent2){
    Configuration* son= new Configuration();



return son;
}

int Algorithm::evaluation(const Configuration & C) {
    return C.countNbErrors();
}

Configuration * Algorithm::local_search(const Configuration * config) {
    int nb_eval = 0;
//    int x = 0;
//    int y = 0;
    // 1. Sélectionner une solution initiale x0 € X
    Configuration * c0 = new Configuration(*config);
    // 2. x <- x0 (x est la solution courante)
    Configuration * c = c0;
    // 3. x* <- x (x* est la meilleure solution rencontrée au sens de f)
    Configuration * cStar = c;
    // 4. Tant que le critère d'arret n'est pas respecté faire
    Configuration * cprime;
    while(nb_eval < 1000) {
        // 5. Sélectionner une solution voisine x' ∈ N(x)
        cprime = getFirstBetterNeighbour(*c);
        // 6. x <- x'
        c = cprime;
        nb_eval++;
        // 7. si f(x) > f(x*) alors
        if(Algorithm::evaluation(*c) < Algorithm::evaluation(*cStar)) {
            // 8. x* <- x
            cStar = c;  // Nouvelle meilleure solution
            nb_eval = 0;
            cout << "Nouvelle meilleure solution : " << endl << *cStar << endl;
        }   // 9. fin
    } // 10. fin
    // 11. retourner x*
    return cStar;
}

//Configuration * Algorithm::build_Configuration(const Instance *instance) {
//    Configuration * config = new Configuration(instance);

//    list<Piece> pieces;

//    for(const Piece & p : *(config->getPieces())) {
//        pieces.push_back(config->getPiece(p.get_id()));
//    }
//    vector<bool> used(pieces.size(), false);

//    bool found;
//    for(int j=0 ; j<config->get_height() ; j++) {
//        for(int i=0 ; i<config->get_width() ; i++) {
//            // Pour chaque case, choisir une pièce s'accordant au mieux aux contraintes
//            // de lignes, de colonnes et d'adjacences
//            found = false;
//            for(int k=0 ; k<(signed) pieces.size() && !found ; k++) {
//                // Si la pièce n'est pas utilisé, on l'essaye
//                if(!used[k]) {
//                    Piece piece = pieces[k];
//                    config->placePiece(make_pair(piece.get_id(), 0));
//                    // Bien placé ?
//                    if(config->isConstraintColsXtremRespected(i, j) && config->isConstraintColsXtremRespected(i, j) && config->isConstraintEdgesRespected(i, j) && config->isConstraintAdjacencesRespected(i, j)) {
//                        // Bien placé !
//                        used[k] = true;
//                        found = true;
//                    } else {
//                        config->removePiece();
//                        // Tentative de rotation
//                        for(int r=1 ; r<4 && !found; r++) {
//                            config->placePiece(make_pair(piece.get_id(), r));
//                            if(config->isConstraintColsXtremRespected(i, j) && config->isConstraintColsXtremRespected(i, j) && config->isConstraintEdgesRespected(i, j) && config->isConstraintAdjacencesRespected(i, j)) {
//                                // Bien placé !
//                                used[k] = true;
//                                found = true;
//                            } else config->removePiece();
//                        }
//                    }
//                    // Si aucun de ces tests n'a fonctionné (found == false), on teste une autre pièce
//                    // TODO BackTracking
//                }
//            }
//        }
//    }

//    return config;
//}

Configuration* Algorithm::resolveWithCSP(const Instance *instance)
{
    Configuration* solution = new Configuration(instance);
    bool has_first_corner= false;

    list<Piece> available_pieces;

    for(const Piece p : *(solution->getPieces())) {
        if (!has_first_corner && p.isCorner()){
            solution->addPieceAsCorner(p.get_id(), 0,0);
            has_first_corner= true;
#if DEBUG_CSP
            cout << p<< " placée au coin"<< endl;
#endif
        }
        else {
            available_pieces.push_back(p);
        }
    }

#if DEBUG_CSP
    cout << "Nombre de pièces disponibles : "<< available_pieces.size()<< endl;
#endif

    // Parcours du tableau @SEE si on l'améliore en escargot
    for(int i= 2; i<= solution->get_width() * solution->get_height(); ++i){
//    for (int y= 0; y < solution->get_height(); ++y){
//        for (int x= 0; x < solution->get_width(); ++x){
            Piece current_piece= available_pieces.front();
            available_pieces.pop_front();
            // Je vérifie si la pièce a été ajoutée à la suite des autres
            unsigned int num_try= 0;
            bool placed= false;
            do {
                placed= solution->tryPlaceAtEnd(current_piece);
                 ++num_try;
                // La pièce ne peut pas être ajoutée, donc on la replace à la fin
                //  de la liste des pièces disponibles
                if (!placed){
                #if DEBUG_CSP
    //                cout << "Essai de placer "<< current_piece<< " en "<< x<< ";"<< y<< endl;
                    cout << "Essai num "<< num_try<< " : placer "<< current_piece<< " en "
                         << i<< " eme case (placé : "<< placed<< ")"<< endl;
                    cout << solution->get_ids_and_rots().size()<< " déjà placées, "<<
                         solution->get_width() * solution->get_height()-i +1<< " à placer"<< endl;
                    cout << available_pieces.size() +1<< " disponibles"<< endl;
                #endif
                    available_pieces.push_back(current_piece);
                    current_piece= available_pieces.front();
                    available_pieces.pop_front();
                }
            }while (!placed && num_try <= available_pieces.size());

            // En cas d'echec de placement de la pièce suivante
            if (!placed){
                available_pieces.push_front(current_piece);
                clog << "IL FAUT PLACER LES PIECES SUIVANTES SANS RESPECTER LES CONTRAINTES"
                        " OU FAIRE DU BACKTRACKING"<< endl;
            }

//        }
    }

    return solution;
}

Configuration** Algorithm::genetic_search(const Configuration **configs){
    //selection de 2 parents
    //croisement (sur quel critere croiser ?)
    //mutation (s'arranger pour tourner les pieces si besoin)
    //injection (fils = meilleure solution ?)

}
