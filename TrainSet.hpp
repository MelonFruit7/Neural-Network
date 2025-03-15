#pragma once
#include <vector>
#include <string>
#include "NetworkTools.hpp"
using std::vector;
using std::string;

class TrainSet {
    private:
        int INPUT_SIZE;
        int OUTPUT_SIZE;

        vector<vector<vector<double>>> data;
    public:
        NetworkTools t;
        TrainSet(int INPUT_SIZE, int OUTPUT_SIZE);  
        void add_data(vector<double> in, vector<double> target);
        TrainSet extract_batch(int size);
        string to_string();

        int size();
        vector<double>& get_input(int idx);
        vector<double>& get_output(int idx);
};