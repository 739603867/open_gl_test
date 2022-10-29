//
// Created by 刘小备 on 2019/4/11.
//

#ifndef TEST_SCENECONTROLLER_H
#define TEST_SCENECONTROLLER_H

#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Camera.h"
#include <irrKlang.h>
#include <random>
#include <ctime>
struct Ray{
    glm::vec3 origin;
    glm::vec3 direction;
    float t;
    Ray();
};

bool interscetBox(const Ray& ray, const Collider& collider);

struct Node{
    Node * next;
    Model * model;
    glm::mat4 tran;
    std::string tag;
    Node(const char * path, std::string tag, glm::mat4 model);
    Node(Model * model1, std::string tag, glm::mat4 model);
    ~Node();
};

struct EnemyNode{
    EnemyNode * next;
    Model * model;
    glm::mat4 tran;
    glm::mat4 moveTran;
    std::string tag;
    int health;
    bool dead;
    EnemyNode(const char * path, std::string tag, glm::mat4 model);
};

class SceneController {
public:
    Node * head;
    unsigned int size;
    SceneController();
    ~SceneController();
    void insert(Node * node);
    void Draw(Shader shader);
    void InitScene();
    void checkCollision(Node * player, Camera * camera);
    float calcuteAngle(glm::vec3 a, glm::vec3 b);
};

class Enemy{
public:
    Enemy();
    EnemyNode * enemy;
    unsigned int size;
    const static int maxSize = 3;
    void Init();
    void Insert(EnemyNode * node);
    void checkShoot(Camera * camera, Node * player, irrklang::ISoundEngine* engine, int& score);
    void Draw(Shader shader);
    void checkAmount();
};

#endif //TEST_SCENECONTROLLER_H
