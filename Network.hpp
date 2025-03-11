#pragma once
#include "Neuron.hpp"
#include "NetworkTools.hpp"
#include <vector>
using std::vector;

class Network {
    private:
        NetworkTools t;
        vector<vector<Neuron>> net;
        vector<int> NETWORK_LAYER_SIZES;
        int INPUT_SIZE;
        int NETWORK_SIZE;
        int OUTPUT_SIZE;
    public:
        Network(vector<int> NETWORK_LAYER_SIZES);
        vector<Neuron> calculate(vector<double> input);
};