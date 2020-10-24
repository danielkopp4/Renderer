#include "sampler.hpp"
#include <cmath>
#include <random>
#include <thread>
#include <chrono>

double* Sampler::get_sample(int n) {
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        // arr[i] = double(rand()) / RAND_MAX;
        // std::cout << (2.0*(double)rand_r(&seed)/RAND_MAX-1.0) << std::endl;
        while (in_use) {
            // std::cout << "in use" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // reduce this time
        }
        in_use = true;
        arr[i] = std::abs(2.0*(double)rand_r(&seed)/RAND_MAX-1.0);
        in_use = false;
    }
    return arr;
}

Vector Sampler::get_random_direction() {
    Vector dir = get_random_sphere_direction();

    dir[1] = fabs(dir[1]); // only returns a hemisphere
    dir.normalize(); // probably remove but idk
    return dir;
}

Vector Sampler::get_random_sphere_direction() { // change to unifrm sampling (take the cos and sin of random numbers)
    Vector dir;
    double* sample = get_sample(dir.size());
    for (unsigned int i = 0; i < dir.size(); ++i) {
        dir[i] = sample[i] - 0.5;
    }
    return dir;
}