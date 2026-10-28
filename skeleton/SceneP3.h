#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"

class SceneP3 : public Scene {
public:
    explicit SceneP3(std::string name) : Scene(std::move(name)) {}

    void init() override {
        auto fuente = std::make_unique<ParticleSystem>(1000);
        fuente->addEmitter(ParticleGenerator(
            Vector3D(0, 0, 0), Vector3D(0, 0, 0),
            true, Vector3D(0, 25, 0), Vector3D(3, 2, 3),
            4, 2,
            4.0f, 0.5f,
            0.2f, 0.99, 1.0f,
            Vector4(0.2f, 0.5f, 1.0f, 1.0f)));
        fuente->addForceGenerator(std::make_shared<GravityGenerator>(Vector3D(0, -9.8, 0)));
        fuente->addForceGenerator(std::make_shared<WindGenerator>(Vector3D(15, 0, 0), Vector3D(0, 10, 0), 20.0f, 0.5f));
        systems.push_back(std::move(fuente));

        auto niebla = std::make_unique<ParticleSystem>(1000, 50);
        niebla->addEmitter(ParticleGenerator(
            Vector3D(30, 2, 0), Vector3D(15, 2, 15),
            true, Vector3D(0, 0.5f, 0), Vector3D(0.5f, 0.3f, 0.5f),
            5, 2,
            6.0f, 1.0f,
            0.1f, 0.99, 0.0f,
            Vector4(0.8f, 0.8f, 0.8f, 0.15f)));
        systems.push_back(std::move(niebla));

        auto chispas = std::make_unique<ParticleSystem>(1000);
        chispas->addEmitter(ParticleGenerator(
            Vector3D(-30, 0, 0), Vector3D(0.5f, 0, 0.5f),
            false, Vector3D(-6, 11, -6), Vector3D(6, 19, 6),
            6, 3,
            1.2f, 0.3f,
            0.15f, 0.95, 1.0f,
            Vector4(1.0f, 0.5f, 0.0f, 1.0f)));
        chispas->addForceGenerator(std::make_shared<GravityGenerator>(Vector3D(0, -9.8, 0)));
        systems.push_back(std::move(chispas));
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
