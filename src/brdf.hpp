#ifndef __brdf_hpp_
#define __brdf_hpp_

#include "radiance.hpp"
#include "sampler.hpp"
#include "utils.hpp"
#include "ray.hpp"

#include <cmath>

class BRDF {
private:
    Radiance Kd;
    Radiance Ks; // for now we are just going to use the diffuse model
    bool spec;
    double sigma;
    // Radiance get_diffuse(const Ray &normal) const;
public:
    BRDF(Radiance Kd_=Radiance(1, 1, 1), Radiance Ks_=Radiance(1, 1, 1), bool spec_=false, double sigma_=0) : Kd(Kd_), Ks(Ks_), spec(spec_), sigma(sigma_) {}

    Radiance get_albedo(const Ray &in, const Ray &out, const Vector &normal, double t) const {
        if (spec) {
            Vector reflected_in = in.get_direction() - normal * (in.get_direction().dot(normal)) * 2;
            return Ks * ((1 - reflected_in.dot(out.get_direction())) < Utils::DOUBLE_EPS ? 1 : 0);
        }

        // double thetai = acos((in.get_direction() * -1).dot(normal));
        // double thetar = acos(out.get_direction().dot(normal));

        // double A = 1-0.5*(sigma*sigma / (sigma * sigma + 0.33));
        // double B = 0.45 * (sigma * sigma / (sigma * sigma + 0.09));
        // double alpha = thetai > thetar ? thetai : thetar;
        // double beta  = thetai > thetar ? thetar : thetai;


        return Kd / 3.1415;
    }

    Ray generate_importance_sample(const Ray &in, double t, Sampler &sampler, const Vector &normal) const {
        if (spec) {
            Vector point = in.get_origin() + in.get_direction() * t;
            Vector reflected_in = in.get_direction() - normal * (in.get_direction().dot(normal)) * 2;
            return Ray(point, reflected_in);
        }

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
