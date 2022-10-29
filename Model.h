//
// Created by 刘小备 on 2019/3/14.
//

#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "stb_image.h"
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"
#include <string>
class Model {
public:
    std::string tag;
    Collider collider;
    Model(std::string const & path, std::string tag);
    void Draw(Shader shader);
    std::vector<Mesh> meshes;
    glm::vec3 getPosition();
    void translate(glm::mat4 model);
    void printPoint();
    void merge();
    void setMeshTexture(int index, const char * path);
    void setMeshTexture(const char * path);
private:
    void loadModel(std::string const & path);
    void processNode(aiNode * node, const aiScene * scene);
    Mesh processMesh(aiMesh * mesh, const aiScene * scene);
    unsigned int textureFromFile(const char* path);
};

#endif //TEST_MODEL_H
