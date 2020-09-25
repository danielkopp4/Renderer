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
    Sphere(double radius_, Vector center_, Radiance emission_=Radiance(0, 0, 0), BRDF distrib_=BRDF()) : center(center_), radius(radius_) {
        emission = emission_;
        distrib = distrib_;
    }

    Radiance get_emission(const Ray& ray, double t) const;
    Intersection intersect(const Ray &ray) const;
    Vector get_normal(const Ray &ray, double t) const;
    Vector sample_light(Sampler &sampler) const;
    bool operator==(Object &other) const;
};

#endif
