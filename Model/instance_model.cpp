#include "instance_model.h"

using namespace std;

Instance::Instance() :
    nbRows(0), nbCols(0)
{
    pieces = new vector<Piece>;
}

Instance::Instance(const Instance& instance) :
    nbRows(instance.nbRows), nbCols(instance.nbCols)
{
    pieces= new vector<Piece>( *(instance.get_pieces()) );
}


ostream& Instance::print(ostream& out){

    int nbPiece = nbRows * nbCols;

    for(int i=0; i < nbPiece; ++i){
        out << (pieces->at(i));
    }
    return out;
}

bool Instance::tryLoadFile(const string& fileName){

    ifstream f(fileName.c_str());

    if(!f){
        cerr << "Erreur pendant l'ouverture du fichier" << endl;
        return false;
    }else{
        string line;
        int indice = -1;
        while(getline(f,line)){

            vector<string>& tokens = explode(line);

            // Lecture de la première ligne renseignant nombre de lignes et nombre de colonnes
            if(indice < 0){
                /*
                 * tokens[0] : nombre de lignes
                 * tokens[1] : nombre de colonnes
                 */
                nbRows = atoi(tokens[0].c_str());
                nbCols = atoi(tokens[1].c_str());

            }else{
                /*
                 * tokens[0] : couleur Sud
                 * tokens[1] : couleur Ouest
                 * tokens[2] : couleur Nord
                 * tokens[3] : couleur Est
                 */
                PairColors tab[MAX_CARD];
                for(int i=0; i < MAX_CARD; ++i){
                    tab[i] = (PairColors)atoi(tokens[i].c_str());
                }
                Piece p(indice+1, tab); // Utiliser indice pour id = indice, indice+1 pour id = indice +1
                pieces->push_back(p);
            }
            ++indice;
            delete(&tokens);
            }
        }


    return true;

}

const Piece & Instance::getPiece(int id) const {
    return (*pieces)[id-1];
}
