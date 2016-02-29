#include "configuration.h"

using namespace std;


Configuration::Configuration() :
    instance()
{

}

Configuration::Configuration(const Instance& _instance)
{
    instance = new Instance(_instance);
}

Configuration::Configuration(const string& fileName)
{
    instance = new Instance();
    if (!instance->tryLoadFile(fileName)){
        cerr << "Impossible de charger le fichier " << fileName << endl;
        exit(EXIT_FAILURE);
    }
}

vector<pair<int, int> >& Configuration::getVectPosition() {
    return vectPosition;
}

const pair<int, int>& Configuration::getPiece(int x, int y) const {
    const pair<int, int>& position = vectPosition[ x *instance->height() + y *instance->width() - (x +y)];
    return position;
}

int Configuration::getPosition(const Piece& p) const {
    bool found = false;
    int ind = 0;
    while(!found) {
        if(vectPosition[ind].first == p.get_id())
            found = true;
        else ind++;
    }
    return ind;
}

ostream& Configuration::print(ostream& out){
    const int* swne;

    for(int i=1; i <= instance->width(); ++i){
        for(int j = 1; j <= instance->height(); ++j){

            out << "Case " << i << "," << j << " : " <<
                   getPiece(i, j).first << " .SONE : ";

            /*
            if(getPiece(i,j).second != 0 ){
                swne = rotate(instance->get_vectPieces()->at(i+j-2).get_motif(), getPiece(i,j).second );
            }*/

            for(int l=0; l<MAX_CARD; ++l){
                out << swne[l] << " ; ";
            }
            out << endl;
        }
    }
    return out;

}

int* Configuration::rotate(int* motif,int nbRotation){
    int* tmp = new int;
    copy(motif, motif+4, tmp);

    cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << endl;

    cout << "Rotation" << endl;

    std::rotate(tmp, tmp+nbRotation , tmp+4);

    cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << endl;

    return tmp;
}

bool Configuration::tryLoadFile(const string &fileName){

    if( instance->width() * instance->height() == 0){
        cerr << "Aucune instance n'est chargée" << endl;
        return false;
    }else{
        ifstream f(fileName.c_str());

        if(!f){
            cerr << "Erreur pendant l'ouverture du fichier" << endl;
            return false;
        } else {

            string line;

            while(getline(f,line)){

                vector<string>& tokens = explode(line);

                vectPosition.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(vectPosition.size() != (unsigned)(instance->width() * instance->height()) ){
                cerr << "Fichier de configuration incomplet" << endl;
                return false;
            } else {
                return true;
            }

        }
    }
}

void Configuration::randomConfiguration() {
    int i_rot;
    srand(time(NULL));
    vector<int> pieces_id;

    // Travail uniquement sur l'id des pieces
    for(const Piece & p : *(instance->get_vectPieces()) ) {
        pieces_id.push_back(p.get_id());
    }
    // Mélange aléatoire
    random_shuffle(pieces_id.begin(), pieces_id.end());

    while(!pieces_id.empty()) {
        // Récupération de la pièce (id)
        int p = pieces_id.back();
        pieces_id.pop_back();
        // Choix aléatoire de la rotation
        i_rot = rand() % 4;
        pair<int, int> piece;
            piece.first = p;
            piece.second = i_rot;
        // Ajout de la pair
        placePiece(piece);
    }
}

vector<Configuration*>&  Configuration::generateRandomConfigurations(Instance instance, int limit) {
    vector<Configuration*>& configurations= *(new vector<Configuration*>);

    srand(time(NULL));

    for(int ind_conf=0 ; ind_conf < limit ; ind_conf++) {
        Configuration* configuration= new Configuration(instance);
        configuration->randomConfiguration();

        cout << configuration->instance->width() << endl;
        configurations.push_back(configuration);
    }

    return configurations;
}
