//
// Created by 刘小备 on 2019/4/11.
//

#include "SceneController.h"

SceneController::SceneController() {
    size = 0;
    head = nullptr;
}

void SceneController::insert(Node * node) {
    node->model->merge();
    node->model->translate(node->tran);
    node->next = head;
    head = node;
    ++size;
}

void SceneController::Draw(Shader shader) {
    for(Node * tmp = head; tmp!= nullptr; tmp = tmp->next){
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &tmp->tran[0][0]);
        tmp->model->Draw(shader);
    }
}

void SceneController::InitScene() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    Node * node = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Land.obj","Land",model);
    node->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/med cobble.jpg");
    node->model->collider._max.y += 4.0f;
    insert(node);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node1 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/guildhall.obj","build",model);
    node1->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node1);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(30.0f, 5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node2 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/TownhouseA.obj","build",model);
    node2->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node2);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 5.0f,30.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node3 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/TownHouseB.obj","build",model);
    node3->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node3);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-30.0f, 5.0f,30.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node4 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/RowHousePartA.obj", "build",model);
    node4->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node4);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(30.0f, 5.0f,30.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node5 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/RowHousePartB.obj", "build",model);
    node5->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node5);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(50.0f, 4.0f,30.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    Node * node6 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/RowHousePartC.obj", "build",model);
    node6->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node6);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(20.0f, 5.3f,20.0f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    Node * node7 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/breadstall.obj", "build",model);
    node7->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node7);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-30.0f, 5.3f,-30.0f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    Node * node8 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/ClothingStall.obj","build",model);
    node8->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node8);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-10.0f, 5.3f,30.0f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    Node * node9 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/fish stall.obj","build",model);
    node9->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node9);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-20.0f, 5.3f, 20.0f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    Node * node10 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/fish stall.obj","build",model);
    node10->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node10);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(65.0f, 4.3f, 0.0f));
    model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
    Node * node11 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/FruitStall.obj","build",model);
    node11->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container2.png");
    insert(node11);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(70.0f, 4.0f, -20.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    Node * node12 = new Node("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/palmtree.obj","tree",model);
    node12->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node12->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node12);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-60.0f, 3.8f, -20.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    Node * node13 = new Node(node12->model,"tree",model);
    node13->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node13->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node13);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(45.0f, 3.5f, 40.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    Node * node14 = new Node(node12->model,"tree",model);
    node14->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node14->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node14);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(20.0f, 3.5f, 40.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    Node * node15= new Node(node12->model,"tree",model);
    node15->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node15->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node15);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(10.0f, 3.5f, 40.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    Node * node16= new Node(node12->model,"tree",model);
    node16->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node16->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node16);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(40.0f, 3.5f, 10.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    Node * node17= new Node(node12->model,"tree",model);
    node17->model->setMeshTexture(0,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/trunk.jpg");
    node17->model->setMeshTexture(1,"/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/Doc4b2.jpg");
    insert(node17);
}

SceneController::~SceneController() {

}

void SceneController::checkCollision(Node * player, Camera * camera) {
    for(Node * tmp = head; tmp!= nullptr;tmp = tmp->next){
        if(player->model->collider.intersects(tmp->model->collider)){
            if(tmp->model->tag=="Land")
                camera->rigidbody.onland = true;
            if(tmp->model->tag == "build"&!camera->rigidbody.collide){
                camera->rigidbody.collide=true;
                Ray ray;
                ray.origin = camera->Position;
                ray.direction = camera->Forward;
                if(interscetBox(ray, tmp->model->collider)){
                    camera->rigidbody.collideForward = true;
                }
                ray.direction = -camera->Forward;
                if(interscetBox(ray, tmp->model->collider)){
                    camera->rigidbody.collideBack = true;
                }
                ray.direction = camera->Right + camera->Forward * 3.0f;
                if(interscetBox(ray, tmp->model->collider)){
                    camera->rigidbody.collideRight = true;
                }
                ray.direction = -camera->Right + camera->Forward * 3.0f;
                if(interscetBox(ray, tmp->model->collider)){
                    camera->rigidbody.collideLeft = true;
                }
            }
        }
        else{
            camera->rigidbody.onland = false;
        }
    }
}

float SceneController::calcuteAngle(glm::vec3 a, glm::vec3 b) {
    a = glm::normalize(a);
    b = glm::normalize(b);
    return glm::dot(a,b);
}


Node::Node(const char *path, std::string tag, glm::mat4 model) {
    this->model = new Model(path,tag);
    this->tran = model;
    this->tag = tag;
    this->model->merge();
    this->model->translate(model);
    this->next = nullptr;
}

Node::Node(Model * model1, std::string tag, glm::mat4 model) {
    this->model = model1;
    this->tran = model;
    this->tag = tag;
    this->model->merge();
    this->model->translate(model);
    this->next = nullptr;
}

Node::~Node() {

}

void Enemy::Init() {
    size = 0;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(30.0f,30.0f,18.0f));
    EnemyNode * node = new EnemyNode("/Users/liuxiaobei/CLionProjects/openGL_Test/gun_n/StarFighter.obj","enemy",model);
    node->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/air.jpg");
    Insert(node);
    model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(10.0f,30.0f,-6.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
    EnemyNode * node1 = new EnemyNode("/Users/liuxiaobei/CLionProjects/openGL_Test/gun_n/StarFighter.obj","enemy",model);
    node1->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/air.jpg");
    Insert(node1);
    model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(-25.0f,30.0f,-22.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
    EnemyNode * node2 = new EnemyNode("/Users/liuxiaobei/CLionProjects/openGL_Test/gun_n/StarFighter.obj","enemy",model);
    node2->model->setMeshTexture("/Users/liuxiaobei/CLionProjects/openGL_Test/Scene/Texture/air.jpg");
    Insert(node2);
}

void Enemy::Insert(EnemyNode *node) {
    if(node != nullptr && size < maxSize){
        node->model->merge();
        node->model->translate(node->tran);
        node->next = enemy;
        enemy = node;
        ++size;
    }
}

void Enemy::Draw(Shader shader) {
    for(EnemyNode * tmp = enemy; tmp!= nullptr; tmp = tmp->next){
        if(!tmp->dead){
            float a = sin(glfwGetTime()) * 0.02;
            tmp->moveTran = glm::translate(tmp->moveTran, a * glm::vec3(10, 0, 10));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &tmp->moveTran[0][0]);
            tmp->model->Draw(shader);
            tmp->model->merge();
            tmp->model->translate(tmp->moveTran);
        }
    }
}

void Enemy::checkAmount() {
    static std::default_random_engine e(time(nullptr));
    static std::uniform_int_distribution<unsigned> u(0,40);
    if(size == 0){
        for(EnemyNode * tmp = enemy; tmp != nullptr; tmp = tmp->next){
            tmp->dead = false;
            tmp->health = 100;
            int xmove = u(e) - 20;
            int zmove = u(e) -20;
//            tmp->moveTran = tmp->tran;
            tmp->moveTran = glm::translate(tmp->tran,glm::vec3(xmove,0,zmove));
            ++size;
        }
    }
}

Enemy::Enemy() {
    enemy = nullptr;
    Init();
}

void Enemy::checkShoot(Camera * camera, Node * player, irrklang::ISoundEngine* engine, int & score) {
   for(EnemyNode * tmp = enemy; tmp != nullptr; tmp = tmp->next){
       Ray ray;
       ray.origin = camera->Position;
       ray.direction = camera->Forward;
       if(interscetBox(ray,tmp->model->collider) && !tmp->dead)
       {
           tmp->health -= 2;
           if(tmp->health<0){
               tmp->dead = true;
               --size;
               engine->play2D("/Users/liuxiaobei/CLionProjects/openGL_Test/Sound/explosion.wav");
               score += 10;
           }
       }
   }
}


Ray::Ray() {
    origin = glm::vec3(0);
    direction = glm::vec3(0);
    t = std::numeric_limits<float>::max();
}

bool interscetBox(const Ray& ray, const Collider& collider) {
    glm::vec3 inv_dir = 1.0f/ray.direction;
    glm::vec3 tMin = (collider._min - ray.origin) * inv_dir;
    glm::vec3 tMax = (collider._max - ray.origin) * inv_dir;
    glm::vec3 t1 = glm::min(tMin,tMax);
    glm::vec3 t2 = glm::max(tMin,tMax);
    float tNear = std::max(std::max(t1.x, t1.y), t1.z);
    float tFar = std::min(std::min(t2.x, t2.y), t2.z);
    if(tNear > tFar)
        return false;
    else
        return true;
}

EnemyNode::EnemyNode(const char *path, std::string tag, glm::mat4 model){
    this->model = new Model(path,tag);
    this->tran = model;
    this->next = nullptr;
    this->tag = tag;
    this->model->merge();
    this->model->translate(this->tran);
    this->moveTran = model;
    dead = false;
    health = 100;
}
