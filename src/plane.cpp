#include "plane.hpp"
#include "intersection.hpp"

#include <cmath>

double Plane::get_t(const Ray &ray) const {
    if (ray.get_direction().dot(normal) == 0) {
        return -1;
    }

    return -((normal.dot(ray.get_origin() - point)) / (normal.dot(ray.get_direction())));
}

Intersection Plane::intersect(const Ray &ray) const {
    double t = get_t(ray);

    if (t == -1) {
        return Intersection();
    } else {
        return Intersection(t, this); // Move implementation to Object class
    }
}

Vector Plane::sample_light(Sampler &sampler) const {
    int cutoff = 10000;
    // Initialize this at the beginning
    Vector dy = normal;
    Vector dx;
    Vector dz;
    ons(dy, dx, dz);
    double* sample = sampler.get_sample();
    return (dx * sample[0] + dz * sample[1]) * cutoff;
}

Radiance Plane::get_emission(const Ray &ray, double t) const {
    return (emission * (ray.get_origin() * -1).dot(normal));
}

bool Plane::operator==(Object &other) const {
    if (Plane* other_ = dynamic_cast<Plane*>(&other)) {
        return normal == normal && point == point; // maybe add brdf and emission but that seems unnesecary
    }
    return false;
}