#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, Particle* liquid_particle) :
    _height(h), _volume(V), _liquid_density(d), _liquid_particle(liquid_particle) {}


void BuoyancyForceGenerator::updateForce(Particle* p, double dt) {
    float h = p->getPos().y;
    float h0 = _liquid_particle->getPos().y;

    Vector3 f(0, 0, 0);
    float immersed = 0.0;
    if (h - h0 > _height * 0.5) 
        immersed = 0.0;
    else if (h0 - h > _height * 0.5)
        immersed = 1.0;
    else 
        immersed = (h0 - h) / _height + 0.5;

    f.y = _liquid_density * _volume * immersed;

    p->addForce(f);
}