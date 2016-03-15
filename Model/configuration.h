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
#include "coordinates.h"

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
    std::vector<std::pair<int, int> > ids_and_rots;

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

    /**
     * Récupération de l'ensemble des pièces
     * @return le vecteur de pièce de l'instance
     */
    const std::vector<Piece> * getPieces() const
        { return instance->get_pieces(); }
    /**
     * Récupération des ids et rotation des pièces
     * @return attribut ids_and_rots
     */
    const std::vector<std::pair<int, int> >& get_ids_and_rots() const
        {return ids_and_rots;}

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
     * Retourne les coordonnées de la case qui contient la pièce portant l'id
     * @param id : int
     * @return pair<int, int>
     */
    Coordinates& getPosition(int id) const;

    /*** Placement des pièces ***/
    /**
     * Ajout d'une position
     * @param position
     */
    void placePiece(std::pair<int, int> piece){ ids_and_rots.push_back(piece); }

    void placePiece(const Piece & piece, int rotation) { ids_and_rots.push_back(std::make_pair(piece.get_id(), rotation)); }

    /**
     * Retrait de la dernière position
     */
    void removePiece() { ids_and_rots.pop_back(); }

    /**
     * Mutateur de la position (x,y)
     * @param x : int
     * @param y : int
     * @param pos : pair<int, int>
     */
    void setPiece(int x, int y, std::pair<int, int> pos);

    /**
     * @brief permutation_two_pieces
     * @param indice_piece_1
     * @param indice_piece_2
     * @author GARNIER Antoine
     */
    int permutation_two_pieces(int piece1_x, int piece1_y, int piece2_x, int piece2_y);

    /*** Recherche des pièces ***/
    /**
     * Retourne la position dans le vecteur de positions de la piece P
     * @param p : Piece
     * @return position : p
     */
    int searchPosition(const Piece &p) const;

    /**
     * Récupération de la position dans le vecteur de positions de la pièce portant l'id
     * @param id : int
     * @return position : int
     */
    int searchPosition(const int id) const;

    /*** Recupération des motifs ***/
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

    /*** Affichage ***/

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Configuration& r)
    { return r.print(out); }

    /**
     * Rotation de la pièce en position (x,y) de 90, 180, 270, 360
     * @param x : int
     * @param y : int
     * @param degree :int - 0, 1, 2, 3
     */
    void rotatePiece(int x, int y, int degree);

    /**
     * Vérifie que la forme de la configuration correspond à la taille de l'instance
     * @return vrai la configuration est bien formée
     */
    bool isValid() { return (unsigned)(instance->get_width()* instance->get_height()) == ids_and_rots.size(); }

    /**
     * Chargement d'un graphe sous forme de matrice
     * à partir d'un fichier d'exemple
     * @param fileName
     * @return
     */
    bool tryLoadFile(const std::string& fileName);

    /**
     * @brief get_rotated_motifs
     * @param current_piece_indice
     * @return
     */
    PairColors* get_rotated_motifs(int piece_indice) const;

    /**
     * Récupère le motif Nord de la pièce au sud de la piece courante tournée
     *  piece sud de piece courante = position piece courante + width
     * @param current_piece_indice
     * @return la paire de couleurs au Nord de la pièce au Sud
     */
    PairColors& getNorthMotifSouthPiece(int current_piece_indice) const;
    /**
     * Récupère le motif Ouest de la pièce à l'Est de la piece courante tournée
     *  piece est de piece courante = position piece courante + 1
     * @param current_piece_indice
     * @return la paire de couleurs à l'Ouest de la pièce à l'Est
     */
    PairColors& getWestMotifEastPiece(int current_piece_indice) const;

    /**
     * TODO @AsCris COMMENTER !!
     * @param current_piece
     * @param neightboor_card : piece voisine de current_piece
     * @return La piece voisine de current_piece
     * @author GARNIER Antoine
     */
    const Piece& getClosePiece(int current_piece, Cardinal neightboor_card) const;

    /**
     * TODO @AsCris COMMENTER !!!
     * @param current_piece
     * @param motif_card : Motif de la piece voisine de la piece courante
     * @param neightboor_card : Cardinalite de la piece voisine de la piece courante a prendre en compte
     * @return La valeur du motif situé a la position card de la piece voisine de la piece courante
     * @author GARNIER Antoine
     */
    PairColors getMotifClosePiece(int current_piece, Cardinal neightboor_card, Cardinal motif_card) const;

    /**
     * Vérifie que 2 motifs s'appareillent
     * @param first_motif
     * @param second_motif
     * @return vrai si les 2 motifs sont identiques et ne sont pas noirs
     */
    static bool motifs_match(PairColors first_motif, PairColors second_motif);


    // ############################################## //
    // ############################################## //
    //
    //          Fonctions algorithmiques              //

    //  Définies dans configuration_functions.cpp
    // ############################################## //
    // ############################################## //
    /**
     * Récupération des ids des cases adjacents à la position (x, y)
     * @param x : int
     * @param y : int
     * @return int[4]
     */
    std::vector<std::pair<int, int>>& getAdjacents(int x, int y) const;

/*** GENERATION DE CONFIGURATIONS   ***/
    /**
     * Place une pièce, qui doit être un coin, dans un coin définit,
     *  tourne la pièce si nécessaire
     * @param p_id  id de la pièce
     * @param p_rot rotation de la pièce
     * @param col   colonne du coin (première ou dernière)
     * @param row   ligne du coin (première ou dernière)
     */
    bool placeCorner(int p_id, int col, int row);

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

/*** VERIFICATION DES CONTRAINTES   ***/

    /**
     * Compte des erreurs de contraintes de lignes extrèmes
     * @return int
     * @author FOURMOND Jérôme
     */
    int nbErrorsRowsXtrem() const;

    /**
     * La pièce située en (x,y) respecte-t-elle la contrainte de lignes extrèmes ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool areConstraintRowsXtremRespected(int x, int y) const;

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
    bool areConstraintColsXtremRespected(int x, int y) const;

    /**
     * Compte des erreurs de contraintes d'angles
     * @return int
     * @author FOURMOND Jérôme
     */
    int nbErrorsCorners() const;

    /**
     * La pièce située en (x,y) respecte-t-elle la contrainte d'angles ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérôme
     */
    bool areConstraintEdgesRespected(int x, int y) const;

    /**
     * Compte les erreurs de contraintes d'adjacences
     * @return int
     * @author FOURMOND Jérome
     */
    int nbErrorsAdjacences() const;

    /**
     * La pièce située en (x,y) s'accorde-t-elle correctement à ses voisins ?
     * @param x : int
     * @param y : int
     * @return boolean
     * @author FOURMOND Jérome
     */
    bool areConstraintAdjacencesRespected(int x, int y) const;

/*** VERIFICATION DES ERREURS   ***/
    /**
     * Verifie toutes les pièces de la configuration et compte le nombre d'erreurs
     * @return Le nombre d'erreurs dans la configuration
     * @author GARNIER Antoine
     */
    int countNbErrors() const;

    /**
     * Retourne le nombre de pièces mal placée
     * @return int
     */
    int misplacedPieces();

    /**
     * @brief pieces_match
     * @param indice_current_piece
     * @param direction_neightboor_piece : position de la piece voisin par rapport a la piece courante
     * @return true si les pieces sont bien emboitees
     * @author GARNIER Antoine
     */
    bool pieces_match(int indice_current_piece, Cardinal direction_neightboor_piece);

    /**
     * Compte le nombre d'erreurs qu'il y a avec la piece positions[indice] (de 0 à 4 possibles)
     * @return Le nombre d'erreurs de la piece indice (de 0 à 4 selon la position)
     * @author GARNIER Antoine
     */
    int getPieceNbErrors(const Piece &current_piece);

    /**
      * Compte le nombre d'erreurs d'une piece si on lui applique une certaine rotation
      * @return Le nombre d'erreurs lié à une piece ayant subit une rotation de val_rot
      * @author GARNIER Antoine
      */
    int isBestPlaced(int piece_id);


//    Essais d'ajout de pièce dans la configuration     //
    /**
     * Vérifie qu'une pièce peut-être placée à la fin de la liste de pièce
     * @param piece pièce que l'on essaie de placer
     * @param rotation valeur de rotation de la pièce, comprise entre 0 et 3
     * @return false si la pièce n'est pas appareible avec les pièces déjà présentes
     */
    bool canBePlaced(Piece& piece, int rotation) const;

    /**
     * Essai de placer une pièce à la suite des autres :
     *  vérifie qu'il y a de la place dans le plateau et  teste les 4 rotations
     * @param piece pièce à placer dans le plateau
     * @return false si on n'a pas réussi à placer la pièce
     */
    bool tryPlaceAtEnd(Piece& piece);
};

#endif // CONFIGURATION_H
