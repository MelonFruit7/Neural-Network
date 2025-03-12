#include "NetworkTools.hpp"
#include <stdlib.h>
#include <time.h>


NetworkTools::NetworkTools() {
    srand(time(NULL));
}

double NetworkTools::random_value(double lower, double upper) {
    return ((double)rand()/RAND_MAX)*(upper-lower)+lower;
}

int NetworkTools::index_of_largest(vector<Neuron> ns) {
    int idx = 0;
    for (int i = 1; i < ns.size(); i++) if (ns[i].val > ns[idx].val) idx = i;
    return idx;
}