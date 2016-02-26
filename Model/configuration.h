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
    std::vector<std::pair<int, int>> vectPosition;
public:

    /**
     * Constructeur
     */
    Configuration();

    /**
      * Getters et Setters, ne pas hésiter à en faire plein
      */
};

#endif // CONFIGURATION_H
