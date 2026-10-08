#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Particle.h"
#include "Projectile.h"

class SceneP12 : public Scene {
public:
    explicit SceneP12(std::string name) : Scene(std::move(name)) {}

    void init() override {
		floor = physx::PxTransform(physx::PxVec3(0, -0.5f, 0));
		floorRenderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(500.0f, 0.5f, 500.0f)), &floor, Vector4(0.4f, 0.6f, 0.4f, 1.0f));
    }

    void update(double dt) override {
        for (auto p : projectiles)
            p->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        Vector3D cameraDir;
        switch (key) {
			// Disparar bala de canon
            case '1':
                cameraDir = GetCamera()->getDir();
			    projectiles.push_back(new Projectile(GetCamera()->getEye(), cameraDir * 50, cameraDir * 250, 15, 1.0f));
                break;

			// Disparar bala de pistola
            case '2':
                cameraDir = GetCamera()->getDir();
			    projectiles.push_back(new Projectile(GetCamera()->getEye(), cameraDir * 330, cameraDir * 330, 0.008, 0.25f));
                break;
        default:
            break;
        }
    }

    void cleanup() override {
        if (floorRenderItem) { 
            floorRenderItem->release(); 
            floorRenderItem = nullptr;
        }
        for (auto p : projectiles) 
            delete p;
        projectiles.clear();
    }

private:
    std::vector<Projectile*> projectiles = std::vector<Projectile*>();

    physx::PxTransform floor;
    RenderItem* floorRenderItem = nullptr;
};