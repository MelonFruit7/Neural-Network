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
                net[i][j].bias = t.random_value(-1, 1); //Apply random bias
                for (int k = 0; k < NETWORK_LAYER_SIZES[i-1]; k++)
                    net[i][j].add_connection(&net[i-1][k], t.random_value(-1, 1)); //Add back connections
            }
        }
    }
}

vector<Neuron> Network::calculate(vector<double> &input) {
    if (input.size() != INPUT_SIZE) std::__throw_invalid_argument("Wrong input size");
    for (int i = 0; i < INPUT_SIZE; i++) net[0][i] = Neuron(input[i], 1.0f);

    //Perform forward pass
    for (int layer = 1; layer < NETWORK_SIZE; layer++) {
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer]; neuron++) {

            double sum = net[layer][neuron].bias;
            for (connection c : net[layer][neuron].con) 
                sum += c.n->val * c.weight;
            net[layer][neuron].val = sigmoid(sum);

            //Apply derivative of sigmoid function
            net[layer][neuron].val_derivative = net[layer][neuron].val * (1 - net[layer][neuron].val);
        }
    }  
    return net[NETWORK_SIZE-1]; 
}

void Network::train(TrainSet &ts, int loops, int batch_size) {
    for (int i = 0; i < loops; i++) {
        TrainSet t = ts.extract_batch(batch_size);
        for (int j = 0; j < batch_size; j++) train(t.get_input(j), t.get_output(j));
    }
}
void Network::train(vector<double> &input, vector<double> &target) {
    if (input.size() != INPUT_SIZE || target.size() != OUTPUT_SIZE) std::__throw_invalid_argument("Wrong input/target size");
    calculate(input);
    backprop_error(target);
    update_weights(0.3);
}

void Network::backprop_error(vector<double> &target) {
    for (int neuron = 0; neuron < OUTPUT_SIZE; neuron++) {
        //Loss function for output neurons
        net[NETWORK_SIZE-1][neuron].error_signal = (net[NETWORK_SIZE-1][neuron].val - target[neuron]) * net[NETWORK_SIZE-1][neuron].val_derivative;
    }
    for (int layer = NETWORK_SIZE-2; layer > 0; layer--) {
        //Set error loss to zero before changes are made
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer]; neuron++) net[layer][neuron].error_signal = 0;

        //Calculate error loss for prior nodes
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer+1]; neuron++) 
            for (connection c : net[layer+1][neuron].con) c.n->error_signal += c.weight * net[layer+1][neuron].error_signal;

        //Apply derivative for gradient descent
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer]; neuron++) net[layer][neuron].error_signal *= net[layer][neuron].val_derivative;
    }
} 

void Network::update_weights(double learning_rate) {
    for (int layer = 1; layer < NETWORK_SIZE; layer++) {
        for (int neuron = 0; neuron < NETWORK_LAYER_SIZES[layer]; neuron++) {
            for (connection &c : net[layer][neuron].con) {
                double delta = -learning_rate * c.n->val * net[layer][neuron].error_signal;
                c.weight += delta;
            }
            double delta = -learning_rate * net[layer][neuron].error_signal;
            net[layer][neuron].bias += delta;
        }
    }
}

void Network::save_network() {
    FILE *fp = fopen("network.dat", "wb");
    if (fp != NULL) {
        size_t sz = NETWORK_LAYER_SIZES.size();
        fwrite(&sz, sizeof(size_t), 1, fp);
        for (int i = 0; i < sz; i++) {
            fwrite(&NETWORK_LAYER_SIZES[i], sizeof(int), 1, fp);
            for (int j = 0; j < NETWORK_LAYER_SIZES[i]; j++) {
                fwrite(&net[i][j].bias, sizeof(double), 1, fp);
                if (i > 0) for (connection c : net[i][j].con) fwrite(&c.weight, sizeof(double), 1, fp);
            }
        }
        fclose(fp);
    }
}

void Network::load_network() {
    FILE *fp = fopen("network.dat", "rb");
    if (fp != NULL) {
        size_t sz; fread(&sz, sizeof(size_t), 1, fp);

        NETWORK_LAYER_SIZES.clear();
        net.clear();
        net = vector<vector<Neuron>>(sz);
        for (int i = 0; i < sz; i++) {
            int net_layer_size; fread(&net_layer_size, sizeof(int), 1, fp);
            net[i] = vector<Neuron>(net_layer_size);
            NETWORK_LAYER_SIZES.push_back(net_layer_size);
            for (int j = 0; j < NETWORK_LAYER_SIZES[i]; j++) {
                fread(&net[i][j].bias, sizeof(double), 1, fp);
                if (i > 0) {
                    for (int k = 0; k < NETWORK_LAYER_SIZES[i-1]; k++) {
                        double weight; fread(&weight, sizeof(double), 1, fp);
                        net[i][j].add_connection(&net[i-1][k], weight);
                    }
                }
            }
        }

        INPUT_SIZE = NETWORK_LAYER_SIZES[0];
        NETWORK_SIZE = NETWORK_LAYER_SIZES.size();
        OUTPUT_SIZE = NETWORK_LAYER_SIZES[NETWORK_SIZE-1];
        fclose(fp);
    }
}