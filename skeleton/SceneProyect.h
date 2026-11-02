#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <memory>
#include "Particle.h"

class SceneProyect : public Scene {
public:
    explicit SceneProyect(std::string name) : Scene(std::move(name)) {}

    void init() override {
        seaTr = physx::PxTransform(physx::PxVec3(0, -0.5f, 0));
        sea = new RenderItem(CreateShape(physx::PxBoxGeometry(500.0f, 0.5f, 500.0f)), &seaTr, Vector4(0.2f, 0.5f, 1.0f, 1.0f));
    }

    void update(double dt) override {
        for (auto& s : systems)
            s->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        if (sea) {
            sea->release();
            sea = nullptr;
        }
        systems.clear();
    }

private:
    std::vector<std::unique_ptr<ParticleSystem>> systems;

    physx::PxTransform seaTr;
    RenderItem* sea = nullptr;
};