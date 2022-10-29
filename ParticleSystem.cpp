//
// Created by 刘小备 on 2019/4/21.
//

#include "ParticleSystem.h"

void initParticlePool(unsigned int size){
    Particle* particle = nullptr;
    for ( int i = 0; i < size; i++ ) {
        particle = new Particle;
        vParticlePool.push_back(particle);
        vUnusedParticleList.push_back(particle);
    }
}