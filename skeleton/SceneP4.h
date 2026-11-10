#pragma once
#include "Scene.h"
#include "BuoyancyForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "ParticleForceRegistry.h"
#include "GravityGenerator.h"

class SceneP4 : public Scene {
public:
    explicit SceneP4(std::string name) : Scene(std::move(name)) {}

    void init() override {
        //_p1 = new Particle(Vector3D(10, 10, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        //_anchored = new AnchoredSpringFG(0.1, 0, Vector3D(0, 10, 0));
        //_gravityG = new GravityGenerator(Vector3D(0, -9.8, 0));
        //_registry.add(_p1, _gravityG);
        //_registry.add(_p1, _anchored);

        _p2 = new Particle(Vector3D(10, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _p3 = new Particle(Vector3D(-10, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _spring2 = new SpringForceGenerator(0.1, 5, _p2);
        _spring3 = new SpringForceGenerator(0.1, 5, _p3);

        _registry.add(_p3, _spring2);
        _registry.add(_p2, _spring3);
    }

    void update(double dt) override {
        _registry.updateForces(dt);
        //_p1->integrateEulerSI(dt);
        _p2->integrateEulerSI(dt);
        _p3->integrateEulerSI(dt);

    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
    }

private:
    Particle* _p1 = nullptr;
    AnchoredSpringFG* _anchored = nullptr;
    GravityGenerator* _gravityG;

    Particle* _p2 = nullptr;
    Particle* _p3 = nullptr;
    SpringForceGenerator* _spring2 = nullptr;
    SpringForceGenerator* _spring3 = nullptr;


    ParticleForceRegistry _registry;
};
