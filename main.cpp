#include <iostream>
#include "Network.hpp"
#include "Neuron.hpp"
using std::cout;
using std::endl;

int main() {
    //Network Layer Sizes
    vector<int> layer_sizes = {4, 8, 16, 1};
    Network network(layer_sizes);

    //Input & Output
    vector<double> input = {0.1, 0.5, 0.2, 0.9};
    vector<double> target = {1};


    //Training
    for (int i = 0; i < 100000; i++) {
        double addition = 0;
        for (int j = 0; j < 4; j++) {
            input[j] = network.t.random_value(0.1, 0.5);
            addition += input[j];
        }
        target[0] = addition >= 1 ? 1 : 0;

        network.train(input, target);
    }


    //Testing
    input = {0.1, 0, 0, 1};
    vector<Neuron> output = network.calculate(input);
    for (int i = 0; i < output.size(); i++) cout << output[i].val << endl;
    return 0;
}