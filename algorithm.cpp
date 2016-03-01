#include "algorithm.h"

using namespace std;

Algorithm::Algorithm()
{}

int Algorithm::vicinity(const Configuration & C1, const Configuration & C2) {
    assert(C1.getPositions().size() == C2.getPositions().size());
    int vicinity = 0;

    for(unsigned int i=0 ; i<C1.getPositions().size() ; i++) {
        if(C1.getPositions().at(i).first == C2.getPositions().at(i).first)
            vicinity++;
    }
    return vicinity;
}

int Algorithm::evaluation(const Configuration &C) {

}

void Algorithm::local_search(const Instance * instance) {
    vector<Configuration *> configurations = Configuration::generateRandomConfigurations(instance, 10);

   int i = 1;
   for(auto C : configurations) {
       cout << "Configuration n°" << i << endl;
       cout << (*C) << endl;
       i++;
   }
}
