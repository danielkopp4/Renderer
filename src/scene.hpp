#ifndef __scene_hpp_
#define __scene_hpp_

#include<vector>
#include "object.hpp"
#include "ray.hpp"
#include "intersection.hpp"

class Scene {
private:
    std::vector<Object*> objects;
    // camera
    // lights
public:
    void add_object(Object& object);
    Intersection closest_intersection(const Ray& ray) const;
};

#endif
