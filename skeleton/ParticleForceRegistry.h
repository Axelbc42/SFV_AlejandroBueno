#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
class ParticleForceRegistry
{
public:
    void add(Particle* p, ForceGenerator* fg) { registry.push_back({ p, fg }); }

    void remove(Particle* p, ForceGenerator* fg) {
        for (int i = 0; i < registry.size(); ) {
            if (registry[i].p == p && registry[i].fg == fg)
                registry.erase(registry.begin() + i);   // no avanzo i ya que el siguiente elemento ocupa este hueco
            else
                i++;
        }
    }

    void updateForces(double dt) {
        for (auto& r : registry)
            if (r.p->isAlive())
                r.fg->updateForce(r.p, dt);
    }

    void updateBoat(double dt) {
        for (auto& r : bRegistry)
            if (r.b->isAlive())
				r.fg->updateForce(r.b, dt);
	}

private:
    struct Pair { Particle* p; ForceGenerator* fg; };
    std::vector<Pair> registry;

    struct bFG { Boat* b; ForceGenerator* fg; };
    std::vector<bFG> bRegistry;
};

