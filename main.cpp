#include <iostream>
#include "Network.hpp"
#include "Neuron.hpp"
#include "TrainSet.hpp"

#include <fstream>
#include <algorithm>
#include <raylib.h>
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

void read_minst(TrainSet &s) {
    std::ifstream file ("MINST/train-images.idx3-ubyte", std::ios::binary);
    std::ifstream labels ("MINST/train-labels.idx1-ubyte", std::ios::binary);

    int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0;
    file.read((char*)&magic_number,sizeof(magic_number)); 
    magic_number= reverseInt(magic_number);
    file.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images= reverseInt(number_of_images);
    file.read((char*)&n_rows,sizeof(n_rows));
    n_rows= reverseInt(n_rows);
    file.read((char*)&n_cols,sizeof(n_cols));
    n_cols= reverseInt(n_cols);

    int label_magic_number=0, num_labels=0;
    labels.read((char*)&label_magic_number, sizeof(label_magic_number));
    labels.read((char*)&num_labels, sizeof(num_labels));

    int total_read = std::min(num_labels, number_of_images);
    vector<double> input(28*28, 0), target(10, 0);

    for(int i=0;i<total_read;++i)
    {
        unsigned char temp=0;
        for(int r=0;r<n_rows;++r)
        {
            for(int c=0;c<n_cols;++c)
            {
                file.read((char*)&temp,sizeof(temp));
                input[r*n_rows + c] = temp / 256.0;
            }
        }
        labels.read((char*)&temp, sizeof(temp));
        target = vector<double>(10, 0);
        target[temp] = 1;

        s.add_data(input, target);
    }
}

Image input_to_raylib_im(vector<double> &input) {
    Image im = GenImageColor(28, 28, WHITE);

    Color* pixels = (Color*)im.data;
    for (int i = 0; i < input.size(); i++) {
        u_char c = (u_char)(input[i] * 255.0);
        pixels[i] = (Color){c, c, c, 255};
    }

    return im;
}

int main() {
    //Network Layer Sizes
    vector<int> layer_sizes = {28*28, 100, 50, 10};
    Network network(layer_sizes);

    //Training
    TrainSet s(layer_sizes[0], layer_sizes[layer_sizes.size()-1]);
    read_minst(s);
    network.train(s, 50, 2000);


    //Testing
    int test_cases = 100000, passed = 0;
    cout << "Test Cases: " << test_cases << endl;
    cout << "Passed: " << passed << "/" << test_cases << endl;

   
    InitWindow(500, 500, "MINST");
    SetTargetFPS(60);

    int loops = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        if (loops % 60 == 0) {
            int test = (int)network.t.random_value(0, s.size());
            Image im = input_to_raylib_im(s.get_input(test));
            Texture2D texture = LoadTextureFromImage(im);

            DrawTexturePro(texture, {0, 0, 28, 28}, {0, 0, 500, 500}, {0, 0}, 0, WHITE);
            int res = network.t.index_of_largest(network.calculate(s.get_input(test)));
            string tex = std::to_string(res);
            DrawText(tex.c_str(), 0, 0, 48, GREEN);
            loops = 0;
        }
        EndDrawing();

        loops++;
    }
    CloseWindow();  
    return 0;
}