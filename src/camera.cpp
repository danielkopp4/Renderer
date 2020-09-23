#include "camera.hpp"

#include<cmath>

Ray Camera::pix_to_ray(double x, double y) const {
    Vector origin = view.get_origin();
    double z = width / tan(fov / 2);
    Vector dz = view.get_direction();
    Vector dx;
    Vector dy;
    ons(dz, dy, dx);
    // std::cout << "y: " << z << std::endl;
    
    Vector direction = dx * x + dy * y + dz * z; //Vector(view.get_direction().get_x() * x, view.get_direction().get_y() * y, view.get_direction().get_z() * z);
    return Ray(origin, direction);
}

Ray Camera::get_ray(double* sample, int row, int col) const {
    // std::cout << sample[0] << std::endl;
    
    double x = (col + sample[0] - (width / 2.0));// / (width  / 2.0);
    double y = ((height / 2.0) - row + sample[1]); /// (height / 2.0);
    return pix_to_ray(x, y);
}