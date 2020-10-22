#ifndef __object_hpp_
#define __object_hpp_

#include "intersection.hpp"
#include "radiance.hpp"
#include "ray.hpp"
#include "brdf.hpp"

#include <iostream> // REMOVE


class Intersection; // this looks gross please find another way

class Object {
protected:
    Radiance emission;
    BRDF distrib;
public:
    virtual Object* clone() const = 0;
    virtual Intersection intersect(const Ray& ray) const = 0;
    virtual Vector get_normal(const Ray& in, double t) const = 0;
    virtual Radiance get_emission(const Ray &ray, double t) const = 0;
    Radiance brdf(const Ray &in, const Ray &out, double t) const { 
        // std::cout << "scale: " << fabs((in.get_direction() * -1).dot(get_normal(in, t))) << std::endl; 
        // std::cout << in.get_direction() << " in dir" << std::endl;
        // std::cout << get_normal(in, t) << " normal" << std::endl;
        Radiance ret = (distrib.get_albedo(in, out, get_normal(in, t), t) * ((in.get_direction() * -1).dot(get_normal(in, t)))); // need to remove the lambertian when it is specular
        return ret.clamp();
        // return   (distrib.get_albedo(in, out, get_normal(in, t), t) * ((in.get_direction() * -1).dot(get_normal(in, t)))).abs()
    }
    virtual Vector sample_light(Sampler &sampler) const = 0;

    virtual bool is_equal(Object &other) const = 0;
    Ray importance_sample(const Ray &in, double t, Sampler& sampler) const { return distrib.generate_importance_sample(in, t, sampler, get_normal(in, t)); } 
};

#endif
