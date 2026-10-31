#include "WindGenerator.h"

WindGenerator::WindGenerator(const Vector3D& windVel, const Vector3D& center, float r, float k1, float k2)
    : wind(windVel), pos(center), dist(r), k1(k1), k2(k2) {
}

void WindGenerator::updateForce(Particle* p, double dt) {
    if (!active || !inside(p->getPos())) return;

    Vector3D dv = windAt(p->getPos()) - p->getVel();     // vv - v
    float mod = sqrt(dv.x * dv.x + dv.y * dv.y + dv.z * dv.z);

    p->addForce(dv * k1 + dv * (k2 * mod));              // F = k1*(vv-v) + k2*|vv-v|*(vv-v)
}

bool WindGenerator::inside(const Vector3D& pPos) const {
    Vector3D d = pPos - pos;
    return d.x * d.x + d.y * d.y + d.z * d.z < dist * dist;
}
