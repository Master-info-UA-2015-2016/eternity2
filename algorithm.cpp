#include "algorithm.h"

using namespace std;

Algorithm::Algorithm()
{

}

void Algorithm::local_search(Instance instance) {
    vector<Configuration *> configurations = Configuration::generateRandomConfigurations(instance, 10);

    int i = 0;
    for(auto C : configurations) {
        cout << "Configuration n°" << i;
        cout << (*C) << endl;
        i++;
    }
}
