#pragma once
#include "Neuron.hpp"
#include "NetworkTools.hpp"
#include "TrainSet.hpp"
#include <vector>
using std::vector;

class Network {
    private:
        vector<vector<Neuron>> net;
        vector<int> NETWORK_LAYER_SIZES;
        int INPUT_SIZE;
        int NETWORK_SIZE;
        int OUTPUT_SIZE;
    public:
        NetworkTools t;
        Network(vector<int> NETWORK_LAYER_SIZES);
        vector<Neuron> calculate(vector<double> &input);
        void train(TrainSet &ts, int loops, int batch_size);
        void train(vector<double> &input, vector<double> &target);
        void backprop_error(vector<double> &target);
        void update_weights(double learning_rate);
};