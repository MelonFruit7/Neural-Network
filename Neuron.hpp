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
        double error_signal, val_derivative;
        vector<connection> con;

        Neuron();
        Neuron(double val, double bias);
        void add_connection(Neuron *n, double weight);
};
