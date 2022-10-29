//
// Created by 刘小备 on 2019/4/21.
//

#ifndef TEST_PARTICLESYSTEM_H
#define TEST_PARTICLESYSTEM_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

const int maxSize = 100;
int nFreeIndex = 0;
class Particle{
public:
    glm::vec3 vPos;
    glm::vec3 vChangePos;
    glm::vec3 vStartPos;
    glm::vec3 color;
    glm::vec3 deltaColor;
    float fCurrentSize;
    float fSize;
    float fDeltaSize;
    float fRemainingLife;
};

struct GravityModeData{
    glm::vec3 vInitialValocity;  //初始化速度
    glm::vec3 fRadialAccel;      //径向加速度，与运动方向垂直
    glm::vec3 fTangentialAccel;  //切向加速度
} gravityMode;

struct RadiusModeData{
    float fAngle;               //发射角度
    float fDegressPerSecond;    //每秒旋转角度
    float fRadius;              //半径
    float fDelatRadius;         //半径变化量
} radiusMode;

static std::vector<Particle *> vParticlePool;   //存储粒子容器
static std::vector<Particle *> vUnusedParticleList;     //存储未被使用的容器

class ParticleSystem {

};

void initParticlePool();

#endif //TEST_PARTICLESYSTEM_H
