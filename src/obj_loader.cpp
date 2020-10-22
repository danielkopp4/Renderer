#include "obj_loader.hpp"
#include <fstream>

Vertex::Vertex(const std::string &input) {
    // format: 'v 0.551801 -0.551801 -1.000000'


    int current_index = input.find(' ');
    int next_index = input.find(' ', current_index + 1);

    // std::cout << input << std::endl;
    // std::cout << current_index << " " << next_index << std::endl;

    double x = std::stof(input.substr(current_index + 1, next_index - current_index - 1));
    current_index = next_index;
    next_index = input.find(' ', current_index + 1);
    
    // std::cout << current_index << " " << next_index << std::endl;
    
    double y = std::stof(input.substr(current_index + 1, next_index - current_index - 1));


    double z = std::stof(input.substr(next_index + 1));
    // std::cout << input.substr(next_index + 1) << std::endl;

    vector = Vector(x, y, z);
}

Texture::Texture(const std::string &input) {
    // format: 'vt 0.568975 0.056025'
    int current_index = input.find(' ');
    int next_index = input.find(' ', current_index + 2);

    nums = new double[2];

    // std::cout << input << std::endl;
    // std::cout << current_index << " " << next_index << std::endl;
    // std::cout << input.substr(current_index + 1, next_index - current_index - 1) << std::endl;


    nums[0] = std::stof(input.substr(current_index + 1, next_index - current_index - 1));
    nums[1] = std::stof(input.substr(next_index + 1));
}

Normal::Normal(const std::string &input) {
    // format: 'vn -0.7071 -0.7071 0.0000'
    int current_index = input.find(' ');
    int next_index = input.find(' ', current_index + 1);


    double x = std::stof(input.substr(current_index + 1, next_index - current_index - 1));
    current_index = next_index;
    next_index = input.find(' ', current_index + 1);

    double y = std::stof(input.substr(current_index + 1, next_index - current_index - 1));
    double z = std::stof(input.substr(next_index + 1));

    vector = Vector(x, y, z);
}

Triangle Face::create_triangle() const {
    // std::cout << verticies[0].vector << std::endl;
    
    Vector verticies_[3];
    for (int i = 0; i < 3; i++) {
        verticies_[i] = verticies[i].vector;
        // std::cout << verticies[i].vector << std::endl;
    }
    Triangle ret(verticies_, BRDF(), Radiance(1, 1, 1));
    return ret;
}

void Face::operator+= (const Vector &offset) {
    for (int i = 0; i < 3; i++) {
        verticies[i] += offset;
    }
}

void ObjLoader::parse() {
    std::ifstream file(path);

    if (!file.good()) {
        std::cerr << "File not found: '" << path << "'" << std::endl;
        exit(1);
    }

    std::string input;
    while (getline(file, input)) {
        add_line(input);
    }
    file.close();

    load_verticies();
    load_textures();
    load_normals();
    load_faces();

    // std::cout << "ALSO AT THE END: " << faces.back().verticies[0].vector << std::endl;

    // saves memory
    vert_str.clear();
    text_str.clear();
    norm_str.clear();
    verticies.clear();
    textures.clear();
    normals.clear();
}

void ObjLoader::add_line(const std::string &input) {
    if (input.substr(0, 2) == "vn") {
        norm_str.push_back(input);
        return;
    }

    if (input.substr(0, 2) == "vt") {
        text_str.push_back(input);
        return;
    }

    if (input.substr(0, 1) == "v") {
        vert_str.push_back(input);
        return;
    }   

    if (input.substr(0, 1) == "f") {
        face_str.push_back(input);
        return;
    }
}

void ObjLoader::load_verticies() {
    for (size_t i = 0; i < vert_str.size(); i++) {
        verticies.push_back(Vertex(vert_str[i]));
    }
}

void ObjLoader::load_textures() {
    for (size_t i = 0; i < text_str.size(); i++) {
       textures.push_back(Texture(text_str[i]));
    }
}

void ObjLoader::load_normals() {
    for (size_t i = 0; i < norm_str.size(); i++) {
        normals.push_back(Normal(norm_str[i]));
    }
}  

void ObjLoader::load_faces() {
    for (size_t i = 0; i < face_str.size(); i++) {
        create_face(face_str[i]);
    }
}

void ObjLoader::create_face(const std::string &input) {
    Vertex verticies_[3];
    Texture textures_[3];
    Normal normals_[3];

    int curr_index = input.find(' ');
    int next_index = 0;

    // input format: 'f 4/1/1 22/2/1 18/3/1'

    for (int i = 0; i < 3; i++) {
        next_index = input.find(' ', curr_index + 1);

        std::string sub = input.substr(curr_index + 1, next_index - curr_index - 1);


        // sub format: '14/122/1'

        int inner_curr_index = 0;
        int inner_next_index = sub.find('/');


        // std::cout << verticies[std::stoi(sub.substr(inner_curr_index, inner_next_index - inner_curr_index))].vector << std::endl;
        verticies_[i] = verticies[std::stoi(sub.substr(inner_curr_index, inner_next_index - inner_curr_index))];

        inner_curr_index = inner_next_index;
        inner_next_index = sub.find('/', inner_curr_index + 1);

        textures_[i] = textures[std::stoi(sub.substr(inner_curr_index + 1, inner_next_index - inner_curr_index - 1))];


        normals_[i] = normals[std::stoi(sub.substr(inner_next_index + 1))];

        curr_index = next_index;
    }
    faces.push_back(Face(verticies_, textures_, normals_));
}

void ObjLoader::add_to_scene(Scene &scene) {
    // std::cout << "AT THE END: " << faces.back().verticies[0].vector << std::endl;
    for (size_t i = 0; i < faces.size(); i++) {
        // std::cout << faces[i].verticies[0].vector << std::endl;
        Triangle tri = faces[i].create_triangle();
        scene.add_object(tri);
    }
}

void ObjLoader::offset(const Vector &vector) {
    for (size_t i = 0; i < faces.size(); i++) {
        faces[i] += vector;
    }
}

void ObjLoader::rotate(const Vector &vector) {
    std::cerr << "ERROR: ObjLoader::rotate not implemeted yet" << std::endl;
}