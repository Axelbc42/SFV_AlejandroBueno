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
        seaTr.assign(seaWidth * seaWidth, physx::PxTransform(physx::PxVec3(0, 0, 0)));
        seaItems.assign(seaWidth * seaWidth, nullptr);
        float half = (seaWidth - 1) * cellSize * 0.5f;

        for (int x = 0; x < seaWidth; x++) {
            for (int z = 0; z < seaWidth; z++) {
                int i = x * seaWidth + z;
                seaTr[i].p = physx::PxVec3(x * cellSize - half, 0.0f, z * cellSize - half);

                seaItems[i] = new RenderItem(
                    CreateShape(physx::PxBoxGeometry(cellSize * 0.5f, 0.25f, cellSize * 0.5f)),
                    &seaTr[i],
                    Vector4(0.2f, 0.5f, 1.0f, 1.0f));
            }
        }

        auto niebla = std::make_unique<ParticleSystem>(10000, 50);
        niebla->addEmitter(ParticleGenerator(
            Vector3D(0, 2, 0), Vector3D(20, 1.5f, 20),
            true, Vector3D(0, 0.5f, 0), Vector3D(0.5f, 0.3f, 0.5f),
            5, 2,
            6.0f, 1.0f,
            0.05f, 0.99,
            Vector4(0.8f, 0.8f, 0.8f, 0.15f)));
        niebla->addForceGenerator(std::make_shared<TornadoGenerator>(Vector3D(0, 1.5f, 0), 10.0f, 0.5f, 2.0f, 0.0f, 10.0f));
        systems.push_back(std::move(niebla));


    }

    void update(double dt) override {
        time += dt;

        for (auto& s : systems)
            s->update(dt);

        for (int x = 0; x < seaWidth; x++) {
            for (int z = 0; z < seaWidth; z++) {
                float distance = (float)(x + z);
                float offset = std::sin(time * waveSpeed + distance * waveFrequency) * waveMaxHeight;
                seaTr[x * seaWidth + z].p.y = offset;
            }
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        systems.clear();

        for (auto* item : seaItems) {
            // Libéralos igual que haces en Particle::deactivate() (desregistrar y luego delete)
            // DeregisterRenderItem(item);
            // delete item;
        }
        seaItems.clear();
        seaTr.clear();
    }

private:
    std::vector<std::unique_ptr<ParticleSystem>> systems;

    int   seaWidth = 20;
    float cellSize = 2.0f;
    float waveSpeed = 0.5f;
    float waveFrequency = 0.5f;
    float waveMaxHeight = 0.5f;
    float time = 0.0f;

    std::vector<physx::PxTransform> seaTr;   // un transform por celda
    std::vector<RenderItem*> seaItems;       // un RenderItem por celda
};