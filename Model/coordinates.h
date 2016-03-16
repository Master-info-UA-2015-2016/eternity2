#ifndef COORDINATES_H
#define COORDINATES_H

/**
 * Représentation d'une coordonnées
 */
class Coordinates
{

public:
	int col;
	int row;

public:
    /**
     * Constructeur
     * @param _x : int
     * @param _y : int
     * @author Florian David
     */
    Coordinates(int _x, int _y);
    /**
     * Constructeur par recopie
     * @param other : Coordonnées
     * @author Florian David
     */
    Coordinates(const Coordinates& other);
    /**
     * Surcharge opérateur
     * @param other
     * @return Valeur de test (booléenne)
     * @author Florian David
     */
    virtual bool operator==(const Coordinates& other) const;
	
};

#endif // COORDINATES_H
