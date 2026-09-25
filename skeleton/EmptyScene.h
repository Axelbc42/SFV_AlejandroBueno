#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Particle.h"

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        std::vector<Vector3D> pos;
        pos.push_back(Vector3D(0.0f, 0.0f, 0.0f));
        pos.push_back(Vector3D(1.0f, 0.0f, 0.0f));
        pos.push_back(Vector3D(0.0f, 1.0f, 0.0f));
        pos.push_back(Vector3D(0.0f, 0.0f, 1.0f));

        axis_transforms.reserve(pos.size());  // <- reserva capacidad fija de antemano
        for (Vector3D p : pos) {
            physx::PxShape* X = CreateShape(physx::PxSphereGeometry(1.0f));
            axis_transforms.push_back(physx::PxTransform(p * 5));
            axis_renderItemOrigins.push_back(new RenderItem(X, &axis_transforms.back(), Vector4(p.x, p.y, p.z, 1.0f)));
        }

        p = new Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 10));
    }


    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        p->integrateVerlet(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        // Liberar los RenderItem de los ejes
        for (RenderItem* item : axis_renderItemOrigins) {
            item->release();
            item = nullptr;
        }
        axis_renderItemOrigins.clear();
        axis_transforms.clear();

        // Liberar la partícula
        if (p) {
            delete p;
            p = nullptr;
        }
    }

private:
    std::vector<physx::PxTransform> axis_transforms;
    std::vector<RenderItem*> axis_renderItemOrigins;

    Particle* p;
};