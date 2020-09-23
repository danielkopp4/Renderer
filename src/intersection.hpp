#ifndef __intersection_hpp_
#define __intersection_hpp_

#include "object.hpp"
#include <limits.h>
#include<cmath>

class Object;

class Intersection {
private:
    double t;
    const Object* object;
public:
    Intersection() : t(INT_MAX), object(nullptr) {}
    Intersection(double t_, const Object* object_) : t(t_), object(object_) {}
    bool isIntersection() { return object != nullptr; } // NO CAMEL CASE PLS CHANGE
    double get_t() const { return t; }
    const Object& get_object() const { return *object; }
};

#endif
