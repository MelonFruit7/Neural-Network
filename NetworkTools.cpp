#include "NetworkTools.hpp"
#include <stdlib.h>
#include <time.h>


NetworkTools::NetworkTools() {
    srand(time(NULL));
}

double NetworkTools::random_value(double lower, double upper) {
    return ((double)rand()/RAND_MAX)*(upper-lower)+lower;
}