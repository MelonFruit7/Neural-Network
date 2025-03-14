#include <iostream>
#include "Network.hpp"
#include "Neuron.hpp"
#include "TrainSet.hpp"

#include <fstream>
using std::cout;
using std::endl;

int reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

int main() {
    //Network Layer Sizes
    vector<int> layer_sizes = {28*28, 100, 50, 10};
    Network network(layer_sizes);

    //Input & Output
    vector<double> input(28*28, 0);
    vector<double> target(10, 0);


    //Training
    TrainSet set(layer_sizes[0], layer_sizes[layer_sizes.size()-1]);
    std::ifstream file ("MINST/train-images.idx3-ubyte", std::ios::binary);
    std::ifstream labels ("MINST/train-labels.idx1-ubyte", std::ios::binary);

    int magic_number=0;
    int number_of_images=0;
    int n_rows=0;
    int n_cols=0;
    file.read((char*)&magic_number,sizeof(magic_number)); 
    magic_number= reverseInt(magic_number);
    file.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images= reverseInt(number_of_images);
    file.read((char*)&n_rows,sizeof(n_rows));
    n_rows= reverseInt(n_rows);
    file.read((char*)&n_cols,sizeof(n_cols));
    n_cols= reverseInt(n_cols);

    labels.read((char*)&magic_number, sizeof(magic_number));
    labels.read((char*)&magic_number, sizeof(magic_number));

    for(int i=0;i<number_of_images;++i)
    {
        unsigned char temp=0;
        for(int r=0;r<n_rows;++r)
        {
            for(int c=0;c<n_cols;++c)
            {
                file.read((char*)&temp,sizeof(temp));
                input[r*n_rows + c] = temp;
            }
        }
        labels.read((char*)&temp, sizeof(temp));
        target = vector<double>(10, 0);
        target[temp] = 1;

        set.add_data(input, target);
    }
    network.train(set, 10, 20);


    //Testing
    int test_cases = 100000, passed = 0;
    // for (int i = 0; i < test_cases; i++) {
    //     double addition = 0;
    //     for (int j = 0; j < 4; j++) {
    //         input[j] = network.t.random_value(1, 5);
    //         addition += input[j];
    //     }
    //     vector<Neuron> output = network.calculate(input);
    //     if ((addition >= 10 && output[0].val > 0.9) || (addition < 10 && output[0].val < 0.1)) passed++;
    // }
    cout << "Test Cases: " << test_cases << endl;
    cout << "Passed: " << passed << "/" << test_cases << endl;
    // for (int i = 0; i < output.size(); i++) cout << output[i].val << endl;
    return 0;
}