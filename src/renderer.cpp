#include "renderer.hpp"
#include "camera.hpp"
#include "sampler.hpp"
#include "ray.hpp"
#include <cmath>

void Renderer::take_sample() {
    for (int i = 0; i < film->get_height(); ++i) {
        for (int j = 0; j < film->get_width(); ++j) {
            Ray r = camera->get_ray(sampler->get_sample(), i, j);
            Intersection intersection = scene->closest_intersection(r);
            if (intersection.isIntersection()) {
                // std::cout << intersection.get_t() << std::endl;
                
                film->add_sample(i, j, Radiance(1,1,1) * cos(2 * (intersection.get_t() - 9.3096)));
            } else {
                film->add_sample(i, j, Radiance(0,0,0));
            }
        }
    }
    film->increment_sample_count();
}