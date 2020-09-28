#include "renderer.hpp"
#include "camera.hpp"
#include "sampler.hpp"
#include "ray.hpp"
#include <cmath>

void Renderer::take_sample() {
    for (int i = 0; i < film->get_height(); ++i) {
        for (int j = 0; j < film->get_width(); ++j) {
            Ray ray = camera->get_ray(sampler->get_sample(), i, j);
            // std::cout << "camera ray: " << ray.get_direction() << std::endl;
            film->add_sample(i, j, get_radiance(ray, 0));
        }
    }
    film->increment_sample_count();
}

Radiance Renderer::get_radiance(Ray ray, int depth) const { // BTW if this doesnt work blame the cos term !!!!!!!!!
    Intersection intersection = scene->closest_intersection(ray);
    if (intersection.isIntersection()) { // && !(depth > 0 && scene->is_light(intersection.get_object()))) {
        // std::cout << intersection.get_t() << std::endl;
        Vector point = ray.get_direction() * intersection.get_t() + ray.get_origin();
        // return Radiance(1,1,1) * cos(2 * (intersection.get_t() - 9.3096));
        // film->add_sample(i, j, )
        Radiance emision = intersection.get_object().get_emission(ray, intersection.get_t());
        
        // Get direct light
        // Radiance direct_light = get_light_contribution(point);
        Radiance integral;
        double total = 3.1415; // (b - a)
        int samples = 0;
        for (size_t i = 0; i < scene->get_lights().size(); ++i) {
            
            Ray light_ray (point, scene->get_lights()[i]->sample_light(*sampler) - point);
            // std::cout << "Light Ray: " << light_ray.get_direction() << std::endl;
            Intersection light_ray_intersection = scene->closest_intersection(light_ray);
            // std::cout << "for: " << i << std::endl;
            // std::cout << "intersection: " << light_ray_intersection.get_object().intersect(light_ray).get_t() << std::endl;
            if (light_ray_intersection.get_object_ptr()->is_equal(*(scene->get_lights()[i]))) {
                // Li(x, w') * fr(w, x, w') * cos(theta) * dw'
                
                integral = integral + scene->get_lights()[i]->get_emission(light_ray, light_ray_intersection.get_t()) * intersection.get_object().brdf(ray, light_ray, intersection.get_t());
            }
            // std::cout << integral.get_average_light() << std::endl;
            samples++;
        }

        // generate sample
        // INCLUDE IMPORTANCE SAMPLING!!!!!!!!!!!!
        // do if condition (russian roulette)
        // Vector direction = sampler->get_random_direction();
        Ray new_ray = intersection.get_object().importance_sample(ray, intersection.get_t(), *sampler); // this might be messed up <====
        Radiance fr = intersection.get_object().brdf(ray, new_ray, intersection.get_t());
        double albedo = fr.get_average_light();
        double epsillon = sampler->get_sample(1)[0];
        // double px = 1/3.1415;
        double px = 0.1;
        double min_depth = 5;
        // std::cout << albedo << std::endl;
        // if (epsillon < 50*albedo) { // russian roulette path termination
        if (depth <= min_depth || epsillon > px) {
            // std::cout << "new ray: " << new_ray.get_direction() << std::endl;
            Radiance Li = get_radiance(new_ray, depth+1);
            if (depth <= min_depth) {
                integral = integral + fr * Li / (1 - px);
            } else {
                integral = integral + fr * Li;  // NOTE: the labertian factor does not apply for secular  
            }
            // integral = integral + (fr * Li) / (px); // mignt not work check signs on the cos term (dot)
            samples++;
            // std::cout << (depth > 5) << std::endl;
        } 

        if (samples != 0) {
            integral = (integral / samples) * total; 
            integral = integral.abs();
            // std::cout << integral.get_average_light() << std::endl;
        } 

        return emision + integral;
    } else {
        return Radiance(0, 0, 0);
    }
}