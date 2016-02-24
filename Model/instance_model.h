#ifndef INSTANCE_MODEL_H
#define INSTANCE_MODEL_H

#include "piece_model.h"
#include "vector"
#include "string"

using namespace std;

/*
 * Classe définissant une instance de puzzle eternity2 à partir
 * d'un fichier source dont on suppose à l'heure actuelle qu'il
 * est bien formé.
 *
 * Une instance est représenté par l'ensemble des pièces composant
 * le puzzle, ainsi que par le nombre de lignes et de colonnes du
 * plateau de jeu.
 *
 * @author Ugo
 */
class instance_model
{
private:
    int nbRows, nbCols;
    vector<piece_model> *vectPieces;

public:

    /*
     * Constructeurs
     */
    instance_model();
    instance_model(string filename); // TODO

    /*
     * Affichage par défaut sur terminal (print et <<)
     * initialisation avec lecture du fichier (explode et tryLoad)
     * Voir sur grapheMat du projet VisualGraph
     *
     */

    /*
     * Getters et Setters
     */
    int get_nbRows() { return nbRows; }
    int get_nbCols() { return nbCols; }
    const vector<piece_model>* get_vectPieces() { return vectPieces; }

    void set_nbRows(int n) { nbRows = n; }
    void set_nbCols(int m) { nbCols = m; }




};

#endif // INSTANCE_MODEL_H
