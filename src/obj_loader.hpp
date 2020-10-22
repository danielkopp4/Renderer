#ifndef __obj_loader_hpp_
#define __obj_loader_hpp_

#include "scene.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <vector>
#include <algorithm>
#include <string>

struct Vertex {
    Vector vector;
    Vertex(const std::string &input);
    Vertex() {}
    void operator+= (const Vector &offset) { vector = vector + offset; }
};

struct Texture {
    double* nums;
    Texture(const std::string &input);
    Texture() {}
};

struct Normal {
    Vector vector;
    Normal(const std::string &input);
    Normal() {}
};

struct Face {
    Vertex* verticies;
    Texture* textures;
    Normal* normals;
    Face(Vertex verticies_[3], Texture textures_[3], Normal normals_[3]) {
        verticies = new Vertex[3];
        textures = new Texture[3];
        normals = new Normal[3];

        std::copy(verticies_, verticies_+3, verticies);
        std::copy(textures_, textures_+3, textures);
        std::copy(normals_, normals_+3, normals);
    } // std::cout << "face: " << verticies[0].vector <<std::endl; }
    Triangle create_triangle() const;
    void operator+= (const Vector &offset);
};

class ObjLoader { 
private:
    std::vector<std::string> vert_str;
    std::vector<std::string> text_str;
    std::vector<std::string> norm_str;
    std::vector<std::string> face_str;

    std::vector<Vertex> verticies;
    std::vector<Texture> textures;
    std::vector<Normal> normals;
    std::vector<Face> faces;

    std::string path;

    void add_line(const std::string &input);
    void load_verticies();
    void load_textures();
    void load_normals();
    void load_faces();
    void create_face(const std::string &input);
public:
    ObjLoader(const std::string &path_) : path(path_) {}

    void parse();
    
    void add_to_scene(Scene &scene);
    void offset(const Vector &vector);
    void rotate(const Vector &vector); // roll pitch yaw
};


#endif
