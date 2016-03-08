#include "algorithm.h"

using namespace std;

int Algorithm::vicinity(const Configuration & C1, const Configuration & C2) {
    assert(C1.getPositions().size() == C2.getPositions().size());
    int vicinity = 0;

    for(unsigned int i=0 ; i<C1.getPositions().size() ; i++) {
        if(C1.getPositions().at(i).first == C2.getPositions().at(i).first)
            vicinity++;
    }
    return vicinity;
}

static Configuration * voisinage(const Configuration & C) {
    Configuration * voisin = new Configuration(C);
    // Modifier la configuration pour en avoir une meilleure
    int x = rand() % (C.get_width()-1);
    int y = rand() % (C.get_width()-1);
    pair<int, int> piece = C.getPair(x, y);
    int rot_add =((rand() % (4)) + piece.second) % 4;

    voisin->setPiece(x, y, make_pair(piece.first, rot_add));
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

int Algorithm::evaluation(Configuration & C) {
    return C.checkPieces();
}

Configuration * Algorithm::local_search(const Instance * instance) {
    // Génération de configurations
    vector<Configuration *> configurations = Configuration::generateRandomConfigurations(instance, 1000);

    int nb_eval = 0;
    // 1. Sélectionner une solution initiale x0 € X
    Configuration * x0 = configurations[0];
    // 2. x <- x0 (x est la solution courante)
    Configuration * x = x0;
    // 3. x* <- x (x* est la meilleure solution rencontrée au sens de f)
    Configuration * xStar = x;
    // 4. Tant que le critère d'arret n'est pas respecté faire

    vector<Configuration *> voisins;
    Configuration * xprime;
    while(nb_eval < 100) {
        // 5. Sélectionner une solution voisine x' ∈ N(x)
        voisins = get_neighbours((*x), configurations);
        random_shuffle(voisins.begin(), voisins.end());
        xprime = voisins[0];
        // 6. x <- x'
        x = xprime;
        nb_eval++;
        // 7. si f(x) > f(x*) alors
        if(Algorithm::evaluation(*x) < Algorithm::evaluation(*xStar)) {
            // 8. x* <- x
            xStar = x;  // Nouvelle meilleure solution
            nb_eval = 0;
            cout << "Nouvelle meilleure solution : " << endl << *xStar << endl;
        }   // 9. fin
    } // 10. fin
    // 11. retourner x*
    return xStar;
}

Configuration * Algorithm::build_Configuration(const Instance *instance) {
    Configuration * config = new Configuration(instance);

    vector<Piece> pieces;

    for(const Piece & p : *(config->getPieces())) {
        pieces.push_back(config->getPiece(p.get_id()));
    }
    vector<bool> used(pieces.size(), false);

    bool found;
    for(int j=0 ; j<config->get_height() ; j++) {
        for(int i=0 ; i<config->get_width() ; i++) {
            // Pour chaque case, choisir une pièce s'accordant au mieux aux contraintes
            // de lignes, de colonnes et d'adjacences
            found = false;
            for(int k=0 ; k<(signed) pieces.size() && !found ; k++) {
                // Si la pièce n'est pas utilisé, on l'essaye
                if(!used[k]) {
                    Piece piece = pieces[k];
                    config->placePiece(make_pair(piece.get_id(), 0));
                    // Bien placé ?
                    if(config->constraintColsXtrem(i, j) && config->constraintColsXtrem(i, j) && config->constraintEdges(i, j) && config->constraintAdjacences(i, j)) {
                        // Bien placé !
                        used[k] = true;
                        found = true;
                    } else {
                        config->removePiece();
                        // Tentative de rotation
                        for(int r=1 ; r<4 && !found; r++) {
                            config->placePiece(make_pair(piece.get_id(), r));
                            if(config->constraintColsXtrem(i, j) && config->constraintColsXtrem(i, j) && config->constraintEdges(i, j) && config->constraintAdjacences(i, j)) {
                                // Bien placé !
                                used[k] = true;
                                found = true;
                            } else config->removePiece();
                        }
                    }
                    // Si aucun de ces tests n'a fonctionné (found == false), on teste une autre pièce
                    // TODO BackTracking
                }
            }
        }
    }

    return config;
}
