#include <iostream>
#include "Network.hpp"
#include "Neuron.hpp"
using std::cout;
using std::endl;

int main() {
    vector<int> layer_sizes = {2, 2};
    Network network(layer_sizes);
    vector<double> input = {0.4, 0.3};


    vector<Neuron> output = network.calculate(input);
    for (int i = 0; i < output.size(); i++) cout << output[i].val << endl;
    return 0;
}