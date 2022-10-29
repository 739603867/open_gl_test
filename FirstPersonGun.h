//
// Created by 刘小备 on 2019/4/4.
//

#ifndef TEST_FIRSTPERSONGUN_H
#define TEST_FIRSTPERSONGUN_H

#include "Model.h"
#include "Camera.h"
#include "SceneController.h"
class FirstPersonGun {
public:
    FirstPersonGun(Camera & camera);
    ~FirstPersonGun();
    void Draw(Shader shader);
    void setPlayerModel();
    Node * player;
    Camera * camera;
};

#endif //TEST_FIRSTPERSONGUN_H
