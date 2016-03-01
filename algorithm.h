#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Model/instance_model.h"
#include "Model/configuration.h"

#include <assert.h>
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

        int vicinity(const Configuration & C1, const Configuration & C2);

        static void local_search(const Instance * instance);
};

#endif // ALGORITHM_H
