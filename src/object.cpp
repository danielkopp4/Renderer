#include "object.hpp"
#include "intersection.hpp"

Intersection Object::intersect(const Ray& ray) const {
    return Intersection(10, this);
}