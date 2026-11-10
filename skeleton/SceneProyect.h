#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <memory>
#include "Particle.h"
#include "Boat.h"

class SceneProyect : public Scene {
public:
    explicit SceneProyect(std::string name) : Scene(std::move(name)) {}

    void init() override {
        seaTr.assign(seaWidth * seaWidth, physx::PxTransform(physx::PxVec3(0, 0, 0)));
        seaItems.assign(seaWidth * seaWidth, nullptr);
        float gridHalf = (seaWidth - 1) * cellSize * 0.5f;

        for (int x = 0; x < seaWidth; x++) {
            for (int z = 0; z < seaWidth; z++) {
                int i = x * seaWidth + z;
                seaTr[i].p = physx::PxVec3(x * cellSize - gridHalf, 0.0f, z * cellSize - gridHalf);

                seaItems[i] = new RenderItem(
                    CreateShape(physx::PxBoxGeometry(cellSize * 0.5f, 0.25f, cellSize * 0.5f)),
                    &seaTr[i],
                    Vector4(0.2f, 0.5f, 1.0f, 1.0f));
            }
        }

        float seaHalf = seaWidth * cellSize * 0.5f;
        float maxDist = seaHalf * 0.7f * 2;
        auto niebla = std::make_unique<ParticleSystem>(3600, maxDist);
        niebla->addEmitter(ParticleGenerator(
            Vector3D(0, 2, 0), Vector3D(seaHalf, 1.5f, seaHalf),
            true, Vector3D(0, 0.5f, 0), Vector3D(0.5f, 0.3f, 0.5f),
            5, 2,
            6.0f, 1.0f,
            0.05f, 0.99,
            Vector4(0.8f, 0.8f, 0.8f, 0.15f)));
        niebla->addForceGenerator(std::make_shared<TornadoGenerator>(Vector3D(0, 1.5f, 0), 10.0f, 0.5f, 2.0f, 0.0f, 10.0f));

        Vector3D corners[4] = {
            Vector3D(-seaHalf, 2, -seaHalf),
            Vector3D(seaHalf, 2, -seaHalf),
            Vector3D(seaHalf, 2,  seaHalf),
            Vector3D(-seaHalf, 2,  seaHalf)
        };

        for (int i = 0; i < 4; i++) {
            Vector3D d = corners[(i + 1) % 4] - corners[i];
            Vector3D windVel = d * 0.1f;

            niebla->addForceGenerator(std::make_shared<WindGenerator>(windVel, corners[i], seaHalf, 1.0f));
        }

        boat = new Boat(Vector3D(40, 2, 40), Vector3D(0, 0, 0), 2.0f, Vector3D(0, 0, 0), 20.0f, 0.1f, 0.0f, Vector4(0, 0, 0, 1));
        niebla->addBoat(boat);
        systems.push_back(std::move(niebla));

        auto mar = std::make_unique<ParticleSystem>(5, maxDist);
        mar->addForceGenerator(std::make_shared<GravityGenerator>(Vector3D(-0.25f, 0, -0.25f)));
        mar->addBoat(boat);
		systems.push_back(std::move(mar));
    }

    void update(double dt) override {
        time += dt;

        for (auto& s : systems)
            s->update(dt);

        // Mueve el mar
        for (int x = 0; x < seaWidth; x++) {
            for (int z = 0; z < seaWidth; z++) {
                float distance = (x + z);
                float offset = std::sin(time * waveSpeed + distance * waveFrequency) * waveMaxHeight;
                seaTr[x * seaWidth + z].p.y = offset;
            }
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        switch (key) {
        case 'j':
            boat->rotateBoat(ROTATION_ANGLE);
            break;
        case 'l':
            boat->rotateBoat(-ROTATION_ANGLE);
            break;
        default:
            break;
        }
    }

    void cleanup() override {
        systems.clear();

        for (auto* item : seaItems) {
            item->release();
        }
        seaItems.clear();
        seaTr.clear();

		delete boat;
		boat = nullptr;
    }

private:
    std::vector<std::unique_ptr<ParticleSystem>> systems;

    int   seaWidth = 50;
    float cellSize = 2.0f;
    float waveSpeed = 0.75;
    float waveFrequency = 0.5f;
    float waveMaxHeight = 0.5f;
    float time = 0.0f;
	const float ROTATION_ANGLE = physx::PxPi / 8.0f;    // 22.5 grados

    std::vector<physx::PxTransform> seaTr;   // un transform por celda
    std::vector<RenderItem*> seaItems;       // un RenderItem por celda

    Boat* boat = nullptr;
};