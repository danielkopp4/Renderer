#ifndef __octree_hpp_
#define __octree_hpp_

#include "object.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include <vector>
#include <memory>

struct Bounds {
    Vector point; // most negative values
    double x_len, y_len, z_len;
    Bounds(const Vector &point_, int x_len_, int y_len_, int z_len_) : point(point_), x_len(x_len_), y_len(y_len_), z_len(z_len_) {} 
    Bounds() : point(), x_len(0), y_len(0), z_len(0) {}
};

class Node {
private:
    std::vector<Object*> objects;
    bool is_end;
    Node** nodes;
    Bounds bounding_box;
    std::shared_ptr<std::vector<Object*> > in(const std::vector<Object*> &to_add, const Bounds &bounds); 
    bool ray_intersect(const Ray &ray) const;
public:
    Node(const std::vector<Object*>& to_add, const Bounds &bounds); // and bounds
    Node(const Node &other);
    Node& operator=(const Node &other);
    ~Node();
    std::shared_ptr<std::vector<Object*> > get_objects(const Ray &ray) const;
    // void add(const std::vector<Object*>& to_add);
};

class Octree {
private:
    unsigned int size;
    Node* head;
    Bounds get_bounds(const std::vector<Object*> &objects);
public:
    Octree() : head(NULL), size(0) {}
    Octree(const std::vector<Object*> &objects);
    ~Octree();
    std::shared_ptr<std::vector<Object*> > get_objects(const Ray &ray) const; 
};

#endif
