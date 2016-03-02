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
    for(auto config : configurations) {
        int vic = Algorithm::vicinity(C, (*config));
        cout << vic << endl;
    }
}

// TODO fonction d'évaluation
int Algorithm::evaluation(Configuration & C) {
    int errors = 0;
    errors += C.constraintColsXtrem();
    errors += C.constraintRowsXtrem();
    errors += C.constraintEdges();

    return errors;
}

void Algorithm::local_search(const Instance * instance) {
    // Génération de configurations
    vector<Configuration *> configurations = Configuration::generateRandomConfigurations(instance, 1000);

#if DEBUG_CREATE_CONFIGS
    int i = 1;
    for(auto pC : configurations) {
        cout << "\tConfiguration n°" << i++ << endl;
        cout << (*pC) << endl;
    }
#endif

    int nb_eval = 0;
    // 1. Sélectionner une solution initiale x0 € X
    Configuration * x0 = configurations[0];
    // 2. x <- x0 (x est la solution courante)
    Configuration * x = x0;
    // 3. x* <- x (x* est la meilleure solution rencontrée au sens de f)
    Configuration * xEtoile = x;
    // 4. Tant que le critère d'arret n'est pas respecté faire

#if DEBUG_CREATE_CONFIGS
    vector<Configuration *> voisins = get_neighbours((*x0), configurations);
    i=1;
    for(auto pC : voisins) {
        cout << "\tVoisins n° " << i++ << endl;
        cout << (*pC) << endl;
    }
#endif

    while(nb_eval < 100) {
    // 5. Sélectionner une solution voisine x' ∈ N(x)

    }
}
