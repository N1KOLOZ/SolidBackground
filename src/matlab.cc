//
// Created by niko on 05.03.20.
//

#include "include/matlab.hh"

std::vector<double> mb::linespace(double x1, double x2, uint64_t n = 100) {
    std::vector<double> output(n);

    double step = (double) (x2- x1) / (n - 1);

    for(double &i : output) {
        i = x1;
        x1 += step;
    }

    return output;
}

