//
// Created by 刘小备 on 2019/4/6.
//

#include "rigidbody.h"

Rigidbody::Rigidbody() {
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this->gravity = glm::vec3(0.0f, -gravityAcceler, 0.0f);
    this->accelerUp = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Rigidbody::jumpAndUpdateVelocity() {
    velocity = glm::vec3(0.0f, jumpInitSpeed, 0.0f);
//    accelerUp.y = 0.0f;
}

void Rigidbody::onLand() {
//    if(onland)
//        accelerUp.y = 0.08f;
//    else
//        accelerUp.y = 0.0f;
    if(onland){
        velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        accelerUp = -gravity;
        return;
    }
    accelerUp = glm::vec3(0.0f, 0.0f, 0.0f);
}






