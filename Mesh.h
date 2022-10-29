//
// Created by 刘小备 on 2019/3/14.
//

#ifndef TEST_MESH_H
#define TEST_MESH_H
#include <glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <glew.h>
#include <glfw3.h>
#include "Collider.h"
struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    unsigned int id;
    std::string Type;
    std::string Path;
};

class Mesh {
public:

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;
    void setupMash();
    void Draw(Shader shader);
    void calculatePoint();
    glm::vec3 getMaxPoint();
    glm::vec3 getMinPoint();
    Collider collider;
private:
    unsigned int VBO;
    unsigned int EBO;
    glm::vec3 maxPoint;
    glm::vec3 minPoint;
};


#endif //TEST_MESH_H
