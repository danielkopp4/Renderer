#ifndef __camera_hpp_
#define __camera_hpp_

#include "ray.hpp"

class Camera {
private:
    int height;
    int width;
    double fov;
    Ray view;

    Ray pix_to_ray(double x, double y) const;
public:
    Camera(int height_, int width_, double fov_, Ray view_) : height(height_), width(width_), fov(fov_), view(view_) {}
    Ray get_ray(double* sample, int row, int col) const;
};

#endif
