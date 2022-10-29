//
// Created by 刘小备 on 2019/5/21.
//

#ifndef TEST_ANIMITION_H
#define TEST_ANIMITION_H

#endif //TEST_ANIMITION_H

#include "SceneController.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

void tranlateAni(Node * node){
    float trans = sin(glfwGetTime()) * 0.02;
    node->tran = glm::translate(node->tran, trans * glm::vec3(10, 0, 10));
}

void rotateAni(Node * node, glm::vec3 asix){
    float trans = sin(glfwGetTime());
    node->tran = glm::rotate(node->tran,glm::radians(trans),asix);
}

void scaleAni(Node * node,glm::vec3 scaleSize){
    float trans = sin(glfwGetTime()) * 0.02;
    node->tran = glm::scale(node->tran,trans * scaleSize);
}