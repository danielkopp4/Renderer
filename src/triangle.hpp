#ifndef __triangle_hpp_
#define __triangle_hpp_

#include "object.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include "plane.hpp"
#include <algorithm>

class Triangle : public Plane {
private:
    Vector* verticies;
    Vector calculate_normal(Vector vert[3]) {

        Vector u = vert[1] - vert[0];
        Vector v = vert[2] - vert[0];

        // std::cout << u << " " << v << std::endl;

        double x = u.get_y() * v.get_z() - u.get_z() * v.get_y();
        double y = u.get_z() * v.get_x() - u.get_x() * v.get_z();
        double z = u.get_x() * v.get_y() - u.get_y() * v.get_x();

        // std::cout << x << " " << y << " " << z << std::endl;

        Vector b = Vector(x, y, z).normalize();   
        // std::cout << b <<std::endl;
        return b;    
    }
public:
    Triangle(Vector verticies_[3], BRDF distrib_=BRDF(), Radiance emission_=Radiance()) : Plane((verticies_[0] + verticies_[1] + verticies_[2]) / 3, calculate_normal(verticies_), distrib_, emission_) { 
        verticies = new Vector[3];
        std::copy(verticies_, verticies_+3, verticies);
    } 

    Triangle(const Triangle &other) : Plane(other.point, other.normal, other.distrib, other.emission) {
        verticies = new Vector[3];
        std::copy(other.verticies, other.verticies + 3, verticies);
    }

    Object* clone() const {
        return new Triangle(*this);
    }

    Intersection intersect(const Ray &ray) const {
        Vector a = ray.get_direction() * -1;
        Vector b = verticies[1] - verticies[0];
        Vector c = verticies[2] - verticies[0];
        Vector d = ray.get_origin() - verticies[0];
        
        double B = determinant(a, b, c);
        double t = determinant(d, b, c) / B;
        double t_2 = Plane::get_t(ray);
        double u = determinant(a, d, c) / B;
        double v = determinant(a, b, d) / B;

        Vector point = ray.get_origin() + ray.get_direction() * t;

        // if (t - 1 < Utils::DOUBLE_EPS) {
            // std::cout << "t: " << t << ", u: " << u << ", v:" << v << std::endl;
        //     std::cout << ray.get_direction() << " " << ray.get_origin() << std::endl;
        // }

        // std::cout << point << std::endl;

        if (t > 0 && u > 0 && v > 0 && (1 - u - v) > 0) {
            // std::cout << "got it" << std::endl;
            return Intersection(t, this);
        }

        return Intersection();
    }

    Vector sample_light(Sampler &sampler) const {
        double* rands = sampler.get_sample(3);
        Vector rands2 (rands[0], rands[1], rands[2]);
        rands2.normalize();

        return verticies[0] * rands2.get_x() + verticies[1] * rands2.get_y() + verticies[2] * rands2.get_z();
    }

    bool is_equal(Object &other) const {
        if (Triangle* other_t = dynamic_cast<Triangle*>(&other)) {
            for (int i = 0; i < 3; i++) {
                if (!(verticies[i] == other_t->verticies[i])) {
                    return false;
                }
            }
            return true;
        }  
        return false;
    }

    void print() {
        std::cout << verticies[0] << " " << verticies[1] << " " << verticies[2] << std::endl;
    }
};

#endif
