#include "sampler.hpp"
#include <cmath>

double* Sampler::get_sample(int n) {
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = double(rand()) / RAND_MAX;
    }
    return arr;
}

Vector Sampler::get_random_direction() {
    Vector dir = get_random_sphere_direction();

    dir[1] = fabs(dir[1]); // only returns a hemisphere
    dir.normalize(); // probably remove but idk
    return dir;
}

Vector Sampler::get_random_sphere_direction() {
    Vector dir;
    double* sample = get_sample(dir.size());
    for (int i = 0; i < dir.size(); ++i) {
        dir[i] = sample[i] - 0.5;
    }
    return dir;
}