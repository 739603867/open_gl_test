//
// Created by 刘小备 on 2019/4/4.
//

#include "FirstPersonGun.h"

FirstPersonGun::FirstPersonGun(Camera & camera) {
    this->camera = &camera;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,camera.Position);
    model = glm::rotate(model, glm::radians(camera.Pitch), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(-camera.Yaw), glm::vec3(0, 1, 0));
    model = glm::translate(model,glm::vec3(2.5f, -1.0f, -0.3f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    this->player = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/gun_n/AK47.obj", "person",model);
    this->player->model->translate(model);
    this->player->model->merge();
}

FirstPersonGun::~FirstPersonGun() {
    this->player = nullptr;
    this->camera = nullptr;
}

void FirstPersonGun::Draw(Shader shader) {
    setPlayerModel();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &this->player->tran[0][0]);
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view(1.0f);
    view = camera->getViewMat();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
    player->model->Draw(shader);
    //对于玩家里说相当于重新组装包围盒
    player->model->merge();
    player->model->translate(this->player->tran);
}

void FirstPersonGun::setPlayerModel() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,camera->Position);
    model = glm::rotate(model, glm::radians(-camera->Yaw), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(camera->Pitch), glm::vec3(0, 0, 1));
    model = glm::translate(model,glm::vec3(2.5f, -1.0f, -0.3f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    this->player->tran = model;
}



