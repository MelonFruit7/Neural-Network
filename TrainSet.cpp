#include "TrainSet.hpp"

TrainSet::TrainSet(int INPUT_SIZE, int OUTPUT_SIZE) {
    this->INPUT_SIZE = INPUT_SIZE;
    this->OUTPUT_SIZE = OUTPUT_SIZE;
}

void TrainSet::add_data(vector<double> in, vector<double> target) {
    if (in.size() != INPUT_SIZE || target.size() != OUTPUT_SIZE) std::__throw_invalid_argument("Invalid sized arguments");
    data.push_back({in, target});
}

TrainSet TrainSet::extract_batch(int size) {
    if (size <= 0 || size > data.size()) std::__throw_invalid_argument("Invalid size");
    TrainSet set(INPUT_SIZE, OUTPUT_SIZE);
    vector<int> ids = t.random_values(0, data.size(), size);
    for (int id : ids) set.add_data(data[id][0], data[id][1]);
    return set;
}

int TrainSet::size() {
    return data.size();
}
vector<double>& TrainSet::get_input(int idx) {
    if (idx < 0 || idx > data.size()) std::__throw_invalid_argument("Invalid index");
    return data[idx][0];
}
vector<double>& TrainSet::get_output(int idx) {
    if (idx < 0 || idx > data.size()) std::__throw_invalid_argument("Invalid index");
    return data[idx][1];
}

string TrainSet::to_string() {
    string s = "TrainSet ["+std::to_string(INPUT_SIZE)+" ; "+std::to_string(OUTPUT_SIZE)+"]\n";
    for (int i = 0; i < data.size(); i++) {
        s += std::to_string(i)+":   [ ";
        for (int j = 0; j < data[i][0].size(); j++) s += std::to_string(data[i][0][j])+" ";
        s += "]  >-||-<  [ ";
        for (int j = 0; j < data[i][1].size(); j++) s+= std::to_string(data[i][1][j])+" ";
        s += "]";
    } 
    return s;
}
