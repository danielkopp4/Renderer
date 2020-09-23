#ifndef __object_hpp_
#define __object_hpp_

#include "intersection.hpp"
#include "ray.hpp"

class Intersection; // this looks gross please find another way

class Object {
private:
    // add stuff
public:
    // add stuff
    virtual Intersection intersect(const Ray& ray) const = 0;
    
};

#endif
