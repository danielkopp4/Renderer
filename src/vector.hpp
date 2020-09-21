#ifndef __vector_hpp_
#define __vector_hpp_
#include<iostream>

class Vector {
private:
    double x;
    double y;
    double z;
public:
    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    double length() const;
    Vector& normalize();    

    Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z - other.z); }
    Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z); }
    Vector operator*(double n) const { return Vector(x*n, y*n, z*n); }
    Vector operator/(double n) const { return Vector(x/n, y/n, z/n); }

    friend std::ostream& operator<< (std::ostream& out, const Vector& vector); 

    Vector element_multiply(const Vector& other) const { return Vector(x * other.x, y * other.y, z * other.z); }
    
    double dot(const Vector& other) const { return x * other.x + y * other.y + z * other.z; }
    Vector operator%(const Vector& other) { return Vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x); }
    const double& operator[](size_t i) const; // import this somehow

    void set_x(double x_) { x = x_; }
    void set_y(double y_) { y = y_; }
    void set_z(double z_) { z = z_; }

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }
};

#endif
