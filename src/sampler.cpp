#include "sampler.hpp"

double* Sampler::get_sample(int n) {
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = double(rand()) / RAND_MAX;
    }
    return arr;
}