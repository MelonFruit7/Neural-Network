#include "NetworkTools.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
typedef long long ll;

NetworkTools::NetworkTools() {
    srand(time(NULL));
}

double NetworkTools::random_value(double lower, double upper) {
    return ((double)rand()/((ll)RAND_MAX+1))*(upper-lower)+lower;
}

int NetworkTools::index_of_largest(vector<Neuron> ns) {
    int idx = 0;
    for (int i = 1; i < ns.size(); i++) if (ns[i].val > ns[idx].val) idx = i;
    return idx;
}
int NetworkTools::index_of_largest(vector<double> ns) {
    int idx = 0;
    for (int i = 1; i < ns.size(); i++) if (ns[i] > ns[idx]) idx = i;
    return idx;
}

vector<int> NetworkTools::random_values(int lower_bound, int upper_bound, int amount) {
    if (amount > (upper_bound-lower_bound+1)) std::__throw_invalid_argument("No valid amount");

    vector<int> res;
    for (int i = 0; i < amount; i++) {
        int n = (int)random_value(lower_bound, upper_bound);
        while (std::find(res.begin(), res.end(), n) != res.end()) n = (int)random_value(lower_bound, upper_bound);
        res.push_back(n);
    }
    return res;
}