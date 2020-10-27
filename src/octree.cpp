#include "octree.hpp"
#include <iostream>

std::shared_ptr<std::vector<Object*> > Node::in(const std::vector<Object*> &to_add, const Bounds &bounds) {
    std::shared_ptr<std::vector<Object*> > ret = std::shared_ptr<std::vector<Object*> >::make_shared();
    for (int i = 0; i < to_add.size(); i++) {
        if (to_add[i]->in_bounds(bounds.point, bounds.x_len, bounds.y_len, bounds.z_len)) {
            ret->push_back(to_add[i]);
        }
    }
    return ret;
}

bool Node::ray_intersect(const Ray &ray) const {
    Vector p1 = bounding_box.point;
    Vector p2 = bounding_box.point + Vector(bounding_box.x_len, bounding_box.y_len, bounding_box.z_len);
    double t_x = (bounding_box.point.get_x() - ray.get_origin().get_x()) / (ray.get_direction().get_x());
    double t_y = (bounding_box.point.get_x() - ray.get_origin().get_x()) / (ray.get_direction().get_x());
    double t_z = (bounding_box.point.get_x() - ray.get_origin().get_x()) / (ray.get_direction().get_x());

    Vector ix = ray.get_origin() + ray.get_direction() * t_x;
    Vector iy = ray.get_origin() + ray.get_direction() * t_y;
    Vector iz = ray.get_origin() + ray.get_direction() * t_z;

    if (p1.get_y() < ix.get_y() && ix.get_y() < p2.get_y() && p1.get_z() < ix.get_z() && ix.get_z() < p2.get_z()) {
        return true; // intersects the x plane
    }  

    if (p1.get_x() < iy.get_x() && iy.get_x() < p2.get_x() && p1.get_z() < iy.get_z() && iy.get_z() < p2.get_z()) {
        return true; // intersects the y plane
    }

    if (p1.get_x() < iz.get_x() && iz.get_x() < p2.get_x() && p1.get_y() < iz.get_y() && iz.get_y() < p2.get_y()) {
        return true;
    }

    return false;
}

Node::Node(const std::vector<Object*>& to_add, const Bounds &bounds) {
    std::vector<Object*> &objects_in_bounds = *in(to_add, bounds);
    bounding_box = bounds;
    if (objects.size() > 8) {
        is_end = false;

        double new_x_len = bounding_box.x_len / 2;
        double new_y_len = bounding_box.y_len / 2;
        double new_z_len = bounding_box.z_len / 2;

        double x = bounding_box.point.get_x();
        double y = bounding_box.point.get_y();
        double z = bounding_box.point.get_z();

        double mid_x = new_x_len + x;
        double mid_y = new_y_len + y;
        double mid_z = new_z_len + z;

        Bounds b000 (bounding_box.point, new_x_len, new_y_len, new_z_len);
        Bounds b100 (Vector(mid_x, y, z), new_x_len, new_y_len, new_z_len);
        Bounds b010 (Vector(x, mid_y, z), new_x_len, new_y_len, new_z_len);
        Bounds b110 (Vector(mid_x, mid_y, z), new_x_len, new_y_len, new_z_len);
        Bounds b001 (Vector(x, y, mid_z), new_x_len, new_y_len, new_z_len);
        Bounds b101 (Vector(mid_x, y, mid_z), new_x_len, new_y_len, new_z_len);
        Bounds b011 (Vector(x, mid_y, mid_z), new_x_len, new_y_len, new_z_len);
        Bounds b111 (Vector(mid_x, mid_y, mid_z), new_x_len, new_y_len, new_z_len);

        nodes = new Node*[8];

        nodes[0] = new Node(objects_in_bounds, b000);
        nodes[1] = new Node(objects_in_bounds, b100);
        nodes[2] = new Node(objects_in_bounds, b010);
        nodes[3] = new Node(objects_in_bounds, b110);
        nodes[4] = new Node(objects_in_bounds, b001);
        nodes[5] = new Node(objects_in_bounds, b101);
        nodes[6] = new Node(objects_in_bounds, b011);
        nodes[7] = new Node(objects_in_bounds, b111);
    } else {
        is_end = true;
        objects = to_add;
        nodes = NULL;
    }
}

Node::Node(const Node& other) {
    is_end = other.is_end;
    // copy objects array creating clones of the other
    // copy nodes creating copies (recursive call)
    std::cerr << "NODE COPY CONSTRUCTOR IS CALLED!" << std::endl;
}

Node& Node::operator=(const Node &other) {
    *this = Node(other);
    return *this;
}

Node::~Node() {
    // if (is_end) {
    //     for (int i = 0; i < objects.size(); i++) {
    //         if (objects[i] != null)
    //         delete objects[i];
    //         objects[i] = NULL;
    //     }
    // }
    // delte objects somehow?

    for (int i = 0; i < 8; i++) {
        delete nodes[i];
    }

    delete [] nodes;
}

std::shared_ptr<std::vector<Object*> > Node::get_objects(const Ray &ray) const {
    std::shared_ptr<std::vector<Object*> > ret = std::shared_ptr<std::vector<Object*> >::make_shared();
    
    if (!ray_intersect(ray)) {
        return ret; // if no intersection return no objects
    }

    if (is_end) {
        *ret = objects;
        return ret;
    }

    for (int i = 0; i < 8; i++) {
        std::shared_ptr<std::vector<Object*> > curr = nodes[i]->get_objects(ray);
        for (int j = 0; j < curr->size(); j++) {
            ret->push_back((*curr)[j]);
        }
    }

    return ret;
}

Bounds Octree::get_bounds(const std::vector<Object*> &objects) {
    Vector most_negative;
    Vector most_positive;
    for (int i = 0; i < objects.size(); i++) {
        Vector negative = objects[i]->most_negative();
        if (negative.get_x() < most_negative.get_x()) {
            most_negative.set_x(negative.get_x());
        }

        if (negative.get_y() < most_negative.get_y()) {
            most_negative.set_y(negative.get_y());
        }

        if (negative.get_z() < most_negative.get_z()) {
            most_negative.set_z(negative.get_z());
        }

        Vector positive = objects[i]->most_positive();

        if (positive.get_x() < most_positive.get_x()) {
            most_positive.set_x(positive.get_x());
        }

        if (positive.get_y() < most_positive.get_y()) {
            most_positive.set_y(positive.get_y());
        }

        if (positive.get_y() < most_positive.get_y()) {
            most_positive.set_y(positive.get_y());
        }
    }
    Vector len = most_positive - most_negative;
    double x_len = len.get_x();
    double y_len = len.get_y();
    double z_len = len.get_z();
    return Bounds(most_negative, x_len, y_len, z_len);
}

Octree::~Octree() {
    delete head;
    head = NULL;

    // should i delete objects here ?
}

Octree::Octree(const std::vector<Object*> &objects) {
    size = objects.size();
    Bounds bounds = get_bounds(objects);
    head = new Node(objects, bounds);

}

 std::shared_ptr<std::vector<Object*> > Octree::get_objects(const Ray &ray) const {
     return head->get_objects(ray);
 }