#include "algorithm.h"

using namespace std;

Algorithm::Algorithm()
{}

int Algorithm::vicinity(const Configuration & C1, const Configuration & C2) {
    assert(C1.getPositions().size() == C2.getPositions().size());
    int vicinity = 0;

    for(unsigned int i=0 ; i<C1.getPositions().size() ; i++) {
        if(C1.getPositions().at(i).first == C2.getPositions().at(i).first)
            vicinity++;
    }
    return vicinity;
}

vector<Configuration *> Algorithm::get_neighbours(Configuration & C, vector<Configuration *> configurations) {
    vector<Configuration *> neightbours;
    int i = 0;
    int vic_max = 0;
    for(auto config : configurations) {
        int vic = Algorithm::vicinity(C, (*config));
        if(vic != C.width()*C.height()) {
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

// TODO fonction d'évaluation
int Algorithm::evaluation(Configuration & C) {
    int errors = 0;

    errors = C.checkPieces();

//    errors += C.constraintColsXtrem();
//    errors += C.constraintRowsXtrem();
//    errors += C.constraintEdges();
//    errors = C.constraintPieces();

    return errors;
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
