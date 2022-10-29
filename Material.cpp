//
// Created by 刘小备 on 2019/3/10.
//

#include "Material.h"

const glm::vec3 &Material::getAmbient() const {
    return ambient;
}

const glm::vec3 &Material::getDiffuse() const {
    return diffuse;
}

const glm::vec3 &Material::getSpecular() const {
    return specular;
}

float Material::getShininess() const {
    return shininess;
}
void Material::setAmbient(glm::vec3 ambient){
    this->ambient = ambient;
}

void Material::setDiffuse(glm::vec3 diffuse){
    this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec3 specular){
    this->specular = specular;
}

void Material::setShininess(float shininess){
    this->shininess = shininess;
}