#ifndef __sampler_hpp_
#define __sampler_hpp_

#include <cstdlib>

class Sampler {
public:
    double* get_sample(int n=2);
};

#endif
