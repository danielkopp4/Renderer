#ifndef __renderer_hpp_
#define __renderer_hpp_

#include "film.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sampler.hpp"
#include "thread_pooler.hpp"
#include <vector>
#include <thread>

class ThreadPooler;
class Renderer {
private:
    Film* film;
    Scene* scene;
    Camera* camera;
    Sampler* sampler;
    // friend class ThreadPooler;
    ThreadPooler* threadPooler;

    Radiance get_radiance(Ray ray, int depth) const;
    
public:
    Renderer(Film &film_, Scene &scene_, Camera &camera_, Sampler &sampler_);
    void take_sample(int samples);
    void add_pixel(int i, int j, int samples, unsigned int id);
    void wait_to_finish();
};



#endif
