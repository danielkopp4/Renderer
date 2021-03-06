#ifndef __scene_hpp_
#define __scene_hpp_

#include<vector>
#include "object.hpp"
#include "ray.hpp"
#include "intersection.hpp"
#include "octree.hpp"

#include <mutex> // remove

class Scene {
private:
    std::vector<Object*> objects;
    Octree* object_accel;
    std::vector<Object*> lights;
    // camera
    // lights

    std::mutex mutex;
public:
    Scene() : object_accel(NULL) {}
    void add_object(const Object &object);
    void add_light(const Object &light);
    bool is_light(const Object &light) const;
    void convert_to_accel();
    Intersection closest_intersection(const Ray& ray);
    // Radiance get_light_sum();
    const std::vector<Object*> get_lights() const { return lights; } // migrate this functionality to the above function
};

#endif
