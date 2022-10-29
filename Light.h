//
// Created by 刘小备 on 2019/3/25.
//

#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>
#include <glew.h>
#include <glfw3.h>

class Light {
public:
    glm::vec3 ambient;
    glm::vec3 specular;
    glm::vec3 diffuse;
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    Light(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse);

    virtual void setAmbinet(unsigned int shaderID);
    virtual void setSpecular(unsigned int shaderID);
    virtual void setDiffuse(unsigned int shaderID);
};


class DirectionalLight:public Light{
public:
    glm::vec3 direction;
    DirectionalLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 direction);
    void UpdateDirection(glm::vec3 angles);
    virtual void setAmbinet(unsigned int shaderID);
    virtual void setSpecular(unsigned int shaderID);
    virtual void setDiffuse(unsigned int shaderID);
    void setDirection(unsigned int shaderID);
};

class PointLight:public Light{
public:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    PointLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 position, float constant, float linear, float quadratic);
    virtual void setAmbinet(unsigned int shaderID);
    virtual void setSpecular(unsigned int shaderID);
    virtual void setDiffuse(unsigned int shaderID);
    void setConstant(unsigned int shaderID);
    void setLinear(unsigned int shaderID);
    void setQuadratic(unsigned int shaderID);
    void setPosition(unsigned int shaderID);
};

class SpotLight:public Light{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    SpotLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 position, glm::vec3 direction,
            float constant, float linear, float quadratic, float cutoff, float outerCutoff);
    virtual void setAmbinet(unsigned int shaderID);
    virtual void setSpecular(unsigned int shaderID);
    virtual void setDiffuse(unsigned int shaderID);
    void setPosition(unsigned int shaderID);
    void setDirection(unsigned int shaderID);
    void setConstant(unsigned int shaderID);
    void setLinear(unsigned int shaderID);
    void setQuadratic(unsigned int shaderID);
    void setCutff(unsigned int shaderID);
    void setOuterCutoff(unsigned int shaderID);
};

#endif //TEST_LIGHT_H
