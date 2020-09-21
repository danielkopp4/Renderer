#ifndef __intersection_hpp_
#define __intersection_hpp_

#include "object.hpp"

class Intersection {
private:
    double t;
    Object* object;
public:
    Intersection() : t(inf), object(nullptr) {}
    Intersection(double t_, Object* object_) : t(t_), object(object_) {}
    bool isIntersection() { return object != nullptr; }
};

#endif
