#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "instance_model.h"

/**
 * Classe définissant une configuration, qui correspond à un ensemble
 * de position ( case, rotation ) pour une instance donnée. La classe
 * hérite d'instance car une instance peut disposer de plusieurs configurations
 * mais une configuration dépend d'une et une seule instance.
 * @author Ugo
 */


class Configuration : public Instance
{
private:
    std::vector<std::pair<int, int> > vectPosition;
public:

    /**
     * Constructeur
     */
    Configuration();

    /**
      * Getters
      */
    std::vector<std::pair<int, int> >& getVectPosition();

    /**
     * Récupération de l'idée de la pièce en position (x, y)
     * @param x : X
     * @param y : Y
     * @return position : int
     */
    std::pair<int, int> getPiece(int x, int y);

    /**
     * Retourne la position dans le vecteur de positions de la piece P
     * (x*nbRows + y*nbCols - (x+y))
     * @param p : Piece
     * @return position : p
     */
    int getPosition(Piece p);

    /**
     * Ajout d'une position
     * @param position
     */
    void addPosition(std::pair<int, int> position);

    bool isValid();
};

#endif // CONFIGURATION_H
