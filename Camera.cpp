//
// Created by 刘小备 on 2019/2/26.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldup, glm::vec3 target) {
    Position = position;
    WorldUP = worldup;
    Forward = glm::normalize(Position-target);
    Right = glm::normalize(glm::cross(Forward,WorldUP));
    Up = glm::normalize(glm::cross(Forward,Right));
}

Camera::Camera(glm::vec3 position, glm::vec3 worldup, float yaw, float pitch) {
    Position = position;
    WorldUP = worldup;
    Pitch = pitch;
    Yaw = yaw;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMat() {
    return glm::lookAt(Position, Position+Forward, Up);
}

void Camera::updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Forward = glm::normalize(front);
        Right = glm::normalize(glm::cross(Forward, WorldUP));
        Up    = glm::normalize(glm::cross(Right, Forward));
}

void Camera::processKeyBoard(Camera_Movement movement, float deltaTime) {
    float velocity = SpeedZ * deltaTime;
    if(rigidbody.collide){
        if(movement == FORWARD && !rigidbody.collideForward){
        float lastY = Position.y;
        Position += Forward * velocity;
        if(rigidbody.onland){
            Position.y = lastY;
        }
        }
        else if(movement == BACK && !rigidbody.collideBack){
        float lastY = Position.y;
        Position -= Forward * velocity;
        if(rigidbody.onland){
            Position.y = lastY;
        }
        }
        else if(movement == LEFT && !rigidbody.collideLeft){
        Position -= Right * velocity;
        }
        else if(movement == RIGHT && !rigidbody.collideRight)
        Position += Right * velocity;
        else ;
    }
    else{
        if(movement == FORWARD){
            float lastY = Position.y;
            Position += Forward * velocity;
            if(rigidbody.onland){
                Position.y = lastY;
            }
        }
        else if(movement == BACK){
            float lastY = Position.y;
            Position -= Forward * velocity;
            if(rigidbody.onland){
                Position.y = lastY;
            }
        }
        else if(movement == LEFT){
            Position -= Right * velocity;
        }
        else if(movement == RIGHT)
            Position += Right * velocity;
        else ;
    }
    if(movement == UP && rigidbody.onland) {
        rigidbody.jumpAndUpdateVelocity();
        Position += rigidbody.velocity;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    if (Yaw > 180)//横向角度范围0-360，超界后如下处理可以保证视角连贯变化
        Yaw = -180;
    else if (Yaw < -180)
        Yaw = 180;
    updateCameraVectors();
}

void Camera::updatePosition() {
    if(Position.y < 8.0f && !rigidbody.onland)
        Position.y = 8.0f;
    glm::vec3 acceleration = this->rigidbody.gravity+this->rigidbody.accelerUp;
    this->rigidbody.velocity += acceleration;
    Position += this->rigidbody.velocity;
}

