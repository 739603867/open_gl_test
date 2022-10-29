//
// Created by 刘小备 on 2019/3/25.
//

#include "Light.h"

Light::Light(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse) {
    this->ambient = ambient;
    this->specular = specular;
    this->diffuse = diffuse;
}

void Light::setAmbinet(unsigned int shaderID) {

}

void Light::setSpecular(unsigned int shaderID) {

}

void Light::setDiffuse(unsigned int shaderID) {

}

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 direction):Light(ambient,specular,diffuse),
direction(direction) {}

void DirectionalLight::UpdateDirection(glm::vec3 angles) {
    direction = glm::rotateZ(direction,angles.z);
    direction = glm::rotateX(direction,angles.x);
    direction = glm::rotateY(direction,angles.y);
    direction = -1.0f * direction;
}

void DirectionalLight::setAmbinet(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"directionLight.ambient"),this->ambient.x,this->ambient.y,this->ambient.z);
}

void DirectionalLight::setSpecular(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"directionLight.specular"),this->specular.x,this->specular.y,this->specular.z);
}

void DirectionalLight::setDiffuse(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"directionLight.diffuse"),this->diffuse.x,this->diffuse.y,this->diffuse.z);
}

void DirectionalLight::setDirection(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"directionLight.angle"),this->direction.x,this->direction.y,this->direction.z);
}

PointLight::PointLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 position, float constant,
                       float linear, float quadratic):Light(ambient,specular,diffuse),position(position),constant(constant),
                       linear(linear),quadratic(quadratic){}

void PointLight::setAmbinet(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"pointLight.ambient"),this->ambient.x,this->ambient.y,this->ambient.z);
}

void PointLight::setSpecular(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"pointLight.specular"),this->specular.x,this->specular.y,this->specular.z);
}

void PointLight::setDiffuse(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"pointLight.diffuse"),this->diffuse.x,this->diffuse.y,this->diffuse.z);
}

void PointLight::setConstant(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"pointLight.constant"),this->constant);
}

void PointLight::setLinear(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"pointLight.linear"),this->linear);
}

void PointLight::setQuadratic(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"pointLight.quadratic"),this->quadratic);
}

void PointLight::setPosition(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"pointLight.Position"),this->position.x,this->position.y,this->position.z);
}

SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 position, glm::vec3 direction,
                     float constant, float linear, float quadratic, float cutoff, float outerCutoff):Light(ambient,specular,diffuse),position(position),
                     direction(direction),constant(constant),linear(linear),quadratic(quadratic),cutOff(cutoff),outerCutOff(outerCutoff){}

void SpotLight::setAmbinet(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"spotLightt.ambient"),this->ambient.x,this->ambient.y,this->ambient.z);
}

void SpotLight::setSpecular(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"spotLight.specular"),this->specular.x,this->specular.y,this->specular.z);
}

void SpotLight::setDiffuse(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"spotLight.diffuse"),this->diffuse.x,this->diffuse.y,this->diffuse.z);
}

void SpotLight::setPosition(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"spotLight.position"),this->position.x,this->position.y,this->position.z);
}

void SpotLight::setDirection(unsigned int shaderID) {
    glUniform3f(glGetUniformLocation(shaderID,"spotLight.direction"),this->direction.x,this->direction.y,this->direction.z);
}

void SpotLight::setConstant(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"spotLight.constant"),this->constant);
}

void SpotLight::setLinear(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"spotLight.linear"),this->linear);
}

void SpotLight::setQuadratic(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"spotLight.quadratic"),this->quadratic);
}

void SpotLight::setCutff(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"spotLight.cutOff"),this->cutOff);
}

void SpotLight::setOuterCutoff(unsigned int shaderID) {
    glUniform1f(glGetUniformLocation(shaderID,"spotLight.outerCutOff"),this->outerCutOff);
}
