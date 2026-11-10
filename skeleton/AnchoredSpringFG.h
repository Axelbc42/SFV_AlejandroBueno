#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG :public SpringForceGenerator {
public:
    AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
        _other = new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 100, 1, 0.0);
    }

    ~AnchoredSpringFG() { delete _other; }
};