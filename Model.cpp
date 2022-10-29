//
// Created by 刘小备 on 2019/3/14.
//

#include "Model.h"

Model::Model(std::string const &path, std::string tag){
    loadModel(path);
    this->tag = tag;
}

void Model::Draw(Shader shader) {
    for(unsigned int i = 0; i < meshes.size(); ++i)
        meshes[i].Draw(shader);
}

void Model::loadModel(std::string const &path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate| aiProcess_FlipUVs| aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"ERROR ASSIMP: :"<<importer.GetErrorString()<<std::endl;
        return;
    }
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    std::cout<<node->mName.data<<std::endl;
    for(int i = 0; i < node->mNumMeshes; ++i){
        aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }
    for(int i = 0; i< node->mNumChildren; ++i){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }
    return Mesh(vertices, indices, {});
}

unsigned int Model::textureFromFile(const char *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}

glm::vec3 Model::getPosition() {
    return this->collider.getCenter();
}

void Model::translate(glm::mat4 model) {
    this->collider.transform(model);
}

void Model::printPoint() {
   std::cout<<this->collider._min.x<<"-----"<<this->collider._min.y<<"-----"<<this->collider._min.z<<std::endl;
   std::cout<<this->collider._max.x<<"-----"<<this->collider._max.y<<"-----"<<this->collider._max.z<<std::endl;
}

void Model::merge() {
    this->collider = meshes[0].collider;
    for(unsigned int i = 1; i < meshes.size(); ++i)
        this->collider.merge(meshes[i].collider);
}

void Model::setMeshTexture(int index, const char *path) {
    if(index >= this->meshes.size()){
        std::cout<<"out of boundary"<<std::endl;
        return ;
    }
    Texture texture;
    texture.Path = path;
    texture.Type = "specular";
    texture.id = textureFromFile(path);
    this->meshes[index].textures.push_back(texture);
}

void Model::setMeshTexture(const char *path) {
    Texture texture;
    texture.Path = path;
    texture.Type = "specular";
    texture.id = textureFromFile(path);
    for(unsigned int i = 0; i < meshes.size(); ++i)
        meshes[i].textures.push_back(texture);
}
