#include<cmath>
#include "utils.hpp"
#include "vector.hpp"

void Vector::floor_zero(double &num) const {
    if (std::abs(num) < Utils::DOUBLE_EPS) {
        num = 0;
    }
}

double Vector::length() const {
    return sqrt(x*x + y*y + z*z);
}

Vector& Vector::normalize() {
    zero_sign();
    return *this = *this / length();
}

Vector& Vector::zero_sign() {
    floor_zero(x);
    floor_zero(y);
    floor_zero(z);
    return *this;
}

const double& Vector::operator[](size_t i) const { 
    return (*this)[i];
}

double& Vector::operator[](size_t i) { // see if i can have a error return if not recognized i value
    if (i == 0) {
        return x; 
    } else if (i == 1) {
        return y;
    } else if (i == 2) {
        return z;
    } else {
		// print error
		exit(1);
	}
}

std::ostream& operator<< (std::ostream& out, const Vector& vector) {
    return out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

// rename to orthonormal system
void ons(const Vector& vec1, Vector& vec2, Vector& vec3) { // rewrite
    // vec2 = Vector(-vec1.get_y(), vec1.get_x(), vec1.get_z());
    // vec3 = Vector(vec1.get_x(), -vec1.get_z(), vec1.get_y());
    if (std::abs(vec1.x) > std::abs(vec1.y)) {
		// project to the y = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.f / sqrtf(vec1.x * vec1.x + vec1.z * vec1.z);
		vec2 = Vector(-vec1.z * invLen, 0.0f, vec1.x * invLen);
    } else {
		// project to the x = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.0f / sqrtf(vec1.y * vec1.y + vec1.z * vec1.z);
		vec2 = Vector(0.0f, vec1.z * invLen, -vec1.y * invLen);
    }
    vec3 = vec1 % vec2;
}

double determinant(const Vector &v1, const Vector &v2, const Vector &v3) {
    double t1 = v1.x * (v2.y * v3.z - v3.y * v2.z);
    double t2 = -1 * v2.x * (v1.y * v3.z - v3.y * v1.z);
    double t3 = v3.x * (v1.y * v2.z - v2.y * v1.z);
    return t1 + t2 + t3;
}