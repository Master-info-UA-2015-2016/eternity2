#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <algorithm>
#include <iterator>
#include "time.h"
#include "instance_model.h"

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
    std::vector<std::pair<int, int> > vectPosition;

public:

    /**
     * Constructeur
     */
    Configuration();
    /**
     * Construit une configuration par recopie d'une instance existante
     * @param instance Instance utilisée pour recopie de ses paramètres
     * @author Florian
     */
    Configuration(const Instance *instance);
    Configuration(const std::string& fileNameInstance);

    /*** Getters ***/

    std::vector<std::pair<int, int> >& getVectPosition() ;

    /**
     * Récupération de l'idée de la pièce en position (x, y)
     * (x*nbRows + y*nbCols - (x+y))
     * @param x : X
     * @param y : Y
     * @return position : int
     */
    const std::pair<int, int> & getPiece(int x, int y) const ;

    /**
     * Retourne la position dans le vecteur de positions de la piece P
     * @param p : Piece
     * @return position : p
     */
    int getPosition(const Piece &p) const;

    /**
     * @brief height
     * @return
     */
    int height()    const { return instance->height(); }
    /**
     * @brief width
     * @return
     */
    int width()     const { return instance->width(); }

    /**
     * Ajout d'une position
     * @param position
     */
    void placePiece(std::pair<int, int> piece){ vectPosition.push_back(piece); }

    /**
     * Vérifie que la forme de la configuration correspond à la taille de l'instance
     * @return vrai la configuration est bien formée
     */
    bool isValid() { return (unsigned)(instance->width()* instance->height()) == vectPosition.size(); }

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Configuration& r)
    { return r.print(out); }

    /**
      * Rotation d'une pièce.
      * @param tableau_motif nbRotation
      * @return tab_result
      * @author Ugo
      */
    int* rotate(const int* motif,int nbRotation);

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
    static std::vector<Configuration*>&  generateRandomConfigurations(Instance instance, int limit);

};

#endif // CONFIGURATION_H
