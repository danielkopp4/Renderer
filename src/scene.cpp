#include "scene.hpp"

Intersection Scene::closest_intersection(const Ray& ray) const {
    Intersection closestIntersection;
    for (size_t i = 0; i < objects.size(); ++i) {
        Intersection intersection = objects[i]->intersect(ray);
        if (intersection.get_t() < closestIntersection.get_t()) {
            closestIntersection = intersection;
        }
    }
    return closestIntersection;
}

void Scene::add_object(const Object &object) {
    objects.push_back(object.clone());
}

void Scene::add_light(const Object &light) {
    lights.push_back(light.clone());
}

bool Scene::is_light(const Object &light) const {
    for (size_t i = 0; i < lights.size(); ++i) {
        if (light.is_equal(*lights[i])) {
            return true;
        }
    }
    return false;
}
