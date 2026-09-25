#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Particle.h"

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        //// Origen del eje de coordenadas
        //physx::PxShape* origen = CreateShape(physx::PxSphereGeometry(1.0f));
        //m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        //m_renderItemOrigen = new RenderItem(origen, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        //Vector3D u(5.0f, 0.0f, 0.0f);
        //Vector3D v(0.0f, 5.0f, 0.0f);
        //Vector3D w(0.0f, 0.0f, 5.0f);

        //physx::PxShape* X = CreateShape(physx::PxSphereGeometry(1.0f));
        //m_transform1 = physx::PxTransform(u);
        //m_renderItemX = new RenderItem(X, &m_transform1, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        //physx::PxShape* Y = CreateShape(physx::PxSphereGeometry(1.0f));
        //m_transform2 = physx::PxTransform(v);
        //m_renderItemY = new RenderItem(Y, &m_transform2, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        //physx::PxShape* Z = CreateShape(physx::PxSphereGeometry(1.0f));
        //m_transform3 = physx::PxTransform(w);
        //m_renderItemZ = new RenderItem(Z, &m_transform3, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

        p = new Particle(Vector3D(0,0,0), Vector3D(0,0,-0.1));
    }


    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        p->integrateEuler(1);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }

    void cleanup() override {
        if (m_renderItemOrigen) { 
            m_renderItemOrigen->release(); 
            m_renderItemOrigen = nullptr;
        }
        if (m_renderItemX)  { 
            m_renderItemX->release();      
            m_renderItemX = nullptr; 
        }
        if (m_renderItemY) { 
            m_renderItemY->release();      
            m_renderItemY = nullptr;
        }
        if (m_renderItemZ) { 
            m_renderItemZ->release();      
            m_renderItemZ = nullptr; 
        }   
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transform1;
    physx::PxTransform m_transform2;
    physx::PxTransform m_transform3;

    RenderItem* m_renderItemOrigen{ nullptr };
    RenderItem* m_renderItemX{ nullptr };
    RenderItem* m_renderItemY{ nullptr };
    RenderItem* m_renderItemZ{ nullptr };

    Particle* p;
};