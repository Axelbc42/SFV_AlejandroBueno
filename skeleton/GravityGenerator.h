#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator {
public:
    GravityGenerator(const Vector3D& g) : gravity(g) {}

    void updateForce(Particle* p, double dt) override {
        p->addForce(gravity * p->getMass());   // F = m * g
    }
private:
    Vector3D gravity;
};