#ifndef INSTANCE_MODEL_H
#define INSTANCE_MODEL_H

#include "piece_model.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>

/**
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
class Instance
{
private:
    int nbRows, nbCols;
    std::vector<Piece> *vectPieces;

public:

    /**
     * Constructeurs
     */
    Instance();

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Instance& r)
    { return r.print(out); }

    /**
     * Chargement d'un graphe sous forme de matrice
     * à partir d'un fichier d'exemple
     * @param fileName
     * @return
     */
    bool tryLoadFile(const std::string& fileName);

    /**
     * Affichage par défaut sur terminal (print et <<)
     * initialisation avec lecture du fichier (explode et tryLoad)
     * Voir sur grapheMat du projet VisualGraph
     *
     */

    /**
     * Getters et Setters
     */
    int get_nbRows() { return nbRows; }
    int get_nbCols() { return nbCols; }
    const std::vector<Piece>* get_vectPieces() { return vectPieces; }

    void set_nbRows(int n) { nbRows = n; }
    void set_nbCols(int m) { nbCols = m; }




};

#endif // INSTANCE_MODEL_H
