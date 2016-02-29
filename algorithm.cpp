#include "algorithm.h"

using namespace std;

Algorithm::Algorithm()
{

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
