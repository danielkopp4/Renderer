#include "camera.hpp"

#include<cmath>
#include <iostream>

Ray Camera::pix_to_ray(double x, double y) const {
    Vector origin = view.get_origin();
    double z = width / tan(fov / 2);
    // double z = 1;
    Vector dz = view.get_direction();
    Vector dx;
    Vector dy;
    ons(dz, dy, dx);
    // std::cout << "z: " << z << std::endl;
    // std::cout << dz.get_z() << std::endl;
    Vector direction = dx * x + dy * y + dz * z; //Vector(view.get_direction().get_x() * x, view.get_direction().get_y() * y, view.get_direction().get_z() * z);
    // std::cout << "direction: " << direction.normalize() << std::endl;
    return Ray(origin, direction);
}

Ray Camera::get_ray(double* sample, int row, int col) const {
    // std::cout << sample[0] << std::endl;
    
    double x = (col + sample[0] - (width / 2.0));// / (width  / 2.0);
    double y = ((height / 2.0) - row + sample[1]); /// (height / 2.0);
    
    // From the video
    // double x = col + sample[0];
    // double y = row + sample[1]; 
    // x = tan(fov) * (2 * x - width) / width;
    // y = tan(fov * double(height) / width) * (2 * y - height) / (height);
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    // std::cout << "sample x: " << sample[0] << std::endl;
    // std::cout << "sample y: " << sample[1] << std::endl;
    return pix_to_ray(x, y);
}