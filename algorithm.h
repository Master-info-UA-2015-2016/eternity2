#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>
#include <cassert>
#include <vector>

#include "debug.h"
#include "Model/instance.h"
#include "Model/configuration.h"
#include "Model/board.h"

/**
 * Contient les différentes algorithmes implémentés pour la résolution du
 * problème
 *  - Recherche locale
 */
class Algorithm
{
    public:

        /**
         * Fonction de voisinage
         * @param C1 : Configuration
         * @param C2 : Configuration
         * @return le nombre de pièces à des emplacements communs
         * @author FOURMOND Jérôme
         */
        static int vicinity(const Configuration & C1, const Configuration & C2);
        /**
         * Récupère un voisin,@SEE pour l'instant, il n'y a pas de paramètre définissant
         * la proximité
         * @param C configuration pour laquelle on désire obtenir un voisin
         * @return
         */
        static Configuration * getNeighbour(const Configuration & config );

        /**
         * Récupération des voisins de la Configuration C
         * @param C : Configuration
         * @param configurations : vector<Configuration *> l'ensemble des Configurations
         * @return les voisins de la Configuration C
         * @author FOURMOND Jérôme
         */
        static std::vector<Configuration *> get_neighbours(Configuration & C, std::vector<Configuration * > configurations);

        /**
         * Fonction d'évaluation
         * @param C : Configuration
         * @return le nombre d'erreur de la Configuration
         * @author FOURMOND Jérôme
         */
        static int evaluation(Configuration & C);

        /**
         * Algorithme de recherche locale
         * @param instance : Instance
         * @author FOURMOND Jérôme
         */
        static Configuration * local_search(const Configuration * config);

        /**
         * Algorithme de contruction de Configuration
         * d'après la programmation par contrainte (CCP)
         * @param instance : Instance
         * @return Configuration "solution"
         */
        static Configuration * build_Configuration(const Instance * instance);
};

#endif // ALGORITHM_H
