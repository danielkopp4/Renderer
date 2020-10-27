#ifndef __plane_hpp_
#define __plane_hpp_

#include "object.hpp"
#include "ray.hpp"
#include "vector.hpp"

class Plane : public Object {
protected:
    Vector point;    
    Vector normal;
    double get_t(const Ray &ray) const;
public:
    Plane(Vector point_, Vector normal_=Vector(0,1,0), BRDF distrib_=BRDF(), Radiance emission_=Radiance()) : point(point_), normal(normal_.normalize()) {
        distrib = distrib_;
        emission = emission_;
    } 

    // virtual Object* clone() const;

    Radiance get_emission(const Ray &ray, double t) const;
    virtual Intersection intersect(const Ray & ray) const;
    Vector get_normal(const Ray &ray, double t) const { return normal; }
    virtual Vector sample_light(Sampler &sampler) const;
    virtual bool is_equal(Object &other) const;
};

#endif
