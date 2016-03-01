#include "algorithm.h"

using namespace std;

Algorithm::Algorithm()
{}

int Algorithm::vicinity(const Configuration & C1, const Configuration & C2) {
//    assert(C1.getVectPosition().size() == C2.getVectPosition().size());

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
