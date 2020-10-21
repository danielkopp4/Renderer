#ifndef __obj_loader_hpp_
#define __obj_loader_hpp_

#include "scene.hpp"
#include "vector.hpp"
#include <vector>
#include <string>

struct Vertex {
    Vector vector;
    Vertex(const std::string &input);
};

struct Texture {
    Vector vector;
    Texture(const std::string &input);
};

struct Normal {
    Normal(const std::string &input);
};

struct Face {
    Vertex* verticies;
    Texture* textures;
    Normal* normals;
    Face(Vertex verticies_[3], Texture textures_[3], Normal normals_[3]);
};

class ObjLoader { 
private:
    std::vector<Vertex> verticies;
    std::vector<Texture> textures;
    std::vector<Normal> normals;
    std::vector<Face> faces;
public:
    ObjLoader();

    void parse();
    void load_verticies();
    void load_textures();
    void load_normals();
    void load_faces();
    void create_face(const std::string &input);
    void add_to_scene(Scene &scene);
};


#endif
