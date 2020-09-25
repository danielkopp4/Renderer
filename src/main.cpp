#include "scene.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "film.hpp"
#include "camera.hpp"
#include "sampler.hpp"
#include "renderer.hpp"
#include "sphere.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>

void print_progress(int samples_progressed, int total) {
    std::cout << " [";
    int total_bars = 20;
    double percent_completion = double(samples_progressed) / total;
    for (int i = 0; i < total_bars; ++i) {
        if (i < int(percent_completion * total_bars)) {
            std::cout << "=";
        } else if (i == int(percent_completion * total_bars))  {
            std::cout << ">";
        } else{
            std::cout << " ";
        }
        
    }
    std::cout << "] " << std::fixed << std::setprecision(0) << (100 * percent_completion) << "%" << "\r" << std::flush;
}

int main() {
    // Scene a;
    // Object b;
    // a.add_object(b);
    // Ray c (Vector(0,0,0), Vector(1, 1, 1));
    // Intersection d = a.closest_intersection(c);
    time_t start;
    time_t end;
    time(&start);
    // std::cout << "t: " << d.get_t() << std::endl; 
    int height = 500;
    int width = 500;
    double fov = 1.57079632679;
    Ray view = Ray(Vector(0, 0, 0), Vector(0, 0, 1));
    int samples = 100;

    Vector offset_1 (-0.75, 0, 3);
    Vector offset_2 (0.75, 0, 3);
    Vector offset_3 (0, 1, 4);
    double radius = 0.5;
    Sphere sphere (radius, view.get_origin() + offset_1, Radiance(0, 0, 0), BRDF(Radiance(1, 0, 0)));
    Sphere sphere_2(radius, view.get_origin() + offset_2);
    Sphere sphere_3 (radius, view.get_origin() + offset_3, Radiance(1, 1, 1));

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
    scene.add_object(sphere_2);
    scene.add_object(sphere_3);
    scene.add_object(sphere); // if it turn off the view it creats a segmetation fault(if something is a light but not an object): investigate!
    // scene.add_light(sphere);
    scene.add_object(sphere_3);
    // Ray tester (Vector(0,0,0), Vector(-0.5,0,2));
    // Intersection a = scene.closest_intersection(tester);
    // sphere.get_emission(tester, a.get_t());
    Renderer renderer(film, scene, camera, sampler);
    for (int i = 0; i < samples; ++i) {
        renderer.take_sample();
        print_progress(i, samples);
    }
    // renderer.take_sample();
    
    // film.tone_map();

    // film.print(std::cout);

    time(&end);
    std::cout << std::endl;
    std::cout << "time elapsed: " << difftime(end, start) << " seconds" << std::endl;

    std::string file_name = "render.ppm";
    std::ofstream out(file_name);
    film.write_ppm(out);

    std::cout << "wrote to: '" << file_name << "'" << std::endl;
    
    return 0;
}