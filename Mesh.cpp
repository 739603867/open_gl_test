//
// Created by 刘小备 on 2019/3/14.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMash();
    calculatePoint();
    collider.set(this->minPoint, this->maxPoint);
}

Mesh::~Mesh() {

}

void Mesh::Draw(Shader shader) {
    for(int i=0; i<textures.size(); ++i){
        glActiveTexture(GL_TEXTURE0 + i);
        if(textures[i].Type == "diffuse")
            glUniform1i(glGetUniformLocation(shader.ID, "texture_diffuse"), i);
        else if(textures[i].Type == "specular")
            glUniform1i(glGetUniformLocation(shader.ID, "texture_diffuse"), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMash() {
    glewExperimental = GL_TRUE;
    glewInit();
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::calculatePoint() {
    float xmax,ymax,zmax,xmin,ymin,zmin;
    xmax = ymax = zmax = -9999999;
    xmin = ymin = zmin = +9999999;
    for(int i=0; i < vertices.size(); ++i){

        if( xmax < vertices[i].Position.x )
            xmax = vertices[i].Position.x;
        if( ymax < vertices[i].Position.y )
            ymax = vertices[i].Position.y;
        if( zmax < vertices[i].Position.z )
            zmax = vertices[i].Position.z;

        // 计算pMin
        if( xmin > vertices[i].Position.x )
            xmin = vertices[i].Position.x;
        if( ymin > vertices[i].Position.y )
            ymin = vertices[i].Position.y;
        if( zmin > vertices[i].Position.z )
            zmin = vertices[i].Position.z;
    }
    this->maxPoint.x = xmax;
    this->maxPoint.y = ymax;
    this->maxPoint.z = zmax;
    this->minPoint.x = xmin;
    this->minPoint.y = ymin;
    this->minPoint.z = zmin;
}

glm::vec3 Mesh::getMaxPoint() {
    return this->maxPoint;
}

glm::vec3 Mesh::getMinPoint() {
    return this->minPoint;
}
