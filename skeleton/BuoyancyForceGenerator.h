#pragma once

#include "ForceGenerator.h"

class BuoyancyForceGenerator :public ForceGenerator {
public:
    BuoyancyForceGenerator(float h, float V, float d, Particle* liquid_particle);
    virtual ~BuoyancyForceGenerator() {}

    virtual void updateForce(Particle* particle, double dt);

protected:
    float _height;
    float _volume;
    float _liquid_density;

    Particle* _liquid_particle;
};