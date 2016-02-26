#ifndef INSTANCE_MODEL_H
#define INSTANCE_MODEL_H

#include <fstream>

#include "piece_model.h"
#include "Tools/string_tools.h"

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
protected:
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
     * Getters et Setters
     */
    int height() { return nbRows; }
    int width() { return nbCols; }
    std::vector<Piece>* get_vectPieces() { return vectPieces; }

    void set_nbRows(int n) { nbRows = n; }
    void set_nbCols(int m) { nbCols = m; }




};

#endif // INSTANCE_MODEL_H
