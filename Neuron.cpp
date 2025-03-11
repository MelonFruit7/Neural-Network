#include "Neuron.hpp"

Neuron::Neuron() {
    this->val = 0;
    this->bias = 0;
}

Neuron::Neuron(double val, double bias) {
    this->val = val;
    this->bias = bias;
}

void Neuron::add_connection(Neuron *n, double weight) {
    connection c;
    c.n = n;
    c.weight = weight;
    
    connections.push_back(c);
}