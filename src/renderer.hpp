#ifndef __renderer_hpp_
#define __renderer_hpp_

#include "film.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sampler.hpp"

class Renderer {
private:
    Film* film;
    Scene* scene;
    Camera* camera;
    Sampler* sampler;
    
    Radiance get_radiance(Ray ray, int depth) const;
public:
    Renderer(Film &film_, Scene &scene_, Camera &camera_, Sampler &sampler_) : film(&film_), scene(&scene_), camera(&camera_), sampler(&sampler_) {} 
    void take_sample();
};

#endif
