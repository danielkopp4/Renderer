#ifndef __brdf_hpp_
#define __brdf_hpp_

#include "radiance.hpp"
#include "sampler.hpp"
#include "ray.hpp"

class BRDF {
private:
    Radiance Kd;
    Radiance Ks; // for now we are just going to use the diffuse model
    // Radiance get_diffuse(const Ray &normal) const;
public:
    BRDF(Radiance Kd_=Radiance(1, 1, 1), Radiance Ks_=Radiance(1, 1, 1)) : Kd(Kd_), Ks(Ks_) {}

    Radiance get_albedo(const Ray &in, const Ray &out, const Vector &normal, double t) const {
        return Kd / 3.1415;
    }

    Ray generate_importance_sample(const Ray &in, double t, Sampler &sampler, const Vector &normal) const {
        // Lookup how to generate random sample on distribution
        Vector new_origin = in.get_origin() + in.get_direction() * t;
        Vector dy = normal;
        Vector dz;
        Vector dx;
        ons(dy, dx, dz);
        Vector random_direction = sampler.get_random_direction();
        Vector new_direction = dx * random_direction.get_x() + dy * random_direction.get_y() + dz * random_direction.get_z();
        return Ray(new_origin, new_direction);
    }  
};

#endif
