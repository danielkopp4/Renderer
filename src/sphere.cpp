#include "sphere.hpp"
#include "intersection.hpp"

double Sphere::get_t(Ray ray) const {
    double A = ray.get_direction().dot(ray.get_direction());
    double B = (ray.get_origin() - center).dot(ray.get_direction()) * 2;
    double C = (ray.get_origin() - center).dot(ray.get_origin() - center) - radius * radius;

    double radicand = B * B - 4 * A * C;

    if (radicand < 0) {
        return -1;
    } if (radicand == 0) {
        double t = -B / (2 * A);
        return t > 0 ? t : -1;
    }

    double t1 = (-B + sqrt(radicand)) / (2 * A);
    double t2 = (-B - sqrt(radicand)) / (2 * A);

    // std::cout << t1 << std::endl;
    

    if (t1 <= 0 && t2 <= 0) {
        return -1;
    }

    if (t1 <= 0) {
        return t2;
    }

    if (t2 <= 0) {
        return t1;
    }

    return t1 < t2 ? t1 : t2;
}

Intersection Sphere::intersect(const Ray &ray) const {
    double t = get_t(ray);
    if (t == -1) {
        // std::cout << ray.get_direction() << std::endl;
                
        return Intersection();
    } else {
        // std::cout << t << std::endl;
        return Intersection(get_t(ray), this);
    }
}