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
        std::vector<Vector3D> pos;
        pos.push_back(Vector3D(0.0f, 0.0f, 0.0f));
        pos.push_back(Vector3D(1.0f, 0.0f, 0.0f));
        pos.push_back(Vector3D(0.0f, 1.0f, 0.0f));
        pos.push_back(Vector3D(0.0f, 0.0f, 1.0f));

        axis_transforms.reserve(pos.size());
        for (Vector3D p : pos) {
            physx::PxShape* X = CreateShape(physx::PxSphereGeometry(1.0f));
            axis_transforms.push_back(physx::PxTransform(p * 5));
            axis_renderItemOrigins.push_back(new RenderItem(X, &axis_transforms.back(), Vector4(p.x, p.y, p.z, 1.0f)));
        }
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
			    projectiles.push_back(new Projectile(GetCamera()->getEye(), cameraDir * 50, cameraDir * 250, 15));
                contadorProyectiles++;
                break;

			// Disparar bala de pistola
            case '2':
                cameraDir = GetCamera()->getDir();
			    projectiles.push_back(new Projectile(GetCamera()->getEye(), cameraDir * 330, cameraDir * 330, 0.008));
                contadorProyectiles++;
                break;
        default:
            break;
        }
    }

    void cleanup() override {
        // Liberar los RenderItem de los ejes
        for (RenderItem* item : axis_renderItemOrigins) {
            item->release();
            item = nullptr;
        }
        axis_renderItemOrigins.clear();
        axis_transforms.clear();
    }

private:
	int contadorProyectiles = 0;

    std::vector<physx::PxTransform> axis_transforms;
    std::vector<RenderItem*> axis_renderItemOrigins;

    std::vector<Projectile*> projectiles = std::vector<Projectile*>();
};