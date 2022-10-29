//
// Created by 刘小备 on 2019/3/10.
//

#ifndef TEST_MATERIAL_H
#define TEST_MATERIAL_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Material {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
public:
    const glm::vec3 &getAmbient() const;

    const glm::vec3 &getDiffuse() const;

    const glm::vec3 &getSpecular() const;

    float getShininess() const ;

    void setAmbient(glm::vec3 ambient);

    void setDiffuse(glm::vec3 diffuse);

    void setSpecular(glm::vec3 specular);

    void setShininess(float shininess);
};


#endif //TEST_MATERIAL_H
