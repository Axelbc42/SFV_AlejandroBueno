#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
class ParticleForceRegistry
{
public:
    void add(Particle* p, ForceGenerator* fg) { registry.push_back({ p, fg }); }

    void updateForces(double dt) {
        for (auto& r : registry)
            if (r.p->isAlive())
                r.fg->updateForce(r.p, dt);
    }

private:
    struct Pair { Particle* p; ForceGenerator* fg; };
    std::vector<Pair> registry;
};

