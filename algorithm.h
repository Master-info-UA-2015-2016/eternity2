#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Model/instance_model.h"
#include "Model/configuration.h"

#include <algorithm>
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

        /**
         * Fonction de voisinage
         * @param C1 : Configuration
         * @param C2 : Configuration
         * @return le nombre de pièces à des emplacements communs
         * @author FOURMOND Jérôme
         */
        static int vicinity(const Configuration & C1, const Configuration & C2);

        /**
         * Fonction d'évaluation
         * @param C : Configuration
         * @return le nombre d'erreur de la Configuration
         * @author FOURMOND Jérôme
         */
        static int evaluation(const Configuration & C);

        /**
         * Algorithme de recherche locale
         * @param instance : Instance
         * @author FOURMOND Jérôme
         */
        static void local_search(const Instance * instance);
};

#endif // ALGORITHM_H
