#include "piece_model.h"

using namespace std;

Piece::Piece(int _id, int tab[]) :
    id(_id)
{
    for(int i=0; i<MAX_CARD; ++i){
        motif[i] = tab[i];
    }
}

ostream& Piece::print(ostream& out) const{
    out << "Pièce n° " << id << " : ";

    // Affichage des n-1 premières couleurs chacune suivie d'un espace
    for(int i = 0; i < MAX_CARD-1; ++i)
        out << motif[i] << " ";

    // Affichage de la n-ième couleur suivie d'un ; et d'un saut de ligne
    out << motif[MAX_CARD-1] << ";" << endl;

    return out;
}
