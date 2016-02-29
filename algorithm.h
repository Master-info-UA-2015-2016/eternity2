#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Model/instance_model.h"
#include "Model/configuration.h"

#include <vector>

/**
 * Contient les différentes algorithmes implémentés pour la résolution du
 * problème
 *  - Recherche locale
 */
class Algorithm
{
    public:
        Algorithm();

        static void local_search(const Instance * instance);
};

#endif // ALGORITHM_H
