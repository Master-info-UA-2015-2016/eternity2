#ifndef STRING_TOOLS
#define STRING_TOOLS

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>


/**
 * Découpe une ligne du fichier et retourne chaque élément dans un tableau.
 * @param str chaine en entrée à découper
 * @return vecteur de chaine
 */
std::vector< std::string >& explode(const std::string& str);

#endif 
