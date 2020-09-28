#ifndef __sampler_hpp_
#define __sampler_hpp_

#include "vector.hpp"
#include <cstdlib>

class Sampler {
    unsigned int seed;
public:
    Sampler() { seed = time(NULL); }
    double* get_sample(int n=2);
    Vector get_random_sphere_direction();
    Vector get_random_direction();
};

#endif
