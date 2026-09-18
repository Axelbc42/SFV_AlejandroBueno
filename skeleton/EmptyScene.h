#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
		// Origen del eje de coordenadas
        physx::PxShape* origen = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        m_renderItem = new RenderItem(origen, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        Vector3D u(5.0f, 0.0f, 0.0f);
        Vector3D v(0.0f, 5.0f, 0.0f);
        Vector3D w(0.0f, 0.0f, 5.0f);

        physx::PxShape* X = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform1 = physx::PxTransform(u);
        m_renderItem = new RenderItem(X, &m_transform1, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        physx::PxShape* Y = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform2 = physx::PxTransform(v);
        m_renderItem = new RenderItem(Y, &m_transform2, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        physx::PxShape* Z = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transform3 = physx::PxTransform(w);
        m_renderItem = new RenderItem(Z, &m_transform3, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transform1;
    physx::PxTransform m_transform2;
    physx::PxTransform m_transform3;
    RenderItem* m_renderItem{ nullptr };
};