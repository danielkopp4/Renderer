#include<cmath>
#include "vector.hpp"

double Vector::length() const {
    return sqrt(x*x + y*y + z*z);
}

Vector& Vector::normalize() {
    return *this = *this / length();
}

const double& Vector::operator[](size_t i) const { // see if i can have a error return if not recognized i value
    if (i == 0) {
        return x; 
    } else if (i == 1) {
        return y;
    } else {
        return z;
    }
}

std::ostream& operator<< (std::ostream& out, const Vector& vector) {
    return out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}
