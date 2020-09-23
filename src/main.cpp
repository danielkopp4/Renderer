#include "scene.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "film.hpp"
#include "camera.hpp"
#include "sampler.hpp"
#include "renderer.hpp"
#include "sphere.hpp"
#include<iostream>


int main() {
    // Scene a;
    // Object b;
    // a.add_object(b);
    // Ray c (Vector(0,0,0), Vector(1, 1, 1));
    // Intersection d = a.closest_intersection(c);

    // std::cout << "t: " << d.get_t() << std::endl; 
    int height = 1000;
    int width = 1000;
    double fov = 0.78539816339;
    Ray view = Ray(Vector(0, 0, 0), Vector(0, 0, 1));
    int samples = 20;

    double distance_from_cam = 10;
    double radius = 1;
    Sphere sphere (radius, view.get_origin() + view.get_direction() * distance_from_cam);

    Film film (samples, height, width);
    film.init();
    Camera camera(height, width, fov, view);
    Sampler sampler;

    // Vector dz(0,0, 1);
    // Vector dx;
    // Vector dy;
    // ons (dz, dy, dx);
    // std::cout << dz << " " << dx << " " << dy << std::endl;

    // Ray close_0 = camera.get_ray(sampler.get_sample(), height/2, width/2);
    // Ray far_0 = camera.get_ray(sampler.get_sample(), height/2, 0);
    // Ray other_far = camera.get_ray(sampler.get_sample(), height/2, width-1);
    // std::cout << close_0.get_direction() << std::endl;
    
    Scene scene;
    scene.add_object(sphere);
    Renderer renderer(film, scene, camera, sampler);
    for (int i = 0; i < samples; ++i) {
        renderer.take_sample();
    }
    // renderer.take_sample();
    
    // film.tone_map();
    film.write_ppm(std::cout);
    
    return 0;
}