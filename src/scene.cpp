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

void Scene::add_object(Object &object) {
    objects.push_back(&object);
}

void Scene::add_light(Object &light) {
    lights.push_back(&light);
}
