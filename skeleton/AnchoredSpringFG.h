#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG :public SpringForceGenerator {
public:
    AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
        _other = new Particle(anchor_pos, Vector3D(0,0,0), Vector3D(0,0,0), 99999, 1, 0.0, Vector4(0,0,1,1), 0.0, CUBE);
    }

    ~AnchoredSpringFG() { delete _other; }
};