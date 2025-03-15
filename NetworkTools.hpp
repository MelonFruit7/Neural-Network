#pragma once
#include "Neuron.hpp"

class NetworkTools {
    public:
        NetworkTools();
        double random_value(double lower_bound, double upper_bound);
        vector<int> random_values(int lower_bound, int upper_bound, int amount);
        int index_of_largest(vector<Neuron> ns);
        int index_of_largest(vector<double> ns);
};