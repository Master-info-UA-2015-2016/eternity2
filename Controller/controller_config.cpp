#include "Model/configuration.h"
#include <algorithm>
#include <time.h>

using namespace std;

/**
 * Génération de configurations aléatoires à partir de l'instance
 * @param instance : Instance en question
 * @param limit : nombre de configuration-s généré-es
 * @return Configuration -s généré-es
 * @author FOURMOND Jérôme
 */
vector<Configuration*>& generateRandomConfiguration(Instance instance, int limit) {
    vector<Configuration*>& configurations= *(new vector<Configuration*>);

    srand(time(NULL));

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        vector<Piece>* remaining_pieces = instance.get_vectPieces();
        random_shuffle(remaining_pieces->begin(), remaining_pieces->end());
        int i_rot;
        Configuration* configuration = new Configuration();
        while(!remaining_pieces->empty()) {
            Piece p = remaining_pieces->back();
            remaining_pieces->pop_back();
            // Choix aléatoire de la rotation
            i_rot = rand() % 4;
            // Création de la pair
            pair<int, int> piece;
                piece.first = p.get_id();
                piece.second = i_rot;
            // Ajout de la pair
            configuration->placePiece(piece);
        }
        configurations.push_back(configuration);
    }

    return configurations;
}
