#pragma once
#include "WindGenerator.h"

class TornadoGenerator : public WindGenerator {
public:
    TornadoGenerator(const Vector3D& center, float radius, float K,
        float k1, float k2 = 0.0f, float lift = 50.0f)
        : WindGenerator(Vector3D(0, 0, 0), center, radius, k1, k2), K(K), lift(lift) {
    }

protected:
    Vector3D windAt(const Vector3D& p) const override {
        Vector3D d = p - pos;
        return Vector3D(-d.z, lift - d.y, d.x) * K;
    }

private:
    float K;        // intensidad del torbellino
    float lift;     // componente vertical
};

