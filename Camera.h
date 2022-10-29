//
// Created by 刘小备 on 2019/2/26.
//

#ifndef TEST_CAMERA_H
#define TEST_CAMERA_H
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "rigidbody.h"
enum Camera_Movement{
    FORWARD,
    BACK,
    RIGHT,
    LEFT,
    UP
};
class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 worldup, glm::vec3 target);
//    ~Camera();
    Camera(glm::vec3 position, glm::vec3 worldup, float yaw, float pitch);
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Up;
    glm::vec3 WorldUP;
    glm::vec3 Right;
    Rigidbody rigidbody;

    float Yaw;
    float Pitch;
    float SpeedZ = 0.5f;
    float MouseSensitivity = 0.10f;
    glm::mat4 getViewMat();
    void updatePosition();

    void processKeyBoard(Camera_Movement movement, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
private:
    void updateCameraVectors();

};


#endif //TEST_CAMERA_H
