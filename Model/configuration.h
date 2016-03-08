#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <algorithm>
#include <iterator>
#include <exception> // ??
#include <cassert>
#include <stdexcept>    // for out_of_range
#include <ctime>

#include "debug.h"

#include "instance.h"

#define id first
#define rot second

/**
 * Classe définissant une configuration, qui correspond à un ensemble
 * de position ( case, rotation ) pour une instance donnée. La classe
 * hérite d'instance car une instance peut disposer de plusieurs configurations
 * mais une configuration dépend d'une et une seule instance.
 * @author Ugo
 */
class Configuration
{
private:
    const Instance* instance;
    std::vector<std::pair<int, int> > positions;

public:
    /**
     * Construit une configuration par recopie d'une instance existante
     * @param instance Instance utilisée pour recopie de ses paramètres
     * @author Florian
     */
    Configuration(const Instance *instance = NULL);
    Configuration(const std::string& fileNameInstance);
    Configuration(const Configuration & C);

    /*** Getters ***/
    /**
     * @brief height
     * @return la hauteur du plateau (nombre de pièces verticalement)
     */
    int get_height()    const { assert(instance != NULL); return instance->get_height(); }
    /**
     * @brief width
     * @return la largeur du plateau (nombre de pièces horizontalement)
     */
    int get_width()     const { assert(instance != NULL); return instance->get_width(); }

    const std::vector<std::pair<int, int> >& getPositions() const
        {return positions;}

    /**
     * Récupération de la paire en position (x, y)
     * (x*nbRows + y*nbCols - (x+y))
     * @param x : X
     * @param y : Y
     * @return position : int
     */
    const std::pair<int, int> & getPair(int x, int y) const ;

    /**
     * Récupération de la pièce en position (x, y)
     * @param x : X
     * @param y : Y
     * @return Piece
     */
    const Piece & getPiece(int x, int y) const;

    /**
     * Récupération de la pièce portant l'id
     * @param id : int
     * @return Piece
     */
    const Piece & getPiece(int id) const;

    /**
     * Récupération de l'ensemble des pièces
     * @return vector<Piece *>
     */
    const std::vector<Piece> * getPieces() const
        { return instance->get_pieces(); }
    /**
     * Récupération du motif pivoté en position (x, y)
     * @param x : X
     * @param y : Y
     * @return int *
     */
    PairColors * getRotatedMotif(int x, int y) const;

    /**
     * Récupération du motif pivoté, selon son id
     * @return int *
     */
    PairColors * getRotatedMotif(int pos) const;

    /**
     * Retourne la position dans le vecteur de positions de la piece P
     * @param p : Piece
     * @return position : p
     */
    int getPosition(const Piece &p) const;

    /**
     * Récupération de la position dans le vecteur de positions de la pièce portant l'id
     * @param id : int
     * @return position : int
     */
    int getPosition(const int id) const;

    /**
     * Retourne les coordonnées de la case qui contient la pièce portant l'id
     * @param id : int
     * @return pair<int, int>
     */
    std::pair<int, int> getCase(int id) const;

    /**
     * Récupération des ids des cases adjacents à la position (x, y)
     * @param x : int
     * @param y : int
     * @return int[4]
     */
    std::vector<std::pair<int, int>> getAdjacent(int x, int y) const;

    /**
     * Ajout d'une position
     * @param position
     */
    void placePiece(std::pair<int, int> piece){ positions.push_back(piece); }

    /**
     * Retrait de la dernière position
     */
    void removePiece() { positions.pop_back(); }

    /**
     * Mutateur de la position (x,y)
     * @param x : int
     * @param y : int
     * @param pos : pair<int, int>
     */
    void setPiece(int x, int y, std::pair<int, int> pos);

    /**
     * Vérifie que la forme de la configuration correspond à la taille de l'instance
     * @return vrai la configuration est bien formée
     */
    bool isValid() { return (unsigned)(instance->get_width()* instance->get_height()) == positions.size(); }

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Configuration& r)
    { return r.print(out); }

    /**
     * Chargement d'un graphe sous forme de matrice
     * à partir d'un fichier d'exemple
     * @param fileName
     * @return
     */
    bool tryLoadFile(const std::string& fileName);

    /**
     * Création des placements aléatoires des pièces (nécessaire pour l'affichage)
     */
    void randomConfiguration();

    /**
     * Génération de configurations aléatoires à partir de l'instance
     * @param instance : Instance en question
     * @param limit : nombre de configuration-s généré-es
     * @return Configuration -s généré-es
     * @author FOURMOND Jérôme
     */
    static std::vector<Configuration*>&  generateRandomConfigurations(const Instance * instance, int limit);

    /**
     * Compte des erreurs de contraintes de lignes extrèmes
     * @return int
     * @author FOURMOND Jérôme
     */
    int constraintRowsXtrem() const;

    /**
     * La pièce située en (x,y) respecte-t-elle la contrainte de lignes extrèmes ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool isConstraintRowsXtremRespected(int x, int y) const;

    /**
     * Compte des erreurs de contraintes de colonnes
     * @return int
     * @author FOURMOND Jérôme
     */
    int constraintColsXtrem() const;

    /**
     * La pièce située en (x,y) respecte-t-elle la contrainte de colonnes extrèmes ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool isConstraintColsXtremRespected(int x, int y) const;

    /**
     * Compte des erreurs de contraintes d'angles
     * @return int
     * @author FOURMOND Jérôme
     */
    int constraintEdges() const;

    /**
     * La pièce située en (x,y) respecte-t-elle la contrainte d'angles ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool isConstraintEdgesRespected(int x, int y) const;

    /**
     * La pièce située en (x,y) s'accorde-t-elle correctement à ses voisins ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérome
     */
    bool isConstraintAdjacencesRespected(int x, int y) const;

    /**
     * @brief getNorthMotifSouthPiece
     * @param current_piece_indice
     * @return
     * TODO A REFAIRE, avec meilleures fonctions d'accès au motif pivoté
     */
    PairColors getNorthMotifSouthPiece(int current_piece_indice) const;
    /**
     * @brief getWestMotifEastPiece
     * @param current_piece_indice
     * @return
     * TODO A REFAIRE, avec meilleures fonctions d'accès au motif pivoté
     */
    PairColors getWestMotifEastPiece(int current_piece_indice) const;

    /**
     * Vérifie que 2 motifs s'appareillent
     * @param first_motif
     * @param second_motif
     * @return vrai si les 2 motifs sont identiques et ne sont pas noirs
     */
    bool motifs_match(PairColors first_motif, PairColors second_motif) const;

    /**
     * Verifie toutes les pièces de la configuration et compte le nombre d'erreurs
     * @return Le nombre d'erreurs dans la configuration
     * @author GARNIER Antoine
     * TODO renommer @Ascris (countNbErrors, nbMisplacedErrors, checkNbErrors ?)
     */
    int checkPieces() const;

    /**
     * Retourne le nombre de pièces mal placée
     * @return int
     */
    int misplacedPieces();

    /**
     * Compte le nombre d'erreurs qu'il y a avec la piece positions[indice] (de 0 à 4 possibles)
     * @return Le nombre d'erreurs de la piece indice
     * @author GARNIER Antoine
     */
    int getPieceNbErrors(int indice);

    /**
      * Compte le nombre d'erreurs d'une piece si on lui applique une certaine rotation
      * @return Le nombre d'erreurs lié à une piece ayant subit une rotation de val_rot
      * @author GARNIER Antoine
      */
    int isBestPlaced(int indice_piece, int val_rot);

};

#endif // CONFIGURATION_H
