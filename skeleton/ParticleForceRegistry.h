#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
class ParticleForceRegistry
{
public:
    void add(Particle* p, ForceGenerator* fg) { registry.push_back({ p, fg }); }

    //void remove(Particle* p, ForceGenerator* fg) {
    //    for (int i = 0; i < registry.size(); ) {
    //        if (registry[i].p == p && registry[i].fg == fg)
    //            registry.erase(registry.begin() + i);   // no avanzo i ya que el siguiente elemento ocupa este hueco
    //        else
    //            i++;
    //    }
    //}

    //void removeParticle(Particle* p) {
    //    for (int i = 0; i < registry.size(); ) {
    //        if (registry[i].p == p)
    //            registry.erase(registry.begin() + i);   // no avanzo i ya que el siguiente elemento ocupa este hueco
    //        else
    //            i++;
    //    }
    //}

    //void removeGenerator(ForceGenerator* fg) {
    //    for (int i = 0; i < registry.size(); ) {
    //        if (registry[i].fg == fg)
    //            registry.erase(registry.begin() + i);   // no avanzo i ya que el siguiente elemento ocupa este hueco
    //        else
    //            i++;
    //    }
    //}

    void clear() { registry.clear(); }

    void updateForces(double dt) {
        for (auto& r : registry)
            if (r.p->isAlive())
                r.fg->updateForce(r.p, dt);
    }

private:
    struct Pair { Particle* p; ForceGenerator* fg; };
    std::vector<Pair> registry;     // no es dueño de nada, solo punteros
};

