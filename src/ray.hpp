#ifndef __ray_hpp_
#define __ray_hpp_

#include "vector.hpp"

class Ray {
private:
    Vector origin;
    Vector direction;
public:
    Ray(const Vector& origin_, const Vector& direction_) : origin(Vector(origin_)), direction(Vector(direction_).normalize()) {}

    const Vector& get_origin() const { return origin; }
    const Vector& get_direction() const { return direction; }

    void set_origin(const Vector& origin_) { origin = Vector(origin_); }
    void set_direction(const Vector& direction_) { direction = Vector(direction_).normalize(); }

    Vector atT(double t) { return direction * t + origin; }
};

#endif
