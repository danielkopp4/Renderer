#ifndef __radiance_hpp_
#define __radiance_hpp_
#include "vector.hpp"
#include<cmath>

// Implementation of RGB radiance
class Radiance {
private:
    double r;
    double g;
    double b;
public:
    Radiance(double r_ = 0, double g_ = 0, double b_ = 0) : r(r_), g(g_), b(b_) {}
    
    Radiance operator+(const Radiance &other) const { return Radiance(r + other.r, g + other.g, b + other.b); }
    Radiance operator+(double num) const { return Radiance(num + r, num + g, num + b); }
    Radiance operator*(const Radiance &other) const { return Radiance(r * other.r, g * other.g, b * other.b); }
    Radiance operator*(double scale) const { return Radiance(r * scale, g * scale, b * scale); }
    Radiance operator-(const Radiance &other) const { return other * -1 + *this; } // maybe properly implement this later bur rn idc
    Radiance operator/(const Radiance &other) const { return Radiance(r / other.r, g / other.g, b / other.b); }
    Radiance operator/(double scale) const { return *this * (1 / scale); } // maybe properly implemetn this one too, used for averages in tonemapping
    Radiance exp() const { return Radiance(std::exp(r), std::exp(g), std::exp(b)); }
    Radiance log() const { return Radiance(std::log(r), std::log(g), std::log(b)); }
    Radiance pow(double n) const { return Radiance(std::pow(r, n), std::pow(g, n), std::pow(b, n)); }
    Radiance abs() const { return Radiance(fabs(r), fabs(g), fabs(b)); }
    // double get_average_light() const { return (r + g + b) / 3; }
    double get_average_light() const { return 0.265*r + 0.67*g + 0.065*b; }

    double get_r() const { return r; }
    double get_g() const { return g; }
    double get_b() const { return b; }
};

#endif
