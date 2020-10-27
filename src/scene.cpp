#include "scene.hpp"

Intersection Scene::closest_intersection(const Ray& ray) {
    // Intersection closestIntersection;
    

    Intersection closestIntersection;
    if (object_accel == NULL) {
        std::cerr << "accell undefined" << std::endl;
        exit(1);
    }
    std::shared_ptr<std::vector<Object*> > current_objects = object_accel->get_objects(ray);
    // mutex.lock();
    // std::cout << current_objects->size() << std::endl;
    // mutex.unlock();
    // std::cout << current_objects.size()  << " vs " << objects.size() << std::endl;
    for (size_t i = 0; i < current_objects->size(); ++i) {
        Intersection intersection = (*current_objects)[i]->intersect(ray);
        if (intersection.get_t() < closestIntersection.get_t()) {
            closestIntersection = intersection;
        }
        mutex.lock();
        std::cout << intersection.get_t() << std::endl;
        mutex.unlock();
    }
    return closestIntersection;
}

void Scene::add_object(const Object &object) {
    objects.push_back(object.clone());
}

void Scene::add_light(const Object &light) {
    lights.push_back(light.clone());
}

void Scene::convert_to_accel() {
    object_accel = new Octree(objects);
}

bool Scene::is_light(const Object &light) const {
    for (size_t i = 0; i < lights.size(); ++i) {
        if (light.is_equal(*lights[i])) {
            return true;
        }
    }
    return false;
}
