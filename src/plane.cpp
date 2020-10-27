#include "plane.hpp"
#include "intersection.hpp"
#include "utils.hpp"

#include <iostream> // REMOVE

#include <cmath>

// Object* Plane::clone() const {
//     return new Plane(*this);
// }

double Plane::get_t(const Ray &ray) const {
    if (ray.get_direction().dot(normal) == 0) {
        return -1;
    }

    
    double t = ((normal.dot(ray.get_origin() - point)) / (normal.dot(ray.get_direction() * -1)));

    // std::cout << normal << point << std::endl;

    if (t > Utils::DOUBLE_EPS) {
        // std::cout << -((normal.dot(ray.get_origin() - point)) / (normal.dot(ray.get_direction()))) << std::endl;
        return t;
    } else {
        return -1;
    }
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
    // std::cout << "us run" << std::endl;
    // std::cout << (emission * (ray.get_direction() * -1).dot(normal)).get_average_light() << std::endl;
    return (emission * (ray.get_direction() * -1).dot(normal)).abs(); // possible error (take the absolute value when there are two normals)
}

bool Plane::is_equal(Object &other) const {
    // std::cout << "got here" << std::endl;
    if (Plane* other_ = dynamic_cast<Plane*>(&other)) {
        return normal == normal && point == point; // maybe add brdf and emission but that seems unnesecary
    }
    return false;
}