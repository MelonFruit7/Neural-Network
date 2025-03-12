#pragma once
#include "Neuron.hpp"

class NetworkTools {
    public:
        NetworkTools();
        double random_value(double lower_bound, double upper_bound);
        int index_of_largest(vector<Neuron> ns);
};