#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "instance_model.h"

/**
 * Classe définissant une configuration, qui correspond à un ensemble
 * de position ( case, rotation ) pour une instance donnée. La classe
 * hérite d'instance car une instance peut disposer de plusieurs configurations
 * mais une configuration dépend d'une et une seule instance.
 *
 * @brief The Configuration class
 * @author Ugo
 */


class Configuration : public Instance
{
private:
    std::vector< std::pair <int, int> > vectPosition;
public:

    /**
     * Constructeur
     */
    Configuration();

    /**
      * Getters et Setters, ne pas hésiter à en faire plein
      */

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Configuration& r)
    { return r.print(out); }

    /**
      * Charge une configuration à partir d'un fichier source.
      * @param filePath
      * @return bool
      */
     bool tryLoadFile(const std::string& fileName);

     /**
      * Rotation de la pièce.
      * On décalera simplement la valeur de chaque case d'un rang vers la
      * droite. Ainsi, on effectuera systématiquement une rotation horaire.
      *
      */
     int* rotate(int* motif, int nbRotation); // 1, 2, 3
};

#endif // CONFIGURATION_H
