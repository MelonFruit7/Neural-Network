#pragma once
#include <vector>
using std::vector;

class Neuron;

struct connection {
    Neuron *n;
    double weight;
};

class Neuron {
    public:
        double val, bias;
        vector<connection> connections;

        Neuron();
        Neuron(double val, double bias);
        void add_connection(Neuron *n, double weight);
};
