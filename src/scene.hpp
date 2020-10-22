#ifndef __scene_hpp_
#define __scene_hpp_

#include<vector>
#include "object.hpp"
#include "ray.hpp"
#include "intersection.hpp"

class Scene {
private:
    std::vector<Object*> objects;
    std::vector<Object*> lights;
    // camera
    // lights
public:
    void add_object(const Object &object);
    void add_light(const Object &light);
    bool is_light(const Object &light) const;
    Intersection closest_intersection(const Ray& ray) const;
    // Radiance get_light_sum();
    const std::vector<Object*> get_lights() const { return lights; } // migrate this functionality to the above function
};

#endif
