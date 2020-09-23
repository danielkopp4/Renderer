#ifndef __sphere_hpp_
#define __sphere_hpp_

#include "object.hpp"
#include "vector.hpp"

class Sphere : public Object {
private:
    double radius;
    Vector center;
    double get_t(Ray ray) const;
public:
    Sphere(double radius_, Vector center_) : center(center_), radius(radius_) {}
    Intersection intersect(const Ray &ray) const;
};

#endif
