#include "Network.hpp"
#include <cmath>
#include <time.h>

#define DEFAULT_NETWORK {2, 2}


double sigmoid(double x) {
    return 1.0/(1+exp(-x));
}

Network::Network(vector<int> NETWORK_LAYER_SIZES = DEFAULT_NETWORK) {
    this->NETWORK_LAYER_SIZES = NETWORK_LAYER_SIZES;
    INPUT_SIZE = NETWORK_LAYER_SIZES[0];
    NETWORK_SIZE = NETWORK_LAYER_SIZES.size();
    OUTPUT_SIZE = NETWORK_LAYER_SIZES[NETWORK_SIZE-1];

    net = vector<vector<Neuron>>(NETWORK_SIZE);
    for (int i = 0; i < NETWORK_SIZE; i++) {
        net[i] = vector<Neuron>(NETWORK_LAYER_SIZES[i]);

        //Calculate random start weights
        if (i > 0) {
            for (int j = 0; j < net[i].size(); j++) {
                net[i][j].bias = t.random_value(0.3, 0.7);
                for (int k = 0; k < net[i-1].size(); k++) {
                    net[i][j].add_connection(&net[i-1][k], t.random_value(-0.3, 0.5));
                }
            }
        }
    }
}

vector<Neuron> Network::calculate(vector<double> input) {
    if (input.size() != INPUT_SIZE) std::__throw_invalid_argument("Wrong input size");
    for (int i = 0; i < INPUT_SIZE; i++) net[0][i] = Neuron(input[i], 1.0f);
    for (int layer = 1; layer < NETWORK_SIZE; layer++) {
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer]; neuron++) {

            double sum = net[layer][neuron].bias;
            for (connection c : net[layer][neuron].connections) 
                sum += c.n->val * c.weight;
            net[layer][neuron].val = sigmoid(sum);
        }
    }  
    return net[NETWORK_SIZE-1]; 
}
