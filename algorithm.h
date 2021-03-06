#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>
#include <cassert>
#include <vector>

#include "debug.h"
#include "Model/instance.h"
#include "Model/configuration.h"
#include "Model/board.h"

typedef std::pair<Piece, int> PieceRot ;

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
         * Récupération du premier voisin améliorant de la configuration
         * @param config : Configuration
         * @return Configuration
         * @author FOURMOND Jérome
         */
        static Configuration * getFirstBetterNeighbour(const Configuration & config);

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
        static int evaluation(const Configuration & C);

        /**
         * Algorithme de recherche locale
         * @param instance : Instance
         * @author FOURMOND Jérôme
         */
        static Configuration * local_search(const Configuration * config);

        /*** Programmation par contrainte ***/
        /**
         * Initalise le CSP : place la première pièce et retourne les pièces à ajouter
         * @param config Configuration vide, à remplir
         * @return
         */
        static std::list<Piece>* initCSP(Configuration* config);
        /**
         * Cherche les pièces pouvant aller à une position donnée
         * @param config Configuration sur laquelle on travaille (courante)
         * @param col abscisse
         * @param row ordonnée
         * @return la liste des pièces pouvant aller sur la position donnée
         */
//        static Piece* tryNextValidPiece(Configuration * config, std::list<Piece>* availables, int nbToCheck, int col, int row);
        /**
         * Cherche les pièces pouvant aller à une position donnée
         * @param config Configuration sur laquelle on travaille (courante)
         * @return la liste des pièces pouvant aller sur la position donnée
         */
        static std::list< PieceRot > *getValidPieces(Configuration * config, std::list<Piece>* availables);
        /**
         * Effectue un chainage avant (récursif)
         * @param config Configuration sur laquelle on travaille (courante)
         * @param valids Pièce allant à la position courante
         * @return la configuration finale si il y a une trouvée NULL sinon
         */
        static Configuration* forwardCheck(Configuration * config, std::list<Piece>* availables);
        /**
         * Place toutes les pièces restantes dans la config
         * @param config    Configuration à remplir
         * @param remainingPieces   Pièces à placer dans la configuration
         */
        static void placeWithoutConstraints(Configuration* config, std::list<Piece>* remainingPieces);
        /**
         * Resolution CSP
         * @param instance
         * @return
         */
        static Configuration* resolveWithCSP(const Instance * instance);

        /*** Génétique ***/

        /**
         * Retourne l'indice de la configuration ayant le moins d'erreurs dans new_generation
         * @param new_generation
         * @return l'indice de la meilleure configuration dans new_generation
         */
        static int getBestConfig(std::vector<Configuration *> new_generation);

        /**
         * Fabrique 2 enfants a partir des 2 parents et ajoute a la liste d'enfants
         * @param children
         * @param parent1
         * @param parent2
         */
        static void add_child(std::vector<Configuration*>& children, Configuration* parent1, Configuration* parent2);

        /**
         * A partir de 2 parents, fabrique des configurations "fils" et "fille" pour la nouvelle generation
         * @note Fonction de croisement
         * @param parent1
         * @param parent2
         * @return les configurations fils et fille issues du croisement des 2 parents
         */
        static std::pair<Configuration*, Configuration*> make_children(Configuration* parent1, Configuration* parent2);

        /**
         * Creation de "nb_config" Configurations à partir de l'instance "instance"
         * @param instance
         * @param nb_config : nombre de configurations voulues
         * @return
         */
        static std::vector<Configuration*> initGenetic(const Instance * instance, int nb_config);

        /**
         * Algorithme de recherche genetique
         * @param configs = un ensemble de configurations (generation actuelle - parents)
         * @return un ensemble de configurations (nouvelle generation)
         */
        static std::vector<Configuration *> geneticSearch(std::vector<Configuration *> configs);
};

#endif // ALGORITHM_H
