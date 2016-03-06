#ifndef INSTANCE_H
#define INSTANCE_H

#include <fstream>

#include "piece.h"
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
private:
    int nbRows, nbCols;
    std::vector<Piece> *pieces;

public:

    /*** Constructeurs ***/
    Instance();

    /**
     * Constructeur par recopie
     * @param instance Instance à recopier
     * @author Florian
     */
    Instance(const Instance& instance);


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
    int height()    const { return nbRows; }
    int width()     const { return nbCols; }
    const std::vector<Piece>* get_pieces() const { return pieces; }

    void set_nbRows(int n) { nbRows = n; }
    void set_nbCols(int m) { nbCols = m; }

    /**
     * Récupération de la pièce qui porte l'id : id
     * @param id : l'id à rechercher
     * @return Piece
     */
    const Piece & getPiece(int id) const;
};

#endif // INSTANCE_H
