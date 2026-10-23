#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"


class SceneP2 : public Scene {
public:
    explicit SceneP2(std::string name) : Scene(std::move(name)) {}

    void init() override {

    }

    void update(double dt) override {
        for (auto& s : systems)
            s->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        systems.clear();
    }

private:
    std::vector<std::unique_ptr<ParticleSystem>> systems;
};
