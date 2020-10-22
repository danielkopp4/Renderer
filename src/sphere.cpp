#include "sphere.hpp"
#include "intersection.hpp"
#include "utils.hpp"
#include "plane.hpp" // REMOVE

#include <cmath>
#include <iostream> // REMOVE

Object* Sphere::clone() const {
    return new Sphere(*this);
}

double Sphere::get_t(Ray ray) const {

    double A = ray.get_direction().dot(ray.get_direction());
    double B = (ray.get_origin() - center).dot(ray.get_direction()) * 2;
    double C = (ray.get_origin() - center).dot(ray.get_origin() - center) - radius * radius;

    double radicand = B * B - 4 * A * C;

    if (radicand < 0) {
        return -1;
    }

    double t1 = ((-1 * B) + sqrt(radicand)) / (2 * A);
    double t2 = ((-1  * B) - sqrt(radicand)) / (2 * A);

    // return t1;

    // std::cout << t1 << std::endl;
    // std::cout << t2 << std::endl;

    if (t1 <= Utils::DOUBLE_EPS && t2 <= Utils::DOUBLE_EPS) {
        return -1;
    }

    if (t1 <= Utils::DOUBLE_EPS) {
        return t2;
    }

    if (t2 <= Utils::DOUBLE_EPS) {
        return t1;
    }

    return t1 < t2 ? t1 : t2;
}

Intersection Sphere::intersect(const Ray &ray) const {
    double t = get_t(ray);
    // std::cout << t << std::endl;
    if (t == -1) {
        // std::cout << ray.get_direction() << std::endl;
                
        return Intersection();
    } else {
        // std::cout << t << std::endl;
        return Intersection(t, this);
    }
}

Vector Sphere::get_normal(const Ray &ray, double t) const {
    Vector point = ray.get_origin() + ray.get_direction() * t;
    return (point - center).normalize();
}

Vector Sphere::sample_light(Sampler& sampler) const {
    return center + sampler.get_random_sphere_direction() * radius;
}

bool Sphere::is_equal(Object &other) const {
    // std::cout 
    if (Sphere* other_ = dynamic_cast<Sphere*>(&other)) {
        return radius == other_->radius && center == other_->center; 
    } 

    // if (Plane* other_ = dynamic_cast<Plane*>(&other)) {
    //     std::cout << "wrong place!" << std::endl; // maybe add brdf and emission but that seems unnesecary
    // }

    return false;
}

Radiance Sphere::get_emission(const Ray &ray, double t) const {
    // std::cout << "ray(origin=" << ray.get_origin()<< ", dir=" << ray.get_direction() << ")" << std::endl;
    // Vector normal = get_normal(ray, t);
    // std::cout << "normal: " << normal << std::endl;
    // std::cout << "scale: " << (ray.get_direction() * -1).dot(get_normal(ray, t)) << std::endl;
    // std::cout << "angle: " << acos((ray.get_direction() * -1).dot(get_normal(ray, t))) << std::endl;
    // std::cout << "t: " << t << std::endl;
    // std::cout << "center: " << center << std::endl;
    // std::

    return (emission * (ray.get_direction() * -1).dot(get_normal(ray, t))).abs();
}