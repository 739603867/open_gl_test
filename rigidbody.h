//
// Created by 刘小备 on 2019/4/6.
//

#ifndef TEST_RIGIDBODY_H
#define TEST_RIGIDBODY_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Model.h"
const float gravityAcceler = 0.08f;
const float jumpInitSpeed = 2.0f;

class Rigidbody {
public:
    Rigidbody();
    void jumpAndUpdateVelocity();
    void onLand();
    bool onland = false;
    bool collide = false;
    bool collideForward = false;
    bool collideBack = false;
    bool collideLeft = false;
    bool collideRight = false;
    glm::vec3 velocity;
    glm::vec3 accelerUp;
    glm::vec3 gravity;
};


#endif //TEST_RIGIDBODY_H
